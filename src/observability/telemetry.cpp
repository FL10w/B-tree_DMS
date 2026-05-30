#include "observability/telemetry.h"

#include <algorithm>
#include <fstream>
#include <numeric>
#include <stdexcept>
#include <utility>

#include "core/string_interner.h"

namespace app {

TelemetryCollector::TelemetryCollector(fs::path snapshotPath) : snapshotPath_(std::move(snapshotPath)) {
    fs::create_directories(snapshotPath_.parent_path());
    const auto now = std::chrono::steady_clock::now();
    writeSnapshotLocked(now);
}

void TelemetryCollector::record(std::chrono::milliseconds duration, bool success) {
    const auto now = std::chrono::steady_clock::now();
    events_.push_back({now, duration, success});
    ++totalRequests_;
    if (!success) {
        ++totalErrors_;
    }
    pruneLocked(now);
    writeSnapshotLocked(now);
}

json TelemetryCollector::snapshotJson() const {
    const auto now = std::chrono::steady_clock::now();
    pruneLocked(now);
    return buildSnapshotLocked(now);
}

const fs::path& TelemetryCollector::path() const {
    return snapshotPath_;
}

void TelemetryCollector::pruneLocked(std::chrono::steady_clock::time_point now) const {
    const auto minute = std::chrono::seconds(60);
    events_.erase(std::remove_if(events_.begin(), events_.end(), [now, minute](const auto& event) {
        return now - event.finishedAt > minute;
    }), events_.end());
}

json TelemetryCollector::buildSnapshotLocked(std::chrono::steady_clock::time_point now) const {
    size_t currentSecondRequests = 0;
    size_t lastTenSecondRequests = 0;
    size_t lastTenSecondLatencyCount = 0;
    long long lastTenSecondLatencyMs = 0;
    size_t errorsLastMinute = 0;
    size_t requestsLastMinute = 0;
    std::vector<size_t> rpsBuckets(10, 0);

    for (const auto& event : events_) {
        const auto ageMs = std::chrono::duration_cast<std::chrono::milliseconds>(now - event.finishedAt);
        if (ageMs <= std::chrono::seconds(60)) {
            ++requestsLastMinute;
            if (!event.success) {
                ++errorsLastMinute;
            }
        }
        if (ageMs <= std::chrono::seconds(1)) {
            ++currentSecondRequests;
        }
        if (ageMs <= std::chrono::seconds(10)) {
            ++lastTenSecondRequests;
            ++lastTenSecondLatencyCount;
            lastTenSecondLatencyMs += event.duration.count();
            const auto ageSeconds = static_cast<size_t>(ageMs.count() / 1000);
            if (ageSeconds < rpsBuckets.size()) {
                ++rpsBuckets[ageSeconds];
            }
        }
    }

    const auto maxRps = *std::max_element(rpsBuckets.begin(), rpsBuckets.end());
    const double averageLatency = lastTenSecondLatencyCount == 0
                                      ? 0.0
                                      : static_cast<double>(lastTenSecondLatencyMs) / lastTenSecondLatencyCount;
    const double errorRate = requestsLastMinute == 0
                                 ? 0.0
                                 : 100.0 * static_cast<double>(errorsLastMinute) / requestsLastMinute;

    json data;
    data["current_rps"] = currentSecondRequests;
    data["average_rps_10s"] = static_cast<double>(lastTenSecondRequests) / 10.0;
    data["max_rps_10s"] = maxRps;
    data["average_latency_ms_10s"] = averageLatency;
    data["errors_last_minute"] = errorsLastMinute;
    data["error_rate_last_minute_percent"] = errorRate;
    data["total_requests"] = totalRequests_;
    data["total_errors"] = totalErrors_;
    data["string_pool"] = {
        {"unique_strings", StringInterner::instance().uniqueCount()},
        {"intern_requests", StringInterner::instance().requestCount()}
    };
    return data;
}

void TelemetryCollector::writeSnapshotLocked(std::chrono::steady_clock::time_point now) const {
    std::ofstream out(snapshotPath_, std::ios::binary);
    if (!out) {
        throw std::runtime_error("cannot write telemetry snapshot: " + snapshotPath_.string());
    }
    out << buildSnapshotLocked(now).dump(2);
}

}  // namespace app
