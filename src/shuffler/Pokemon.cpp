#include <shuffler/Random.h>
#include <shuffler/Pokemon.h>
#include "../../emerald/include/constants/species.h"

static std::uint32_t randInt(Random& rng, std::uint32_t max)
{
    std::uint32_t mask;
    std::uint32_t value;

    if (max == 0 || max == 1)
        return 0;

    /* Build the mask */
    mask = max - 1;
    mask |= mask >> 1;
    mask |= mask >> 2;
    mask |= mask >> 4;
    mask |= mask >> 8;
    mask |= mask >> 16;

    for (;;)
    {
        value = rng.next() & mask;
        if (value < max)
            return value;
    }
}

std::uint16_t Pokemon::randPokemon(Random& rng)
{
    std::uint16_t value;

    value = randInt(rng, 1025) + 1;
    return value;
}

std::uint16_t Pokemon::randVisiblePokemon(Random& rng)
{
    return Pokemon::randPokemon(rng);
}
