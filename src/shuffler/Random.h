#ifndef RANDOM_H
#define RANDOM_H

#include <cstdint>

class Random
{
public:
    Random();
    ~Random();

    void seed();
    std::uint32_t next();

private:
    std::uint32_t _state[5];
    std::uint32_t _counter;
};

#endif
