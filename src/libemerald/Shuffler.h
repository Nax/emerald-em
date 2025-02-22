#ifndef SHUFFLER_H
#define SHUFFLER_H

#include <libemerald/Random.h>
#include <libemerald/Rom.h>
#include <libemerald/Database.h>
#include <string>
#include <fstream>
#include <memory>
#include <map>
#include <cstdint>

struct Context;
class Shuffler
{
public:
    Shuffler(Context& ctx) : _ctx{ctx} {}

    bool run();

private:
    bool         applyLang(const char* lang);
    void         shuffle();
    void         shuffleWild();
    void         shuffleWildList(uint32_t offset, int count);
    void         shuffleLearnset(uint32_t offset);
    void         shuffleLearnsets();

    Context&        _ctx;
};

#endif
