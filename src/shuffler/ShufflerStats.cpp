#include <set>
#include <map>
#include <array>
#include <cstring>
#include <shuffler/Shuffler.h>
#include <shuffler/Random.h>
#include <shuffler/SpeciesGroups.h>
#include <emerald/include/constants/species.h>

static const std::vector<SpeciesSet> kSpeciesSharedStats = {
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
};

static const std::vector<SpeciesSet> kSpeciesSharedHp = {
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
        tmp = randInt(rng, 4096);
        weights[i] = 1 + tmp;
        totalWeight += (1 + tmp);
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
        {
            return false;
        }
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
    }

    void run()
    {
        const SpeciesSet* group;

        /* Index sharing tables */
        for (auto& g : kSpeciesSharedStats)
        {
            for (auto s : g)
            {
                _speciesSharedStats[s] = &g;
            }
        }

        for (auto& g : kSpeciesSharedHp)
        {
            for (auto s : g)
                _speciesSharedHP[s] = &g;
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
        const SpeciesSet* sameStatsGroup;
        const SpeciesSet* sameHpGroup;
        int bst;
        std::array<uint8_t, 6> stats;
        std::array<uint8_t, 6> inStats;
        bool hasStats;
        bool hasHp;

        /* Get the groups */
        hasStats = false;
        hasHp = false;
        sameStatsGroup = _speciesSharedStats[speciesId];
        sameHpGroup = _speciesSharedHP[speciesId];

        if (speciesId == SPECIES_SHEDINJA)
        {
            stats[0] = 1;
            hasHp = true;
        }

        if (sameStatsGroup)
        {
            /* Try to find a shuffled pokemon with the same stats */
            for (auto id : *sameStatsGroup)
            {
                auto it = _stats.find(id);
                if (it != _stats.end())
                {
                    stats = it->second;
                    hasStats = true;
                    break;
                }
            }
        }

        if (!hasStats && sameHpGroup)
        {
            /* Try to find a shuffled pokemon with the same HP */
            for (auto id : *sameHpGroup)
            {
                auto it = _stats.find(id);
                if (it != _stats.end())
                {
                    stats[0] = it->second[0];
                    hasHp = true;
                    break;
                }
            }
        }

        if (!hasStats)
        {
            /* Read the stats */
            readStats(inStats.data(), speciesId);

            /* Compute BST */
            bst = 0;
            for (int i = 0; i < 6; ++i)
                bst += inStats[i];
            if (bst == 0)
                return;

            /* Shuffle */
            if (hasHp)
            {
                bst -= stats[0];
                genStats(_shuffler.random(), stats.data() + 1, 5, bst);
            }
            else
            {
                genStats(_shuffler.random(), stats.data(), 6, bst);
            }
        }

        /* Store the stats */
        _stats[speciesId] = stats;

        /* Patch the stats */
        writeStats(speciesId, stats.data());
    }

    Shuffler&                                       _shuffler;
    std::map<uint16_t, const SpeciesSet*>           _speciesSharedStats;
    std::map<uint16_t, const SpeciesSet*>           _speciesSharedHP;
    std::map<uint16_t, std::array<uint8_t, 6>>      _stats;
    uint32_t                                        _base;
};

void shuffleStats(Shuffler& shuffler)
{
    ShufflerStats ss(shuffler);
    ss.run();
}
