#pragma once

#include <filesystem>

#include "engine/mini_db.h"

namespace fs = std::filesystem;

namespace app {

class AccessLogger;
class TelemetryCollector;

void runFile(MiniDb& db, const fs::path& scriptPath, AccessLogger& accessLog, TelemetryCollector& telemetry);
void runInteractive(MiniDb& db, AccessLogger& accessLog, TelemetryCollector& telemetry);

}  // namespace app
