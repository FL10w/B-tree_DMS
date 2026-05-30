#pragma once

#include <string>

#include <nlohmann/json.hpp>

#include "sql/ast.h"

namespace app {

using json = nlohmann::json;

std::string fieldTypeName(FieldType type);
FieldType parseFieldType(const std::string& name);
json valueToJson(const Value& value);
Value valueFromJson(const json& item);
int compareValues(const Value& left, const Value& right);
bool compareByOperator(const Value& left, const std::string& op, const Value& right);

}  // namespace app
