#include <emerald/include/constants/offsets.h>
#include "Database.h"
#include "Rom.h"

static void databasePokemonsLoad(DatabasePokemons& db, const Rom& rom)
{
    uint32_t baseSpeciesInfo;
    uint32_t base;
    uint32_t evolutionsPtr;

    baseSpeciesInfo = rom.sym("gSpeciesInfo");

    for (int i = 0; i < NUM_SPECIES; ++i)
    {
        db.evolutions[i].fill(SPECIES_NONE);
        db.evolutionsCounts[i] = 0;

        base = baseSpeciesInfo + DATA_SPECIES_SIZE * i;
        rom.read(db.stats[i].data(), base + DATA_SPECIES_OFF_STATS, 6);
        rom.read(db.types[i].data(), base + DATA_SPECIES_OFF_TYPES, 2);
        rom.read(db.abilities[i].data(), base + DATA_SPECIES_OFF_ABILITIES, 6);
        evolutionsPtr = rom.readU32(base + DATA_SPECIES_OFF_EVOLUTIONS);

        if (evolutionsPtr)
        {
            int j = 0;
            uint16_t evolution;
            uint16_t method;
            for (;;)
            {
                method = rom.readU16(evolutionsPtr + j * 8 + 0);
                if (method == 0xffff)
                    break;
                evolution = rom.readU16(evolutionsPtr + j * 8 + 4);
                db.evolutions[i][j] = evolution;
                ++j;
            }

            db.evolutionsCounts[i] = (uint8_t)j;
        }
    }
}

static void databasePokemonsSave(const DatabasePokemons& db, Rom& rom)
{
    uint32_t baseSpeciesInfo;
    uint32_t base;
    uint32_t evolutionsPtr;

    baseSpeciesInfo = rom.sym("gSpeciesInfo");

    for (int i = 0; i < NUM_SPECIES; ++i)
    {
        base = baseSpeciesInfo + DATA_SPECIES_SIZE * i;
        rom.write(base + DATA_SPECIES_OFF_STATS, db.stats[i].data(), 6);
        rom.write(base + DATA_SPECIES_OFF_ABILITIES, db.abilities[i].data(), 6);
        evolutionsPtr = rom.readU32(base + DATA_SPECIES_OFF_EVOLUTIONS);
        if (evolutionsPtr)
        {
            for (int j = 0; j < db.evolutionsCounts[i]; ++j)
            {
                rom.writeU16(evolutionsPtr + j * 8 + 4, db.evolutions[i][j]);
            }
        }
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
