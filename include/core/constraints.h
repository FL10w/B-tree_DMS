#pragma once

#include <string>

#include "core/table.h"

namespace app {

void ensureValueFitsColumn(const Value& value, FieldType type, const std::string& columnName, bool notNull);
void validateRow(const TableSchema& schema, const Row& row);
void validateAllRows(const TableSchema& schema, const TableData& data);

}  // namespace app
