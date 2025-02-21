#include <emerald/include/constants/offsets.h>
#include "Database.h"
#include "Rom.h"
#include "Random.h"
#include "Pokemon.h"

void shuffleGrowthRates(Database& db, Random& rand)
{
    uint8_t rate;

    (void)rand;

    for (int j = 1; j < NUM_SPECIES; ++j)
    {
        if (Pokemon::isLegendary(j))
            rate = 5;
        else
            rate = 4;

        db.pokemons.growthRate[j] = rate;
    }
}
