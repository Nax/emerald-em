#include <array>
#include <libemerald/Database.h>
#include <libemerald/Shuffler.h>
#include <libemerald/SpeciesGroups.h>
#include <emerald/include/constants/abilities.h>
#include <emerald/include/constants/species.h>

static const std::vector<const SpeciesSet*> kSpeciesSharedAbilities = {
    &SpeciesGroups::Unown,
    &SpeciesGroups::Castform,
    &SpeciesGroups::Deoxys,
    &SpeciesGroups::Burmy,
    &SpeciesGroups::Wormadam,
    &SpeciesGroups::Cherrim,
    &SpeciesGroups::Shellos,
    &SpeciesGroups::Gastrodon,
    &SpeciesGroups::Rotom,
    &SpeciesGroups::Dialga,
    &SpeciesGroups::Palkia,
    &SpeciesGroups::Arceus,
    &SpeciesGroups::Basculegion,
    &SpeciesGroups::DarmanitanNormal,
    &SpeciesGroups::DarmanitanGalarian,
    &SpeciesGroups::Deerling,
    &SpeciesGroups::Sawsbuck,
    &SpeciesGroups::Keldeo,
    &SpeciesGroups::Meloetta,
    &SpeciesGroups::Genesect,
    &SpeciesGroups::Greninja,
    &SpeciesGroups::Vivillon,
    &SpeciesGroups::Flabebe,
    &SpeciesGroups::Floette,
    &SpeciesGroups::Florges,
    &SpeciesGroups::Furfrou,
    &SpeciesGroups::Aegislash,
    &SpeciesGroups::Pumpkaboo,
    &SpeciesGroups::Gourgeist,
    &SpeciesGroups::Xerneas,
    &SpeciesGroups::Zygarde,
    &SpeciesGroups::Hoopa,
    &SpeciesGroups::Oricorio,
    &SpeciesGroups::Wishiwashi,
    &SpeciesGroups::Silvally,
    &SpeciesGroups::Minior,
    &SpeciesGroups::Mimikyu,
    &SpeciesGroups::Magearna,
    &SpeciesGroups::Cramorant,
    &SpeciesGroups::Sinistea,
    &SpeciesGroups::Polteageist,
    &SpeciesGroups::Alcremie,
    &SpeciesGroups::Eiscue,
    &SpeciesGroups::Morpeko,
    &SpeciesGroups::Zacian,
    &SpeciesGroups::Zamazenta,
    &SpeciesGroups::Urshifru,
    &SpeciesGroups::Zarude,
    &SpeciesGroups::Maushold,
    &SpeciesGroups::Squawkabilly,
    &SpeciesGroups::Palafin,
    &SpeciesGroups::Tatsugiri,
    &SpeciesGroups::Dudunsparce,
    &SpeciesGroups::Poltchageist,
    &SpeciesGroups::Sinistcha,
};

static uint16_t randAbility(Random& rand)
{
    uint16_t ability;

reroll:
    ability = randInt(rand, ABILITIES_COUNT);
    switch (ability)
    {
    /* Trap */
    case ABILITY_NONE:
    case ABILITY_ARENA_TRAP:
    case ABILITY_MAGNET_PULL:
    case ABILITY_SHADOW_TAG:

    /* Shedinja-only */
    case ABILITY_WONDER_GUARD:

    /* Form changes/single pokemon */
    case ABILITY_FORECAST:
    case ABILITY_MULTITYPE:
    case ABILITY_ZEN_MODE:
    case ABILITY_BATTLE_BOND:
    case ABILITY_STANCE_CHANGE:
    case ABILITY_POWER_CONSTRUCT:
    case ABILITY_SCHOOLING:
    case ABILITY_RKS_SYSTEM:
    case ABILITY_SHIELDS_DOWN:
    case ABILITY_DISGUISE:
    case ABILITY_GULP_MISSILE:
    case ABILITY_ICE_FACE:
    case ABILITY_HUNGER_SWITCH:
    case ABILITY_ZERO_TO_HERO:
    case ABILITY_COMMANDER:
    case ABILITY_TERA_SHELL:
    case ABILITY_TERA_SHIFT:
        goto reroll;
    }
    return ability;
}

class ShufflerAbilities
{
public:
    ShufflerAbilities(Database& db, Random& rand)
    : _db{db}, _rand{rand}
    {
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
        std::array<uint16_t, 3> abilities = { ABILITY_NONE, ABILITY_NONE, ABILITY_NONE };
        std::uint16_t ability;

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
                    auto it = _shuffled.find(s);
                    if (it != _shuffled.end())
                    {
                        abilities = _db.pokemons.abilities[s];
                        break;
                    }
                }
            }
        }

        if (abilities[0] == ABILITY_NONE)
        {
            /* Assign abilities */
            for (int i = 0; i < 3; ++i)
            {
                for (;;)
                {
                    bool valid = true;
                    ability = randAbility(_rand);
                    for (int j = 0; j < i; ++j)
                    {
                        if (abilities[j] == ability)
                        {
                            valid = false;
                            break;
                        }
                    }
                    if (valid)
                    {
                        abilities[i] = ability;
                        break;
                    }
                }
            }

            /* Species-specific ability */
            ability = ABILITY_NONE;
            switch (speciesId)
            {
            case SPECIES_CASTFORM:
                ability = ABILITY_FORECAST;
                break;
            case SPECIES_ARCEUS:
                ability = ABILITY_MULTITYPE;
                break;
            case SPECIES_DARMANITAN:
            case SPECIES_DARMANITAN_GALAR:
                ability = ABILITY_ZEN_MODE;
                break;
            case SPECIES_GRENINJA:
                ability = ABILITY_BATTLE_BOND;
                break;
            case SPECIES_AEGISLASH:
                ability = ABILITY_STANCE_CHANGE;
                break;
            case SPECIES_ZYGARDE_50:
            case SPECIES_ZYGARDE_10:
                ability = ABILITY_POWER_CONSTRUCT;
                break;
            case SPECIES_WISHIWASHI:
                ability = ABILITY_SCHOOLING;
                break;
            case SPECIES_SILVALLY:
                ability = ABILITY_RKS_SYSTEM;
                break;
            case SPECIES_MINIOR:
                ability = ABILITY_SHIELDS_DOWN;
                break;
            case SPECIES_MIMIKYU:
                ability = ABILITY_DISGUISE;
                break;
            case SPECIES_CRAMORANT:
                ability = ABILITY_GULP_MISSILE;
                break;
            case SPECIES_EISCUE:
                ability = ABILITY_ICE_FACE;
                break;
            case SPECIES_MORPEKO:
                ability = ABILITY_HUNGER_SWITCH;
                break;
            case SPECIES_PALAFIN:
                ability = ABILITY_ZERO_TO_HERO;
                break;
            case SPECIES_TATSUGIRI_CURLY:
            case SPECIES_TATSUGIRI_DROOPY:
            case SPECIES_TATSUGIRI_STRETCHY:
                ability = ABILITY_COMMANDER;
                break;
            case SPECIES_TERAPAGOS_NORMAL:
                ability = ABILITY_TERA_SHIFT;
                break;
            case SPECIES_TERAPAGOS_TERASTAL:
                ability = ABILITY_TERA_SHELL;
                break;
            }
            if (ability) {
                abilities[randInt(_rand, 3)] = ability;
            }

            /* 50% to not have ability 2 */
            if (_rand.next() & 0x80)
                abilities[1] = ABILITY_NONE;
        }

        /* Store the abilities */
        _db.pokemons.abilities[speciesId] = abilities;
        _shuffled.insert(speciesId);
    }

    Database&           _db;
    Random&             _rand;
    std::set<uint16_t>  _shuffled;
};

void shuffleAbilities(Database& db, Random& rand)
{
    ShufflerAbilities sa{db, rand};
    sa.run();
}
