#include <emerald/include/constants/opponents.h>
#include "Context.h"
#include "Pokemon.h"

static uint8_t fixupLevel(uint8_t level)
{
    level += level / 2;
    if (level > 100)
        level = 100;
    return level;
}

void shuffleTrainers(Context& ctx)
{
    for (int i = 0; i < TRAINERS_COUNT; ++i)
    {
        uint8_t teamSize = ctx.db.trainers.teamSize[i];
        for (int j = 0; j < teamSize; ++j)
        {
            uint16_t species = ctx.db.trainers.pokemons[i][j];
            uint8_t level = ctx.db.trainers.levels[i][j];
            level = fixupLevel(level);

            switch (species)
            {
            case SPECIES_TREECKO:
            case SPECIES_GROVYLE:
            case SPECIES_SCEPTILE:
                if (level >= 30)
                {
                    species = ctx.db.misc.starters[0][2];
                }
                else
                {
                    species = ctx.db.misc.starters[0][species - SPECIES_TREECKO];
                }
                break;
            case SPECIES_TORCHIC:
            case SPECIES_COMBUSKEN:
            case SPECIES_BLAZIKEN:
                if (level >= 30)
                {
                    species = ctx.db.misc.starters[1][2];
                }
                else
                {
                    species = ctx.db.misc.starters[1][species - SPECIES_TORCHIC];
                }
                break;
            case SPECIES_MUDKIP:
            case SPECIES_MARSHTOMP:
            case SPECIES_SWAMPERT:
                if (level >= 30)
                {
                    species = ctx.db.misc.starters[2][2];
                }
                else
                {
                    species = ctx.db.misc.starters[2][species - SPECIES_MUDKIP];
                }
                break;
            default:
                species = ctx.pkmnGenerator.randPokemon(ctx.rng);
                if (level >= 30)
                    species = Pokemon::evolution(ctx.db, ctx.rng, species, 99);
            }

            ctx.db.trainers.pokemons[i][j] = species;
            ctx.db.trainers.levels[i][j] = level;
        }
    }
}
