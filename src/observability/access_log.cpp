#include "observability/access_log.h"

#include <fstream>
#include <iomanip>
#include <sstream>
#include <stdexcept>
#include <ctime>
#include <utility>

#include <nlohmann/json.hpp>

namespace app {

namespace {

std::string formatTimestamp(std::chrono::system_clock::time_point point) {
    const auto time = std::chrono::system_clock::to_time_t(point);
    const auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(point.time_since_epoch()) %
                        std::chrono::seconds(1);

    std::tm local{};
#ifdef _WIN32
    const auto* localPtr = std::localtime(&time);
    if (localPtr) {
        local = *localPtr;
    }
#else
    localtime_r(&time, &local);
#endif

    std::ostringstream out;
    out << std::put_time(&local, "%Y-%m-%d %H:%M:%S")
        << '.' << std::setw(3) << std::setfill('0') << millis.count();
    return out.str();
}

}  // namespace

AccessLogger::AccessLogger(fs::path logPath) : logPath_(std::move(logPath)) {
    fs::create_directories(logPath_.parent_path());
}

void AccessLogger::append(const AccessLogEntry& entry) {
    nlohmann::json data;
    data["query"] = entry.query;
    data["client_id"] = entry.clientId;
    data["handler_id"] = entry.handlerId;
    data["started_at"] = formatTimestamp(entry.startedAt);
    data["finished_at"] = formatTimestamp(entry.finishedAt);
    data["status"] = entry.status;
    data["code"] = entry.code;
    data["message"] = entry.message;

    std::ofstream out(logPath_, std::ios::app | std::ios::binary);
    if (!out) {
        throw std::runtime_error("cannot write access log: " + logPath_.string());
    }
    out << data.dump() << '\n';
}

const fs::path& AccessLogger::path() const {
    return logPath_;
}

}  // namespace app
