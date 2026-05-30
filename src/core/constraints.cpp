#include "core/constraints.h"

#include <map>
#include <set>
#include <stdexcept>

namespace app {

void ensureValueFitsColumn(const Value& value, FieldType type, const std::string& columnName, bool notNull) {
    if (value.kind == ValueKind::Null) {
        if (notNull) {
            throw std::runtime_error("column " + columnName + " cannot be NULL");
        }
        return;
    }
    if (type == FieldType::Int && value.kind != ValueKind::Int) {
        throw std::runtime_error("column " + columnName + " expects int");
    }
    if (type == FieldType::String && value.kind != ValueKind::String) {
        throw std::runtime_error("column " + columnName + " expects string");
    }
}

void validateRow(const TableSchema& schema, const Row& row) {
    for (const auto& column : schema.columns) {
        const auto it = row.values.find(column.name);
        if (it == row.values.end()) {
            throw std::runtime_error("stored row misses column: " + column.name);
        }
        ensureValueFitsColumn(it->second, column.type, column.name, column.notNull);
    }
}

void validateAllRows(const TableSchema& schema, const TableData& data) {
    std::map<std::string, std::set<long long>> intUnique;
    std::map<std::string, std::set<std::string>> stringUnique;

    for (const auto& row : data.rows) {
        if (row.deleted) {
            continue;
        }
        validateRow(schema, row);
        for (const auto& column : schema.columns) {
            if (!column.indexed) {
                continue;
            }
            const auto value = row.values.at(column.name);
            if (value.kind == ValueKind::Int) {
                if (!intUnique[column.name].insert(value.intValue).second) {
                    throw std::runtime_error("INDEXED column must be unique: " + column.name);
                }
            } else if (value.kind == ValueKind::String) {
                if (!stringUnique[column.name].insert(value.asString()).second) {
                    throw std::runtime_error("INDEXED column must be unique: " + column.name);
                }
            } else {
                throw std::runtime_error("INDEXED column cannot contain NULL: " + column.name);
            }
        }
    }
}

}  // namespace app
