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

    if (!loadRom())
        return 1;

    if (!loadOffsets())
        return 1;

    if (!applyLang("fr_FR"))
        return 1;

    _random.seed();
    shuffle();

    outFilename = out;
    outFilename.append("/emerald-em.gba");
    outFile = std::fstream(outFilename, std::ios::out | std::ios::binary);
    if (!outFile.good())
    {
        std::fprintf(stderr, "Failed to open output file: %s\n", outFilename.c_str());
        return 1;
    }

    outFile.write(_rom.get(), 32 * 1024 * 1024);

    return 0;
}

bool Shuffler::loadRom()
{
    std::fstream file;

    file = dataFile("rom.gba");
    if (!file.good())
    {
        std::fprintf(stderr, "Failed to open ROM\n");
        return false;
    }

    _rom = std::make_unique<char[]>(32 * 1024 * 1024);
    file.read(_rom.get(), 32 * 1024 * 1024);
    return true;
}

bool Shuffler::loadOffsets()
{
    std::uint32_t count;
    std::uint32_t offset;
    std::uint32_t nameSize;
    std::string name;

    std::fstream file;

    file = dataFile("offsets.bin");
    if (!file.good())
    {
        std::fprintf(stderr, "Failed to open offsets.bin\n");
        return false;
    }

    /* Read count */
    file.read(reinterpret_cast<char*>(&count), sizeof(count));
    for (std::uint32_t i = 0; i < count; i++)
    {
        /* Read offset */
        file.read(reinterpret_cast<char*>(&offset), sizeof(offset));

        /* Read name */
        file.read(reinterpret_cast<char*>(&nameSize), sizeof(nameSize));
        name.resize(nameSize);
        file.read(&name[0], nameSize);

        _offsets[name] = offset;
    }

    return true;
}

std::fstream Shuffler::dataFile(const std::string& name)
{
    std::string fname;
    std::fstream file;

    fname = _dataDir;
    fname.append("/");
    fname.append(name);

    file.open(fname, std::ios::in | std::ios::binary);
    return file;
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
    file = dataFile(langFileName);
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
        file.read(_rom.get() + offset, size);
    }

    return true;
}

void Shuffler::patchSymbol(const char* sym, const void* data, std::size_t size)
{
    std::uint32_t offset;

    offset = _offsets[sym];
    memcpy(_rom.get() + offset, data, size);
    printf("Patched %s at 0x%08X\n", sym, offset);
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
    offset = romRead<uint32_t>(offset + 4);
    if (!offset)
        return;

    /* Scan for the original list */
    for (int i = 0; i < count; ++i)
    {
        match = false;
        tmp = romRead<uint16_t>(offset + i * 4 + 2);
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
        tmp = romRead<uint16_t>(offset + i * 4 + 2);
        for (int j = 0; j < countOriginal; ++j)
        {
            if (originalWilds[j] == tmp)
            {
                romWrite<uint16_t>(offset + i * 4 + 2, replacedWilds[j]);
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

    offset = _offsets["gWildMonHeaders"];
    for (int i = 0; i < 125; ++i)
    {
        land = romRead<uint32_t>(offset + i * 20 + 4);
        water = romRead<uint32_t>(offset + i * 20 + 8);
        rock = romRead<uint32_t>(offset + i * 20 + 12);
        fish = romRead<uint32_t>(offset + i * 20 + 16);

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
        move = romRead<uint16_t>(offset + count * 4 + 0);
        level = romRead<uint16_t>(offset + count * 4 + 2);

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
        romWrite<uint16_t>(offset + i * 4 + 0, moves[i]);
}

void Shuffler::shuffleLearnsets()
{
    std::set<uint32_t> offsets;
    uint32_t base;
    uint32_t tmp;

    base = _offsets["gSpeciesInfo"];
    for (int i = 1; i < 1524; ++i)
    {
        tmp = romRead<uint32_t>(base + 0x94 * i + 0x80);
        if (tmp)
            offsets.insert(tmp);
    }

    for (auto o : offsets)
        shuffleLearnset(o);
}

void Shuffler::shuffle()
{
    std::uint16_t starters[3];
    std::uint16_t tmp;

    /* Shuffle starters */
    for (int i = 0; i < 3; i++)
        starters[i] = Pokemon::randPokemon(_random);
    patchSymbol("kStarterMons", starters, sizeof(starters));
    tmp = Pokemon::randPokemon(_random);
    patchSymbol("kFirstBattlePokemon", &tmp, sizeof(tmp));

    /* Shuffle things */
    shuffleWild();
    shuffleLearnsets();
}
