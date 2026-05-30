#include "engine/mini_db.h"

#include "engine/mini_db_impl.h"

#include <algorithm>
#include <filesystem>
#include <iterator>
#include <map>
#include <optional>
#include <set>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

#include "common/string_utils.h"
#include "core/condition.h"
#include "core/constraints.h"
#include "core/value_ops.h"
#include "storage/file_io.h"
#include "storage/json_codec.h"

namespace app {

MiniDbImpl::MiniDbImpl(fs::path root) : root_(std::move(root)) {
    fs::create_directories(root_);
}

std::string MiniDbImpl::activeDatabase() const {
    return currentDatabase_.empty() ? "-" : currentDatabase_;
}

json MiniDbImpl::execute(const Statement& statement) {
    switch (statement.kind) {
        case StatementKind::CreateDatabase:
            return createDatabase(statement.databaseName);
        case StatementKind::DropDatabase:
            return dropDatabase(statement.databaseName);
        case StatementKind::UseDatabase:
            return useDatabase(statement.databaseName);
        case StatementKind::CreateTable:
            return createTable(statement);
        case StatementKind::DropTable:
            return dropTable(statement.table);
        case StatementKind::Insert:
            return insertRows(statement);
        case StatementKind::Update:
            return updateRows(statement);
        case StatementKind::DeleteRows:
            return deleteRows(statement);
        case StatementKind::SelectRows:
            return selectRows(statement);
        case StatementKind::Empty:
            return {{"status", "empty"}};
    }
    return {{"status", "unknown"}};
}

fs::path MiniDbImpl::databasePath(const std::string& database) const {
    return root_ / database;
}

fs::path MiniDbImpl::schemaPath(const std::string& database, const std::string& table) const {
    return databasePath(database) / (table + ".schema.json");
}

fs::path MiniDbImpl::rowsPath(const std::string& database, const std::string& table) const {
    return databasePath(database) / (table + ".rows.json");
}

fs::path MiniDbImpl::indexPath(const std::string& database,
                               const std::string& table,
                               const std::string& column) const {
    return databasePath(database) / (table + "." + column + ".idx.json");
}

fs::path MiniDbImpl::indexPagesPath(const std::string& database,
                                    const std::string& table,
                                    const std::string& column) const {
    return BTree<long long>::pagesPathFor(indexPath(database, table, column));
}

std::string MiniDbImpl::resolveDatabase(const TableRef& ref) const {
    if (ref.database.has_value()) {
        return *ref.database;
    }
    if (currentDatabase_.empty()) {
        throw std::runtime_error("no active database; use USE database_name first");
    }
    return currentDatabase_;
}

void MiniDbImpl::ensureDatabaseExists(const std::string& database) const {
    if (!fs::exists(databasePath(database))) {
        throw std::runtime_error("database does not exist: " + database);
    }
}

void MiniDbImpl::ensureTableExists(const std::string& database, const std::string& table) const {
    ensureDatabaseExists(database);
    if (!fs::exists(schemaPath(database, table)) || !fs::exists(rowsPath(database, table))) {
        throw std::runtime_error("table does not exist: " + table);
    }
}

TableSchema MiniDbImpl::loadSchema(const std::string& database, const std::string& table) const {
    ensureTableExists(database, table);
    auto in = openInput(schemaPath(database, table));
    json data;
    in >> data;
    return schemaFromJson(data);
}

TableData MiniDbImpl::loadRows(const std::string& database, const std::string& table) const {
    ensureTableExists(database, table);
    auto in = openInput(rowsPath(database, table));
    json data;
    in >> data;
    return rowsFromJson(data);
}

void MiniDbImpl::saveSchema(const std::string& database, const TableSchema& schema) const {
    auto out = openOutput(schemaPath(database, schema.name));
    out << schemaToJson(schema).dump(2);
}

void MiniDbImpl::saveRows(const std::string& database, const std::string& table, const TableData& data) const {
    auto out = openOutput(rowsPath(database, table));
    out << rowsToJson(data).dump(2);
}

json MiniDbImpl::createDatabase(const std::string& name) {
    checkIdentifier(name, "database name");
    const auto path = databasePath(name);
    if (fs::exists(path)) {
        throw std::runtime_error("database already exists: " + name);
    }
    fs::create_directories(path);
    return {{"status", "ok"}, {"message", "database created"}, {"database", name}};
}

json MiniDbImpl::dropDatabase(const std::string& name) {
    checkIdentifier(name, "database name");
    const auto path = databasePath(name);
    if (!fs::exists(path)) {
        throw std::runtime_error("database does not exist: " + name);
    }
    fs::remove_all(path);
    if (currentDatabase_ == name) {
        currentDatabase_.clear();
    }
    return {{"status", "ok"}, {"message", "database dropped"}, {"database", name}};
}

json MiniDbImpl::useDatabase(const std::string& name) {
    checkIdentifier(name, "database name");
    ensureDatabaseExists(name);
    currentDatabase_ = name;
    return {{"status", "ok"}, {"message", "database selected"}, {"database", name}};
}

json MiniDbImpl::createTable(const Statement& statement) {
    const auto database = resolveDatabase(statement.table);
    ensureDatabaseExists(database);
    checkIdentifier(statement.table.table, "table name");
    if (statement.columnDefs.empty()) {
        throw std::runtime_error("table must contain at least one column");
    }
    if (fs::exists(schemaPath(database, statement.table.table))) {
        throw std::runtime_error("table already exists: " + statement.table.table);
    }

    TableSchema schema;
    schema.name = statement.table.table;
    std::set<std::string> names;
    for (const auto& def : statement.columnDefs) {
        checkIdentifier(def.name, "column name");
        if (!names.insert(def.name).second) {
            throw std::runtime_error("duplicate column: " + def.name);
        }
        Column column;
        column.name = def.name;
        column.type = def.type;
        column.notNull = def.notNull || def.indexed;
        column.indexed = def.indexed;
        if (def.hasDefault) {
            ensureValueFitsColumn(def.defaultValue, column.type, column.name, column.notNull);
            column.defaultValue = def.defaultValue;
        }
        schema.columns.push_back(column);
    }

    saveSchema(database, schema);
    saveRows(database, schema.name, TableData{});
    rebuildIndexes(database, schema, TableData{});
    return {{"status", "ok"}, {"message", "table created"}, {"table", schema.name}};
}

json MiniDbImpl::dropTable(const TableRef& ref) {
    const auto database = resolveDatabase(ref);
    ensureTableExists(database, ref.table);
    fs::remove(schemaPath(database, ref.table));
    fs::remove(rowsPath(database, ref.table));
    for (const auto& entry : fs::directory_iterator(databasePath(database))) {
        const std::string filename = entry.path().filename().string();
        const std::string prefix = ref.table + ".";
        if (filename.rfind(prefix, 0) == 0 && filename.find(".idx.") != std::string::npos) {
            if (entry.is_directory()) {
                fs::remove_all(entry.path());
            } else {
                fs::remove(entry.path());
            }
        }
    }
    return {{"status", "ok"}, {"message", "table dropped"}, {"table", ref.table}};
}

Row MiniDbImpl::makeRow(const TableSchema& schema,
                        const std::vector<std::string>& columns,
                        const std::vector<Value>& values,
                        long long id) const {
    if (columns.size() != values.size()) {
        throw std::runtime_error("INSERT column count does not match value count");
    }

    Row row;
    row.id = id;
    std::set<std::string> seen;
    for (const auto& column : schema.columns) {
        row.values[column.name] = initialValueForColumn(column);
    }
    for (size_t i = 0; i < columns.size(); ++i) {
        const auto& columnName = columns[i];
        const auto& column = schema.column(columnName);
        if (!seen.insert(columnName).second) {
            throw std::runtime_error("duplicate INSERT column: " + columnName);
        }
        ensureValueFitsColumn(values[i], column.type, column.name, column.notNull);
        row.values[column.name] = values[i];
    }
    validateRow(schema, row);
    return row;
}

Value MiniDbImpl::initialValueForColumn(const Column& column) {
    if (column.defaultValue.has_value()) {
        return *column.defaultValue;
    }
    return Value::null();
}

json MiniDbImpl::insertRows(const Statement& statement) {
    const auto database = resolveDatabase(statement.table);
    auto schema = loadSchema(database, statement.table.table);
    auto data = loadRows(database, statement.table.table);
    std::vector<Row> insertedRows;

    for (const auto& rawValues : statement.insertRows) {
        auto row = makeRow(schema, statement.insertColumns, rawValues, data.nextId++);
        insertedRows.push_back(row);
        data.rows.push_back(std::move(row));
    }
    validateAllRows(schema, data);
    saveRows(database, schema.name, data);
    for (const auto& row : insertedRows) {
        insertRowIndexes(database, schema, row);
    }
    return {{"status", "ok"}, {"message", "rows inserted"}, {"count", statement.insertRows.size()}};
}

json MiniDbImpl::updateRows(const Statement& statement) {
    const auto database = resolveDatabase(statement.table);
    auto schema = loadSchema(database, statement.table.table);
    auto data = loadRows(database, statement.table.table);
    const auto candidates = indexedCandidates(database, schema, statement.where.get());
    size_t changed = 0;
    std::vector<std::pair<Row, Row>> changedRows;

    for (auto& row : data.rows) {
        if (row.deleted || !isCandidate(row.id, candidates) || !evaluateExpr(statement.where.get(), row)) {
            continue;
        }
        Row oldRow = row;
        for (const auto& assignment : statement.assignments) {
            const auto& column = schema.column(assignment.column);
            ensureValueFitsColumn(assignment.value, column.type, column.name, column.notNull);
            row.values[column.name] = assignment.value;
        }
        changedRows.push_back({std::move(oldRow), row});
        ++changed;
    }

    validateAllRows(schema, data);
    saveRows(database, schema.name, data);
    for (const auto& [oldRow, newRow] : changedRows) {
        removeRowIndexes(database, schema, oldRow);
    }
    for (const auto& change : changedRows) {
        insertRowIndexes(database, schema, change.second);
    }
    return {{"status", "ok"}, {"message", "rows updated"}, {"count", changed}};
}

json MiniDbImpl::deleteRows(const Statement& statement) {
    const auto database = resolveDatabase(statement.table);
    auto schema = loadSchema(database, statement.table.table);
    auto data = loadRows(database, statement.table.table);
    const auto candidates = indexedCandidates(database, schema, statement.where.get());
    size_t changed = 0;
    std::vector<Row> removedRows;

    for (auto& row : data.rows) {
        if (!row.deleted && isCandidate(row.id, candidates) && evaluateExpr(statement.where.get(), row)) {
            removedRows.push_back(row);
            row.deleted = true;
            ++changed;
        }
    }

    saveRows(database, schema.name, data);
    for (const auto& row : removedRows) {
        removeRowIndexes(database, schema, row);
    }
    return {{"status", "ok"}, {"message", "rows deleted"}, {"count", changed}};
}

json MiniDbImpl::selectRows(const Statement& statement) {
    const auto database = resolveDatabase(statement.table);
    auto schema = loadSchema(database, statement.table.table);
    auto data = loadRows(database, statement.table.table);
    const auto candidates = indexedCandidates(database, schema, statement.where.get());

    if (hasAggregateItems(statement.selectItems)) {
        return selectAggregates(schema, data, statement, candidates);
    }

    json result = json::array();
    for (const auto& row : data.rows) {
        if (row.deleted || !isCandidate(row.id, candidates) || !evaluateExpr(statement.where.get(), row)) {
            continue;
        }
        json item = json::object();
        if (statement.selectItems.size() == 1 && statement.selectItems[0].star) {
            for (const auto& column : schema.columns) {
                item[column.name] = valueToJson(row.values.at(column.name));
            }
        } else {
            for (const auto& projection : statement.selectItems) {
                const auto& column = schema.column(projection.column);
                const auto outputName = projection.alias.empty() ? column.name : projection.alias;
                item[outputName] = valueToJson(row.values.at(column.name));
            }
        }
        result.push_back(std::move(item));
    }
    return result;
}

json MiniDbImpl::selectAggregates(const TableSchema& schema,
                                  const TableData& data,
                                  const Statement& statement,
                                  const std::optional<std::set<long long>>& candidates) const {
    json item = json::object();
    for (const auto& projection : statement.selectItems) {
        if (projection.aggregate == AggregateKind::None) {
            throw std::runtime_error("aggregate SELECT cannot mix columns and aggregate functions");
        }
        if (projection.aggregateStar && projection.aggregate != AggregateKind::Count) {
            throw std::runtime_error("only COUNT supports * argument");
        }

        long long count = 0;
        long long sum = 0;
        if (!projection.aggregateStar) {
            const auto& column = schema.column(projection.column);
            if ((projection.aggregate == AggregateKind::Sum || projection.aggregate == AggregateKind::Avg) &&
                column.type != FieldType::Int) {
                throw std::runtime_error("SUM and AVG require int column: " + column.name);
            }
        }

        for (const auto& row : data.rows) {
            if (row.deleted || !isCandidate(row.id, candidates) || !evaluateExpr(statement.where.get(), row)) {
                continue;
            }
            if (projection.aggregateStar) {
                ++count;
                continue;
            }
            const auto& value = row.values.at(projection.column);
            if (value.kind == ValueKind::Null) {
                continue;
            }
            ++count;
            if (projection.aggregate == AggregateKind::Sum || projection.aggregate == AggregateKind::Avg) {
                sum += value.intValue;
            }
        }

        const auto outputName = aggregateOutputName(projection);
        switch (projection.aggregate) {
            case AggregateKind::Count:
                item[outputName] = count;
                break;
            case AggregateKind::Sum:
                item[outputName] = sum;
                break;
            case AggregateKind::Avg:
                item[outputName] = count == 0 ? json(nullptr) : json(static_cast<double>(sum) / count);
                break;
            case AggregateKind::None:
                break;
        }
    }

    json result = json::array();
    result.push_back(std::move(item));
    return result;
}

bool MiniDbImpl::isCandidate(long long rowId, const std::optional<std::set<long long>>& candidates) {
    return !candidates.has_value() || candidates->count(rowId) > 0;
}

bool MiniDbImpl::hasAggregateItems(const std::vector<SelectItem>& items) {
    return std::any_of(items.begin(), items.end(), [](const auto& item) {
        return item.aggregate != AggregateKind::None;
    });
}

std::string MiniDbImpl::aggregateOutputName(const SelectItem& item) {
    if (!item.alias.empty()) {
        return item.alias;
    }
    switch (item.aggregate) {
        case AggregateKind::Count:
            return item.aggregateStar ? "count" : "count_" + item.column;
        case AggregateKind::Sum:
            return "sum_" + item.column;
        case AggregateKind::Avg:
            return "avg_" + item.column;
        case AggregateKind::None:
            return item.column;
    }
    return item.column;
}

template <typename Key>
BTree<Key> MiniDbImpl::openIndexTree(const std::string& database,
                                     const TableSchema& schema,
                                     const Column& column,
                                     bool reset) const {
    const std::string keyType = column.type == FieldType::Int ? "int" : "string";
    return BTree<Key>(indexPath(database, schema.name, column.name), keyType, 3, reset);
}

void MiniDbImpl::rebuildIndexes(const std::string& database, const TableSchema& schema, const TableData& data) const {
    for (const auto& column : schema.columns) {
        const auto path = indexPath(database, schema.name, column.name);
        if (!column.indexed) {
            if (fs::exists(path)) {
                fs::remove(path);
            }
            const auto pagesPath = indexPagesPath(database, schema.name, column.name);
            if (fs::exists(pagesPath)) {
                fs::remove_all(pagesPath);
            }
            continue;
        }
        if (column.type == FieldType::Int) {
            auto tree = openIndexTree<long long>(database, schema, column, true);
            for (const auto& row : data.rows) {
                if (!row.deleted) {
                    tree.insert(row.values.at(column.name).intValue, row.id);
                }
            }
        } else {
            auto tree = openIndexTree<std::string>(database, schema, column, true);
            for (const auto& row : data.rows) {
                if (!row.deleted) {
                    tree.insert(row.values.at(column.name).asString(), row.id);
                }
            }
        }
    }
}

void MiniDbImpl::insertRowIndexes(const std::string& database, const TableSchema& schema, const Row& row) const {
    for (const auto& column : schema.columns) {
        if (!column.indexed) {
            continue;
        }
        const auto& value = row.values.at(column.name);
        bool inserted = false;
        if (column.type == FieldType::Int) {
            auto tree = openIndexTree<long long>(database, schema, column, false);
            inserted = tree.insert(value.intValue, row.id);
        } else {
            auto tree = openIndexTree<std::string>(database, schema, column, false);
            inserted = tree.insert(value.asString(), row.id);
        }
        if (!inserted) {
            throw std::runtime_error("index already contains key for column: " + column.name);
        }
    }
}

void MiniDbImpl::removeRowIndexes(const std::string& database, const TableSchema& schema, const Row& row) const {
    for (const auto& column : schema.columns) {
        if (!column.indexed) {
            continue;
        }
        const auto& value = row.values.at(column.name);
        bool removed = false;
        if (column.type == FieldType::Int) {
            auto tree = openIndexTree<long long>(database, schema, column, false);
            removed = tree.remove(value.intValue);
        } else {
            auto tree = openIndexTree<std::string>(database, schema, column, false);
            removed = tree.remove(value.asString());
        }
        if (!removed) {
            throw std::runtime_error("index does not contain key for column: " + column.name);
        }
    }
}

std::optional<std::set<long long>> MiniDbImpl::indexedCandidates(const std::string& database,
                                                                 const TableSchema& schema,
                                                                 const Expr* expr) const {
    if (!expr) {
        return std::nullopt;
    }
    if (expr->kind == ExprKind::And) {
        auto left = indexedCandidates(database, schema, expr->lhs.get());
        auto right = indexedCandidates(database, schema, expr->rhs.get());
        if (left.has_value() && right.has_value()) {
            std::set<long long> both;
            std::set_intersection(left->begin(), left->end(), right->begin(), right->end(),
                                  std::inserter(both, both.begin()));
            return both;
        }
        return left.has_value() ? left : right;
    }
    if (expr->kind == ExprKind::Or) {
        auto left = indexedCandidates(database, schema, expr->lhs.get());
        auto right = indexedCandidates(database, schema, expr->rhs.get());
        if (!left.has_value() || !right.has_value()) {
            return std::nullopt;
        }
        left->insert(right->begin(), right->end());
        return left;
    }
    return indexedCandidatesForSimpleExpr(database, schema, expr);
}

std::optional<std::set<long long>> MiniDbImpl::indexedCandidatesForSimpleExpr(const std::string& database,
                                                                              const TableSchema& schema,
                                                                              const Expr* expr) const {
    if (expr->kind == ExprKind::Between) {
        if (!expr->left.column || expr->right.column || expr->high.column) {
            return std::nullopt;
        }
        const auto& column = schema.column(expr->left.columnName);
        if (!column.indexed || !literalFits(column, expr->right.literal) || !literalFits(column, expr->high.literal)) {
            return std::nullopt;
        }
        return rangeByIndex(database, schema, column, expr->right.literal, expr->high.literal, true, true);
    }
    if (expr->kind != ExprKind::Compare) {
        return std::nullopt;
    }

    bool reversed = false;
    std::string columnName;
    Value literal;
    if (expr->left.column && !expr->right.column) {
        columnName = expr->left.columnName;
        literal = expr->right.literal;
    } else if (!expr->left.column && expr->right.column) {
        columnName = expr->right.columnName;
        literal = expr->left.literal;
        reversed = true;
    } else {
        return std::nullopt;
    }

    const auto& column = schema.column(columnName);
    if (!column.indexed || !literalFits(column, literal)) {
        return std::nullopt;
    }
    const auto op = reversed ? flipOperator(expr->op) : expr->op;
    if (op == "!=") {
        return std::nullopt;
    }
    return compareByIndex(database, schema, column, op, literal);
}

bool MiniDbImpl::literalFits(const Column& column, const Value& value) const {
    if (value.kind == ValueKind::Null) {
        return false;
    }
    return (column.type == FieldType::Int && value.kind == ValueKind::Int) ||
           (column.type == FieldType::String && value.kind == ValueKind::String);
}

std::string MiniDbImpl::flipOperator(const std::string& op) {
    if (op == "<") return ">";
    if (op == "<=") return ">=";
    if (op == ">") return "<";
    if (op == ">=") return "<=";
    return op;
}

std::optional<std::set<long long>> MiniDbImpl::compareByIndex(const std::string& database,
                                                              const TableSchema& schema,
                                                              const Column& column,
                                                              const std::string& op,
                                                              const Value& literal) const {
    if (op == "=" || op == "==") {
        std::set<long long> result;
        if (column.type == FieldType::Int) {
            const auto tree = openIndexTree<long long>(database, schema, column, false);
            const auto row = tree.find(literal.intValue);
            if (row.has_value()) {
                result.insert(*row);
            }
        } else {
            const auto tree = openIndexTree<std::string>(database, schema, column, false);
            const auto row = tree.find(literal.asString());
            if (row.has_value()) {
                result.insert(*row);
            }
        }
        return result;
    }

    std::optional<Value> low;
    std::optional<Value> high;
    bool includeLow = false;
    bool includeHigh = false;
    if (op == ">") {
        low = literal;
    } else if (op == ">=") {
        low = literal;
        includeLow = true;
    } else if (op == "<") {
        high = literal;
    } else if (op == "<=") {
        high = literal;
        includeHigh = true;
    } else {
        return std::nullopt;
    }
    return rangeByIndex(database, schema, column, low, high, includeLow, includeHigh);
}

std::optional<std::set<long long>> MiniDbImpl::rangeByIndex(const std::string& database,
                                                            const TableSchema& schema,
                                                            const Column& column,
                                                            const std::optional<Value>& low,
                                                            const std::optional<Value>& high,
                                                            bool includeLow,
                                                            bool includeHigh) const {
    std::set<long long> result;
    if (column.type == FieldType::Int) {
        std::optional<long long> lowKey;
        std::optional<long long> highKey;
        if (low.has_value()) lowKey = low->intValue;
        if (high.has_value()) highKey = high->intValue;
        const auto tree = openIndexTree<long long>(database, schema, column, false);
        for (const auto row : tree.range(lowKey, highKey, includeLow, includeHigh)) {
            result.insert(row);
        }
    } else {
        std::optional<std::string> lowKey;
        std::optional<std::string> highKey;
        if (low.has_value()) lowKey = low->asString();
        if (high.has_value()) highKey = high->asString();
        const auto tree = openIndexTree<std::string>(database, schema, column, false);
        for (const auto row : tree.range(lowKey, highKey, includeLow, includeHigh)) {
            result.insert(row);
        }
    }
    return result;
}

MiniDb::MiniDb(fs::path root) : impl_(std::make_unique<MiniDbImpl>(std::move(root))) {}

MiniDb::~MiniDb() = default;
MiniDb::MiniDb(MiniDb&&) noexcept = default;
MiniDb& MiniDb::operator=(MiniDb&&) noexcept = default;

std::string MiniDb::activeDatabase() const {
    return impl_->activeDatabase();
}

json MiniDb::execute(const Statement& statement) {
    return impl_->execute(statement);
}

}  // namespace app
