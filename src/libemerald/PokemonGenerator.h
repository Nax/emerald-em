#ifndef INCLUDED_POKEMON_GENERATOR_H
#define INCLUDED_POKEMON_GENERATOR_H

#include <set>
#include <vector>
#include <cstdint>
#include <libemerald/SpeciesGroups.h>

struct Config;
class Random;
class PokemonGenerator
{
public:
    PokemonGenerator(const Config& cfg);
    ~PokemonGenerator() = default;

    std::uint16_t randPokemon(Random& rng);
    bool          isValid(uint16_t id) const;

private:
    void buildPokemonList();
    void buildPokemonValidSet();

    const Config&                   _cfg;
    std::vector<std::uint16_t>      _pokemonList;
    std::set<std::uint16_t>         _validPokemons;
};

#endif
