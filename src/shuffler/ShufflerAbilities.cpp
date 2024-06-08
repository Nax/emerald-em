#include <shuffler/Shuffler.h>
#include <emerald/include/constants/abilities.h>
#include <emerald/include/constants/species.h>

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
    case ABILITY_FLOWER_GIFT: return species == SPECIES_CHERRIM;
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

static void shuffleAbility(Shuffler& shuffler, uint32_t base, int speciesId)
{
    uint16_t abilities[3];

    if (speciesId == SPECIES_SHEDINJA)
        return;

    /* Get the abilities */
    abilities[0] = randAssignable(shuffler.random(), speciesId, ABILITY_NONE);
    if (shuffler.random().next() & 0x80)
        abilities[1] = randAssignable(shuffler.random(), speciesId, abilities[0]);
    else
        abilities[1] = ABILITY_NONE;
    abilities[2] = ABILITY_NONE;

    shuffler.rom().write(base + 0x94 * speciesId + 0x18, abilities, sizeof(abilities));
}

void shuffleAbilities(Shuffler& shuffler)
{
    uint32_t base;

    base = shuffler.rom().sym("gSpeciesInfo");
    for (int i = 1; i < NUM_SPECIES; ++i)
        shuffleAbility(shuffler, base, i);
}
