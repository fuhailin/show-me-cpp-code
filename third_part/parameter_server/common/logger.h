
#ifndef COMMON_LOGGER_H
#define COMMON_LOGGER_H

#include <spdlog/async.h>
#include <spdlog/sinks/daily_file_sink.h>
#include <spdlog/spdlog.h>

#include <chrono>
#include <memory>
#include <string>

extern std::shared_ptr<spdlog::logger> logger;

#endif  // COMMON_LOGGER_H
