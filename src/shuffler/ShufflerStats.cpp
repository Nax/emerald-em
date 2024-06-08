#include <shuffler/Shuffler.h>
#include <shuffler/Random.h>
#include <emerald/include/constants/species.h>

static bool genStatsOnce(Random& rng, uint8_t* dst, int count, int bst)
{
    int bstCopy;
    int tmp;
    int weights[6];
    int totalWeight;
    int stats[6];

    /* Because of 1 in every stat */
    bst -= count;

    /* Assign weights */
    totalWeight = 0;
    for (int i = 0; i < count; ++i)
    {
        tmp = randInt(rng, 256);
        weights[i] = tmp;
        totalWeight += tmp;
    }

    /* Assign stats */
    bstCopy = bst;
    for (int i = 0; i < count; ++i)
    {
        tmp = ((bstCopy * weights[i]) / totalWeight);
        stats[i] = 1 + tmp;
        bst -= tmp;
    }

    /* Safety */
    if (bst < 0)
        return false;

    /* Rounding may leave a few points, assign them at random */
    while (bst)
    {
        tmp = randInt(rng, count);
        stats[tmp]++;
        bst--;
    }

    /* Check for stats > 255 */
    for (int i = 0; i < count; ++i)
    {
        if (stats[i] > 255)
            return false;
    }

    /* Copy the stats */
    for (int i = 0; i < count; ++i)
    {
        dst[i] = stats[i];
    }
    return true;
}

static void genStats(Random& rng, uint8_t* dst, int count, int bst)
{
    for (;;)
    {
        if (genStatsOnce(rng, dst, count, bst))
            return;
    }
}

static void shufflePokemonStats(Shuffler& shuffler, uint32_t base, uint16_t speciesId)
{
    int bst;
    uint8_t stats[6];

    /* Read the stats */
    shuffler.rom().read(stats, base + 0x94 * speciesId, 6);

    /* Compute BST */
    bst = 0;
    for (int i = 0; i < 6; ++i)
        bst += stats[i];
    if (bst == 0)
        return;

    /* Shuffle */
    if (speciesId == SPECIES_SHEDINJA)
    {
        stats[0] = 1;
        bst -= 1;
        genStats(shuffler.random(), stats + 1, 5, bst);
    }
    else
    {
        genStats(shuffler.random(), stats, 6, bst);
    }

    /* Patch the stats */
    shuffler.rom().write(base + 0x94 * speciesId, stats, sizeof(stats));
}

void shuffleStats(Shuffler& shuffler)
{
    uint32_t base;

    base = shuffler.rom().sym("gSpeciesInfo");
    for (int i = 1; i < NUM_SPECIES; ++i)
        shufflePokemonStats(shuffler, base, i);
}
