#include <set>
#include <emerald/include/constants/items.h>
#include "Database.h"
#include "Rom.h"
#include "Random.h"
#include "Pokemon.h"

static bool isItemTMHM(uint16_t itemId)
{
    return itemId >= ITEM_TM01 && itemId <= ITEM_HM08;
}

static bool isItemUnshufflable(uint16_t itemId)
{
    switch (itemId)
    {
    case ITEM_NONE:
    case ITEM_SCANNER:
    case ITEM_STORAGE_KEY:
        return true;
    }

    return false;
}

static bool isItemSingle(uint16_t itemId)
{
    if (isItemTMHM(itemId))
        return true;

    switch (itemId)
    {
    case ITEM_FLAME_PLATE:
    case ITEM_SPLASH_PLATE:
    case ITEM_ZAP_PLATE:
    case ITEM_MEADOW_PLATE:
    case ITEM_ICICLE_PLATE:
    case ITEM_FIST_PLATE:
    case ITEM_TOXIC_PLATE:
    case ITEM_EARTH_PLATE:
    case ITEM_SKY_PLATE:
    case ITEM_MIND_PLATE:
    case ITEM_INSECT_PLATE:
    case ITEM_STONE_PLATE:
    case ITEM_SPOOKY_PLATE:
    case ITEM_DRACO_PLATE:
    case ITEM_DREAD_PLATE:
    case ITEM_IRON_PLATE:
    case ITEM_PIXIE_PLATE:
    case ITEM_VENUSAURITE:
    case ITEM_CHARIZARDITE_X:
    case ITEM_CHARIZARDITE_Y:
    case ITEM_BLASTOISINITE:
    case ITEM_BEEDRILLITE:
    case ITEM_PIDGEOTITE:
    case ITEM_ALAKAZITE:
    case ITEM_SLOWBRONITE:
    case ITEM_GENGARITE:
    case ITEM_KANGASKHANITE:
    case ITEM_PINSIRITE:
    case ITEM_GYARADOSITE:
    case ITEM_AERODACTYLITE:
    case ITEM_MEWTWONITE_X:
    case ITEM_MEWTWONITE_Y:
    case ITEM_AMPHAROSITE:
    case ITEM_STEELIXITE:
    case ITEM_SCIZORITE:
    case ITEM_HERACRONITE:
    case ITEM_HOUNDOOMINITE:
    case ITEM_TYRANITARITE:
    case ITEM_SCEPTILITE:
    case ITEM_BLAZIKENITE:
    case ITEM_SWAMPERTITE:
    case ITEM_GARDEVOIRITE:
    case ITEM_SABLENITE:
    case ITEM_MAWILITE:
    case ITEM_AGGRONITE:
    case ITEM_MEDICHAMITE:
    case ITEM_MANECTITE:
    case ITEM_SHARPEDONITE:
    case ITEM_CAMERUPTITE:
    case ITEM_ALTARIANITE:
    case ITEM_BANETTITE:
    case ITEM_ABSOLITE:
    case ITEM_GLALITITE:
    case ITEM_SALAMENCITE:
    case ITEM_METAGROSSITE:
    case ITEM_LATIASITE:
    case ITEM_LATIOSITE:
    case ITEM_LOPUNNITE:
    case ITEM_GARCHOMPITE:
    case ITEM_LUCARIONITE:
    case ITEM_ABOMASITE:
    case ITEM_GALLADITE:
    case ITEM_AUDINITE:
    case ITEM_DIANCITE:
    case ITEM_NORMALIUM_Z:
    case ITEM_FIRIUM_Z:
    case ITEM_WATERIUM_Z:
    case ITEM_ELECTRIUM_Z:
    case ITEM_GRASSIUM_Z:
    case ITEM_ICIUM_Z:
    case ITEM_FIGHTINIUM_Z:
    case ITEM_POISONIUM_Z:
    case ITEM_GROUNDIUM_Z:
    case ITEM_FLYINIUM_Z:
    case ITEM_PSYCHIUM_Z:
    case ITEM_BUGINIUM_Z:
    case ITEM_ROCKIUM_Z:
    case ITEM_GHOSTIUM_Z:
    case ITEM_DRAGONIUM_Z:
    case ITEM_DARKINIUM_Z:
    case ITEM_STEELIUM_Z:
    case ITEM_FAIRIUM_Z:
    case ITEM_PIKANIUM_Z:
    case ITEM_EEVIUM_Z:
    case ITEM_SNORLIUM_Z:
    case ITEM_MEWNIUM_Z:
    case ITEM_DECIDIUM_Z:
    case ITEM_INCINIUM_Z:
    case ITEM_PRIMARIUM_Z:
    case ITEM_LYCANIUM_Z:
    case ITEM_MIMIKIUM_Z:
    case ITEM_KOMMONIUM_Z:
    case ITEM_TAPUNIUM_Z:
    case ITEM_SOLGANIUM_Z:
    case ITEM_LUNALIUM_Z:
    case ITEM_MARSHADIUM_Z:
    case ITEM_ALORAICHIUM_Z:
    case ITEM_PIKASHUNIUM_Z:
    case ITEM_ULTRANECROZIUM_Z:
        return true;
    }

    return false;
}

static void shuffleOneItem(uint16_t* inOut, std::set<std::uint16_t>& list, Random& rng)
{
    uint16_t itemId;
    uint16_t tmp;

    itemId = *inOut;
    if (isItemUnshufflable(itemId))
        return;

retry:
    if (isItemTMHM(itemId))
        tmp = Pokemon::randItemTmHm(rng);
    else
        tmp = Pokemon::randItemGeneric(rng);
    if (isItemSingle(tmp))
    {
        if (list.find(tmp) != list.end())
            goto retry;
        list.insert(tmp);
    }

    *inOut = tmp;
}

static void shuffleItemVector(std::vector<uint16_t>& vec, Random& rng, std::set<std::uint16_t>& list)
{
    for (auto& item : vec)
        shuffleOneItem(&item, list, rng);
}

void shuffleItems(Database& db, Random& rand)
{
    std::set<std::uint16_t> list;

    /* TODO - randomize the iteration order */
    shuffleItemVector(db.misc.itemsBalls, rand, list);
    shuffleItemVector(db.misc.itemsGiven, rand, list);
}
