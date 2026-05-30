#include "core/table.h"

#include <stdexcept>

namespace app {

int TableSchema::indexOf(const std::string& columnName) const {
    for (size_t i = 0; i < columns.size(); ++i) {
        if (columns[i].name == columnName) {
            return static_cast<int>(i);
        }
    }
    return -1;
}

const Column& TableSchema::column(const std::string& columnName) const {
    const int idx = indexOf(columnName);
    if (idx < 0) {
        throw std::runtime_error("unknown column: " + columnName);
    }
    return columns[static_cast<size_t>(idx)];
}

}  // namespace app
