/*
 * @Company: TWL
 * @Author: xue jian
 * @Email: xuejian@kanzhun.com
 * @Date: 2019-08-19 15:13:01
 * @LastEditTime: 2019-08-21 11:26:30
 */
#ifndef _PEDIS_UTIL_LOG_H
#define _PEDIS_UTIL_LOG_H

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include <cstdarg>
#include <mutex>
#include <sstream>
#include <string>
#include <thread>

namespace util {
class Logger {
   public:
    enum { kLevelTrace, kLevelDebug, kLevelInfo, kLevelWarn, kLevelError, kLevelFatal };

    // default log to stdout
    Logger() : level_(kLevelInfo), reopen_(false), logfile_(stdout), current_max_id_(0) {}

    ~Logger() {
        std::lock_guard<std::mutex> _(mutex_);
        this->Close();
    }

    // Open a logger, filename can be "stdout". rotate every rotateHour
    bool Open(const std::string &filename, int level = kLevelInfo);

    bool Enabled(int level) { return level >= level_; }

    void Reopen() {
        std::lock_guard<std::mutex> _(mutex_);
        this->reopen_ = true;
    }

    void Logv(int level, const char *fmt, va_list ap);

    void Logv(int level, const char *fmt, ...) {
        va_list ap;
        va_start(ap, fmt);
        this->Logv(level, fmt, ap);
        va_end(ap);
    }

    int SetLevel(int level) {
        assert(level <= kLevelFatal && level >= kLevelTrace && "logger level out of range");
        int old = level_;
        level_ = level;
        return old;
    }

   private:
    int level_;
    bool reopen_;
    FILE *logfile_;
    std::mutex mutex_;
    std::string filename_;

    int current_max_id_;
    static __thread int thread_id_;

    inline long MilliTime(struct timeval const *now) { return now->tv_sec * 1000 + now->tv_usec / 1000; }

    // prerequisite: mutex held
    inline void Close() {
        if (logfile_ && logfile_ != stdout) {
            fclose(logfile_);
        }
    }

    Logger(const Logger &);  // No copying allowed
    void operator=(const Logger &);
};

// convenient methods, operate on a global Logger(static)
void log_write(int level, const char *fmt, ...);

bool log_open(const std::string &filename, int level = Logger::kLevelInfo);

void log_reopen();

int set_log_level(int level);

void set_thread_name(const std::string &name);

#define __FILE_NAME (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

/*
  sample:
  2014-01-04 19:43:49.888 E [main] util/log.cpp(81): hello world

  no thread name
  2014-01-04 19:44:32.437 E [0x7fff7c80a310] util/log.cpp(74): hello world
*/
#ifdef NDEBUG

#define log_trace(fmt, ...) \
    util::log_write(util::Logger::kLevelTrace, "%s(%d): " fmt, __FILE_NAME, __LINE__, __VA_ARGS__)
#define log_debug(fmt, ...) \
    util::log_write(util::Logger::kLevelDebug, "%s(%d): " fmt, __FILE_NAME, __LINE__, __VA_ARGS__)
#define log_info(fmt, ...) util::log_write(util::Logger::kLevelInfo, "%s(%d): " fmt, __FILE_NAME, __LINE__, __VA_ARGS__)
#define log_warn(fmt, ...) util::log_write(util::Logger::kLevelWarn, "%s(%d): " fmt, __FILE_NAME, __LINE__, __VA_ARGS__)
#define log_error(fmt, ...) \
    util::log_write(util::Logger::kLevelError, "%s(%d): " fmt, __FILE_NAME, __LINE__, __VA_ARGS__)
#define log_fatal(fmt, ...) \
    util::log_write(util::Logger::kLevelFatal, "%s(%d): " fmt, __FILE_NAME, __LINE__, __VA_ARGS__)

#else

#define log_trace(fmt, ...) printf("%s(%d): " fmt "\n", __FILE_NAME, __LINE__, __VA_ARGS__)
#define log_debug(fmt, ...) printf("%s(%d): " fmt "\n", __FILE_NAME, __LINE__, __VA_ARGS__)
#define log_info(fmt, ...) printf("%s(%d): " fmt "\n", __FILE_NAME, __LINE__, __VA_ARGS__)
#define log_warn(fmt, ...) printf("%s(%d): " fmt "\n", __FILE_NAME, __LINE__, __VA_ARGS__)
#define log_error(fmt, ...) printf("%s(%d): " fmt "\n", __FILE_NAME, __LINE__, __VA_ARGS__)
#define log_fatal(fmt, ...) printf("%s(%d): " fmt "\n", __FILE_NAME, __LINE__, __VA_ARGS__)

#endif

}  // namespace util

#endif /* _PEDIS_UTIL_LOG_H */
