#include "sql/ast.h"

#include <stdexcept>
#include <utility>

#include "core/string_interner.h"

Value Value::null() {
    return {};
}

Value Value::integer(long long value) {
    Value result;
    result.kind = ValueKind::Int;
    result.intValue = value;
    return result;
}

Value Value::text(std::string value) {
    Value result;
    result.kind = ValueKind::String;
    result.stringRef = app::StringInterner::instance().intern(value);
    return result;
}

const std::string& Value::asString() const {
    if (kind != ValueKind::String || !stringRef) {
        throw std::runtime_error("value is not a string");
    }
    return *stringRef;
}

Operand Operand::fromColumn(std::string name) {
    Operand result;
    result.column = true;
    result.columnName = std::move(name);
    return result;
}

Operand Operand::fromLiteral(Value value) {
    Operand result;
    result.literal = std::move(value);
    return result;
}
