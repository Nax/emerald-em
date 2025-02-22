#ifndef CONTEXT_H
#define CONTEXT_H

#include <fstream>
#include <libemerald/Config.h>
#include <libemerald/Random.h>
#include <libemerald/Rom.h>
#include <libemerald/Database.h>

struct Context
{
    Context(Config& cfg);

    Config& cfg;
    Random rng;
    Rom rom;
    Database db;
    std::string dataPath;
    std::ofstream outRom;
};

#endif
