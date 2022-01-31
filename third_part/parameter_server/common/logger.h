
#ifndef COMMON_LOGGER_H
#define COMMON_LOGGER_H

#include <memory>
#include <string>
#include <chrono>

#include <spdlog/spdlog.h>
#include <spdlog/async.h>
#include <spdlog/sinks/daily_file_sink.h>

extern std::shared_ptr<spdlog::logger> logger;

#endif // COMMON_LOGGER_H

