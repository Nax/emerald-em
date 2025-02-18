#include <shuffler/Random.h>
#include <shuffler/Pokemon.h>
#include <emerald/include/constants/species.h>
#include <emerald/include/constants/moves.h>

#define ARRAY_SIZE(n)   (sizeof((n)) / sizeof((n)[0]))
#define SAMPLE(rng, x)  (sample((rng), (x), ARRAY_SIZE((x))))

template <typename T>
static T sample(Random& rng, const T* array, std::size_t size)
{
    std::size_t index;

    index = randInt(rng, size);
    return array[index];
}

static const std::uint16_t kFormsTaurosPaldea[] = {
    SPECIES_TAUROS_PALDEA_COMBAT,
    SPECIES_TAUROS_PALDEA_BLAZE,
    SPECIES_TAUROS_PALDEA_AQUA,
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
    SPECIES_UNOWN_EXCLAMATION,
    SPECIES_UNOWN_QUESTION,
};

static const uint16_t kFormsDeoxys[] = {
    SPECIES_DEOXYS_NORMAL,
    SPECIES_DEOXYS_ATTACK,
    SPECIES_DEOXYS_DEFENSE,
    SPECIES_DEOXYS_SPEED,
};

static const uint16_t kFormsBurmy[] = {
    SPECIES_BURMY_PLANT,
    SPECIES_BURMY_SANDY,
    SPECIES_BURMY_TRASH,
};

static const uint16_t kFormsWormadam[] = {
    SPECIES_WORMADAM_PLANT,
    SPECIES_WORMADAM_SANDY,
    SPECIES_WORMADAM_TRASH,
};

static const uint16_t kFormsShellos[] = {
    SPECIES_SHELLOS_WEST,
    SPECIES_SHELLOS_EAST,
};

static const uint16_t kFormsGastrodon[] = {
    SPECIES_GASTRODON_WEST,
    SPECIES_GASTRODON_EAST,
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
    SPECIES_BASCULEGION_M,
    SPECIES_BASCULEGION_F,
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
    SPECIES_VIVILLON_POKEBALL,
    SPECIES_VIVILLON_FANCY,
};

static const std::uint16_t kFormsFlabebe[] = {
    SPECIES_FLABEBE_RED,
    SPECIES_FLABEBE_YELLOW,
    SPECIES_FLABEBE_ORANGE,
    SPECIES_FLABEBE_BLUE,
    SPECIES_FLABEBE_WHITE,
};

static const std::uint16_t kFormsFloette[] = {
    SPECIES_FLOETTE_RED,
    SPECIES_FLOETTE_YELLOW,
    SPECIES_FLOETTE_ORANGE,
    SPECIES_FLOETTE_BLUE,
    SPECIES_FLOETTE_WHITE,
};

static const std::uint16_t kFormsFlorges[] = {
    SPECIES_FLORGES_RED,
    SPECIES_FLORGES_YELLOW,
    SPECIES_FLORGES_ORANGE,
    SPECIES_FLORGES_BLUE,
    SPECIES_FLORGES_WHITE,
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
    SPECIES_MEOWSTIC_M,
    SPECIES_MEOWSTIC_F,
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
    SPECIES_ZYGARDE_10,
    SPECIES_ZYGARDE_50,
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
    SPECIES_MAGEARNA_ORIGINAL,
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
    SPECIES_INDEEDEE_M,
    SPECIES_INDEEDEE_F,
};

static const std::uint16_t kFormsUrshifu[] = {
    SPECIES_URSHIFU_SINGLE_STRIKE,
    SPECIES_URSHIFU_RAPID_STRIKE,
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
    SPECIES_OINKOLOGNE_M,
    SPECIES_OINKOLOGNE_F,
};

static const std::uint16_t kFormsMaushold[] = {
    SPECIES_MAUSHOLD_THREE,
    SPECIES_MAUSHOLD_FOUR,
};

static const std::uint16_t kFormsSquawkabily[] = {
    SPECIES_SQUAWKABILLY_GREEN,
    SPECIES_SQUAWKABILLY_BLUE,
    SPECIES_SQUAWKABILLY_YELLOW,
    SPECIES_SQUAWKABILLY_WHITE,
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

static const std::uint16_t kFormsRattata[] = {
    SPECIES_RATTATA,
    SPECIES_RATTATA_ALOLA,
};

static const std::uint16_t kFormsRaticate[] = {
    SPECIES_RATICATE,
    SPECIES_RATICATE_ALOLA,
};

static const std::uint16_t kFormsRaichu[] = {
    SPECIES_RAICHU,
    SPECIES_RAICHU_ALOLA,
};

static const std::uint16_t kFormsSandshrew[] = {
    SPECIES_SANDSHREW,
    SPECIES_SANDSHREW_ALOLA,
};

static const std::uint16_t kFormsSandslash[] = {
    SPECIES_SANDSLASH,
    SPECIES_SANDSLASH_ALOLA,
};

static const std::uint16_t kFormsVulpix[] = {
    SPECIES_VULPIX,
    SPECIES_VULPIX_ALOLA,
};

static const std::uint16_t kFormsNinetales[] = {
    SPECIES_NINETALES,
    SPECIES_NINETALES_ALOLA,
};

static const std::uint16_t kFormsDiglett[] = {
    SPECIES_DIGLETT,
    SPECIES_DIGLETT_ALOLA,
};

static const std::uint16_t kFormsDugtrio[] = {
    SPECIES_DUGTRIO,
    SPECIES_DUGTRIO_ALOLA,
};

static const std::uint16_t kFormsMeowth[] = {
    SPECIES_MEOWTH,
    SPECIES_MEOWTH_ALOLA,
    SPECIES_MEOWTH_GALAR,
};

static const std::uint16_t kFormsPersian[] = {
    SPECIES_PERSIAN,
    SPECIES_PERSIAN_ALOLA,
};

static const std::uint16_t kFormsGrowlithe[] = {
    SPECIES_GROWLITHE,
    SPECIES_GROWLITHE_HISUI,
};

static const std::uint16_t kFormsArcanine[] = {
    SPECIES_ARCANINE,
    SPECIES_ARCANINE_HISUI,
};

static const std::uint16_t kFormsGeodude[] = {
    SPECIES_GEODUDE,
    SPECIES_GEODUDE_ALOLA,
};

static const std::uint16_t kFormsGraveler[] = {
    SPECIES_GRAVELER,
    SPECIES_GRAVELER_ALOLA,
};

static const std::uint16_t kFormsGolem[] = {
    SPECIES_GOLEM,
    SPECIES_GOLEM_ALOLA,
};

static const std::uint16_t kFormsPonyta[] = {
    SPECIES_PONYTA,
    SPECIES_PONYTA_GALAR,
};

static const std::uint16_t kFormsRapidash[] = {
    SPECIES_RAPIDASH,
    SPECIES_RAPIDASH_GALAR,
};

static const std::uint16_t kFormsSlowpoke[] = {
    SPECIES_SLOWPOKE,
    SPECIES_SLOWPOKE_GALAR,
};

static const std::uint16_t kFormsSlowbro[] = {
    SPECIES_SLOWBRO,
    SPECIES_SLOWBRO_GALAR,
};

static const std::uint16_t kFormsfarfetchd[] = {
    SPECIES_FARFETCHD,
    SPECIES_FARFETCHD_GALAR,
};

static const std::uint16_t kFormsGrimer[] = {
    SPECIES_GRIMER,
    SPECIES_GRIMER_ALOLA,
};

static const std::uint16_t kFormsMuk[] = {
    SPECIES_MUK,
    SPECIES_MUK_ALOLA,
};

static const std::uint16_t kFormsVoltorb[] = {
    SPECIES_VOLTORB,
    SPECIES_VOLTORB_HISUI,
};

static const std::uint16_t kFormsElectrode[] = {
    SPECIES_ELECTRODE,
    SPECIES_ELECTRODE_HISUI,
};

static const std::uint16_t kFormsExeggutor[] = {
    SPECIES_EXEGGUTOR,
    SPECIES_EXEGGUTOR_ALOLA,
};

static const std::uint16_t kFormsMarowak[] = {
    SPECIES_MAROWAK,
    SPECIES_MAROWAK_ALOLA,
};

static const std::uint16_t kFormsWeezing[] = {
    SPECIES_WEEZING,
    SPECIES_WEEZING_GALAR,
};

static const std::uint16_t kFormsMrMime[] = {
    SPECIES_MR_MIME,
    SPECIES_MR_MIME_GALAR,
};

static const std::uint16_t kFormsArticuno[] = {
    SPECIES_ARTICUNO,
    SPECIES_ARTICUNO_GALAR,
};

static const std::uint16_t kFormsZapdos[] = {
    SPECIES_ZAPDOS,
    SPECIES_ZAPDOS_GALAR,
};

static const std::uint16_t kFormsMoltres[] = {
    SPECIES_MOLTRES,
    SPECIES_MOLTRES_GALAR,
};

static const std::uint16_t kFormsTyphlosion[] = {
    SPECIES_TYPHLOSION,
    SPECIES_TYPHLOSION_HISUI,
};

static const std::uint16_t kFormsWooper[] = {
    SPECIES_WOOPER,
    SPECIES_WOOPER_PALDEA,
};

static const std::uint16_t kFormsSlowking[] = {
    SPECIES_SLOWKING,
    SPECIES_SLOWKING_GALAR,
};

static const std::uint16_t kFormsQwilfish[] = {
    SPECIES_QWILFISH,
    SPECIES_QWILFISH_HISUI,
};

static const std::uint16_t kFormsSneasel[] = {
    SPECIES_SNEASEL,
    SPECIES_SNEASEL_HISUI,
};

static const std::uint16_t kFormsCorsola[] = {
    SPECIES_CORSOLA,
    SPECIES_CORSOLA_GALAR,
};

static const std::uint16_t kFormsZigzagoon[] = {
    SPECIES_ZIGZAGOON,
    SPECIES_ZIGZAGOON_GALAR,
};

static const std::uint16_t kFormsLinoone[] = {
    SPECIES_LINOONE,
    SPECIES_LINOONE_GALAR,
};

static const std::uint16_t kFormsSamurott[] = {
    SPECIES_SAMUROTT,
    SPECIES_SAMUROTT_HISUI,
};

static const std::uint16_t kFormsLiligant[] = {
    SPECIES_LILLIGANT,
    SPECIES_LILLIGANT_HISUI,
};

static const std::uint16_t kFormsDarumaka[] = {
    SPECIES_DARUMAKA,
    SPECIES_DARUMAKA_GALAR,
};

static const uint16_t kFormsDarmanitan[] = {
    SPECIES_DARMANITAN,
    SPECIES_DARMANITAN_GALAR,
};

static const std::uint16_t kFormsYamask[] = {
    SPECIES_YAMASK,
    SPECIES_YAMASK_GALAR,
};

static const std::uint16_t kFormsZorua[] = {
    SPECIES_ZORUA,
    SPECIES_ZORUA_HISUI,
};

static const std::uint16_t kFormsZoroark[] = {
    SPECIES_ZOROARK,
    SPECIES_ZOROARK_HISUI,
};

static const std::uint16_t kFormsStunfisk[] = {
    SPECIES_STUNFISK,
    SPECIES_STUNFISK_GALAR,
};

static const std::uint16_t kFormsBraviary[] = {
    SPECIES_BRAVIARY,
    SPECIES_BRAVIARY_HISUI,
};

static const std::uint16_t kFormsSliggoo[] = {
    SPECIES_SLIGGOO,
    SPECIES_SLIGGOO_HISUI,
};

static const std::uint16_t kFormsGoodra[] = {
    SPECIES_GOODRA,
    SPECIES_GOODRA_HISUI,
};

static const std::uint16_t kFormsAvalugg[] = {
    SPECIES_AVALUGG,
    SPECIES_AVALUGG_HISUI,
};

static const std::uint16_t kFormsDecidueye[] = {
    SPECIES_DECIDUEYE,
    SPECIES_DECIDUEYE_HISUI,
};

static const std::uint16_t kLegendaries[] =
{
    SPECIES_ZAPDOS,
    SPECIES_ZAPDOS_GALAR,
    SPECIES_MOLTRES,
    SPECIES_MOLTRES_GALAR,
    SPECIES_ARTICUNO,
    SPECIES_ARTICUNO_GALAR,
    SPECIES_MEWTWO,
    SPECIES_MEW,
    SPECIES_RAIKOU,
    SPECIES_ENTEI,
    SPECIES_SUICUNE,
    SPECIES_LUGIA,
    SPECIES_HO_OH,
    SPECIES_CELEBI,
    SPECIES_REGIROCK,
    SPECIES_REGICE,
    SPECIES_REGISTEEL,
    SPECIES_LATIAS,
    SPECIES_LATIOS,
    SPECIES_KYOGRE,
    SPECIES_GROUDON,
    SPECIES_RAYQUAZA,
    SPECIES_JIRACHI,
    SPECIES_DEOXYS_NORMAL,
    SPECIES_DEOXYS_ATTACK,
    SPECIES_DEOXYS_DEFENSE,
    SPECIES_DEOXYS_SPEED,
    SPECIES_UXIE,
    SPECIES_MESPRIT,
    SPECIES_AZELF,
    SPECIES_DIALGA,
    SPECIES_PALKIA,
    SPECIES_HEATRAN,
    SPECIES_REGIGIGAS,
    SPECIES_GIRATINA,
    SPECIES_CRESSELIA,
    SPECIES_PHIONE,
    SPECIES_MANAPHY,
    SPECIES_DARKRAI,
    SPECIES_SHAYMIN_LAND,
    SPECIES_SHAYMIN_SKY,
    SPECIES_ARCEUS,
    SPECIES_VICTINI,
    SPECIES_COBALION,
    SPECIES_TERRAKION,
    SPECIES_VIRIZION,
    SPECIES_TORNADUS_INCARNATE,
    SPECIES_TORNADUS_THERIAN,
    SPECIES_THUNDURUS_INCARNATE,
    SPECIES_THUNDURUS_THERIAN,
    SPECIES_LANDORUS_INCARNATE,
    SPECIES_LANDORUS_THERIAN,
    SPECIES_RESHIRAM,
    SPECIES_ZEKROM,
    SPECIES_KYUREM,
    SPECIES_KELDEO,
    SPECIES_MELOETTA,
    SPECIES_GENESECT,
    SPECIES_XERNEAS,
    SPECIES_YVELTAL,
    SPECIES_ZYGARDE_10,
    SPECIES_ZYGARDE_50,
    SPECIES_DIANCIE,
    SPECIES_HOOPA_CONFINED,
    SPECIES_HOOPA_UNBOUND,
    SPECIES_VOLCANION,
    SPECIES_TYPE_NULL,
    SPECIES_SILVALLY,
    SPECIES_TAPU_KOKO,
    SPECIES_TAPU_LELE,
    SPECIES_TAPU_BULU,
    SPECIES_TAPU_FINI,
    SPECIES_COSMOG,
    SPECIES_COSMOEM,
    SPECIES_SOLGALEO,
    SPECIES_LUNALA,
    SPECIES_NECROZMA,
    SPECIES_MAGEARNA,
    SPECIES_MAGEARNA_ORIGINAL,
    SPECIES_MARSHADOW,
    SPECIES_ZERAORA,
    SPECIES_MELTAN,
    SPECIES_MELMETAL,
    SPECIES_ZACIAN,
    SPECIES_ZAMAZENTA,
    SPECIES_ETERNATUS,
    SPECIES_KUBFU,
    SPECIES_URSHIFU_SINGLE_STRIKE,
    SPECIES_URSHIFU_RAPID_STRIKE,
    SPECIES_REGIELEKI,
    SPECIES_REGIDRAGO,
    SPECIES_GLASTRIER,
    SPECIES_SPECTRIER,
    SPECIES_CALYREX,
    SPECIES_ENAMORUS_INCARNATE,
    SPECIES_ENAMORUS_THERIAN,
    SPECIES_ZARUDE,
    SPECIES_ZARUDE_DADA,
    SPECIES_WO_CHIEN,
    SPECIES_CHIEN_PAO,
    SPECIES_TING_LU,
    SPECIES_CHI_YU,
    SPECIES_KORAIDON,
    SPECIES_MIRAIDON,
    SPECIES_OKIDOGI,
    SPECIES_MUNKIDORI,
    SPECIES_FEZANDIPITI,
    SPECIES_OGERPON,
    SPECIES_TERAPAGOS,
    SPECIES_PECHARUNT,
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
    case SPECIES_DEERLING: return SAMPLE(rng, kFormsDeerling);
    case SPECIES_SAWSBUCK: return SAMPLE(rng, kFormsSawsbuck);
    case SPECIES_TORNADUS: return SAMPLE(rng, kFormsTornadus);
    case SPECIES_THUNDURUS: return SAMPLE(rng, kFormsThundurus);
    case SPECIES_LANDORUS: return SAMPLE(rng, kFormsLandorus);
    case SPECIES_ENAMORUS: return SAMPLE(rng, kFormsEnamorus);
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
    case SPECIES_RATTATA: return SAMPLE(rng, kFormsRattata);
    case SPECIES_RATICATE: return SAMPLE(rng, kFormsRaticate);
    case SPECIES_RAICHU: return SAMPLE(rng, kFormsRaichu);
    case SPECIES_SANDSHREW: return SAMPLE(rng, kFormsSandshrew);
    case SPECIES_SANDSLASH: return SAMPLE(rng, kFormsSandslash);
    case SPECIES_VULPIX: return SAMPLE(rng, kFormsVulpix);
    case SPECIES_NINETALES: return SAMPLE(rng, kFormsNinetales);
    case SPECIES_DIGLETT: return SAMPLE(rng, kFormsDiglett);
    case SPECIES_DUGTRIO: return SAMPLE(rng, kFormsDugtrio);
    case SPECIES_MEOWTH: return SAMPLE(rng, kFormsMeowth);
    case SPECIES_PERSIAN: return SAMPLE(rng, kFormsPersian);
    case SPECIES_GROWLITHE: return SAMPLE(rng, kFormsGrowlithe);
    case SPECIES_ARCANINE: return SAMPLE(rng, kFormsArcanine);
    case SPECIES_GEODUDE: return SAMPLE(rng, kFormsGeodude);
    case SPECIES_GRAVELER: return SAMPLE(rng, kFormsGraveler);
    case SPECIES_GOLEM: return SAMPLE(rng, kFormsGolem);
    case SPECIES_PONYTA: return SAMPLE(rng, kFormsPonyta);
    case SPECIES_RAPIDASH: return SAMPLE(rng, kFormsRapidash);
    case SPECIES_SLOWPOKE: return SAMPLE(rng, kFormsSlowpoke);
    case SPECIES_SLOWBRO: return SAMPLE(rng, kFormsSlowbro);
    case SPECIES_FARFETCHD: return SAMPLE(rng, kFormsfarfetchd);
    case SPECIES_GRIMER: return SAMPLE(rng, kFormsGrimer);
    case SPECIES_MUK: return SAMPLE(rng, kFormsMuk);
    case SPECIES_VOLTORB: return SAMPLE(rng, kFormsVoltorb);
    case SPECIES_ELECTRODE: return SAMPLE(rng, kFormsElectrode);
    case SPECIES_EXEGGUTOR: return SAMPLE(rng, kFormsExeggutor);
    case SPECIES_MAROWAK: return SAMPLE(rng, kFormsMarowak);
    case SPECIES_WEEZING: return SAMPLE(rng, kFormsWeezing);
    case SPECIES_MR_MIME: return SAMPLE(rng, kFormsMrMime);
    case SPECIES_ARTICUNO: return SAMPLE(rng, kFormsArticuno);
    case SPECIES_ZAPDOS: return SAMPLE(rng, kFormsZapdos);
    case SPECIES_MOLTRES: return SAMPLE(rng, kFormsMoltres);
    case SPECIES_TYPHLOSION: return SAMPLE(rng, kFormsTyphlosion);
    case SPECIES_WOOPER: return SAMPLE(rng, kFormsWooper);
    case SPECIES_SLOWKING: return SAMPLE(rng, kFormsSlowking);
    case SPECIES_QWILFISH: return SAMPLE(rng, kFormsQwilfish);
    case SPECIES_SNEASEL: return SAMPLE(rng, kFormsSneasel);
    case SPECIES_CORSOLA: return SAMPLE(rng, kFormsCorsola);
    case SPECIES_ZIGZAGOON: return SAMPLE(rng, kFormsZigzagoon);
    case SPECIES_LINOONE: return SAMPLE(rng, kFormsLinoone);
    case SPECIES_SAMUROTT: return SAMPLE(rng, kFormsSamurott);
    case SPECIES_LILLIGANT: return SAMPLE(rng, kFormsLiligant);
    case SPECIES_DARUMAKA: return SAMPLE(rng, kFormsDarumaka);
    case SPECIES_DARMANITAN: return SAMPLE(rng, kFormsDarmanitan);
    case SPECIES_YAMASK: return SAMPLE(rng, kFormsYamask);
    case SPECIES_ZORUA: return SAMPLE(rng, kFormsZorua);
    case SPECIES_ZOROARK: return SAMPLE(rng, kFormsZoroark);
    case SPECIES_STUNFISK: return SAMPLE(rng, kFormsStunfisk);
    case SPECIES_BRAVIARY: return SAMPLE(rng, kFormsBraviary);
    case SPECIES_SLIGGOO: return SAMPLE(rng, kFormsSliggoo);
    case SPECIES_GOODRA: return SAMPLE(rng, kFormsGoodra);
    case SPECIES_AVALUGG: return SAMPLE(rng, kFormsAvalugg);
    case SPECIES_DECIDUEYE: return SAMPLE(rng, kFormsDecidueye);
    }

    return value;
}

bool Pokemon::isLegendary(std::uint16_t pokemon)
{
    for (int i = 0; i < ARRAY_SIZE(kLegendaries); i++)
    {
        if (pokemon == kLegendaries[i])
            return true;
    }

    return false;
}

uint16_t Pokemon::randMove(Random& rng)
{
    uint16_t move;
    bool valid;

    for (;;)
    {
        move = randInt(rng, MOVES_COUNT);

        valid = true;
        if (IS_Z_MOVE(move) || IS_MAX_MOVE(move))
            valid = false;
        else
        {
            switch (move)
            {
            /* Invalid moves */
            case MOVE_NONE:
            case MOVE_STRUGGLE:
            case MOVE_BLAZING_TORQUE:
            case MOVE_WICKED_TORQUE:
            case MOVE_NOXIOUS_TORQUE:
            case MOVE_COMBAT_TORQUE:
            case MOVE_MAGICAL_TORQUE:
                valid = false;
                break;
            }
        }

        if (valid)
            return move;
    }
}
