#include <fstream>
#include <cstring>
#include <shuffler/Rom.h>

static uint32_t romAddr(uint32_t offset)
{
    return offset & 0x1ffffff;
}

uint32_t Rom::sym(const std::string& name) const
{
    auto it = _symbols.find(name);
    if (it == _symbols.end())
    {
        fprintf(stderr, "Symbol not found: %s\n", name.c_str());
        return 0xffffffff;
    }

    return it->second;
}

bool Rom::open(const std::string& path)
{
    std::fstream file;

    file.open(path, std::ios::in | std::ios::binary);
    if (!file.good())
        return false;
    _data = std::make_unique<uint8_t[]>(32 * 1024 * 1024);
    file.read(reinterpret_cast<char*>(_data.get()), 32 * 1024 * 1024);
    if (!file.good())
    {
        _data.reset();
        return false;
    }
    file.close();
    return true;
}

bool Rom::loadSymbols(const std::string& path)
{
    std::uint32_t count;
    std::uint32_t offset;
    std::uint32_t nameSize;
    std::string name;

    std::fstream file;

    file.open(path, std::ios::in | std::ios::binary);
    if (!file.good())
        return false;

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

        _symbols[name] = offset;
    }

    return true;
}

bool Rom::save(const std::string& path) const
{
    std::fstream file;

    file.open(path, std::ios::out | std::ios::binary);
    if (!file.good())
        return false;
    file.write(reinterpret_cast<const char*>(_data.get()), 32 * 1024 * 1024);
    if (!file.good())
        return false;
    file.close();
    return true;
}

void* Rom::ptr(uint32_t offset)
{
    return _data.get() + romAddr(offset);
}

void Rom::read(void* dst, uint32_t offset, size_t size) const
{
    memcpy(dst, _data.get() + romAddr(offset), size);
}

uint8_t Rom::readU8(uint32_t offset) const
{
    uint8_t tmp;

    read(&tmp, offset, sizeof(tmp));
    return tmp;
}

uint16_t Rom::readU16(uint32_t offset) const
{
    uint16_t tmp;

    read(&tmp, offset, sizeof(tmp));
    return tmp;
}

uint32_t Rom::readU32(uint32_t offset) const
{
    uint32_t tmp;

    read(&tmp, offset, sizeof(tmp));
    return tmp;
}

void Rom::write(uint32_t offset, const void* src, size_t size)
{
    memcpy(_data.get() + romAddr(offset), src, size);
}

void Rom::writeU8(uint32_t offset, uint8_t value)
{
    write(offset, &value, sizeof(value));
}

void Rom::writeU16(uint32_t offset, uint16_t value)
{
    write(offset, &value, sizeof(value));
}

void Rom::writeU32(uint32_t offset, uint32_t value)
{
    write(offset, &value, sizeof(value));
}
