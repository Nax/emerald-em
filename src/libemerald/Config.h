#ifndef CONFIG_H
#define CONFIG_H

#include <string>

typedef void (*ConfigLogCallback)(void*, const char*);

struct Config
{
    Config();

    std::string         pathOriginalRom;
    std::string         pathOutputRom;
    ConfigLogCallback   cbLog;
    void*               cbLogArg;
    ConfigLogCallback   cbError;
    void*               cbErrorArg;
};

#endif
