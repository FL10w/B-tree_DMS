#pragma once

#include <string>

namespace app {

std::string toUpper(std::string text);
std::string trim(const std::string& value);
void checkIdentifier(const std::string& name, const std::string& label);

}  // namespace app
