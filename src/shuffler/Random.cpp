#include <fstream>
#include <shuffler/Random.h>

Random::Random()
: _state{}
, _counter{}
{
}

Random::~Random()
{
}

void Random::seed()
{
    std::fstream file;

    file.open("/dev/urandom", std::ios::in | std::ios::binary);
    if (!file.good())
    {
        std::fprintf(stderr, "Failed to open /dev/urandom\n");
        return;
    }

    file.read(reinterpret_cast<char*>(_state), sizeof(_state));
    _counter = 0;
}

std::uint32_t Random::next()
{
    std::uint32_t t;
    std::uint32_t s;

    t = _state[4];
    s = _state[0];
    _state[4] = _state[3];
    _state[3] = _state[2];
    _state[2] = _state[1];
    _state[1] = s;

    t = ((t >> 2) ^ t);
    t = ((t << 1) ^ t);
    t = (((s << 4) ^ s) ^ t);
    _state[0] = t;
    _counter = (_counter + 362437);
    return (t + _counter);
}


uint32_t randInt(Random& rng, uint32_t max)
{
    uint32_t mask;
    uint32_t value;

    if (max == 0 || max == 1)
        return 0;

    /* Build the mask */
    mask = max - 1;
    mask |= mask >> 1;
    mask |= mask >> 2;
    mask |= mask >> 4;
    mask |= mask >> 8;
    mask |= mask >> 16;

    for (;;)
    {
        value = rng.next() & mask;
        if (value < max)
            return value;
    }
}
