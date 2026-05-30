#pragma once

#include <filesystem>
#include <memory>
#include <string>

#include <nlohmann/json.hpp>

#include "sql/ast.h"

namespace fs = std::filesystem;

namespace app {

using json = nlohmann::json;

class MiniDbImpl;

class MiniDb {
public:
    explicit MiniDb(fs::path root);
    ~MiniDb();

    MiniDb(MiniDb&&) noexcept;
    MiniDb& operator=(MiniDb&&) noexcept;

    MiniDb(const MiniDb&) = delete;
    MiniDb& operator=(const MiniDb&) = delete;

    std::string activeDatabase() const;
    json execute(const Statement& statement);

private:
    std::unique_ptr<MiniDbImpl> impl_;
};

}  // namespace app
