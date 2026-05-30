#include "storage/file_io.h"

#include <stdexcept>

namespace app {

std::ifstream openInput(const fs::path& path) {
    std::ifstream in(path, std::ios::binary);
    if (!in) {
        throw std::runtime_error("cannot read file: " + path.string());
    }
    return in;
}

std::ofstream openOutput(const fs::path& path) {
    const auto parent = path.parent_path();
    if (!parent.empty()) {
        fs::create_directories(parent);
    }

    std::ofstream out(path, std::ios::binary);
    if (!out) {
        throw std::runtime_error("cannot write file: " + path.string());
    }
    return out;
}

}  // namespace app
