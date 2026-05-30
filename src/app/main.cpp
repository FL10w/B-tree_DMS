#include "app/main.h"

#include <filesystem>
#include <iostream>
#include <optional>
#include <stdexcept>
#include <string>

#include "observability/access_log.h"
#include "observability/telemetry.h"

namespace fs = std::filesystem;

int main(int argc, char** argv) {
    try {
        fs::path dataDir = "storage";
        std::optional<fs::path> scriptPath;

        for (int i = 1; i < argc; ++i) {
            const std::string arg = argv[i];
            if (arg == "--data-dir") {
                if (i + 1 >= argc) {
                    throw std::runtime_error("--data-dir requires a path");
                }
                dataDir = argv[++i];
            } else if (!scriptPath.has_value()) {
                scriptPath = arg;
            } else {
                throw std::runtime_error("unexpected argument: " + arg);
            }
        }

        app::MiniDb db(dataDir);
        app::AccessLogger accessLog(dataDir / "_access.log");
        app::TelemetryCollector telemetry(dataDir / "_telemetry.json");
        if (scriptPath.has_value()) {
            app::runFile(db, *scriptPath, accessLog, telemetry);
        } else {
            app::runInteractive(db, accessLog, telemetry);
        }
        return 0;
    } catch (const std::exception& ex) {
        std::cerr << "fatal: " << ex.what() << "\n";
        return 1;
    }
}
