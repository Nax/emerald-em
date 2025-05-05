#ifndef CONTEXT_H
#define CONTEXT_H

#include <fstream>
#include <libemerald/Config.h>
#include <libemerald/Random.h>
#include <libemerald/Rom.h>
#include <libemerald/Database.h>
#include <libemerald/PokemonGenerator.h>

struct Context
{
    Context(Config& cfg);

    Config& cfg;
    Random rng;
    Rom rom;
    Database db;
    PokemonGenerator pkmnGenerator;
    std::string dataPath;
    std::ofstream outRom;
};

#endif
