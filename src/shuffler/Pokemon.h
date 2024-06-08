#ifndef POKEMON_H
#define POKEMON_H

#include <cstdint>

class Random;

namespace Pokemon
{

std::uint16_t randPokemon(Random& rng);
std::uint16_t randMove(Random& rng);
bool          isLegendary(std::uint16_t pokemon);

}

#endif
