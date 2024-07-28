#include "Database.h"
#include "Rom.h"

static void databasePokemonsLoad(DatabasePokemons& db, const Rom& rom)
{
    uint32_t baseSpeciesInfo;
    uint32_t base;

    baseSpeciesInfo = rom.sym("gSpeciesInfo");

    for (int i = 0; i < NUM_SPECIES; ++i)
    {
        base = baseSpeciesInfo + 0x94 * i;
        rom.read(db.stats[i].data(), base + 0x00, 6);
        rom.read(db.abilities[i].data(), base + 0x18, 6);
    }
}

static void databasePokemonsSave(const DatabasePokemons& db, Rom& rom)
{
    uint32_t baseSpeciesInfo;
    uint32_t base;

    baseSpeciesInfo = rom.sym("gSpeciesInfo");

    for (int i = 0; i < NUM_SPECIES; ++i)
    {
        rom.write(baseSpeciesInfo + 0x94 * i, db.stats[i].data(), 6);
        rom.write(baseSpeciesInfo + 0x94 * i + 0x18, db.abilities[i].data(), 6);
    }
}

void databaseLoad(Database& db, const Rom& rom)
{
    databasePokemonsLoad(db.pokemons, rom);
}

void databaseSave(Rom& rom, const Database& db)
{
    databasePokemonsSave(db.pokemons, rom);
}

