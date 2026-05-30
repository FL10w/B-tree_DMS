#include "sql/sql_splitter.h"

#include "common/string_utils.h"

namespace app {

std::vector<std::string> splitSqlStatements(const std::string& source) {
    std::vector<std::string> result;
    std::string current;
    bool inString = false;
    char quote = '\0';
    bool escaped = false;  // Флаг экранирования. чтобы \' не считался концом строки.

    for (char ch : source) {
        current.push_back(ch);
        if (inString) {
            if (escaped) {
                escaped = false;
            } else if (ch == '\\') {
                escaped = true;
            } else if (ch == quote) {
                inString = false;
            }
            continue;
        }
        if (ch == '\'' || ch == '"') {
            inString = true;
            quote = ch;
            continue;
        }
        if (ch == ';') {
            result.push_back(trim(current));
            current.clear();
        }
    }
    const auto tail = trim(current);
    if (!tail.empty()) {
        result.push_back(tail);
    }
    return result;
}

}  // namespace app
