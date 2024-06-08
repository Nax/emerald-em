#include <unistd.h>
#include <cstdint>
#include <cstring>
#include <vector>
#include <set>
#include <shuffler/Shuffler.h>
#include <shuffler/Pokemon.h>

Shuffler::Shuffler()
{
    char tmp[2048];

    /* Load the data dir name */
    if (readlink("/proc/self/exe", tmp, sizeof(tmp)) > 0)
    {
        _dataDir = std::string(tmp);
        _dataDir = _dataDir.substr(0, _dataDir.find_last_of('/'));
    }
    _dataDir.append("/data");
}

Shuffler::~Shuffler()
{
}

int Shuffler::run(const std::string& out)
{
    std::string outFilename;
    std::fstream outFile;

    if (!_rom.open(dataPath("rom.gba")))
    {
        std::fprintf(stderr, "Failed to open ROM\n");
        return 1;
    }

    if (!_rom.loadSymbols(dataPath("offsets.bin")))
    {
        std::fprintf(stderr, "Failed to open offsets.bin\n");
        return 1;
    }

    if (!applyLang("fr_FR"))
        return 1;

    _random.seed();
    shuffle();

    outFilename = out;
    outFilename.append("/emerald-em.gba");
    if (!_rom.save(outFilename))
    {
        std::fprintf(stderr, "Failed to save ROM\n");
        return 1;
    }

    return 0;
}

std::string Shuffler::dataPath(const char* name)
{
    std::string fname;

    fname = _dataDir;
    fname.append("/");
    fname.append(name);

    return fname;
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
    file.open(dataPath(langFileName.c_str()), std::ios::in | std::ios::binary);
    if (!file.good())
    {
        std::fprintf(stderr, "Failed to open language file: %s\n", langFileName.c_str());
        return false;
    }

    /* Read count */
    file.read(reinterpret_cast<char*>(&count), sizeof(count));
    for (std::uint32_t i = 0; i < count; i++)
    {
        /* Apply */
        file.read(reinterpret_cast<char*>(&offset), sizeof(offset));
        file.read(reinterpret_cast<char*>(&size), sizeof(size));
        file.read((char*)_rom.ptr(offset), size);
    }

    return true;
}

void Shuffler::shuffleWildList(uint32_t offset, int count)
{
    std::uint16_t tmp;
    std::uint16_t originalWilds[12];
    std::uint16_t replacedWilds[12];
    int countOriginal = 0;
    int countReplaced = 0;
    bool match;

    /* Deref */
    if (!offset)
        return;
    offset = _rom.readU32(offset + 4);
    if (!offset)
        return;

    /* Scan for the original list */
    for (int i = 0; i < count; ++i)
    {
        match = false;
        tmp = _rom.readU16(offset + i * 4 + 2);
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
            tmp = Pokemon::randPokemon(_random);
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
        tmp = _rom.readU16(offset + i * 4 + 2);
        for (int j = 0; j < countOriginal; ++j)
        {
            if (originalWilds[j] == tmp)
            {
                _rom.writeU16(offset + i * 4 + 2, replacedWilds[j]);
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

    offset = _rom.sym("gWildMonHeaders");
    for (int i = 0; i < 125; ++i)
    {
        land = _rom.readU32(offset + i * 20 + 4);
        water = _rom.readU32(offset + i * 20 + 8);
        rock = _rom.readU32(offset + i * 20 + 12);
        fish = _rom.readU32(offset + i * 20 + 16);

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
        move = _rom.readU16(offset + count * 4 + 0);
        level = _rom.readU16(offset + count * 4 + 2);

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
            move = Pokemon::randMove(_random);
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
        _rom.writeU16(offset + i * 4 + 0, moves[i]);
}

void Shuffler::shuffleLearnsets()
{
    std::set<uint32_t> offsets;
    uint32_t base;
    uint32_t tmp;

    base = _rom.sym("gSpeciesInfo");
    for (int i = 1; i < 1524; ++i)
    {
        tmp = _rom.readU32(base + 0x94 * i + 0x80);
        if (tmp)
            offsets.insert(tmp);
    }

    for (auto o : offsets)
        shuffleLearnset(o);
}

void shuffleAbilities(Shuffler& shuffler);
void shuffleStats(Shuffler& shuffler);

void Shuffler::shuffle()
{
    std::uint16_t starters[3];
    std::uint16_t tmp;

    /* Shuffle starters */
    for (int i = 0; i < 3; i++)
        starters[i] = Pokemon::randPokemon(_random);
    _rom.write(_rom.sym("kStarterMons"), starters, sizeof(starters));
    _rom.writeU16(_rom.sym("kFirstBattlePokemon"), Pokemon::randPokemon(_random));

    /* Shuffle things */
    shuffleWild();
    shuffleLearnsets();
    shuffleAbilities(*this);
    shuffleStats(*this);
}
