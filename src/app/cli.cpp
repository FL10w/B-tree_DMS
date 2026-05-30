#include "app/cli.h"

#include <array>
#include <chrono>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

#include <nlohmann/json.hpp>

#include "common/string_utils.h"
#include "observability/access_log.h"
#include "observability/telemetry.h"
#include "sql/parser_api.h"
#include "sql/sql_splitter.h"
#include "storage/file_io.h"

namespace app {

namespace {

using json = nlohmann::json;

bool isExitCommand(const std::string& statement) {
    const auto normalized = toUpper(trim(statement));
    return normalized == "EXIT" || normalized == "EXIT;" || normalized == "QUIT" || normalized == "QUIT;";
}

bool isTelemetryCommand(const std::string& statement) {
    const auto normalized = toUpper(trim(statement));
    return normalized == "SHOW TELEMETRY" || normalized == "SHOW TELEMETRY;";
}

bool startsWithSqlCommand(const std::string& line) {
    const auto normalized = toUpper(trim(line));
    static constexpr std::array<const char*, 10> commands = {
        "CREATE", "DROP", "USE", "INSERT", "UPDATE", "DELETE", "SELECT", "SHOW", "EXIT", "QUIT"
    };

    for (const auto* command : commands) {
        const std::string word(command);
        if (normalized == word || normalized.rfind(word + " ", 0) == 0) {
            return true;
        }
    }
    return false;
}

std::string currentHandlerId() {
    return "main-thread";
}

void printResult(const json& result) {
    if (result.is_array()) {
        std::cout << result.dump(2) << "\n";
        return;
    }
    if (result.is_object() && result.value("status", "") == "ok") {
        std::cout << "OK";
        if (result.contains("message")) {
            std::cout << ": " << result["message"].get<std::string>();
        }
        if (result.contains("count")) {
            std::cout << " (" << result["count"] << ")";
        }
        std::cout << "\n";
        return;
    }
    std::cout << result.dump(2) << "\n";
}

void executeStatement(MiniDb& db,
                      const std::string& statement,
                      AccessLogger& accessLog,
                      TelemetryCollector& telemetry) {
    const auto text = trim(statement);
    if (text.empty()) {
        return;
    }
    const auto startedAt = std::chrono::system_clock::now();
    const auto startedSteady = std::chrono::steady_clock::now();
    bool success = false;
    std::string message = "ok";

    try {
        if (isTelemetryCommand(text)) {
            printResult(telemetry.snapshotJson());
        } else {
            printResult(db.execute(parseSqlStatement(text)));
        }
        success = true;
    } catch (const std::exception& ex) {
        message = ex.what();
        std::cout << "ERROR: " << ex.what() << "\n";
    }

    const auto finishedAt = std::chrono::system_clock::now();
    const auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::steady_clock::now() - startedSteady);
    telemetry.record(duration, success);
    accessLog.append({
        text,
        "local-cli",
        currentHandlerId(),
        startedAt,
        finishedAt,
        success ? "OK" : "ERROR",
        success ? 0 : 1,
        message
    });
}

}  // namespace

void runFile(MiniDb& db, const fs::path& scriptPath, AccessLogger& accessLog, TelemetryCollector& telemetry) {
    auto in = openInput(scriptPath);
    std::ostringstream buffer;
    buffer << in.rdbuf();
    for (const auto& statement : splitSqlStatements(buffer.str())) {
        if (isExitCommand(statement)) {
            break;
        }
        executeStatement(db, statement, accessLog, telemetry);
    }
}

void runInteractive(MiniDb& db, AccessLogger& accessLog, TelemetryCollector& telemetry) {
    std::string buffer;
    std::string line;
    while (std::cout << "db[" << db.activeDatabase() << "]> " && std::getline(std::cin, line)) {
        if (!trim(buffer).empty() && buffer.find(';') == std::string::npos && startsWithSqlCommand(line)) {
            std::cout << "ERROR: previous statement is missing ;\n";
            buffer.clear();
        }

        buffer += line;
        buffer.push_back('\n');
        const auto statements = splitSqlStatements(buffer);
        if (statements.empty() || buffer.find(';') == std::string::npos) {
            continue;
        }

        const bool complete = trim(buffer).back() == ';';
        const size_t countToRun = complete ? statements.size() : statements.size() - 1;
        for (size_t i = 0; i < countToRun; ++i) {
            if (isExitCommand(statements[i])) {
                return;
            }
            executeStatement(db, statements[i], accessLog, telemetry);
        }
        buffer = complete ? "" : statements.back();
    }
}

}  // namespace app
