#pragma once

#include <string>

#include "sql/ast.h"

Statement parseSqlStatement(const std::string& source);
