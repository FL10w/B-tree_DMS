#include "core/value_ops.h"

#include <stdexcept>

#include "common/string_utils.h"

namespace app {

std::string fieldTypeName(FieldType type) {
    return type == FieldType::Int ? "int" : "string";
}

FieldType parseFieldType(const std::string& name) {
    const auto upper = toUpper(name);
    if (upper == "INT") {
        return FieldType::Int;
    }
    if (upper == "STRING") {
        return FieldType::String;
    }
    throw std::runtime_error("unknown column type: " + name);
}

json valueToJson(const Value& value) {
    switch (value.kind) {
        case ValueKind::Null:
            return nullptr;
        case ValueKind::Int:
            return value.intValue;
        case ValueKind::String:
            return value.asString();
    }
    return nullptr;
}

Value valueFromJson(const json& item) {
    if (item.is_null()) {
        return Value::null();
    }
    if (item.is_number_integer()) {
        return Value::integer(item.get<long long>());
    }
    if (item.is_string()) {
        return Value::text(item.get<std::string>());
    }
    throw std::runtime_error("stored value has unsupported JSON type");
}

int compareValues(const Value& left, const Value& right) {
    if (left.kind == ValueKind::Null || right.kind == ValueKind::Null) {
        throw std::runtime_error("NULL can only be compared with == or !=");
    }
    if (left.kind != right.kind) {
        throw std::runtime_error("values with different types cannot be ordered");
    }
    if (left.kind == ValueKind::Int) {
        if (left.intValue < right.intValue) return -1;
        if (left.intValue > right.intValue) return 1;
        return 0;
    }
    if (left.asString() < right.asString()) return -1;
    if (left.asString() > right.asString()) return 1;
    return 0;
}

bool compareByOperator(const Value& left, const std::string& op, const Value& right) {
    const bool hasNull = left.kind == ValueKind::Null || right.kind == ValueKind::Null;
    if (hasNull) {
        const bool bothNull = left.kind == ValueKind::Null && right.kind == ValueKind::Null;
        if (op == "==" || op == "=") {
            return bothNull;
        }
        if (op == "!=") {
            return !bothNull;
        }
        return false;
    }
    if (left.kind != right.kind) {
        return op == "!=";
    }
    const int cmp = compareValues(left, right);
    if (op == "==" || op == "=") return cmp == 0;
    if (op == "!=") return cmp != 0;
    if (op == "<") return cmp < 0;
    if (op == "<=") return cmp <= 0;
    if (op == ">") return cmp > 0;
    if (op == ">=") return cmp >= 0;
    throw std::runtime_error("unknown comparison operator: " + op);
}

}  // namespace app
