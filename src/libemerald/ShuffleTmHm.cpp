#include <emerald/include/constants/offsets.h>
#include "Database.h"
#include "Rom.h"
#include "Random.h"
#include "Pokemon.h"

void shuffleTmHm(Database& db, Random& rand)
{
    std::uint16_t moves[108];
    std::uint16_t tmp;
    bool valid;

    for (int i = 0; i < 108; ++i)
    {
        for (;;)
        {
            tmp = Pokemon::randMove(rand);
            valid = true;
            for (int j = 0; j < i; ++j)
            {
                if (moves[j] == tmp)
                {
                    valid = false;
                    break;
                }
            }
            if (valid)
                break;
        }

        moves[i] = tmp;
    }

    for (int i = 0; i < 100; ++i)
        db.misc.tmMoves[i] = moves[i];
    for (int i = 0; i < 8; ++i)
        db.misc.hmMoves[i] = moves[i + 100];
    db.misc.tmHmKey = rand.next();
}
