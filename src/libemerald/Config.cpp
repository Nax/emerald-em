#include <libemerald/Config.h>

static void defaultLogCallback(void*, const char* msg)
{
    std::fprintf(stdout, "%s\n", msg);
}

static void defaultErrorCallback(void*, const char* msg)
{
    std::fprintf(stderr, "%s\n", msg);
}

Config::Config()
{
    cbLog = defaultLogCallback;
    cbLogArg = nullptr;
    cbError = defaultErrorCallback;
    cbErrorArg = nullptr;
}
