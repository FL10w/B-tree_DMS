#pragma once

#include <nlohmann/json.hpp>

#include "core/table.h"

namespace app {

using json = nlohmann::json;

json schemaToJson(const TableSchema& schema);
TableSchema schemaFromJson(const json& data);

json rowsToJson(const TableData& data);
TableData rowsFromJson(const json& data);

}  // namespace app
