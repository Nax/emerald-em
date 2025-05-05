#include <fstream>
#include <cstring>
#include <libemerald/Rom.h>
#include <libemerald/Context.h>
#include <libemerald/Log.h>

uint32_t crc32(const void *data, size_t len)
{
    int k;
    uint32_t crc;
    const uint8_t* data8 = static_cast<const uint8_t*>(data);

    crc = 0xffffffff;
    while (len--) {
        crc ^= *data8++;
        for (k = 0; k < 8; k++)
            crc = crc & 1 ? (crc >> 1) ^ 0xedb88320 : crc >> 1;
    }
    return ~crc;
}
static uint32_t romAddr(uint32_t offset)
{
    return offset & 0x1ffffff;
}

Rom::Rom(Context& ctx)
: _ctx{ctx}
{
}

uint32_t Rom::sym(const std::string& name) const
{
    auto it = _symbols.find(name);
    if (it == _symbols.end())
    {
        Log::error(_ctx, "Symbol not found: %s", name.c_str());
        return 0xffffffff;
    }

    return it->second;
}

bool Rom::open()
{
    if (!openDelta())
    {
        Log::error(_ctx, "Failed to open delta");
        return false;
    }

    if (!loadSymbols())
    {
        Log::error(_ctx, "Failed to open symbols");
        return false;
    }

    return true;
}

bool Rom::save(std::ofstream& file) const
{
    file.write(reinterpret_cast<const char*>(_data.get()), 32 * 1024 * 1024);
    if (!file.good())
        return false;
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

bool Rom::openDelta()
{
    uint32_t crc;
    auto originalData = std::make_unique<std::uint8_t[]>(16 * 1024 * 1024);
    auto newData = std::make_unique<std::uint8_t[]>(32 * 1024 * 1024);

    std::fstream file;
    file.open(_ctx.cfg.pathOriginalRom, std::ios::in | std::ios::binary);
    if (!file.good())
    {
        Log::error(_ctx, "Failed to open original ROM: %s", _ctx.cfg.pathOriginalRom.c_str());
        return false;
    }
    file.read(reinterpret_cast<char*>(originalData.get()), 16 * 1024 * 1024);
    if (!file.good())
    {
        Log::error(_ctx, "Failed to read original ROM");
        return false;
    }
    file.close();
    crc = crc32(originalData.get(), 16 * 1024 * 1024);
    if (crc != 0x1F1C08FB)
    {
        Log::error(_ctx, "Invalid CRC-32 for original ROM: 0x%08X", crc);
        return false;
    }

    file.open(_ctx.dataPath + "/delta.bin", std::ios::in | std::ios::binary);
    if (!file.good())
        return false;
    file.read(reinterpret_cast<char*>(newData.get()), 32 * 1024 * 1024);
    if (!file.good())
        return false;
    file.close();

    for (std::uint32_t i = 0; i < 32 * 1024 * 1024; i++)
        newData[i] ^= originalData[i % (16 * 1024 * 1024)];

    _data = std::move(newData);
    return true;
}

bool Rom::loadSymbols()
{
    std::uint32_t count;
    std::uint32_t offset;
    std::uint32_t nameSize;
    std::string name;

    std::fstream file;

    file.open(_ctx.dataPath + "/offsets.bin", std::ios::in | std::ios::binary);
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
