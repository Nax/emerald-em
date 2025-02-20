#include <set>
#include <vector>
#include <shuffler/Database.h>
#include <shuffler/Shuffler.h>
#include <shuffler/Pokemon.h>
#include <shuffler/SpeciesGroups.h>
#include <emerald/include/constants/species.h>

/* Species with shared evolutions, mostly cosmetic forms */
static const std::vector<const SpeciesSet*> kSpeciesSharedEvolutions = {
    &SpeciesGroups::Unown,
    &SpeciesGroups::Shellos,
    &SpeciesGroups::Gastrodon,
    &SpeciesGroups::Deerling,
    &SpeciesGroups::Sawsbuck,
    &SpeciesGroups::Vivillon,
    &SpeciesGroups::Flabebe,
    &SpeciesGroups::Floette,
    &SpeciesGroups::Florges,
    &SpeciesGroups::Furfrou,
    &SpeciesGroups::MiniorCore,
    &SpeciesGroups::Magearna,
    &SpeciesGroups::Sinistea,
    &SpeciesGroups::Polteageist,
    &SpeciesGroups::Alcremie,
    &SpeciesGroups::Zarude,
    &SpeciesGroups::Maushold,
    &SpeciesGroups::Squawkabilly,
    &SpeciesGroups::Dudunsparce,
    &SpeciesGroups::Poltchageist,
    &SpeciesGroups::Sinistcha
};

static void shuffle(std::vector<uint16_t>& data, Random& rng)
{
    for (int i = data.size() - 1; i > 0; --i)
    {
        int j = rng.next() % (i + 1);
        std::swap(data[i], data[j]);
    }
}

static int computeBst(Database& db, int index)
{
    int total{};

    for (int i = 0; i < 6; ++i)
    {
        total += db.pokemons.stats[index][i];
    }

    return total;
}

class ShuffleEvolutions
{
public:
    ShuffleEvolutions(Database& db, Random& rand)
    : _db{db}, _rand{rand}
    {
    }

    void run()
    {
        computeShuffledPokemons();
        computeEvolvedPokemons();

        for (;;)
        {
            if (tryComputeSubstitutions())
                break;
        }

        /* We need to apply the substitutions to the database */
        for (int speciesId = 1; speciesId < NUM_SPECIES; ++speciesId)
        {
            for (unsigned i = 0; i < _db.pokemons.evolutions[speciesId].size(); ++i)
            {
                auto targetId = _db.pokemons.evolutions[speciesId][i];
                if (_substitutions.find(targetId) == _substitutions.end())
                    continue;
                targetId = _substitutions[targetId];
                _db.pokemons.evolutions[speciesId][i] = targetId;
            }
        }
    }

private:
    Database&                       _db;
    Random&                         _rand;
    std::set<uint16_t>              _pokemonsShuffled;
    std::set<uint16_t>              _pokemonsEvolved;
    std::map<uint16_t, uint16_t>    _substitutions;

    void computeShuffledPokemons()
    {
        for (int i = 1; i < NUM_SPECIES; ++i)
        {
            if (!Pokemon::isValidOutOfBattle(i))
                continue;

            _pokemonsShuffled.insert(i);
        }
    }

    void computeEvolvedPokemons()
    {
        for (int i = 1; i < NUM_SPECIES; ++i)
        {
            if (!Pokemon::isValidOutOfBattle(i))
                continue;

            for (auto evo : _db.pokemons.evolutions[i])
            {
                if (evo != SPECIES_NONE && Pokemon::isValidOutOfBattle(evo))
                {
                    _pokemonsEvolved.insert(evo);
                }
            }
        }
    }

    void filterBst(std::vector<std::uint16_t>& pool, std::vector<std::uint16_t>& src, int min, int max)
    {
        pool.clear();
        for (auto p : src)
        {
            int bst = computeBst(_db, p);
            if (bst >= min && bst <= max)
                pool.push_back(p);
        }
    }

    void getEvolutionLineWithSubstitutions(std::set<std::uint16_t>& evoLine, std::uint16_t speciesId, const std::map<std::uint16_t, std::uint16_t>& subs)
    {
        std::set<uint16_t> groupExpanded;
        std::set<uint16_t> evoLineCopy;
        bool changed;

        evoLine.clear();
        evoLine.insert(speciesId);
        do
        {
            changed = false;
            evoLineCopy = evoLine;

            /* Perform group expansion */
            for (auto v : evoLineCopy)
            {
                if (groupExpanded.find(v) != groupExpanded.end())
                    continue;
                const SpeciesSet* group = SpeciesGroups::find(kSpeciesSharedEvolutions, v);
                if (group)
                {
                    groupExpanded.insert(group->begin(), group->end());
                    evoLine.insert(group->begin(), group->end());
                    changed = true;
                }
            }

            /* Lookup pokemons */
            for (uint16_t i = 1; i < NUM_SPECIES; ++i)
            {
                const auto& dbEntry = _db.pokemons.evolutions[i];

                /* If the current pokemon is on the evo line, lookup all its evolutions */
                if (evoLine.find(i) != evoLine.end())
                {
                    for (auto evo : dbEntry)
                    {
                        if (evo == SPECIES_NONE)
                            continue;
                        if (subs.find(evo) == subs.end())
                            continue;
                        evo = subs.at(evo);

                        if (evoLine.find(evo) == evoLine.end())
                        {
                            evoLine.insert(evo);
                            changed = true;
                        }
                    }
                }

                /* Lookup all the subs evo to find the evo line */
                for (auto evo : dbEntry)
                {
                    if (evo == SPECIES_NONE)
                        continue;
                    if (subs.find(evo) == subs.end())
                        continue;
                    evo = subs.at(evo);

                    if (evoLine.find(evo) != evoLine.end())
                    {
                        if (evoLine.find(i) == evoLine.end())
                        {
                            evoLine.insert(i);
                            changed = true;
                        }
                    }
                }
            }
        } while (changed);
    }

    int getRecursiveEvoDepth(std::uint16_t speciesId, const std::map<std::uint16_t, std::uint16_t>& subs, int depth)
    {
        int maxDepth;

        if (depth >= 10)
            return 10;

        const auto& dbEntry = _db.pokemons.evolutions[speciesId];
        maxDepth = depth + 1;
        for (auto evo : dbEntry)
        {
            if (evo == SPECIES_NONE)
                continue;
            if (subs.find(evo) == subs.end())
            {
                if (maxDepth == depth + 1)
                    maxDepth++;
                continue;
            }

            evo = subs.at(evo);
            maxDepth = std::max(maxDepth, getRecursiveEvoDepth(evo, subs, depth + 1));
        }

        return maxDepth;
    }

    int getEvolutionDepthWithSubstitutions(std::uint16_t speciesId, const std::map<std::uint16_t, std::uint16_t>& subs)
    {
        std::set<uint16_t> evoLine;
        int max;
        int tmp;

        getEvolutionLineWithSubstitutions(evoLine, speciesId, subs);
        max = 0;
        for (auto e : evoLine)
        {
            tmp = getRecursiveEvoDepth(e, subs, 0);
            max = std::max(max, tmp);
        }

        return max;
    }

    bool makeCandidatesPool(std::vector<std::uint16_t>& pool, const std::set<std::uint16_t>& poolDst, uint16_t src)
    {
        std::vector<std::uint16_t> tmpPool;
        bool typesInCommon;
        int bst;
        int delta;
        int evoDepth;
        const SpeciesSet* groupSrc;
        const SpeciesSet* groupDst;
        std::map<uint16_t, uint16_t> subs;

        /* Build the temp pool */
        bst = computeBst(_db, src);
        groupSrc = SpeciesGroups::find(kSpeciesSharedEvolutions, src);
        for (auto candidate : poolDst)
        {
            /* Filter by identity */
            if (candidate == src)
                continue;

            if (groupSrc)
            {
                groupDst = SpeciesGroups::find(kSpeciesSharedEvolutions, candidate);
                if (groupDst == groupSrc)
                    continue;
            }

            /* Filter by legendary status */
            if (Pokemon::isLegendary(candidate) != Pokemon::isLegendary(src))
                continue;

            /* Filter by types */
            typesInCommon = false;
            for (int i = 0; i < 2; ++i)
            {
                for (int j = 0; j < 2; ++j)
                {
                    uint8_t typeSrc = _db.pokemons.types[src][i];
                    uint8_t typeCandidate = _db.pokemons.types[candidate][j];

                    //printf("Types: %d / %d\n", typeSrc, typeCandidate);

                    if (typeSrc == typeCandidate && typeSrc != 0)
                    {
                        typesInCommon = true;
                    }
                }
            }
            if (!typesInCommon)
                continue;

            /* Filter by evo line depth */
            subs = _substitutions;
            subs[src] = candidate;
            evoDepth = getEvolutionDepthWithSubstitutions(src, subs);
            if (evoDepth > 3)
            {
                continue;
            }

            tmpPool.push_back(candidate);
        }

        for (int i = 0; i < 5; ++i)
        {
            delta = (i + 1) * 20;
            filterBst(pool, tmpPool, bst - delta, bst + delta);
            if (pool.size() >= 10)
                return true;
        }

        if (pool.size())
            return true;

        /* No pool, try to return ignoring BST */
        if (tmpPool.size())
        {
            pool.swap(tmpPool);
            return true;
        }

        return false;
    }

    void assignSubstitution(std::set<uint16_t>& pool, uint16_t src, uint16_t dst)
    {
        _substitutions[src] = dst;
        pool.erase(dst);
    }

    void assignEvolution(std::set<uint16_t>& pool, uint16_t src, uint16_t dst)
    {
        const SpeciesSet* groupSrc;
        const SpeciesSet* groupDst;

        /* Assign the first substution */
        assignSubstitution(pool, src, dst);
        groupSrc = SpeciesGroups::find(kSpeciesSharedEvolutions, src);
        if (!groupSrc)
            return;

        /* The pokemon is part of a cosmetic group */
        /* If the dst is also a cosmetic group, assign through it */
        /* Otherwise assign the same pokemon to every evo */
        groupDst = SpeciesGroups::find(kSpeciesSharedEvolutions, dst);
        if (groupDst)
        {
            std::vector<std::uint16_t> groupVec{groupDst->begin(), groupDst->end()};
            uint16_t tmp;

            shuffle(groupVec, _rand);
            for (auto s : *groupSrc)
            {
                if (src == s)
                    continue;
                tmp = groupVec[_rand.next() % groupVec.size()];
                assignSubstitution(pool, s, tmp);
            }
            for (auto d : *groupDst)
                pool.erase(d);
        }
        else
        {
            for (auto s : *groupSrc)
            {
                if (src == s)
                    continue;
                assignSubstitution(pool, s, dst);
            }
        }
    }

    bool tryComputeSubstitutions()
    {
        auto poolDst = _pokemonsShuffled;
        std::vector<uint16_t> poolSrc(_pokemonsEvolved.begin(), _pokemonsEvolved.end());
        std::vector<uint16_t> currentPoolDst;

        _substitutions.clear();
        shuffle(poolSrc, _rand);

        while (poolSrc.size())
        {
            auto src = poolSrc.back();
            poolSrc.pop_back();

            if (_substitutions.find(src) != _substitutions.end())
                continue;

            if (!makeCandidatesPool(currentPoolDst, poolDst, src))
            {
                std::printf("No candidates for %d\n", src);
                return false;
            }

            /* Get the subst */
            auto dst = currentPoolDst[_rand.next() % currentPoolDst.size()];
            assignEvolution(poolDst, src, dst);
        }

        return true;
    }
};

void shuffleEvolutions(Database& db, Random& rand)
{
    ShuffleEvolutions s{db, rand};
    s.run();
}
