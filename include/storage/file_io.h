#pragma once

#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

namespace app {

std::ifstream openInput(const fs::path& path);
std::ofstream openOutput(const fs::path& path);

}  // namespace app
