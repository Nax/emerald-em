#ifndef ROM_H
#define ROM_H

#include <cstdint>
#include <string>
#include <map>
#include <memory>

class Rom
{
public:
    uint32_t sym(const std::string& name) const;

    bool open(const std::string& path);
    bool loadSymbols(const std::string& path);
    bool save(const std::string& path) const;

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
    std::unique_ptr<std::uint8_t[]>         _data;
    std::map<std::string, std::uint32_t>    _symbols;
};

#endif
