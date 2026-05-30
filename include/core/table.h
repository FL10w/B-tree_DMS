#pragma once

#include <map>
#include <optional>
#include <string>
#include <vector>

#include "sql/ast.h"

namespace app {

struct Column {
    std::string name;
    FieldType type = FieldType::String;
    bool notNull = false;
    bool indexed = false;
    std::optional<Value> defaultValue;
};

struct TableSchema {
    std::string name;
    std::vector<Column> columns;

    int indexOf(const std::string& columnName) const;
    const Column& column(const std::string& columnName) const;
};

struct Row {
    long long id = 0;
    bool deleted = false;
    std::map<std::string, Value> values;
};

struct TableData {
    long long nextId = 1;
    std::vector<Row> rows;
};

}  // namespace app
