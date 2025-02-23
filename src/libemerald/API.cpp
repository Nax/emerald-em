#if defined(_WIN32)
# define WIN32_LEAN_AND_MEAN 1
# include <windows.h>
#else
# include <unistd.h>
#endif

#include <emerald-em.h>
#include <libemerald/Shuffler.h>
#include <libemerald/Context.h>
#include <libemerald/Database.h>

struct EmeraldGenerator
{
    Config cfg;
};

EMERALDEM_API EmeraldGenerator* EmCreate(void)
{
    return new EmeraldGenerator;
}

EMERALDEM_API void EmDestroy(EmeraldGenerator* emerald)
{
    delete emerald;
}

EMERALDEM_API void  EmSetCallbackLog(EmeraldGenerator* emerald, void (*cb)(void*, const char*), void* arg)
{
    Config& cfg = emerald->cfg;
    cfg.cbLog = cb;
    cfg.cbLogArg = arg;
}

EMERALDEM_API void  EmSetCallbackError(EmeraldGenerator* emerald, void (*cb)(void*, const char*), void* arg)
{
    Config& cfg = emerald->cfg;
    cfg.cbError = cb;
    cfg.cbErrorArg = arg;
}

static std::string dataPath()
{
    char tmp[2048];
    std::string dataDir;

#if defined(WIN32)
    /* Load the data dir name */
    if (GetModuleFileName(NULL, tmp, sizeof(tmp)) > 0)
    {
        dataDir = std::string(tmp);
        dataDir = dataDir.substr(0, dataDir.find_last_of('\\'));
    }
#else
    /* Load the data dir name */
    if (readlink("/proc/self/exe", tmp, sizeof(tmp)) > 0)
    {
        dataDir = std::string(tmp);
        dataDir = dataDir.substr(0, dataDir.find_last_of('/'));
    }
#endif
    dataDir.append("/data");
    return dataDir;
}

EMERALDEM_API int EmRun(EmeraldGenerator* emerald, const char* originalRom, const char* outputRom)
{
    Config& cfg = emerald->cfg;
    cfg.pathOriginalRom = originalRom;
    cfg.pathOutputRom = outputRom;

    Context ctx{cfg};
    /* Open the ROM */
    ctx.dataPath = dataPath();
    if (!ctx.rom.open())
        return 0;
    ctx.outRom.open(cfg.pathOutputRom + "/Emerald-EM-Seed.gba", std::ios::out | std::ios::binary);
    if (!ctx.outRom.good())
        return 0;
    ctx.rng.seed();
    databaseLoad(ctx.db, ctx.rom);
    Shuffler shuffler{ctx};
    if (!shuffler.run())
        return 0;
    databaseSave(ctx.rom, ctx.db);
    if (!ctx.rom.save(ctx.outRom))
        return 0;
    ctx.outRom.close();
    return 1;
}
