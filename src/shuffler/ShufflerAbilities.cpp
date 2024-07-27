#include <array>
#include <shuffler/Shuffler.h>
#include <shuffler/SpeciesGroups.h>
#include <emerald/include/constants/abilities.h>
#include <emerald/include/constants/species.h>

static const std::vector<SpeciesSet> kSpeciesSharedAbilities = {
    SpeciesGroups::Unown,
    SpeciesGroups::Castform,
    SpeciesGroups::Deoxys,
    SpeciesGroups::Burmy,
    SpeciesGroups::Wormadam,
    SpeciesGroups::Cherrim,
    SpeciesGroups::Shellos,
    SpeciesGroups::Gastrodon,
    SpeciesGroups::Rotom,
    SpeciesGroups::Dialga,
    SpeciesGroups::Palkia,
    SpeciesGroups::Arceus,
    SpeciesGroups::Basculegion,
    SpeciesGroups::DarmanitanNormal,
    SpeciesGroups::DarmanitanGalarian,
    SpeciesGroups::Deerling,
    SpeciesGroups::Sawsbuck,
    SpeciesGroups::Keldeo,
    SpeciesGroups::Meloetta,
    SpeciesGroups::Genesect,
    SpeciesGroups::Greninja,
    SpeciesGroups::Vivillon,
    SpeciesGroups::Flabebe,
    SpeciesGroups::Floette,
    SpeciesGroups::Florges,
    SpeciesGroups::Furfrou,
    SpeciesGroups::Aegislash,
    SpeciesGroups::Pumpkaboo,
    SpeciesGroups::Gourgeist,
    SpeciesGroups::Xerneas,
    SpeciesGroups::Zygarde,
    SpeciesGroups::Hoopa,
    SpeciesGroups::Oricorio,
    SpeciesGroups::Wishiwashi,
    SpeciesGroups::Silvally,
    SpeciesGroups::Minior,
    SpeciesGroups::Mimikyu,
    SpeciesGroups::Magearna,
    SpeciesGroups::Cramorant,
    SpeciesGroups::Sinistea,
    SpeciesGroups::Polteageist,
    SpeciesGroups::Alcremie,
    SpeciesGroups::Eiscue,
    SpeciesGroups::Morpeko,
    SpeciesGroups::Zacian,
    SpeciesGroups::Zamazenta,
    SpeciesGroups::Urshifru,
    SpeciesGroups::Zarude,
    SpeciesGroups::Maushold,
    SpeciesGroups::Squawkabilly,
    SpeciesGroups::Palafin,
    SpeciesGroups::Tatsugiri,
    SpeciesGroups::Dudunsparce,
    SpeciesGroups::Poltchageist,
    SpeciesGroups::Sinistcha,
};

static uint16_t randAbility(Random& rand)
{
    uint16_t ability;

reroll:
    ability = randInt(rand, ABILITIES_COUNT);
    switch (ability)
    {
    case ABILITY_NONE:
    case ABILITY_ARENA_TRAP:
    case ABILITY_MAGNET_PULL:
    case ABILITY_SHADOW_TAG:
    case ABILITY_WONDER_GUARD:
    case ABILITY_COMMANDER: /* Not implemented yet */
    case ABILITY_POISON_PUPPETEER: /* Not implemented yet */
    case ABILITY_TERAFORM_ZERO: /* Not implemented yet */
    case ABILITY_TERA_SHELL: /* Not implemented yet */
    case ABILITY_TERA_SHIFT: /* Not implemented yet */
        goto reroll;
    }
    return ability;
}

static bool isAbilityAssignable(uint16_t ability, uint16_t species)
{
    switch (ability)
    {
    case ABILITY_FORECAST: return species == SPECIES_CASTFORM;
    case ABILITY_MULTITYPE: return species == SPECIES_ARCEUS;
    case ABILITY_ZEN_MODE: return species == SPECIES_DARMANITAN || species == SPECIES_DARMANITAN_GALARIAN;
    case ABILITY_BATTLE_BOND: return species == SPECIES_GRENINJA;
    case ABILITY_STANCE_CHANGE: return species == SPECIES_AEGISLASH;
    case ABILITY_POWER_CONSTRUCT: return species == SPECIES_ZYGARDE_50 || species == SPECIES_ZYGARDE_10;
    case ABILITY_SCHOOLING: return species == SPECIES_WISHIWASHI;
    case ABILITY_RKS_SYSTEM: return species == SPECIES_SILVALLY;
    case ABILITY_SHIELDS_DOWN: return species == SPECIES_MINIOR;
    case ABILITY_DISGUISE: return species == SPECIES_MIMIKYU;
    case ABILITY_GULP_MISSILE: return species == SPECIES_CRAMORANT;
    case ABILITY_ICE_FACE: return species == SPECIES_EISCUE;
    case ABILITY_HUNGER_SWITCH: return species == SPECIES_MORPEKO;
    case ABILITY_ZERO_TO_HERO: return species == SPECIES_PALAFIN;
    case ABILITY_COMMANDER: return species == SPECIES_TATSUGIRI_CURLY || species == SPECIES_TATSUGIRI_DROOPY || species == SPECIES_TATSUGIRI_STRETCHY;
    default: return true;
    }
}

static uint16_t randAssignable(Random& rand, uint16_t species, uint16_t other)
{
    uint16_t ability;

reroll:
    ability = randAbility(rand);
    if (ability == other)
        goto reroll;
    if (!isAbilityAssignable(ability, species))
        goto reroll;

    return ability;
}

class ShufflerAbilities
{
public:
    ShufflerAbilities(Shuffler& shuffler)
    : _shuffler{shuffler}
    {
        _base = shuffler.rom().sym("gSpeciesInfo");
    }

    void run()
    {
        for (int i = 1; i < NUM_SPECIES; ++i)
            shuffleAbility(i);
    }

private:
    void shuffleAbility(uint16_t speciesId)
    {
        const SpeciesSet* group;
        std::array<uint16_t, 3> abilities = {ABILITY_NONE, ABILITY_NONE, ABILITY_NONE};
        int i;

        /* Shedinja is special */
        if (speciesId == SPECIES_SHEDINJA)
        {
            abilities[0] = ABILITY_WONDER_GUARD;
        }
        else
        {
            /* Get the group */
            group = SpeciesGroups::find(kSpeciesSharedAbilities, speciesId);
            if (group)
            {
                for (auto s : *group)
                {
                    auto it = _abilities.find(s);
                    if (it != _abilities.end())
                    {
                        abilities = it->second;
                        break;
                    }
                }
            }
        }

        if (abilities[0] == ABILITY_NONE)
        {
            /* Shuffle abilities */
            abilities[0] = randAssignable(_shuffler.random(), speciesId, ABILITY_NONE);
            if (_shuffler.random().next() & 0x80)
                abilities[1] = randAssignable(_shuffler.random(), speciesId, abilities[0]);
        }

        /* Store the abilities */
        _abilities[speciesId] = abilities;

        /* Patch the specie */
        _shuffler.rom().write(_base + 0x94 * speciesId + 0x18, abilities.data(), sizeof(abilities));
    }

    Shuffler&                                   _shuffler;
    uint32_t                                    _base;
    std::map<uint16_t, std::array<uint16_t, 3>> _abilities;
};

void shuffleAbilities(Shuffler& shuffler)
{
    ShufflerAbilities sa{shuffler};

    sa.run();
}
