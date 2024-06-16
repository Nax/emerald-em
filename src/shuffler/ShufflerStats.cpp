#include <set>
#include <map>
#include <shuffler/Shuffler.h>
#include <shuffler/Random.h>
#include <shuffler/SpeciesGroups.h>
#include <emerald/include/constants/species.h>

static const uint16_t* kSpeciesSharedStats[] = {
    SpeciesGroups::TaurosPaldean,
    SpeciesGroups::Unown,
    SpeciesGroups::Castform,
    SpeciesGroups::Burmy,
    SpeciesGroups::Wormadam,
    SpeciesGroups::Cherrim,
    SpeciesGroups::Shellos,
    SpeciesGroups::Gastrodon,
    SpeciesGroups::RotomAppliances,
    SpeciesGroups::Arceus,
    SpeciesGroups::Basculin,
    SpeciesGroups::Deerling,
    SpeciesGroups::Sawsbuck,
    SpeciesGroups::Keldeo,
    SpeciesGroups::Genesect,
    SpeciesGroups::Vivillon,
    SpeciesGroups::Flabebe,
    SpeciesGroups::Floette,
    SpeciesGroups::Florges,
    SpeciesGroups::Furfrou,
    SpeciesGroups::Meowstic,
    SpeciesGroups::Xerneas,
    SpeciesGroups::Oricorio,
    SpeciesGroups::MiniorCore,
    SpeciesGroups::MiniorMeteor,
    SpeciesGroups::Mimikyu,
    SpeciesGroups::Magearna,
    SpeciesGroups::Cramorant,
    SpeciesGroups::Toxtricity,
    SpeciesGroups::Sinistea,
    SpeciesGroups::Polteageist,
    SpeciesGroups::Alcremie,
    SpeciesGroups::Morpeko,
    SpeciesGroups::Urshifru,
    SpeciesGroups::Zarude,
    SpeciesGroups::Maushold,
    SpeciesGroups::Squawkabilly,
    SpeciesGroups::Tatsugiri,
    SpeciesGroups::Dudunsparce,
    SpeciesGroups::Poltchageist,
    SpeciesGroups::Sinistcha,
    SpeciesGroups::Ogerpon,
    nullptr,
};

static const uint16_t* kSpeciesSharedHp[] = {
    SpeciesGroups::Kyogre,
    SpeciesGroups::Groudon,
    SpeciesGroups::Deoxys,
    SpeciesGroups::Rotom,
    SpeciesGroups::Dialga,
    SpeciesGroups::Palkia,
    SpeciesGroups::Giratina,
    SpeciesGroups::Shaymin,
    SpeciesGroups::Basculegion,
    SpeciesGroups::DarmanitanNormal,
    SpeciesGroups::DarmanitanGalarian,
    SpeciesGroups::Tornadus,
    SpeciesGroups::Thundurus,
    SpeciesGroups::Landorus,
    SpeciesGroups::Enamorus,
    SpeciesGroups::Greninja,
    SpeciesGroups::Aegislash,
    SpeciesGroups::Hoopa,
    SpeciesGroups::Wishiwashi,
    SpeciesGroups::Minior,
    SpeciesGroups::Eiscue,
    SpeciesGroups::Zacian,
    SpeciesGroups::Zamazenta,
    SpeciesGroups::Palafin,
    nullptr,
};

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

class ShufflerStats
{
public:
    ShufflerStats(Shuffler& shuffler)
    : _shuffler(shuffler)
    {
        _base = shuffler.rom().sym("gSpeciesInfo");
        _fixedHp[SPECIES_SHEDINJA] = 1;
    }

    void run()
    {
        const uint16_t* group;

        /* Index sharing tables */
        for (int i = 1; i < NUM_SPECIES; ++i)
        {
            group = SpeciesGroups::find(kSpeciesSharedStats, i);
            _speciesSharedStats[i] = group;

            group = SpeciesGroups::find(kSpeciesSharedHp, i);
            _speciesSharedHP[i] = group;
        }

        for (int i = 1; i < NUM_SPECIES; ++i)
            shuffleStats(i);
    }

private:
    void readStats(uint8_t* stats, uint16_t speciesId)
    {
        _shuffler.rom().read(stats, _base + 0x94 * speciesId, 6);
    }

    void writeStats(uint16_t speciesId, const uint8_t* stats)
    {
        _shuffler.rom().write(_base + 0x94 * speciesId, stats, 6);
    }

    void shuffleStats(uint16_t speciesId)
    {
        const uint16_t* sameStatsGroup;
        const uint16_t* sameHpGroup;
        int bst;
        uint8_t stats[6];

        /* Skip if already shuffled */
        if (_shuffled.find(speciesId) != _shuffled.end())
            return;

        /* Get the group */
        sameStatsGroup = _speciesSharedStats[speciesId];
        if (sameStatsGroup && sameStatsGroup[0] != speciesId)
            return;
        sameHpGroup = _speciesSharedHP[speciesId];

        /* Read the stats */
        readStats(stats, speciesId);

        /* Compute BST */
        bst = 0;
        for (int i = 0; i < 6; ++i)
            bst += stats[i];
        if (bst == 0)
            return;

        /* Shuffle */
        auto it = _fixedHp.find(speciesId);
        if (it != _fixedHp.end())
        {
            stats[0] = it->second;
            bst -= it->second;
            genStats(_shuffler.random(), stats + 1, 5, bst);
        }
        else
        {
            genStats(_shuffler.random(), stats, 6, bst);
        }

        /* Patch the stats */
        writeStats(speciesId, stats);
        _shuffled.insert(speciesId);
        if (sameStatsGroup)
        {
            for (int i = 1; sameStatsGroup[i] != SPECIES_NONE; ++i)
            {
                writeStats(sameStatsGroup[i], stats);
                _shuffled.insert(sameStatsGroup[i]);
            }
        }

        /* Write hp */
        if (sameHpGroup)
        {
            for (int i = 0; sameHpGroup[i] != SPECIES_NONE; ++i)
            {
                _fixedHp[sameHpGroup[i]] = stats[0];
            }
        }
    }

    Shuffler&                           _shuffler;
    std::map<uint16_t, const uint16_t*> _speciesSharedStats;
    std::map<uint16_t, const uint16_t*> _speciesSharedHP;
    uint32_t                            _base;
    std::map<uint16_t, uint8_t>         _fixedHp;
    std::set<uint16_t>                  _shuffled;
};

void shuffleStats(Shuffler& shuffler)
{
    ShufflerStats ss(shuffler);
    ss.run();
}
