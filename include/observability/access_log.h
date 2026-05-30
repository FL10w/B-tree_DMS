#pragma once

#include <chrono>
#include <filesystem>
#include <string>

namespace fs = std::filesystem;

namespace app {

struct AccessLogEntry {
    std::string query;
    std::string clientId;
    std::string handlerId;
    std::chrono::system_clock::time_point startedAt;
    std::chrono::system_clock::time_point finishedAt;
    std::string status;
    int code = 0;
    std::string message;
};

class AccessLogger {
public:
    explicit AccessLogger(fs::path logPath);

    void append(const AccessLogEntry& entry);
    const fs::path& path() const;

private:
    fs::path logPath_;
};

}  // namespace app
