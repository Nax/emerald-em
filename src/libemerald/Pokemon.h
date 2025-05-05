#ifndef POKEMON_H
#define POKEMON_H

#include <cstdint>

struct Database;
class Random;

namespace Pokemon
{

std::uint16_t randMove(Random& rng);
bool          isLegendary(std::uint16_t pokemon);
std::uint16_t evolution(const Database& db, Random& rng, std::uint16_t speciesId, int depth = 1);
std::uint16_t randItemTmHm(Random& rng);
std::uint16_t randItemGeneric(Random& rng);

}

#endif
