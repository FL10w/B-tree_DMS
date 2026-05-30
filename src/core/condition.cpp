#include "core/condition.h"

#include <regex>
#include <stdexcept>

#include "core/value_ops.h"
#include "sql/ast.h"

namespace app {

Value resolveOperand(const Operand& operand, const Row& row) {
    if (!operand.column) {
        return operand.literal;
    }
    const auto it = row.values.find(operand.columnName);
    if (it == row.values.end()) {
        throw std::runtime_error("unknown column in condition: " + operand.columnName);
    }
    return it->second;
}

bool evaluateExpr(const Expr* expr, const Row& row) {
    if (!expr) {
        return true;
    }
    switch (expr->kind) {
        case ExprKind::And:
            return evaluateExpr(expr->lhs.get(), row) && evaluateExpr(expr->rhs.get(), row);
        case ExprKind::Or:
            return evaluateExpr(expr->lhs.get(), row) || evaluateExpr(expr->rhs.get(), row);
        case ExprKind::Compare: {
            return compareByOperator(resolveOperand(expr->left, row), expr->op, resolveOperand(expr->right, row));
        }
        case ExprKind::Between: {
            const Value value = resolveOperand(expr->left, row);
            const Value low = resolveOperand(expr->right, row);
            const Value high = resolveOperand(expr->high, row);
            if (value.kind == ValueKind::Null || low.kind == ValueKind::Null || high.kind == ValueKind::Null) {
                return false;
            }
            return compareValues(value, low) >= 0 && compareValues(value, high) <= 0;
        }
        case ExprKind::Like: {
            const Value value = resolveOperand(expr->left, row);
            const Value pattern = resolveOperand(expr->right, row);
            if (value.kind != ValueKind::String || pattern.kind != ValueKind::String) {
                return false;
            }
            return std::regex_match(value.asString(), std::regex(pattern.asString()));
        }
    }
    return false;
}

}  // namespace app
