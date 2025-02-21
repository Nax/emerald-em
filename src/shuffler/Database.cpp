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

static void databaseMiscLoad(DatabaseMisc& db, const Rom& rom)
{
    /* Hardcoded starters */
    db.starters[0][0] = SPECIES_TREECKO;
    db.starters[0][1] = SPECIES_GROVYLE;
    db.starters[0][2] = SPECIES_SCEPTILE;
    db.starters[1][0] = SPECIES_TORCHIC;
    db.starters[1][1] = SPECIES_COMBUSKEN;
    db.starters[1][2] = SPECIES_BLAZIKEN;
    db.starters[2][0] = SPECIES_MUDKIP;
    db.starters[2][1] = SPECIES_MARSHTOMP;
    db.starters[2][2] = SPECIES_SWAMPERT;
}

static void databaseMiscSave(const DatabaseMisc& db, Rom& rom)
{
    uint16_t starters[3];

    starters[0] = db.starters[0][0];
    starters[1] = db.starters[1][0];
    starters[2] = db.starters[2][0];

    rom.write(rom.sym("kStarterMons"), starters, sizeof(starters));
}

void databaseLoad(Database& db, const Rom& rom)
{
    databasePokemonsLoad(db.pokemons, rom);
    databaseMiscLoad(db.misc, rom);
}

void databaseSave(Rom& rom, const Database& db)
{
    databasePokemonsSave(db.pokemons, rom);
    databaseMiscSave(db.misc, rom);
}
