#ifndef DATABASE_H
#define DATABASE_H

#include <emerald/include/constants/species.h>
#include <emerald/include/constants/opponents.h>
#include <cstdint>
#include <array>

class Rom;

struct DatabasePokemons
{
    DatabasePokemons() : stats{}, abilities{} {}

    std::array<uint8_t, 6>      stats[NUM_SPECIES];
    std::array<uint16_t, 3>     abilities[NUM_SPECIES];
    std::array<uint16_t, 16>    evolutions[NUM_SPECIES];
    uint8_t                     evolutionsCounts[NUM_SPECIES];
    std::array<uint8_t, 2>      types[NUM_SPECIES];
    uint8_t                     growthRate[NUM_SPECIES];
};

struct DatabaseTrainers
{
    DatabaseTrainers() {}

    uint8_t                     teamSize[TRAINERS_COUNT];
    std::array<uint16_t, 6>     pokemons[TRAINERS_COUNT];
    std::array<uint8_t, 6>      levels[TRAINERS_COUNT];
};

struct DatabaseMisc
{
    DatabaseMisc() : tmMoves{}, hmMoves{} {}

    std::array<uint16_t, 3>     starters[3];
    uint16_t                    tmMoves[100];
    uint16_t                    hmMoves[8];
    uint32_t                    tmHmKey;
    uint16_t                    itemsGiven[64];
};

struct Database
{
    DatabasePokemons pokemons;
    DatabaseTrainers trainers;
    DatabaseMisc     misc;
};

void databaseLoad(Database& db, const Rom& rom);
void databaseSave(Rom& rom, const Database& db);

#endif
