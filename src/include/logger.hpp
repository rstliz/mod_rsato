
#ifndef __LOGGER_H_
#define __LOGGER_H_

namespace rsato {
class Logger {
   public:
    virtual ~Logger() {}
    virtual void Note(const char* key, const char* value) = 0;
    virtual void Note(const char* key, const int value)   = 0;
    virtual void Notice(const char* format, ...)          = 0;
    virtual void Warning(const char* format, ...)         = 0;
    virtual void Critical(const char* format, ...)        = 0;
};
}  // namespace rsato
#endif