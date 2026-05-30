#include "common/string_utils.h"

#include <algorithm>
#include <cctype>
#include <stdexcept>

namespace app {

namespace {

bool isNameStart(char ch) {
    return std::isalpha(static_cast<unsigned char>(ch)) || ch == '_';
}

bool isNameChar(char ch) {
    return std::isalnum(static_cast<unsigned char>(ch)) || ch == '_';
}

}  // namespace

std::string toUpper(std::string text) {
    std::transform(text.begin(), text.end(), text.begin(), [](unsigned char ch) {
        return static_cast<char>(std::toupper(ch));
    });
    return text;
}

std::string trim(const std::string& value) {
    const auto first = value.find_first_not_of(" \t\r\n");
    if (first == std::string::npos) {
        return "";
    }
    const auto last = value.find_last_not_of(" \t\r\n");
    return value.substr(first, last - first + 1);
}

void checkIdentifier(const std::string& name, const std::string& label) {
    if (name.empty() || !isNameStart(name[0])) {
        throw std::runtime_error(label + " must start with a latin letter or underscore");
    }
    for (char ch : name) {
        if (!isNameChar(ch)) {
            throw std::runtime_error(label + " contains an invalid character: " + name);
        }
    }
}

}  // namespace app
