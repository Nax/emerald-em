#include "Database.h"
#include "Rom.h"
#include "Data.h"

static void databasePokemonsLoad(DatabasePokemons& db, const Rom& rom)
{
    uint32_t baseSpeciesInfo;
    uint32_t base;

    baseSpeciesInfo = rom.sym("gSpeciesInfo");

    for (int i = 0; i < NUM_SPECIES; ++i)
    {
        base = baseSpeciesInfo + DATA_SPECIES_SIZE * i;
        rom.read(db.stats[i].data(), base + DATA_SPECIES_OFF_STATS, 6);
        rom.read(db.abilities[i].data(), base + DATA_SPECIES_OFF_ABILITIES, 6);
    }
}

static void databasePokemonsSave(const DatabasePokemons& db, Rom& rom)
{
    uint32_t baseSpeciesInfo;
    uint32_t base;

    baseSpeciesInfo = rom.sym("gSpeciesInfo");

    for (int i = 0; i < NUM_SPECIES; ++i)
    {
        rom.write(baseSpeciesInfo + DATA_SPECIES_SIZE * i + DATA_SPECIES_OFF_STATS, db.stats[i].data(), 6);
        rom.write(baseSpeciesInfo + DATA_SPECIES_SIZE * i + DATA_SPECIES_OFF_ABILITIES, db.abilities[i].data(), 6);
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
