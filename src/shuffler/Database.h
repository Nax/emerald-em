#ifndef DATABASE_H
#define DATABASE_H

#include <emerald/include/constants/species.h>
#include <cstdint>
#include <array>

class Rom;

struct DatabasePokemons
{
    DatabasePokemons() : stats{}, abilities{} {}

    std::array<uint8_t, 6>  stats[NUM_SPECIES];
    std::array<uint16_t, 3> abilities[NUM_SPECIES];
};

struct Database
{
    DatabasePokemons pokemons;
};

void databaseLoad(Database& db, const Rom& rom);
void databaseSave(Rom& rom, const Database& db);

#endif
