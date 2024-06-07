#include <unistd.h>
#include <cstdint>
#include <cstring>
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
}

void Shuffler::shuffle()
{
    std::uint16_t starters[3];

    /* Shuffle starters */
    for (int i = 0; i < 3; i++)
        starters[i] = Pokemon::randVisiblePokemon(_random);
    patchSymbol("kStarterMons", starters, sizeof(starters));
}
