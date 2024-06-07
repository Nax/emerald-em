#include <shuffler/Random.h>
#include <shuffler/Pokemon.h>
#include "../../emerald/include/constants/species.h"

#define ARRAY_SIZE(n)   (sizeof((n)) / sizeof((n)[0]))
#define SAMPLE(rng, x)  (sample((rng), (x), ARRAY_SIZE((x))))

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

template <typename T>
static T sample(Random& rng, const T* array, std::size_t size)
{
    std::size_t index;

    index = randInt(rng, size);
    return array[index];
}

static const std::uint16_t kFormsMinior[] = {
    SPECIES_MINIOR_RED,
    SPECIES_MINIOR_ORANGE,
    SPECIES_MINIOR_YELLOW,
    SPECIES_MINIOR_GREEN,
    SPECIES_MINIOR_BLUE,
    SPECIES_MINIOR_INDIGO,
    SPECIES_MINIOR_VIOLET
};

std::uint16_t Pokemon::randPokemon(Random& rng)
{
    std::uint16_t value;

    value = randInt(rng, 1025) + 1;

    switch (value)
    {
    case SPECIES_MINIOR: return SAMPLE(rng, kFormsMinior);
    }

    return value;
}

std::uint16_t Pokemon::randVisiblePokemon(Random& rng)
{
    std::uint16_t pokemon;

    pokemon = randPokemon(rng);

    switch (pokemon)
    {
    case SPECIES_MINIOR_RED: return SPECIES_MINIOR_CORE_RED;
    case SPECIES_MINIOR_ORANGE: return SPECIES_MINIOR_CORE_ORANGE;
    case SPECIES_MINIOR_YELLOW: return SPECIES_MINIOR_CORE_YELLOW;
    case SPECIES_MINIOR_GREEN: return SPECIES_MINIOR_CORE_GREEN;
    case SPECIES_MINIOR_BLUE: return SPECIES_MINIOR_CORE_BLUE;
    case SPECIES_MINIOR_INDIGO: return SPECIES_MINIOR_CORE_INDIGO;
    case SPECIES_MINIOR_VIOLET: return SPECIES_MINIOR_CORE_VIOLET;
    }

    return pokemon;
}
