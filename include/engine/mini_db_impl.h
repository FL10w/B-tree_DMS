#pragma once

#include <filesystem>
#include <optional>
#include <set>
#include <string>
#include <vector>

#include <nlohmann/json.hpp>

#include "core/table.h"
#include "index/b_tree.h"
#include "sql/ast.h"

namespace fs = std::filesystem;

namespace app {

using json = nlohmann::json;

class MiniDbImpl {
public:
    explicit MiniDbImpl(fs::path root);

    std::string activeDatabase() const;
    json execute(const Statement& statement);

private:
    fs::path root_;
    std::string currentDatabase_;

    fs::path databasePath(const std::string& database) const;
    fs::path schemaPath(const std::string& database, const std::string& table) const;
    fs::path rowsPath(const std::string& database, const std::string& table) const;
    fs::path indexPath(const std::string& database, const std::string& table, const std::string& column) const;
    fs::path indexPagesPath(const std::string& database, const std::string& table, const std::string& column) const;

    std::string resolveDatabase(const TableRef& ref) const;
    void ensureDatabaseExists(const std::string& database) const;
    void ensureTableExists(const std::string& database, const std::string& table) const;

    TableSchema loadSchema(const std::string& database, const std::string& table) const;
    TableData loadRows(const std::string& database, const std::string& table) const;
    void saveSchema(const std::string& database, const TableSchema& schema) const;
    void saveRows(const std::string& database, const std::string& table, const TableData& data) const;

    json createDatabase(const std::string& name);
    json dropDatabase(const std::string& name);
    json useDatabase(const std::string& name);
    json createTable(const Statement& statement);
    json dropTable(const TableRef& ref);

    Row makeRow(const TableSchema& schema,
                const std::vector<std::string>& columns,
                const std::vector<Value>& values,
                long long id) const;
    static Value initialValueForColumn(const Column& column);

    json insertRows(const Statement& statement);
    json updateRows(const Statement& statement);
    json deleteRows(const Statement& statement);
    json selectRows(const Statement& statement);
    json selectAggregates(const TableSchema& schema,
                          const TableData& data,
                          const Statement& statement,
                          const std::optional<std::set<long long>>& candidates) const;

    static bool isCandidate(long long rowId, const std::optional<std::set<long long>>& candidates);
    static bool hasAggregateItems(const std::vector<SelectItem>& items);
    static std::string aggregateOutputName(const SelectItem& item);

    template <typename Key>
    BTree<Key> openIndexTree(const std::string& database,
                             const TableSchema& schema,
                             const Column& column,
                             bool reset) const;

    void rebuildIndexes(const std::string& database, const TableSchema& schema, const TableData& data) const;
    void insertRowIndexes(const std::string& database, const TableSchema& schema, const Row& row) const;
    void removeRowIndexes(const std::string& database, const TableSchema& schema, const Row& row) const;

    std::optional<std::set<long long>> indexedCandidates(const std::string& database,
                                                         const TableSchema& schema,
                                                         const Expr* expr) const;
    std::optional<std::set<long long>> indexedCandidatesForSimpleExpr(const std::string& database,
                                                                      const TableSchema& schema,
                                                                      const Expr* expr) const;
    bool literalFits(const Column& column, const Value& value) const;
    static std::string flipOperator(const std::string& op);
    std::optional<std::set<long long>> compareByIndex(const std::string& database,
                                                      const TableSchema& schema,
                                                      const Column& column,
                                                      const std::string& op,
                                                      const Value& literal) const;
    std::optional<std::set<long long>> rangeByIndex(const std::string& database,
                                                    const TableSchema& schema,
                                                    const Column& column,
                                                    const std::optional<Value>& low,
                                                    const std::optional<Value>& high,
                                                    bool includeLow,
                                                    bool includeHigh) const;
};

}  // namespace app
