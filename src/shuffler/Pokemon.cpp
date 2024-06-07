#include <shuffler/Random.h>
#include <shuffler/Pokemon.h>
#include "../../emerald/include/constants/species.h"

#define ARRAY_SIZE(n)   (sizeof((n)) / sizeof((n)[0]))
#define SAMPLE(rng, x)  (sample((rng), (x), ARRAY_SIZE((x))))

static std::uint32_t randInt(Random& rng, std::uint32_t max)
{
    std::uint32_t mask;
    std::uint32_t value;

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

template <typename T>
static T sample(Random& rng, const T* array, std::size_t size)
{
    std::size_t index;

    index = randInt(rng, size);
    return array[index];
}

static const std::uint16_t kFormsTaurosPaldea[] = {
    SPECIES_TAUROS_PALDEAN_COMBAT_BREED,
    SPECIES_TAUROS_PALDEAN_BLAZE_BREED,
    SPECIES_TAUROS_PALDEAN_AQUA_BREED,
};

static const uint16_t kFormsUnown[] = {
    SPECIES_UNOWN_A,
    SPECIES_UNOWN_B,
    SPECIES_UNOWN_C,
    SPECIES_UNOWN_D,
    SPECIES_UNOWN_E,
    SPECIES_UNOWN_F,
    SPECIES_UNOWN_G,
    SPECIES_UNOWN_H,
    SPECIES_UNOWN_I,
    SPECIES_UNOWN_J,
    SPECIES_UNOWN_K,
    SPECIES_UNOWN_L,
    SPECIES_UNOWN_M,
    SPECIES_UNOWN_N,
    SPECIES_UNOWN_O,
    SPECIES_UNOWN_P,
    SPECIES_UNOWN_Q,
    SPECIES_UNOWN_R,
    SPECIES_UNOWN_S,
    SPECIES_UNOWN_T,
    SPECIES_UNOWN_U,
    SPECIES_UNOWN_V,
    SPECIES_UNOWN_W,
    SPECIES_UNOWN_X,
    SPECIES_UNOWN_Y,
    SPECIES_UNOWN_Z,
    SPECIES_UNOWN_EMARK,
    SPECIES_UNOWN_QMARK,
};

static const uint16_t kFormsDeoxys[] = {
    SPECIES_DEOXYS_NORMAL,
    SPECIES_DEOXYS_ATTACK,
    SPECIES_DEOXYS_DEFENSE,
    SPECIES_DEOXYS_SPEED,
};

static const uint16_t kFormsBurmy[] = {
    SPECIES_BURMY_PLANT_CLOAK,
    SPECIES_BURMY_SANDY_CLOAK,
    SPECIES_BURMY_TRASH_CLOAK,
};

static const uint16_t kFormsWormadam[] = {
    SPECIES_WORMADAM_PLANT_CLOAK,
    SPECIES_WORMADAM_SANDY_CLOAK,
    SPECIES_WORMADAM_TRASH_CLOAK,
};

static const uint16_t kFormsShellos[] = {
    SPECIES_SHELLOS_WEST_SEA,
    SPECIES_SHELLOS_EAST_SEA,
};

static const uint16_t kFormsGastrodon[] = {
    SPECIES_GASTRODON_WEST_SEA,
    SPECIES_GASTRODON_EAST_SEA,
};

static const uint16_t kFormsRotom[] = {
    SPECIES_ROTOM,
    SPECIES_ROTOM_HEAT,
    SPECIES_ROTOM_WASH,
    SPECIES_ROTOM_FROST,
    SPECIES_ROTOM_FAN,
    SPECIES_ROTOM_MOW,
};

static const uint16_t kFormsShaymin[] = {
    SPECIES_SHAYMIN_LAND,
    SPECIES_SHAYMIN_SKY,
};

static const uint16_t kFormsBasculin[] = {
    SPECIES_BASCULIN_RED_STRIPED,
    SPECIES_BASCULIN_BLUE_STRIPED,
    SPECIES_BASCULIN_WHITE_STRIPED,
};

static const uint16_t kFormsBasculegion[] = {
    SPECIES_BASCULEGION_MALE,
    SPECIES_BASCULEGION_FEMALE,
};

static const uint16_t kFormsDarmanitan[] = {
    SPECIES_DARMANITAN_STANDARD_MODE,
    SPECIES_DARMANITAN_ZEN_MODE,
};

static const uint16_t kFormsDeerling[] = {
    SPECIES_DEERLING_SPRING,
    SPECIES_DEERLING_SUMMER,
    SPECIES_DEERLING_AUTUMN,
    SPECIES_DEERLING_WINTER,
};

static const uint16_t kFormsSawsbuck[] = {
    SPECIES_SAWSBUCK_SPRING,
    SPECIES_SAWSBUCK_SUMMER,
    SPECIES_SAWSBUCK_AUTUMN,
    SPECIES_SAWSBUCK_WINTER,
};

static const uint16_t kFormsTornadus[] = {
    SPECIES_TORNADUS_INCARNATE,
    SPECIES_TORNADUS_THERIAN,
};

static const uint16_t kFormsThundurus[] = {
    SPECIES_THUNDURUS_INCARNATE,
    SPECIES_THUNDURUS_THERIAN,
};

static const uint16_t kFormsLandorus[] = {
    SPECIES_LANDORUS_INCARNATE,
    SPECIES_LANDORUS_THERIAN,
};

static const uint16_t kFormsEnamorus[] = {
    SPECIES_ENAMORUS_INCARNATE,
    SPECIES_ENAMORUS_THERIAN,
};

static const uint16_t kFormsGreninja[] = {
    SPECIES_GRENINJA,
    SPECIES_GRENINJA_ASH,
};

static const uint16_t kFormsVivillion[] = {
    SPECIES_VIVILLON_MEADOW,
    SPECIES_VIVILLON_ARCHIPELAGO,
    SPECIES_VIVILLON_CONTINENTAL,
    SPECIES_VIVILLON_ELEGANT,
    SPECIES_VIVILLON_GARDEN,
    SPECIES_VIVILLON_HIGH_PLAINS,
    SPECIES_VIVILLON_ICY_SNOW,
    SPECIES_VIVILLON_JUNGLE,
    SPECIES_VIVILLON_MARINE,
    SPECIES_VIVILLON_MODERN,
    SPECIES_VIVILLON_MONSOON,
    SPECIES_VIVILLON_OCEAN,
    SPECIES_VIVILLON_POLAR,
    SPECIES_VIVILLON_RIVER,
    SPECIES_VIVILLON_SANDSTORM,
    SPECIES_VIVILLON_SAVANNA,
    SPECIES_VIVILLON_SUN,
    SPECIES_VIVILLON_TUNDRA,
    SPECIES_VIVILLON_POKE_BALL,
    SPECIES_VIVILLON_FANCY,
};

static const std::uint16_t kFormsFlabebe[] = {
    SPECIES_FLABEBE_RED_FLOWER,
    SPECIES_FLABEBE_YELLOW_FLOWER,
    SPECIES_FLABEBE_ORANGE_FLOWER,
    SPECIES_FLABEBE_BLUE_FLOWER,
    SPECIES_FLABEBE_WHITE_FLOWER,
};

static const std::uint16_t kFormsFloette[] = {
    SPECIES_FLOETTE_RED_FLOWER,
    SPECIES_FLOETTE_YELLOW_FLOWER,
    SPECIES_FLOETTE_ORANGE_FLOWER,
    SPECIES_FLOETTE_BLUE_FLOWER,
    SPECIES_FLOETTE_WHITE_FLOWER,
};

static const std::uint16_t kFormsFlorges[] = {
    SPECIES_FLORGES_RED_FLOWER,
    SPECIES_FLORGES_YELLOW_FLOWER,
    SPECIES_FLORGES_ORANGE_FLOWER,
    SPECIES_FLORGES_BLUE_FLOWER,
    SPECIES_FLORGES_WHITE_FLOWER,
};

static const std::uint16_t kFormsFurfrou[] = {
    SPECIES_FURFROU_NATURAL,
    SPECIES_FURFROU_HEART_TRIM,
    SPECIES_FURFROU_DIAMOND_TRIM,
    SPECIES_FURFROU_STAR_TRIM,
    SPECIES_FURFROU_PHARAOH_TRIM,
    SPECIES_FURFROU_KABUKI_TRIM,
    SPECIES_FURFROU_LA_REINE_TRIM,
    SPECIES_FURFROU_MATRON_TRIM,
    SPECIES_FURFROU_DANDY_TRIM,
    SPECIES_FURFROU_DEBUTANTE_TRIM,
};

static const std::uint16_t kFormsMeowstic[] = {
    SPECIES_MEOWSTIC_MALE,
    SPECIES_MEOWSTIC_FEMALE,
};

static const std::uint16_t kFormsPumpkaboo[] = {
    SPECIES_PUMPKABOO_AVERAGE,
    SPECIES_PUMPKABOO_SMALL,
    SPECIES_PUMPKABOO_LARGE,
    SPECIES_PUMPKABOO_SUPER,
};

static const std::uint16_t kFormsGourgeist[] = {
    SPECIES_GOURGEIST_AVERAGE,
    SPECIES_GOURGEIST_SMALL,
    SPECIES_GOURGEIST_LARGE,
    SPECIES_GOURGEIST_SUPER,
};

/* We only use that Zygarde */
static const std::uint16_t kFormsZygarde[] = {
    SPECIES_ZYGARDE_10_POWER_CONSTRUCT,
    SPECIES_ZYGARDE_50_POWER_CONSTRUCT,
};

static const std::uint16_t kFormsHoopa[] = {
    SPECIES_HOOPA_CONFINED,
    SPECIES_HOOPA_UNBOUND,
};

static const std::uint16_t kFormsOricorio[] = {
    SPECIES_ORICORIO_BAILE,
    SPECIES_ORICORIO_POM_POM,
    SPECIES_ORICORIO_PAU,
    SPECIES_ORICORIO_SENSU,
};

static const std::uint16_t kFormsLycanroc[] = {
    SPECIES_LYCANROC_MIDDAY,
    SPECIES_LYCANROC_MIDNIGHT,
    SPECIES_LYCANROC_DUSK,
};

static const std::uint16_t kFormsMinior[] = {
    SPECIES_MINIOR_RED,
    SPECIES_MINIOR_ORANGE,
    SPECIES_MINIOR_YELLOW,
    SPECIES_MINIOR_GREEN,
    SPECIES_MINIOR_BLUE,
    SPECIES_MINIOR_INDIGO,
    SPECIES_MINIOR_VIOLET
};

static const std::uint16_t kFormsMagearna[] = {
    SPECIES_MAGEARNA,
    SPECIES_MAGEARNA_ORIGINAL_COLOR,
};

static const std::uint16_t kFormsToxtricity[] = {
    SPECIES_TOXTRICITY_AMPED,
    SPECIES_TOXTRICITY_LOW_KEY,
};

static const std::uint16_t kFormsSinistea[] = {
    SPECIES_SINISTEA_PHONY,
    SPECIES_SINISTEA_ANTIQUE,
};

static const std::uint16_t kFormsPolteageist[] = {
    SPECIES_POLTEAGEIST_PHONY,
    SPECIES_POLTEAGEIST_ANTIQUE,
};

static const std::uint16_t kFormsAlcremie[] = {
    SPECIES_ALCREMIE_STRAWBERRY_VANILLA_CREAM,
    SPECIES_ALCREMIE_STRAWBERRY_RUBY_CREAM,
    SPECIES_ALCREMIE_STRAWBERRY_MATCHA_CREAM,
    SPECIES_ALCREMIE_STRAWBERRY_MINT_CREAM,
    SPECIES_ALCREMIE_STRAWBERRY_LEMON_CREAM,
    SPECIES_ALCREMIE_STRAWBERRY_SALTED_CREAM,
    SPECIES_ALCREMIE_STRAWBERRY_RUBY_SWIRL,
    SPECIES_ALCREMIE_STRAWBERRY_CARAMEL_SWIRL,
    SPECIES_ALCREMIE_STRAWBERRY_RAINBOW_SWIRL,
    SPECIES_ALCREMIE_BERRY_VANILLA_CREAM,
    SPECIES_ALCREMIE_BERRY_RUBY_CREAM,
    SPECIES_ALCREMIE_BERRY_MATCHA_CREAM,
    SPECIES_ALCREMIE_BERRY_MINT_CREAM,
    SPECIES_ALCREMIE_BERRY_LEMON_CREAM,
    SPECIES_ALCREMIE_BERRY_SALTED_CREAM,
    SPECIES_ALCREMIE_BERRY_RUBY_SWIRL,
    SPECIES_ALCREMIE_BERRY_CARAMEL_SWIRL,
    SPECIES_ALCREMIE_BERRY_RAINBOW_SWIRL,
    SPECIES_ALCREMIE_LOVE_VANILLA_CREAM,
    SPECIES_ALCREMIE_LOVE_RUBY_CREAM,
    SPECIES_ALCREMIE_LOVE_MATCHA_CREAM,
    SPECIES_ALCREMIE_LOVE_MINT_CREAM,
    SPECIES_ALCREMIE_LOVE_LEMON_CREAM,
    SPECIES_ALCREMIE_LOVE_SALTED_CREAM,
    SPECIES_ALCREMIE_LOVE_RUBY_SWIRL,
    SPECIES_ALCREMIE_LOVE_CARAMEL_SWIRL,
    SPECIES_ALCREMIE_LOVE_RAINBOW_SWIRL,
    SPECIES_ALCREMIE_STAR_VANILLA_CREAM,
    SPECIES_ALCREMIE_STAR_RUBY_CREAM,
    SPECIES_ALCREMIE_STAR_MATCHA_CREAM,
    SPECIES_ALCREMIE_STAR_MINT_CREAM,
    SPECIES_ALCREMIE_STAR_LEMON_CREAM,
    SPECIES_ALCREMIE_STAR_SALTED_CREAM,
    SPECIES_ALCREMIE_STAR_RUBY_SWIRL,
    SPECIES_ALCREMIE_STAR_CARAMEL_SWIRL,
    SPECIES_ALCREMIE_STAR_RAINBOW_SWIRL,
    SPECIES_ALCREMIE_CLOVER_VANILLA_CREAM,
    SPECIES_ALCREMIE_CLOVER_RUBY_CREAM,
    SPECIES_ALCREMIE_CLOVER_MATCHA_CREAM,
    SPECIES_ALCREMIE_CLOVER_MINT_CREAM,
    SPECIES_ALCREMIE_CLOVER_LEMON_CREAM,
    SPECIES_ALCREMIE_CLOVER_SALTED_CREAM,
    SPECIES_ALCREMIE_CLOVER_RUBY_SWIRL,
    SPECIES_ALCREMIE_CLOVER_CARAMEL_SWIRL,
    SPECIES_ALCREMIE_CLOVER_RAINBOW_SWIRL,
    SPECIES_ALCREMIE_FLOWER_VANILLA_CREAM,
    SPECIES_ALCREMIE_FLOWER_RUBY_CREAM,
    SPECIES_ALCREMIE_FLOWER_MATCHA_CREAM,
    SPECIES_ALCREMIE_FLOWER_MINT_CREAM,
    SPECIES_ALCREMIE_FLOWER_LEMON_CREAM,
    SPECIES_ALCREMIE_FLOWER_SALTED_CREAM,
    SPECIES_ALCREMIE_FLOWER_RUBY_SWIRL,
    SPECIES_ALCREMIE_FLOWER_CARAMEL_SWIRL,
    SPECIES_ALCREMIE_FLOWER_RAINBOW_SWIRL,
    SPECIES_ALCREMIE_RIBBON_VANILLA_CREAM,
    SPECIES_ALCREMIE_RIBBON_RUBY_CREAM,
    SPECIES_ALCREMIE_RIBBON_MATCHA_CREAM,
    SPECIES_ALCREMIE_RIBBON_MINT_CREAM,
    SPECIES_ALCREMIE_RIBBON_LEMON_CREAM,
    SPECIES_ALCREMIE_RIBBON_SALTED_CREAM,
    SPECIES_ALCREMIE_RIBBON_RUBY_SWIRL,
    SPECIES_ALCREMIE_RIBBON_CARAMEL_SWIRL,
    SPECIES_ALCREMIE_RIBBON_RAINBOW_SWIRL,
};

static const std::uint16_t kFormsIndeedee[] = {
    SPECIES_INDEEDEE_MALE,
    SPECIES_INDEEDEE_FEMALE,
};

static const std::uint16_t kFormsUrshifu[] = {
    SPECIES_URSHIFU_SINGLE_STRIKE_STYLE,
    SPECIES_URSHIFU_RAPID_STRIKE_STYLE,
};

static const std::uint16_t kFormsZarude[] = {
    SPECIES_ZARUDE,
    SPECIES_ZARUDE_DADA,
};

static const std::uint16_t kFormsUrsaluna[] = {
    SPECIES_URSALUNA,
    SPECIES_URSALUNA_BLOODMOON,
};

static const std::uint16_t kFormsOinkologne[] = {
    SPECIES_OINKOLOGNE_MALE,
    SPECIES_OINKOLOGNE_FEMALE,
};

static const std::uint16_t kFormsMaushold[] = {
    SPECIES_MAUSHOLD_FAMILY_OF_THREE,
    SPECIES_MAUSHOLD_FAMILY_OF_FOUR,
};

static const std::uint16_t kFormsSquawkabily[] = {
    SPECIES_SQUAWKABILLY_GREEN_PLUMAGE,
    SPECIES_SQUAWKABILLY_BLUE_PLUMAGE,
    SPECIES_SQUAWKABILLY_YELLOW_PLUMAGE,
    SPECIES_SQUAWKABILLY_WHITE_PLUMAGE,
};

static const std::uint16_t kFormsTatsugiri[] = {
    SPECIES_TATSUGIRI_CURLY,
    SPECIES_TATSUGIRI_DROOPY,
    SPECIES_TATSUGIRI_STRETCHY,
};

static const std::uint16_t kFormsDudunspace[] = {
    SPECIES_DUDUNSPARCE_TWO_SEGMENT,
    SPECIES_DUDUNSPARCE_THREE_SEGMENT,
};

static const std::uint16_t kFormsGimmighoul[] = {
    SPECIES_GIMMIGHOUL_CHEST,
    SPECIES_GIMMIGHOUL_ROAMING,
};

static const std::uint16_t kFormsPoltchageist[] = {
    SPECIES_POLTCHAGEIST_COUNTERFEIT,
    SPECIES_POLTCHAGEIST_ARTISAN,
};

static const std::uint16_t kFormsSinistcha[] = {
    SPECIES_SINISTCHA_UNREMARKABLE,
    SPECIES_SINISTCHA_MASTERPIECE,
};

std::uint16_t Pokemon::randPokemon(Random& rng)
{
    std::uint16_t value;

    value = randInt(rng, 1025) + 1;

    switch (value)
    {
    case SPECIES_TAUROS: if (randInt(rng, 2) == 0) return SAMPLE(rng, kFormsTaurosPaldea); break;
    case SPECIES_UNOWN: return SAMPLE(rng, kFormsUnown);
    case SPECIES_DEOXYS: return SAMPLE(rng, kFormsDeoxys);
    case SPECIES_BURMY: return SAMPLE(rng, kFormsBurmy);
    case SPECIES_WORMADAM: return SAMPLE(rng, kFormsWormadam);
    case SPECIES_SHELLOS: return SAMPLE(rng, kFormsShellos);
    case SPECIES_GASTRODON: return SAMPLE(rng, kFormsGastrodon);
    case SPECIES_ROTOM: return SAMPLE(rng, kFormsRotom);
    case SPECIES_SHAYMIN: return SAMPLE(rng, kFormsShaymin);
    case SPECIES_BASCULIN: return SAMPLE(rng, kFormsBasculin);
    case SPECIES_BASCULEGION: return SAMPLE(rng, kFormsBasculegion);
    case SPECIES_DARMANITAN: return SAMPLE(rng, kFormsDarmanitan);
    case SPECIES_DEERLING: return SAMPLE(rng, kFormsDeerling);
    case SPECIES_SAWSBUCK: return SAMPLE(rng, kFormsSawsbuck);
    case SPECIES_TORNADUS: return SAMPLE(rng, kFormsTornadus);
    case SPECIES_THUNDURUS: return SAMPLE(rng, kFormsThundurus);
    case SPECIES_LANDORUS: return SAMPLE(rng, kFormsLandorus);
    case SPECIES_ENAMORUS: return SAMPLE(rng, kFormsEnamorus);
    case SPECIES_GRENINJA: return SAMPLE(rng, kFormsGreninja);
    case SPECIES_VIVILLON: return SAMPLE(rng, kFormsVivillion);
    case SPECIES_FLABEBE: return SAMPLE(rng, kFormsFlabebe);
    case SPECIES_FLOETTE: return SAMPLE(rng, kFormsFloette);
    case SPECIES_FLORGES: return SAMPLE(rng, kFormsFlorges);
    case SPECIES_FURFROU: return SAMPLE(rng, kFormsFurfrou);
    case SPECIES_MEOWSTIC: return SAMPLE(rng, kFormsMeowstic);
    case SPECIES_PUMPKABOO: return SAMPLE(rng, kFormsPumpkaboo);
    case SPECIES_GOURGEIST: return SAMPLE(rng, kFormsGourgeist);
    case SPECIES_ZYGARDE: return SAMPLE(rng, kFormsZygarde);
    case SPECIES_HOOPA: return SAMPLE(rng, kFormsHoopa);
    case SPECIES_ORICORIO: return SAMPLE(rng, kFormsOricorio);
    case SPECIES_ROCKRUFF: return SPECIES_ROCKRUFF_OWN_TEMPO;
    case SPECIES_LYCANROC: return SAMPLE(rng, kFormsLycanroc);
    case SPECIES_MINIOR: return SAMPLE(rng, kFormsMinior);
    case SPECIES_MAGEARNA: return SAMPLE(rng, kFormsMagearna);
    case SPECIES_TOXTRICITY: return SAMPLE(rng, kFormsToxtricity);
    case SPECIES_SINISTEA: return SAMPLE(rng, kFormsSinistea);
    case SPECIES_POLTEAGEIST: return SAMPLE(rng, kFormsPolteageist);
    case SPECIES_ALCREMIE: return SAMPLE(rng, kFormsAlcremie);
    case SPECIES_INDEEDEE: return SAMPLE(rng, kFormsIndeedee);
    case SPECIES_URSHIFU: return SAMPLE(rng, kFormsUrshifu);
    case SPECIES_ZARUDE: return SAMPLE(rng, kFormsZarude);
    case SPECIES_URSALUNA: return SAMPLE(rng, kFormsUrsaluna);
    case SPECIES_OINKOLOGNE: return SAMPLE(rng, kFormsOinkologne);
    case SPECIES_MAUSHOLD: return SAMPLE(rng, kFormsMaushold);
    case SPECIES_SQUAWKABILLY: return SAMPLE(rng, kFormsSquawkabily);
    case SPECIES_TATSUGIRI: return SAMPLE(rng, kFormsTatsugiri);
    case SPECIES_DUDUNSPARCE: return SAMPLE(rng, kFormsDudunspace);
    case SPECIES_GIMMIGHOUL: return SAMPLE(rng, kFormsGimmighoul);
    case SPECIES_POLTCHAGEIST: return SAMPLE(rng, kFormsPoltchageist);
    case SPECIES_SINISTCHA: return SAMPLE(rng, kFormsSinistcha);
    }

    return value;
}

std::uint16_t Pokemon::randVisiblePokemon(Random& rng)
{
    std::uint16_t pokemon;

    pokemon = randPokemon(rng);

    switch (pokemon)
    {
    case SPECIES_MINIOR_RED: return SPECIES_MINIOR_CORE_RED;
    case SPECIES_MINIOR_ORANGE: return SPECIES_MINIOR_CORE_ORANGE;
    case SPECIES_MINIOR_YELLOW: return SPECIES_MINIOR_CORE_YELLOW;
    case SPECIES_MINIOR_GREEN: return SPECIES_MINIOR_CORE_GREEN;
    case SPECIES_MINIOR_BLUE: return SPECIES_MINIOR_CORE_BLUE;
    case SPECIES_MINIOR_INDIGO: return SPECIES_MINIOR_CORE_INDIGO;
    case SPECIES_MINIOR_VIOLET: return SPECIES_MINIOR_CORE_VIOLET;
    }

    return pokemon;
}
