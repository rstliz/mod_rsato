
#ifndef __AP_LOGGER_H_
#define __AP_LOGGER_H_

#include <apreq_module_apache2.h>
#include <http_log.h>
#include <stdarg.h>

#include <boost/format.hpp>

#include "logger.hpp"

#ifdef APLOG_USE_MODULE
APLOG_USE_MODULE(rsato);
#endif

namespace rsato {
#define LOG_BUFFER_SIZE 4096
#define SPRINTF_VARIADIC_ARG(buffer, format)             \
    do {                                                 \
        va_list arg;                                     \
        va_start(arg, format);                           \
        vsnprintf(buffer, LOG_BUFFER_SIZE, format, arg); \
        va_end(arg);                                     \
    } while (0)

class ApLogger : public Logger {
   private:
    request_rec* r_;

   public:
    ApLogger(request_rec* r) : r_(r){};

    void Note(const char* key, const char* value) { apr_table_set(this->r_->notes, key, value); };
    void Note(const char* key, const int value) { apr_table_set(this->r_->notes, key, std::to_string(value).c_str()); };

    void Notice(const char* format, ...) {
        char buffer[LOG_BUFFER_SIZE];
        SPRINTF_VARIADIC_ARG(buffer, format);
        ap_log_rerror(APLOG_MARK, APLOG_NOTICE, 0, this->r_, buffer);
    }

    void Warning(const char* format, ...) {
        char buffer[LOG_BUFFER_SIZE];
        SPRINTF_VARIADIC_ARG(buffer, format);
        ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, this->r_, buffer);
    }

    void Critical(const char* format, ...) {
        char buffer[LOG_BUFFER_SIZE];
        SPRINTF_VARIADIC_ARG(buffer, format);
        ap_log_rerror(APLOG_MARK, APLOG_CRIT, 0, this->r_, buffer);
    }

    template <typename... Args>
    static void SNotice(const char* format, Args const&... args) {
        ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, NULL, format, args...);
    }

    template <typename... Args>
    static void SWarning(const char* format, Args const&... args) {
        ap_log_error(APLOG_MARK, APLOG_WARNING, 0, NULL, format, args...);
    }

    template <typename... Args>
    static void SCritical(const char* format, Args const&... args) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, 0, NULL, format, args...);
    }
};
}  // namespace rsato
#endif