#include <emerald/include/constants/offsets.h>
#include "Database.h"
#include "Rom.h"
#include "Random.h"
#include "Pokemon.h"

void shuffleStarters(Database& db, Random& rand)
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
            tmp = Pokemon::randPokemon(rand);
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
        starterEvo2 = Pokemon::evolution(db, rand, starterEvo1);
        starterEvoMax = Pokemon::evolution(db, rand, starterEvo2, 999);

        db.misc.starters[i][0] = starterEvo1;
        db.misc.starters[i][1] = starterEvo2;
        db.misc.starters[i][2] = starterEvoMax;
    }
}
