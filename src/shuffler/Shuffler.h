#ifndef SHUFFLER_H
#define SHUFFLER_H

#include <shuffler/Random.h>
#include <string>
#include <fstream>
#include <memory>
#include <map>
#include <cstdint>

class Shuffler
{
public:
    Shuffler();
    ~Shuffler();

    int run(const std::string& out);

private:
    std::fstream dataFile(const std::string& name);
    bool         applyLang(const char* lang);
    bool         loadRom();
    bool         loadOffsets();
    void         patchSymbol(const char* sym, const void* data, std::size_t size);
    void         shuffle();
    void         shuffleWild();
    void         shuffleWildList(uint32_t offset, int count);
    void         shuffleLearnset(uint32_t offset);
    void         shuffleLearnsets();

    template <typename T> T romRead(uint32_t offset) { return *reinterpret_cast<T*>(_rom.get() + (offset & 0x1ffffff)); }
    template <typename T> void romWrite(uint32_t offset, T value) { *reinterpret_cast<T*>(_rom.get() + (offset & 0x1ffffff)) = value; }

    Random                                  _random;
    std::string                             _dataDir;
    std::unique_ptr<char[]>                 _rom;
    std::map<std::string, std::uint32_t>    _offsets;
};

#endif
