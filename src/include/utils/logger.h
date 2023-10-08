#pragma once

#include <spdlog/spdlog.h>

#include "common/defines.h"

namespace hybridfs {

void SetLogLevel(spdlog::level::level_enum level) {
    if (ENABLED_LOG) {
        spdlog::set_level(level);
    }
}

void LogDebug(const char* msg) {
    if (ENABLED_LOG) {
        spdlog::debug(msg);
    }
}

void LogInfo(const char* msg) {
    if (ENABLED_LOG) {
        spdlog::info(msg);
    }
}

void LogWarn(const char* msg) {
    if (ENABLED_LOG) {
        spdlog::warn(msg);
    }
}

void LogError(const char* msg) {
    if (ENABLED_LOG) {
        spdlog::error(msg);
    }
    exit(1);
}

}