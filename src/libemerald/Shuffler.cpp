#include <cstdint>
#include <cstring>
#include <vector>
#include <set>
#include <emerald-em.h>
#include <libemerald/Log.h>
#include <libemerald/Shuffler.h>
#include <libemerald/Pokemon.h>
#include <libemerald/Database.h>
#include <libemerald/Context.h>
#include <emerald/include/constants/offsets.h>

static const char* kLangs[] = {
    "en_US",
    "fr_FR",
};

bool Shuffler::run()
{
    const char* lang = kLangs[_ctx.cfg.lang];
    Log::info(_ctx, "Applying language %s", lang);
    if (!applyLang(lang))
        return false;

    Log::info(_ctx, "Shuffling");
    shuffle();

    return true;
}

bool Shuffler::applyLang(const char* lang)
{
    std::uint32_t count;
    std::uint32_t offset;
    std::uint32_t size;

    std::string langFileName;
    std::fstream file;

    langFileName = lang;
    langFileName.append(".bin");
    file.open(_ctx.dataPath + "/" + langFileName, std::ios::in | std::ios::binary);
    if (!file.good())
    {
        Log::error(_ctx, "Failed to open language file: %s", langFileName.c_str());
        return false;
    }

    /* Read count */
    file.read(reinterpret_cast<char*>(&count), sizeof(count));
    for (std::uint32_t i = 0; i < count; i++)
    {
        /* Apply */
        file.read(reinterpret_cast<char*>(&offset), sizeof(offset));
        file.read(reinterpret_cast<char*>(&size), sizeof(size));
        file.read((char*)_ctx.rom.ptr(offset), size);
    }

    return true;
}

static uint8_t fixLevel(uint8_t level)
{
    level += (level / 2);
    if (level > 100)
        level = 100;
    return level;
}

void Shuffler::shuffleWildList(uint32_t offset, int count)
{
    std::uint16_t tmp;
    std::uint16_t originalWilds[12];
    std::uint16_t replacedWilds[12];
    std::uint8_t minLevel;
    std::uint8_t maxLevel;
    int countOriginal = 0;
    int countReplaced = 0;
    bool match;

    /* Deref */
    if (!offset)
        return;
    offset = _ctx.rom.readU32(offset + 4);
    if (!offset)
        return;

    /* Scan for the original list */
    for (int i = 0; i < count; ++i)
    {
        match = false;
        tmp = _ctx.rom.readU16(offset + i * 4 + 2);
        for (int j = 0; j < countOriginal; ++j)
        {
            if (originalWilds[j] == tmp)
            {
                match = true;
                break;
            }
        }
        if (!match)
        {
            originalWilds[countOriginal++] = tmp;
        }
    }

    /* Build a custom list of replacement */
    for (int i = 0; i < countOriginal; ++i)
    {
        for (;;)
        {
            tmp = _ctx.pkmnGenerator.randPokemon(_ctx.rng);
            if (Pokemon::isLegendary(tmp))
                continue;
            match = false;
            for (int j = 0; j < countReplaced; ++j)
            {
                if (replacedWilds[j] == tmp)
                {
                    match = true;
                    break;
                }
            }
            if (!match)
            {
                replacedWilds[countReplaced++] = tmp;
                break;
            }
        }
    }

    /* Replace */
    for (int i = 0; i < count; ++i)
    {
        /* Patch the level */
        minLevel = _ctx.rom.readU8(offset + i * 4 + 0);
        maxLevel = _ctx.rom.readU8(offset + i * 4 + 1);

        minLevel = fixLevel(minLevel);
        maxLevel = fixLevel(maxLevel);

        _ctx.rom.writeU8(offset + i * 4 + 0, minLevel);
        _ctx.rom.writeU8(offset + i * 4 + 1, maxLevel);

        /* Patch the pokemon */
        tmp = _ctx.rom.readU16(offset + i * 4 + 2);
        for (int j = 0; j < countOriginal; ++j)
        {
            if (originalWilds[j] == tmp)
            {
                _ctx.rom.writeU16(offset + i * 4 + 2, replacedWilds[j]);
                break;
            }
        }
    }
}

void Shuffler::shuffleWild()
{
    uint32_t offset;
    uint32_t land;
    uint32_t water;
    uint32_t rock;
    uint32_t fish;

    offset = _ctx.rom.sym("gWildMonHeaders");
    for (int i = 0; i < 125; ++i)
    {
        land = _ctx.rom.readU32(offset + i * 20 + 4);
        water = _ctx.rom.readU32(offset + i * 20 + 8);
        rock = _ctx.rom.readU32(offset + i * 20 + 12);
        fish = _ctx.rom.readU32(offset + i * 20 + 16);

        shuffleWildList(land, 12);
        shuffleWildList(water, 5);
        shuffleWildList(rock, 5);
        shuffleWildList(fish, 10);
    }
}

void Shuffler::shuffleLearnset(uint32_t offset)
{
    std::vector<uint16_t> moves;
    std::vector<uint16_t> levels;
    std::map<int, int> aliases;
    std::set<uint16_t> uniqueMoves;
    int count;
    uint16_t move;
    uint16_t level;

    /* Load */
    count = 0;
    for (;;)
    {
        move = _ctx.rom.readU16(offset + count * 4 + 0);
        level = _ctx.rom.readU16(offset + count * 4 + 2);

        if (move == 0xffff)
            break;

        moves.push_back(move);
        levels.push_back(level);
        count++;
    }

    /* Check for level 0 aliases */
    for (int i = 0; i < count; ++i)
    {
        for (int j = i + 1; j < count; ++j)
        {
            if (levels[i] == 0 && levels[j] == 1 && moves[i] == moves[j])
            {
                aliases[i] = j;
                break;
            }
        }
    }

    /* Shuffle moves */
    for (int i = 0; i < count; ++i)
    {
        if (aliases.find(i) != aliases.end())
            continue;

        for (;;)
        {
            move = Pokemon::randMove(_ctx.rng);
            if (uniqueMoves.find(move) == uniqueMoves.end())
                break;
        }
        uniqueMoves.insert(move);
        moves[i] = move;
    }

    /* Resolve aliases */
    for (auto a : aliases)
        moves[a.first] = moves[a.second];

    /* Write */
    for (int i = 0; i < count; ++i)
        _ctx.rom.writeU16(offset + i * 4 + 0, moves[i]);
}

void Shuffler::shuffleLearnsets()
{
    std::set<uint32_t> offsets;
    uint32_t base;
    uint32_t tmp;

    base = _ctx.rom.sym("gSpeciesInfo");
    for (int i = 1; i < 1524; ++i)
    {
        tmp = _ctx.rom.readU32(base + DATA_SPECIES_SIZE * i + DATA_SPECIES_OFF_LEVELUP_LEARNSET);
        if (tmp)
            offsets.insert(tmp);
    }

    for (auto o : offsets)
    {
        shuffleLearnset(o);
    }
}

void shuffleGrowthRates(Database& db, Random& rand);
void shuffleStarters(Context& ctx);
void shuffleAbilities(Database& db, Random& rand);
void shuffleStats(Database& db, Random& rand);
void shuffleEvolutions(Context& ctx);
void shuffleTrainers(Context& ctx);
void shuffleTmHm(Database& db, Random& rand);
void shuffleItems(Database& db, Random& rand);

void Shuffler::shuffle()
{
    shuffleTmHm(_ctx.db, _ctx.rng);
    shuffleGrowthRates(_ctx.db, _ctx.rng);

    Log::info(_ctx, "Shuffling Stats");
    shuffleStats(_ctx.db, _ctx.rng);

    Log::info(_ctx, "Shuffling Abilities");
    shuffleAbilities(_ctx.db, _ctx.rng);

    Log::info(_ctx, "Shuffling Learnsets");
    shuffleLearnsets();

    Log::info(_ctx, "Shuffling Evolutions");
    shuffleEvolutions(_ctx);

    /* Shuffle starters */
    Log::info(_ctx, "Shuffling Starters");
    shuffleStarters(_ctx);

    /* Shuffle things */
    Log::info(_ctx, "Shuffling Wild Pokemons");
    shuffleWild();

    Log::info(_ctx, "Shuffling Trainers");
    shuffleTrainers(_ctx);

    /* Shuffle the random encounter */
    _ctx.rom.writeU16(_ctx.rom.sym("kFirstBattlePokemon"), _ctx.pkmnGenerator.randPokemon(_ctx.rng));

    /* Shuffle items */
    shuffleItems(_ctx.db, _ctx.rng);
}
