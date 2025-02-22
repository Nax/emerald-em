#ifndef ROM_H
#define ROM_H

#include <cstdint>
#include <string>
#include <map>
#include <memory>

struct Context;
class Rom
{
public:
    Rom(Context& ctx);

    uint32_t sym(const std::string& name) const;

    bool open();
    bool save(std::ofstream& file) const;

    void* ptr(uint32_t offset);

    void        read(void* dst, uint32_t offset, size_t size) const;
    uint8_t     readU8(uint32_t offset) const;
    uint16_t    readU16(uint32_t offset) const;
    uint32_t    readU32(uint32_t offset) const;

    void write(uint32_t offset, const void* src, size_t size);
    void writeU8(uint32_t offset, uint8_t value);
    void writeU16(uint32_t offset, uint16_t value);
    void writeU32(uint32_t offset, uint32_t value);

private:
    bool openDelta();
    bool loadSymbols();

    Context&                                _ctx;
    std::unique_ptr<std::uint8_t[]>         _data;
    std::map<std::string, std::uint32_t>    _symbols;
};

#endif
