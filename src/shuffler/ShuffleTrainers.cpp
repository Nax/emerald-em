#include <emerald/include/constants/opponents.h>
#include "Database.h"
#include "Rom.h"
#include "Random.h"
#include "Pokemon.h"

static uint8_t fixupLevel(uint8_t level)
{
    level += level / 2;
    if (level > 100)
        level = 100;
    return level;
}

void shuffleTrainers(Database& db, Random& rand)
{
    for (int i = 0; i < TRAINERS_COUNT; ++i)
    {
        uint8_t teamSize = db.trainers.teamSize[i];
        for (int j = 0; j < teamSize; ++j)
        {
            uint16_t species = db.trainers.pokemons[i][j];
            uint8_t level = db.trainers.levels[i][j];
            level = fixupLevel(level);

            switch (species)
            {
            case SPECIES_TREECKO:
            case SPECIES_GROVYLE:
            case SPECIES_SCEPTILE:
                if (level >= 30)
                {
                    species = db.misc.starters[0][2];
                }
                else
                {
                    species = db.misc.starters[0][species - SPECIES_TREECKO];
                }
                break;
            case SPECIES_TORCHIC:
            case SPECIES_COMBUSKEN:
            case SPECIES_BLAZIKEN:
                if (level >= 30)
                {
                    species = db.misc.starters[1][2];
                }
                else
                {
                    species = db.misc.starters[1][species - SPECIES_TORCHIC];
                }
                break;
            case SPECIES_MUDKIP:
            case SPECIES_MARSHTOMP:
            case SPECIES_SWAMPERT:
                if (level >= 30)
                {
                    species = db.misc.starters[2][2];
                }
                else
                {
                    species = db.misc.starters[2][species - SPECIES_MUDKIP];
                }
                break;
            default:
                species = Pokemon::randPokemon(rand);
                if (level >= 30)
                    species = Pokemon::evolution(db, rand, species, 99);
            }

            db.trainers.pokemons[i][j] = species;
            db.trainers.levels[i][j] = level;
        }
    }
}
