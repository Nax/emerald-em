#ifndef SHUFFLER_H
#define SHUFFLER_H

#include <shuffler/Random.h>
#include <shuffler/Rom.h>
#include <shuffler/Database.h>
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

    Rom& rom() { return _rom; }
    Random& random() { return _random; }
    int run(const std::string& out);

private:
    std::string  dataPath(const char* name);
    bool         applyLang(const char* lang);
    void         shuffle();
    void         shuffleWild();
    void         shuffleWildList(uint32_t offset, int count);
    void         shuffleLearnset(uint32_t offset);
    void         shuffleLearnsets();

    std::string     _dataDir;
    Random          _random;
    Rom             _rom;
    Database        _db;
};

#endif
