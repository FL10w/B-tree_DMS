#pragma once

#include <chrono>
#include <filesystem>
#include <vector>

#include <nlohmann/json.hpp>

namespace fs = std::filesystem;

namespace app {

using json = nlohmann::json;

struct TelemetryEvent {
    std::chrono::steady_clock::time_point finishedAt;
    std::chrono::milliseconds duration{0};
    bool success = true;
};

class TelemetryCollector {
public:
    explicit TelemetryCollector(fs::path snapshotPath);

    void record(std::chrono::milliseconds duration, bool success);
    json snapshotJson() const;
    const fs::path& path() const;

private:
    fs::path snapshotPath_;
    mutable std::vector<TelemetryEvent> events_;
    size_t totalRequests_ = 0;
    size_t totalErrors_ = 0;

    void pruneLocked(std::chrono::steady_clock::time_point now) const;
    json buildSnapshotLocked(std::chrono::steady_clock::time_point now) const;
    void writeSnapshotLocked(std::chrono::steady_clock::time_point now) const;
};

}  // namespace app
