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
        db.growthRate[i] = rom.readU8(base + DATA_SPECIES_OFF_GROWTH_RATE);

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
        rom.writeU8(base + DATA_SPECIES_OFF_GROWTH_RATE, db.growthRate[i]);
        rom.writeU8(base + DATA_SPECIES_OFF_CATCH_RATE, 150); /* Forced */
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

static void databaseTrainersLoad(DatabaseTrainers& db, const Rom& rom)
{
    uint32_t baseTrainers;
    uint32_t baseTrainerMons;
    uint32_t base;
    uint8_t teamSize;

    baseTrainers = rom.sym("gTrainers");
    for (int i = 0; i < TRAINERS_COUNT; ++i)
    {
        base = baseTrainers + DATA_TRAINERS_SIZE * i;
        teamSize = rom.readU8(base + DATA_TRAINERS_OFF_POKEMONS_COUNT);
        db.teamSize[i] = teamSize;
        db.levels[i].fill(0);
        db.pokemons[i].fill(SPECIES_NONE);

        baseTrainerMons = rom.readU32(base + DATA_TRAINERS_OFF_POKEMONS);
        for (int j = 0; j < teamSize; ++j)
        {
            base = baseTrainerMons + j * DATA_TRAINERMON_SIZE;
            db.pokemons[i][j] = rom.readU16(base + DATA_TRAINERMON_OFF_SPECIES);
            db.levels[i][j] = rom.readU8(base + DATA_TRAINERMON_OFF_LEVEL);
        }
    }
}

static void databaseTrainersSave(const DatabaseTrainers& db, Rom& rom)
{
    uint32_t baseTrainers;
    uint32_t baseTrainerMons;
    uint32_t base;
    uint8_t teamSize;

    baseTrainers = rom.sym("gTrainers");
    for (int i = 0; i < TRAINERS_COUNT; ++i)
    {
        base = baseTrainers + DATA_TRAINERS_SIZE * i;
        teamSize = db.teamSize[i];
        rom.writeU8(base + DATA_TRAINERS_OFF_POKEMONS_COUNT, teamSize);
        baseTrainerMons = rom.readU32(base + DATA_TRAINERS_OFF_POKEMONS);
        for (int j = 0; j < teamSize; ++j)
        {
            base = baseTrainerMons + j * DATA_TRAINERMON_SIZE;
            rom.writeU16(base + DATA_TRAINERMON_OFF_SPECIES, db.pokemons[i][j]);
            rom.writeU8(base + DATA_TRAINERMON_OFF_LEVEL, db.levels[i][j]);
        }
    }
}

static void loadItemVector(std::vector<uint16_t>& vec, const Rom& rom, const char* sym)
{
    uint32_t addr;
    uint16_t item;

    addr = rom.sym(sym);
    for (;;)
    {
        item = rom.readU16(addr);
        if (item == 0xffff)
            break;
        vec.push_back(item);
        addr += 2;
    }
}

static void databaseMiscLoad(DatabaseMisc& db, const Rom& rom)
{
    (void)rom;

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

    db.tmHmKey = 0;

    /* Read items given */
    loadItemVector(db.itemsGiven, rom, "kItemsGiven");
    loadItemVector(db.itemsBalls, rom, "kItemsBalls");
    loadItemVector(db.itemsHidden, rom, "kItemsHidden");
}

static void writeItemVector(const std::vector<uint16_t>& vec, Rom& rom, const char* sym)
{
    uint32_t addr;

    addr = rom.sym(sym);
    for (uint16_t item : vec)
    {
        rom.writeU16(addr, item);
        addr += 2;
    }
}

static void databaseMiscSave(const DatabaseMisc& db, Rom& rom)
{
    uint16_t starters[3];
    uint32_t base;

    starters[0] = db.starters[0][0];
    starters[1] = db.starters[1][0];
    starters[2] = db.starters[2][0];

    rom.write(rom.sym("kStarterMons"), starters, sizeof(starters));
    base = rom.sym("kItemMoves");
    rom.write(base, db.tmMoves, sizeof(db.tmMoves));
    base += sizeof(db.tmMoves);
    rom.write(base, db.hmMoves, sizeof(db.hmMoves));

    base = rom.sym("kItemMovesKey");
    rom.writeU32(base, db.tmHmKey);

    writeItemVector(db.itemsGiven, rom, "kItemsGiven");
    writeItemVector(db.itemsBalls, rom, "kItemsBalls");
    writeItemVector(db.itemsHidden, rom, "kItemsHidden");
}

void databaseLoad(Database& db, const Rom& rom)
{
    databasePokemonsLoad(db.pokemons, rom);
    databaseTrainersLoad(db.trainers, rom);
    databaseMiscLoad(db.misc, rom);
}

void databaseSave(Rom& rom, const Database& db)
{
    databasePokemonsSave(db.pokemons, rom);
    databaseTrainersSave(db.trainers, rom);
    databaseMiscSave(db.misc, rom);
}
