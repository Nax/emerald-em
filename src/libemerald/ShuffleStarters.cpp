#include <emerald/include/constants/offsets.h>
#include "Context.h"
#include "Pokemon.h"

void shuffleStarters(Context& ctx)
{
    bool valid;
    std::uint16_t starters[3];
    std::uint16_t tmp;
    std::uint16_t starterEvo1;
    std::uint16_t starterEvo2;
    std::uint16_t starterEvoMax;

    /* Select 3 pokemons */
    for (int i = 0; i < 3; i++)
    {
        for (;;)
        {
            valid = true;
            tmp = ctx.pkmnGenerator.randPokemon(ctx.rng);
            for (int j = 0; j < i; ++j)
            {
                if (starters[j] == tmp)
                    valid = false;
            }
            if (valid)
                break;
        }
        starters[i] = tmp;
    }

    /* Copy to the DB, along with evolutions */
    for (int i = 0; i < 3; ++i)
    {
        starterEvo1 = starters[i];
        starterEvo2 = Pokemon::evolution(ctx.db, ctx.rng, starterEvo1);
        starterEvoMax = Pokemon::evolution(ctx.db, ctx.rng, starterEvo2, 999);

        ctx.db.misc.starters[i][0] = starterEvo1;
        ctx.db.misc.starters[i][1] = starterEvo2;
        ctx.db.misc.starters[i][2] = starterEvoMax;
    }
}
