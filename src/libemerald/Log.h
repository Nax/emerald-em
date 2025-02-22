#ifndef LOG_H
#define LOG_H

struct Context;

namespace Log
{
    void info(Context& ctx, const char* fmt, ...);
    void error(Context& ctx, const char* fmt, ...);
};

#endif
