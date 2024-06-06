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

    Random                                  _random;
    std::string                             _dataDir;
    std::unique_ptr<char[]>                 _rom;
    std::map<std::string, std::uint32_t>    _offsets;
};

#endif
