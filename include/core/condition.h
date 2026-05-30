#pragma once

#include "core/table.h"

struct Expr;
struct Operand;

namespace app {

Value resolveOperand(const Operand& operand, const Row& row);
bool evaluateExpr(const Expr* expr, const Row& row);

}  // namespace app
