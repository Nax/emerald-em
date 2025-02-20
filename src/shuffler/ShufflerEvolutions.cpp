#include <set>
#include <vector>
#include <shuffler/Database.h>
#include <shuffler/Shuffler.h>
#include <shuffler/Pokemon.h>
#include <emerald/include/constants/species.h>

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

    bool makeCandidatesPool(std::vector<std::uint16_t>& pool, const std::set<std::uint16_t>& poolDst, uint16_t src)
    {
        std::vector<std::uint16_t> tmpPool;
        bool typesInCommon;
        int bst;
        int delta;

        /* Build the temp pool */
        bst = computeBst(_db, src);
        for (auto candidate : poolDst)
        {
            /* Filter by identity */
            if (candidate == src)
                continue;

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

            tmpPool.push_back(candidate);
        }

        for (int i = 0; i < 4; ++i)
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
            if (!makeCandidatesPool(currentPoolDst, poolDst, src))
            {
                std::printf("No candidates for %d\n", src);
                return false;
            }

            /* Get the subst */
            auto dst = currentPoolDst[_rand.next() % currentPoolDst.size()];
            _substitutions[src] = dst;
            poolDst.erase(dst);
        }

        return true;
    }
};

void shuffleEvolutions(Database& db, Random& rand)
{
    ShuffleEvolutions s{db, rand};
    s.run();
}
