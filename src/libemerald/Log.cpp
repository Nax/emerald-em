#include <cstdarg>
#include <libemerald/Log.h>
#include <libemerald/Context.h>

static void logWithCallback(void (*cb)(void*, const char*), void* arg, const char* fmt, va_list args)
{
    char buffer[2048];

    vsnprintf(buffer, sizeof(buffer), fmt, args);
    cb(arg, buffer);
}

void Log::info(Context& ctx, const char* fmt, ...)
{
    va_list args;

    va_start(args, fmt);
    logWithCallback(ctx.cfg.cbLog, ctx.cfg.cbLogArg, fmt, args);
    va_end(args);
}

void Log::error(Context& ctx, const char* fmt, ...)
{
    va_list args;

    va_start(args, fmt);
    logWithCallback(ctx.cfg.cbError, ctx.cfg.cbErrorArg, fmt, args);
    va_end(args);
}
