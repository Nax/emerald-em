const struct Ability gAbilitiesInfo[ABILITIES_COUNT] =
{
    [ABILITY_NONE] =
    {
        .description = COMPOUND_STRING("No special ability."),
        .aiRating = 0,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
    },

    [ABILITY_STENCH] =
    {
        .description = COMPOUND_STRING("May cause a foe to flinch."),
        .aiRating = 1,
    },

    [ABILITY_DRIZZLE] =
    {
        .description = COMPOUND_STRING("Summons rain in battle."),
        .aiRating = 9,
    },

    [ABILITY_SPEED_BOOST] =
    {
        .description = COMPOUND_STRING("Gradually boosts Speed."),
        .aiRating = 9,
    },

    [ABILITY_BATTLE_ARMOR] =
    {
        .description = COMPOUND_STRING("Blocks critical hits."),
        .aiRating = 2,
        .breakable = TRUE,
    },

    [ABILITY_STURDY] =
    {
        .description = COMPOUND_STRING("Negates 1-hit KO attacks."),
        .aiRating = 6,
        .breakable = TRUE,
    },

    [ABILITY_DAMP] =
    {
        .description = COMPOUND_STRING("Prevents self-destruction."),
        .aiRating = 2,
        .breakable = TRUE,
    },

    [ABILITY_LIMBER] =
    {
        .description = COMPOUND_STRING("Prevents paralysis."),
        .aiRating = 3,
        .breakable = TRUE,
    },

    [ABILITY_SAND_VEIL] =
    {
        .description = COMPOUND_STRING("Ups evasion in a sandstorm."),
        .aiRating = 3,
        .breakable = TRUE,
    },

    [ABILITY_STATIC] =
    {
        .description = COMPOUND_STRING("Paralyzes on contact."),
        .aiRating = 4,
    },

    [ABILITY_VOLT_ABSORB] =
    {
        .description = COMPOUND_STRING("Turns electricity into HP."),
        .aiRating = 7,
        .breakable = TRUE,
    },

    [ABILITY_WATER_ABSORB] =
    {
        .description = COMPOUND_STRING("Changes water into HP."),
        .aiRating = 7,
        .breakable = TRUE,
    },

    [ABILITY_OBLIVIOUS] =
    {
        .description = COMPOUND_STRING("Prevents attraction."),
        .aiRating = 2,
        .breakable = TRUE,
    },

    [ABILITY_CLOUD_NINE] =
    {
        .description = COMPOUND_STRING("Negates weather effects."),
        .aiRating = 5,
    },

    [ABILITY_COMPOUND_EYES] =
    {
        .description = COMPOUND_STRING("Raises accuracy."),
        .aiRating = 7,
    },

    [ABILITY_INSOMNIA] =
    {
        .description = COMPOUND_STRING("Prevents sleep."),
        .aiRating = 4,
        .breakable = TRUE,
    },

    [ABILITY_COLOR_CHANGE] =
    {
        .description = COMPOUND_STRING("Changes type to foe's move."),
        .aiRating = 2,
    },

    [ABILITY_IMMUNITY] =
    {
        .description = COMPOUND_STRING("Prevents poisoning."),
        .aiRating = 4,
        .breakable = TRUE,
    },

    [ABILITY_FLASH_FIRE] =
    {
        .description = COMPOUND_STRING("Powers up if hit by fire."),
        .aiRating = 6,
        .breakable = TRUE,
    },

    [ABILITY_SHIELD_DUST] =
    {
        .description = COMPOUND_STRING("Prevents added effects."),
        .aiRating = 5,
        .breakable = TRUE,
    },

    [ABILITY_OWN_TEMPO] =
    {
        .description = COMPOUND_STRING("Prevents confusion."),
        .aiRating = 3,
        .breakable = TRUE,
    },

    [ABILITY_SUCTION_CUPS] =
    {
        .description = COMPOUND_STRING("Firmly anchors the body."),
        .aiRating = 2,
        .breakable = TRUE,
    },

    [ABILITY_INTIMIDATE] =
    {
        .description = COMPOUND_STRING("Lowers the foe's Attack."),
        .aiRating = 7,
    },

    [ABILITY_SHADOW_TAG] =
    {
        .description = COMPOUND_STRING("Prevents the foe's escape."),
        .aiRating = 10,
    },

    [ABILITY_ROUGH_SKIN] =
    {
        .description = COMPOUND_STRING("Hurts to touch."),
        .aiRating = 6,
    },

    [ABILITY_WONDER_GUARD] =
    {
        .description = COMPOUND_STRING("“Supereffective” hits."),
        .aiRating = 10,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .breakable = TRUE,
    },

    [ABILITY_LEVITATE] =
    {
        .description = COMPOUND_STRING("Not hit by Ground attacks."),
        .aiRating = 7,
        .breakable = TRUE,
    },

    [ABILITY_EFFECT_SPORE] =
    {
        .description = COMPOUND_STRING("Leaves spores on contact."),
        .aiRating = 4,
    },

    [ABILITY_SYNCHRONIZE] =
    {
        .description = COMPOUND_STRING("Passes on status problems."),
        .aiRating = 4,
    },

    [ABILITY_CLEAR_BODY] =
    {
        .description = COMPOUND_STRING("Prevents ability reduction."),
        .aiRating = 4,
        .breakable = TRUE,
    },

    [ABILITY_NATURAL_CURE] =
    {
        .description = COMPOUND_STRING("Heals upon switching out."),
        .aiRating = 7,
    },

    [ABILITY_LIGHTNING_ROD] =
    {
        .description = COMPOUND_STRING("Draws electrical moves."),
        .aiRating = 7,
        .breakable = TRUE,
    },

    [ABILITY_SERENE_GRACE] =
    {
        .description = COMPOUND_STRING("Promotes added effects."),
        .aiRating = 8,
    },

    [ABILITY_SWIFT_SWIM] =
    {
        .description = COMPOUND_STRING("Raises Speed in rain."),
        .aiRating = 6,
    },

    [ABILITY_CHLOROPHYLL] =
    {
        .description = COMPOUND_STRING("Raises Speed in sunshine."),
        .aiRating = 6,
    },

    [ABILITY_ILLUMINATE] =
    {
        .description = COMPOUND_STRING("Encounter rate increases."),
        .aiRating = 0,
        .breakable = TRUE,
    },

    [ABILITY_TRACE] =
    {
        .description = COMPOUND_STRING("Copies special ability."),
        .aiRating = 6,
        .cantBeCopied = TRUE,
        .cantBeTraced = TRUE,
    },

    [ABILITY_HUGE_POWER] =
    {
        .description = COMPOUND_STRING("Raises Attack."),
        .aiRating = 10,
    },

    [ABILITY_POISON_POINT] =
    {
        .description = COMPOUND_STRING("Poisons foe on contact."),
        .aiRating = 4,
    },

    [ABILITY_INNER_FOCUS] =
    {
        .description = COMPOUND_STRING("Prevents flinching."),
        .aiRating = 2,
        .breakable = TRUE,
    },

    [ABILITY_MAGMA_ARMOR] =
    {
        .description = COMPOUND_STRING("Prevents freezing."),
        .aiRating = 1,
        .breakable = TRUE,
    },

    [ABILITY_WATER_VEIL] =
    {
        .description = COMPOUND_STRING("Prevents burns."),
        .aiRating = 4,
        .breakable = TRUE,
    },

    [ABILITY_MAGNET_PULL] =
    {
        .description = COMPOUND_STRING("Traps Steel-type Pokémon."),
        .aiRating = 9,
    },

    [ABILITY_SOUNDPROOF] =
    {
        .description = COMPOUND_STRING("Avoids sound-based moves."),
        .aiRating = 4,
        .breakable = TRUE,
    },

    [ABILITY_RAIN_DISH] =
    {
        .description = COMPOUND_STRING("Slight HP recovery in rain."),
        .aiRating = 3,
    },

    [ABILITY_SAND_STREAM] =
    {
        .description = COMPOUND_STRING("Summons a sandstorm."),
        .aiRating = 9,
    },

    [ABILITY_PRESSURE] =
    {
        .description = COMPOUND_STRING("Raises foe's PP usage."),
        .aiRating = 5,
    },

    [ABILITY_THICK_FAT] =
    {
        .description = COMPOUND_STRING("Heat-and-cold protection."),
        .aiRating = 7,
        .breakable = TRUE,
    },

    [ABILITY_EARLY_BIRD] =
    {
        .description = COMPOUND_STRING("Awakens quickly from sleep."),
        .aiRating = 4,
    },

    [ABILITY_FLAME_BODY] =
    {
        .description = COMPOUND_STRING("Burns the foe on contact."),
        .aiRating = 4,
    },

    [ABILITY_RUN_AWAY] =
    {
        .description = COMPOUND_STRING("Makes escaping easier."),
        .aiRating = 0,
    },

    [ABILITY_KEEN_EYE] =
    {
        .description = COMPOUND_STRING("Prevents loss of accuracy."),
        .aiRating = 1,
        .breakable = TRUE,
    },

    [ABILITY_HYPER_CUTTER] =
    {
        .description = COMPOUND_STRING("Prevents Attack reduction."),
        .aiRating = 3,
        .breakable = TRUE,
    },

    [ABILITY_PICKUP] =
    {
        .description = COMPOUND_STRING("May pick up items."),
        .aiRating = 1,
    },

    [ABILITY_TRUANT] =
    {
        .description = COMPOUND_STRING("Moves only every two turns."),
        .aiRating = -2,
        .cantBeOverwritten = TRUE,
    },

    [ABILITY_HUSTLE] =
    {
        .description = COMPOUND_STRING("Trades accuracy for power."),
        .aiRating = 7,
    },

    [ABILITY_CUTE_CHARM] =
    {
        .description = COMPOUND_STRING("Infatuates on contact."),
        .aiRating = 2,
    },

    [ABILITY_PLUS] =
    {
        .description = COMPOUND_STRING("Powers up with Minus."),
        .aiRating = 0,
    },

    [ABILITY_MINUS] =
    {
        .description = COMPOUND_STRING("Powers up with Plus."),
        .aiRating = 0,
    },

    [ABILITY_FORECAST] =
    {
        .description = COMPOUND_STRING("Changes with the weather."),
        .aiRating = 6,
        .cantBeCopied = TRUE,
        .cantBeTraced = TRUE,
    },

    [ABILITY_STICKY_HOLD] =
    {
        .description = COMPOUND_STRING("Prevents item theft."),
        .aiRating = 3,
        .breakable = TRUE,
    },

    [ABILITY_SHED_SKIN] =
    {
        .description = COMPOUND_STRING("Heals the body by shedding."),
        .aiRating = 7,
    },

    [ABILITY_GUTS] =
    {
        .description = COMPOUND_STRING("Ups Attack if suffering."),
        .aiRating = 6,
    },

    [ABILITY_MARVEL_SCALE] =
    {
        .description = COMPOUND_STRING("Ups Defense if suffering."),
        .aiRating = 5,
        .breakable = TRUE,
    },

    [ABILITY_LIQUID_OOZE] =
    {
        .description = COMPOUND_STRING("Draining causes injury."),
        .aiRating = 3,
    },

    [ABILITY_OVERGROW] =
    {
        .description = COMPOUND_STRING("Ups Grass moves in a pinch."),
        .aiRating = 5,
    },

    [ABILITY_BLAZE] =
    {
        .description = COMPOUND_STRING("Ups Fire moves in a pinch."),
        .aiRating = 5,
    },

    [ABILITY_TORRENT] =
    {
        .description = COMPOUND_STRING("Ups Water moves in a pinch."),
        .aiRating = 5,
    },

    [ABILITY_SWARM] =
    {
        .description = COMPOUND_STRING("Ups Bug moves in a pinch."),
        .aiRating = 5,
    },

    [ABILITY_ROCK_HEAD] =
    {
        .description = COMPOUND_STRING("Prevents recoil damage."),
        .aiRating = 5,
    },

    [ABILITY_DROUGHT] =
    {
        .description = COMPOUND_STRING("Summons sunlight in battle."),
        .aiRating = 9,
    },

    [ABILITY_ARENA_TRAP] =
    {
        .description = COMPOUND_STRING("Prevents fleeing."),
        .aiRating = 9,
    },

    [ABILITY_VITAL_SPIRIT] =
    {
        .description = COMPOUND_STRING("Prevents sleep."),
        .aiRating = 4,
        .breakable = TRUE,
    },

    [ABILITY_WHITE_SMOKE] =
    {
        .description = COMPOUND_STRING("Prevents ability reduction."),
        .aiRating = 4,
        .breakable = TRUE,
    },

    [ABILITY_PURE_POWER] =
    {
        .description = COMPOUND_STRING("Raises Attack."),
        .aiRating = 10,
    },

    [ABILITY_SHELL_ARMOR] =
    {
        .description = COMPOUND_STRING("Blocks critical hits."),
        .aiRating = 2,
        .breakable = TRUE,
    },

    [ABILITY_AIR_LOCK] =
    {
        .description = COMPOUND_STRING("Negates weather effects."),
        .aiRating = 5,
    },

    [ABILITY_TANGLED_FEET] =
    {
        .description = COMPOUND_STRING("Ups evasion if confused."),
        .aiRating = 2,
        .breakable = TRUE,
    },

    [ABILITY_MOTOR_DRIVE] =
    {
        .description = COMPOUND_STRING("Electricity raises Speed."),
        .aiRating = 6,
        .breakable = TRUE,
    },

    [ABILITY_RIVALRY] =
    {
        .description = COMPOUND_STRING("Powers up against rivals."),
        .aiRating = 1,
    },

    [ABILITY_STEADFAST] =
    {
        .description = COMPOUND_STRING("Flinching raises Speed."),
        .aiRating = 2,
    },

    [ABILITY_SNOW_CLOAK] =
    {
        .description = COMPOUND_STRING("Ups evasion in Hail or Snow."),
        .aiRating = 3,
        .breakable = TRUE,
    },

    [ABILITY_GLUTTONY] =
    {
        .description = COMPOUND_STRING("Eats Berries early."),
        .aiRating = 3,
    },

    [ABILITY_ANGER_POINT] =
    {
        .description = COMPOUND_STRING("Critical hits raise Attack."),
        .aiRating = 4,
    },

    [ABILITY_UNBURDEN] =
    {
        .description = COMPOUND_STRING("Using a hold item ups Speed."),
        .aiRating = 7,
    },

    [ABILITY_HEATPROOF] =
    {
        .description = COMPOUND_STRING("Heat and burn protection."),
        .aiRating = 5,
        .breakable = TRUE,
    },

    [ABILITY_SIMPLE] =
    {
        .description = COMPOUND_STRING("Prone to wild stat changes."),
        .aiRating = 8,
        .breakable = TRUE,
    },

    [ABILITY_DRY_SKIN] =
    {
        .description = COMPOUND_STRING("Prefers moisture to heat."),
        .aiRating = 6,
        .breakable = TRUE,
    },

    [ABILITY_DOWNLOAD] =
    {
        .description = COMPOUND_STRING("Adjusts power favorably."),
        .aiRating = 7,
    },

    [ABILITY_IRON_FIST] =
    {
        .description = COMPOUND_STRING("Boosts punching moves."),
        .aiRating = 6,
    },

    [ABILITY_POISON_HEAL] =
    {
        .description = COMPOUND_STRING("Restores HP if poisoned."),
        .aiRating = 8,
    },

    [ABILITY_ADAPTABILITY] =
    {
        .description = COMPOUND_STRING("Boosts same type attacks."),
        .aiRating = 8,
    },

    [ABILITY_SKILL_LINK] =
    {
        .description = COMPOUND_STRING("Multi-hit moves hit 5 times."),
        .aiRating = 7,
    },

    [ABILITY_HYDRATION] =
    {
        .description = COMPOUND_STRING("Cures status in rain."),
        .aiRating = 4,
    },

    [ABILITY_SOLAR_POWER] =
    {
        .description = COMPOUND_STRING("Powers up in sunshine."),
        .aiRating = 3,
    },

    [ABILITY_QUICK_FEET] =
    {
        .description = COMPOUND_STRING("Ups Speed if suffering."),
        .aiRating = 5,
    },

    [ABILITY_NORMALIZE] =
    {
        .description = COMPOUND_STRING("Moves become Normal-type."),
        .aiRating = -1,
    },

    [ABILITY_SNIPER] =
    {
        .description = COMPOUND_STRING("Boosts critical hits."),
        .aiRating = 3,
    },

    [ABILITY_MAGIC_GUARD] =
    {
        .description = COMPOUND_STRING("Only damaged by attacks."),
        .aiRating = 9,
    },

    [ABILITY_NO_GUARD] =
    {
        .description = COMPOUND_STRING("Ensures that all moves hit."),
        .aiRating = 8,
    },

    [ABILITY_STALL] =
    {
        .description = COMPOUND_STRING("Always moves last."),
        .aiRating = -1,
    },

    [ABILITY_TECHNICIAN] =
    {
        .description = COMPOUND_STRING("Boosts weaker moves."),
        .aiRating = 8,
    },

    [ABILITY_LEAF_GUARD] =
    {
        .description = COMPOUND_STRING("Blocks status in sunshine."),
        .aiRating = 2,
        .breakable = TRUE,
    },

    [ABILITY_KLUTZ] =
    {
        .description = COMPOUND_STRING("Can't use hold items."),
        .aiRating = -1,
    },

    [ABILITY_MOLD_BREAKER] =
    {
        .description = COMPOUND_STRING("Moves hit through abilities."),
        .aiRating = 7,
    },

    [ABILITY_SUPER_LUCK] =
    {
        .description = COMPOUND_STRING("Critical hits land often."),
        .aiRating = 3,
    },

    [ABILITY_AFTERMATH] =
    {
        .description = COMPOUND_STRING("Fainting damages the foe."),
        .aiRating = 5,
    },

    [ABILITY_ANTICIPATION] =
    {
        .description = COMPOUND_STRING("Senses dangerous moves."),
        .aiRating = 2,
    },

    [ABILITY_FOREWARN] =
    {
        .description = COMPOUND_STRING("Determines a foe's move."),
        .aiRating = 2,
    },

    [ABILITY_UNAWARE] =
    {
        .description = COMPOUND_STRING("Ignores stat changes."),
        .aiRating = 6,
        .breakable = TRUE,
    },

    [ABILITY_TINTED_LENS] =
    {
        .description = COMPOUND_STRING("Ups “not very effective”."),
        .aiRating = 7,
    },

    [ABILITY_FILTER] =
    {
        .description = COMPOUND_STRING("Weakens “supereffective”."),
        .aiRating = 6,
        .breakable = TRUE,
    },

    [ABILITY_SLOW_START] =
    {
        .description = COMPOUND_STRING("Takes a while to get going."),
        .aiRating = -2,
    },

    [ABILITY_SCRAPPY] =
    {
        .description = COMPOUND_STRING("Hits Ghost-type Pokémon."),
        .aiRating = 6,
    },

    [ABILITY_STORM_DRAIN] =
    {
        .description = COMPOUND_STRING("Draws in Water moves."),
        .aiRating = 7,
        .breakable = TRUE,
    },

    [ABILITY_ICE_BODY] =
    {
        .description = COMPOUND_STRING("HP recovery in Hail or Snow."),
        .aiRating = 3,
    },

    [ABILITY_SOLID_ROCK] =
    {
        .description = COMPOUND_STRING("Weakens “supereffective”."),
        .aiRating = 6,
        .breakable = TRUE,
    },

    [ABILITY_SNOW_WARNING] =
    {
        .description = COMPOUND_STRING("Summons a Hailstorm."),
        .aiRating = 8,
    },

    [ABILITY_HONEY_GATHER] =
    {
        .description = COMPOUND_STRING("May gather Honey."),
        .aiRating = 0,
    },

    [ABILITY_FRISK] =
    {
        .description = COMPOUND_STRING("Checks a foe's item."),
        .aiRating = 3,
    },

    [ABILITY_RECKLESS] =
    {
        .description = COMPOUND_STRING("Boosts moves with recoil."),
        .aiRating = 6,
    },

    [ABILITY_MULTITYPE] =
    {
        .description = COMPOUND_STRING("Changes type to its Plate."),
        .aiRating = 8,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .cantBeSuppressed = TRUE,
        .cantBeOverwritten = TRUE,
    },

    [ABILITY_FLOWER_GIFT] =
    {
        .description = COMPOUND_STRING("Allies power up in sunshine."),
        .aiRating = 4,
        .cantBeCopied = TRUE,
        .cantBeTraced = TRUE,
        .breakable = TRUE,
    },

    [ABILITY_BAD_DREAMS] =
    {
        .description = COMPOUND_STRING("Damages sleeping Pokémon."),
        .aiRating = 4,
    },

    [ABILITY_PICKPOCKET] =
    {
        .description = COMPOUND_STRING("Steals the foe's held item."),
        .aiRating = 3,
    },

    [ABILITY_SHEER_FORCE] =
    {
        .description = COMPOUND_STRING("Trades effects for power."),
        .aiRating = 8,
    },

    [ABILITY_CONTRARY] =
    {
        .description = COMPOUND_STRING("Inverts stat changes."),
        .aiRating = 8,
        .breakable = TRUE,
    },

    [ABILITY_UNNERVE] =
    {
        .description = COMPOUND_STRING("Foes can't eat Berries."),
        .aiRating = 3,
    },

    [ABILITY_DEFIANT] =
    {
        .description = COMPOUND_STRING("Lowered stats up Attack."),
        .aiRating = 5,
    },

    [ABILITY_DEFEATIST] =
    {
        .description = COMPOUND_STRING("Gives up at half HP."),
        .aiRating = -1,
    },

    [ABILITY_CURSED_BODY] =
    {
        .description = COMPOUND_STRING("Disables moves on contact."),
        .aiRating = 4,
    },

    [ABILITY_HEALER] =
    {
        .description = COMPOUND_STRING("Heals partner Pokémon."),
        .aiRating = 0,
    },

    [ABILITY_FRIEND_GUARD] =
    {
        .description = COMPOUND_STRING("Lowers damage to partner."),
        .aiRating = 0,
        .breakable = TRUE,
    },

    [ABILITY_WEAK_ARMOR] =
    {
        .description = COMPOUND_STRING("Its stats change when hit."),
        .aiRating = 2,
    },

    [ABILITY_HEAVY_METAL] =
    {
        .description = COMPOUND_STRING("Doubles weight."),
        .aiRating = -1,
        .breakable = TRUE,
    },

    [ABILITY_LIGHT_METAL] =
    {
        .description = COMPOUND_STRING("Halves weight."),
        .aiRating = 2,
        .breakable = TRUE,
    },

    [ABILITY_MULTISCALE] =
    {
        .description = COMPOUND_STRING("Halves damage at full HP."),
        .aiRating = 8,
        .breakable = TRUE,
    },

    [ABILITY_TOXIC_BOOST] =
    {
        .description = COMPOUND_STRING("Ups Attack if poisoned."),
        .aiRating = 6,
    },

    [ABILITY_FLARE_BOOST] =
    {
        .description = COMPOUND_STRING("Ups Sp. Atk if burned."),
        .aiRating = 5,
    },

    [ABILITY_HARVEST] =
    {
        .description = COMPOUND_STRING("May recycle a used Berry."),
        .aiRating = 5,
    },

    [ABILITY_TELEPATHY] =
    {
        .description = COMPOUND_STRING("Can't be damaged by an ally."),
        .aiRating = 0,
        .breakable = TRUE,
    },

    [ABILITY_MOODY] =
    {
        .description = COMPOUND_STRING("Stats change gradually."),
        .aiRating = 10,
    },

    [ABILITY_OVERCOAT] =
    {
        .description = COMPOUND_STRING("Blocks weather and powder."),
        .aiRating = 5,
        .breakable = TRUE,
    },

    [ABILITY_POISON_TOUCH] =
    {
        .description = COMPOUND_STRING("Poisons foe on contact."),
        .aiRating = 4,
    },

    [ABILITY_REGENERATOR] =
    {
        .description = COMPOUND_STRING("Heals upon switching out."),
        .aiRating = 8,
    },

    [ABILITY_BIG_PECKS] =
    {
        .description = COMPOUND_STRING("Prevents Defense loss."),
        .aiRating = 1,
        .breakable = TRUE,
    },

    [ABILITY_SAND_RUSH] =
    {
        .description = COMPOUND_STRING("Ups Speed in a sandstorm."),
        .aiRating = 6,
    },

    [ABILITY_WONDER_SKIN] =
    {
        .description = COMPOUND_STRING("May avoid status problems."),
        .aiRating = 4,
        .breakable = TRUE,
    },

    [ABILITY_ANALYTIC] =
    {
        .description = COMPOUND_STRING("Moving last boosts power."),
        .aiRating = 5,
    },

    [ABILITY_ILLUSION] =
    {
        .description = COMPOUND_STRING("Appears as a partner."),
        .aiRating = 8,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
    },

    [ABILITY_IMPOSTER] =
    {
        .description = COMPOUND_STRING("Transforms into the foe."),
        .aiRating = 9,
        .cantBeCopied = TRUE,
        .cantBeTraced = TRUE,
    },

    [ABILITY_INFILTRATOR] =
    {
        .description = COMPOUND_STRING("Passes through barriers."),
        .aiRating = 6,
    },

    [ABILITY_MUMMY] =
    {
        .description = COMPOUND_STRING("Spreads with contact."),
        .aiRating = 5,
    },

    [ABILITY_MOXIE] =
    {
        .description = COMPOUND_STRING("KOs raise Attack."),
        .aiRating = 7,
    },

    [ABILITY_JUSTIFIED] =
    {
        .description = COMPOUND_STRING("Dark hits raise Attack."),
        .aiRating = 4,
    },

    [ABILITY_RATTLED] =
    {
        .description = COMPOUND_STRING("Raises Speed when scared."),
        .aiRating = 3,
    },

    [ABILITY_MAGIC_BOUNCE] =
    {
        .description = COMPOUND_STRING("Reflects status moves."),
        .aiRating = 9,
        .breakable = TRUE,
    },

    [ABILITY_SAP_SIPPER] =
    {
        .description = COMPOUND_STRING("Grass increases Attack."),
        .aiRating = 7,
        .breakable = TRUE,
    },

    [ABILITY_PRANKSTER] =
    {
        .description = COMPOUND_STRING("Status moves go first."),
        .aiRating = 8,
    },

    [ABILITY_SAND_FORCE] =
    {
        .description = COMPOUND_STRING("Powers up in a sandstorm."),
        .aiRating = 4,
    },

    [ABILITY_IRON_BARBS] =
    {
        .description = COMPOUND_STRING("Hurts to touch."),
        .aiRating = 6,
    },

    [ABILITY_ZEN_MODE] =
    {
        .description = COMPOUND_STRING("Transforms at half HP."),
        .aiRating = -1,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .cantBeSuppressed = B_UPDATED_ABILITY_DATA >= GEN_7,
    },

    [ABILITY_VICTORY_STAR] =
    {
        .description = COMPOUND_STRING("Raises party accuracy."),
        .aiRating = 6,
    },

    [ABILITY_TURBOBLAZE] =
    {
        .description = COMPOUND_STRING("Moves hit through abilities."),
        .aiRating = 7,
    },

    [ABILITY_TERAVOLT] =
    {
        .description = COMPOUND_STRING("Moves hit through abilities."),
        .aiRating = 7,
    },

    [ABILITY_AROMA_VEIL] =
    {
        .description = COMPOUND_STRING("Prevents limiting of moves."),
        .aiRating = 3,
        .breakable = TRUE,
    },

    [ABILITY_FLOWER_VEIL] =
    {
        .description = COMPOUND_STRING("Protects Grass-types."),
        .aiRating = 0,
    },

    [ABILITY_CHEEK_POUCH] =
    {
        .description = COMPOUND_STRING("Eating Berries restores HP."),
        .aiRating = 4,
    },

    [ABILITY_PROTEAN] =
    {
        .description = COMPOUND_STRING("Changes type to used move."),
        .aiRating = 8,
    },

    [ABILITY_FUR_COAT] =
    {
        .description = COMPOUND_STRING("Raises Defense."),
        .aiRating = 7,
        .breakable = TRUE,
    },

    [ABILITY_MAGICIAN] =
    {
        .description = COMPOUND_STRING("Steals the foe's held item."),
        .aiRating = 3,
    },

    [ABILITY_BULLETPROOF] =
    {
        .description = COMPOUND_STRING("Avoids some projectiles."),
        .aiRating = 7,
    },

    [ABILITY_COMPETITIVE] =
    {
        .description = COMPOUND_STRING("Lowered stats up Sp. Atk."),
        .aiRating = 5,
    },

    [ABILITY_STRONG_JAW] =
    {
        .description = COMPOUND_STRING("Boosts biting moves."),
        .aiRating = 6,
    },

    [ABILITY_REFRIGERATE] =
    {
        .description = COMPOUND_STRING("Normal moves become Ice."),
        .aiRating = 8,
    },

    [ABILITY_SWEET_VEIL] =
    {
        .description = COMPOUND_STRING("Prevents party from sleep."),
        .aiRating = 4,
        .breakable = TRUE,
    },

    [ABILITY_STANCE_CHANGE] =
    {
        .description = COMPOUND_STRING("Transforms as it battles."),
        .aiRating = 10,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .cantBeSuppressed = TRUE,
        .cantBeOverwritten = TRUE,
    },

    [ABILITY_GALE_WINGS] =
    {
        .description = COMPOUND_STRING("Flying moves go first."),
        .aiRating = 6,
    },

    [ABILITY_MEGA_LAUNCHER] =
    {
        .description = COMPOUND_STRING("Boosts pulse moves."),
        .aiRating = 7,
    },

    [ABILITY_GRASS_PELT] =
    {
        .description = COMPOUND_STRING("Ups Defense in grass."),
        .aiRating = 2,
        .breakable = TRUE,
    },

    [ABILITY_SYMBIOSIS] =
    {
        .description = COMPOUND_STRING("Passes its item to an ally."),
        .aiRating = 0,
    },

    [ABILITY_TOUGH_CLAWS] =
    {
        .description = COMPOUND_STRING("Boosts contact moves."),
        .aiRating = 7,
    },

    [ABILITY_PIXILATE] =
    {
        .description = COMPOUND_STRING("Normal moves become Fairy."),
        .aiRating = 8,
    },

    [ABILITY_GOOEY] =
    {
        .description = COMPOUND_STRING("Lowers Speed on contact."),
        .aiRating = 5,
    },

    [ABILITY_AERILATE] =
    {
        .description = COMPOUND_STRING("Normal moves become Flying."),
        .aiRating = 8,
    },

    [ABILITY_PARENTAL_BOND] =
    {
        .description = COMPOUND_STRING("Moves hit twice."),
        .aiRating = 10,
    },

    [ABILITY_DARK_AURA] =
    {
        .description = COMPOUND_STRING("Boosts Dark moves."),
        .aiRating = 6,
    },

    [ABILITY_FAIRY_AURA] =
    {
        .description = COMPOUND_STRING("Boosts Fairy moves."),
        .aiRating = 6,
    },

    [ABILITY_AURA_BREAK] =
    {
        .description = COMPOUND_STRING("Reverse aura abilities."),
        .aiRating = 3,
    },

    [ABILITY_PRIMORDIAL_SEA] =
    {
        .description = COMPOUND_STRING("Summons heavy rain."),
        .aiRating = 10,
    },

    [ABILITY_DESOLATE_LAND] =
    {
        .description = COMPOUND_STRING("Summons intense sunlight."),
        .aiRating = 10,
    },

    [ABILITY_DELTA_STREAM] =
    {
        .description = COMPOUND_STRING("Summons strong winds."),
        .aiRating = 10,
    },

    [ABILITY_STAMINA] =
    {
        .description = COMPOUND_STRING("Boosts Defense when hit."),
        .aiRating = 6,
    },

    [ABILITY_WIMP_OUT] =
    {
        .description = COMPOUND_STRING("Flees at half HP."),
        .aiRating = 3,
    },

    [ABILITY_EMERGENCY_EXIT] =
    {
        .description = COMPOUND_STRING("Flees at half HP."),
        .aiRating = 3,
    },

    [ABILITY_WATER_COMPACTION] =
    {
        .description = COMPOUND_STRING("Water boosts Defense."),
        .aiRating = 4,
    },

    [ABILITY_MERCILESS] =
    {
        .description = COMPOUND_STRING("Criticals poisoned foes."),
        .aiRating = 4,
    },

    [ABILITY_SHIELDS_DOWN] =
    {
        .description = COMPOUND_STRING("Shell breaks at half HP."),
        .aiRating = 6,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .cantBeSuppressed = TRUE,
        .cantBeOverwritten = TRUE,
    },

    [ABILITY_STAKEOUT] =
    {
        .description = COMPOUND_STRING("Stronger as foes switch in."),
        .aiRating = 6,
    },

    [ABILITY_WATER_BUBBLE] =
    {
        .description = COMPOUND_STRING("Guards from fire and burns."),
        .aiRating = 8,
    },

    [ABILITY_STEELWORKER] =
    {
        .description = COMPOUND_STRING("Powers up Steel moves."),
        .aiRating = 6,
    },

    [ABILITY_BERSERK] =
    {
        .description = COMPOUND_STRING("Boosts Sp. Atk at low HP."),
        .aiRating = 5,
    },

    [ABILITY_SLUSH_RUSH] =
    {
        .description = COMPOUND_STRING("Raises Speed in Hail or Snow."),
        .aiRating = 5,
    },

    [ABILITY_LONG_REACH] =
    {
        .description = COMPOUND_STRING("Never makes contact."),
        .aiRating = 3,
    },

    [ABILITY_LIQUID_VOICE] =
    {
        .description = COMPOUND_STRING("Makes sound moves Water."),
        .aiRating = 5,
    },

    [ABILITY_TRIAGE] =
    {
        .description = COMPOUND_STRING("Healing moves go first."),
        .aiRating = 7,
    },

    [ABILITY_GALVANIZE] =
    {
        .description = COMPOUND_STRING("Normal moves turn Electric."),
        .aiRating = 8,
    },

    [ABILITY_SURGE_SURFER] =
    {
        .description = COMPOUND_STRING("Faster on electricity."),
        .aiRating = 4,
    },

    [ABILITY_SCHOOLING] =
    {
        .description = COMPOUND_STRING("Forms a school when strong."),
        .aiRating = 6,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .cantBeSuppressed = TRUE,
        .cantBeOverwritten = TRUE,
    },

    [ABILITY_DISGUISE] =
    {
        .description = COMPOUND_STRING("Decoy protects it once."),
        .aiRating = 8,
        .breakable = TRUE,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .cantBeSuppressed = TRUE,
        .cantBeOverwritten = TRUE,
        .failsOnImposter = TRUE,
    },

    [ABILITY_BATTLE_BOND] =
    {
        .description = COMPOUND_STRING("Changes form after a KO."),
        .aiRating = 6,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .cantBeSuppressed = TRUE,
        .cantBeOverwritten = TRUE,
    },

    [ABILITY_POWER_CONSTRUCT] =
    {
        .description = COMPOUND_STRING("Cells aid it when weakened."),
        .aiRating = 10,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .cantBeSuppressed = TRUE,
        .cantBeOverwritten = TRUE,
    },

    [ABILITY_CORROSION] =
    {
        .description = COMPOUND_STRING("Poisons any type."),
        .aiRating = 5,
    },

    [ABILITY_COMATOSE] =
    {
        .description = COMPOUND_STRING("Always drowsing."),
        .aiRating = 6,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .cantBeSuppressed = TRUE,
        .cantBeOverwritten = TRUE,
    },

    [ABILITY_QUEENLY_MAJESTY] =
    {
        .description = COMPOUND_STRING("Protects from priority."),
        .aiRating = 6,
        .breakable = TRUE,
    },

    [ABILITY_INNARDS_OUT] =
    {
        .description = COMPOUND_STRING("Hurts foe when defeated."),
        .aiRating = 5,
    },

    [ABILITY_DANCER] =
    {
        .description = COMPOUND_STRING("Dances along with others."),
        .aiRating = 5,
    },

    [ABILITY_BATTERY] =
    {
        .description = COMPOUND_STRING("Boosts ally's Sp. Atk."),
        .aiRating = 0,
    },

    [ABILITY_FLUFFY] =
    {
        .description = COMPOUND_STRING("Tougher but flammable."),
        .aiRating = 5,
        .breakable = TRUE,
    },

    [ABILITY_DAZZLING] =
    {
        .description = COMPOUND_STRING("Protects from priority."),
        .aiRating = 5,
        .breakable = TRUE,
    },

    [ABILITY_SOUL_HEART] =
    {
        .description = COMPOUND_STRING("KOs raise Sp. Atk."),
        .aiRating = 7,
    },

    [ABILITY_TANGLING_HAIR] =
    {
        .description = COMPOUND_STRING("Lowers Speed on contact."),
        .aiRating = 5,
    },

    [ABILITY_RECEIVER] =
    {
        .description = COMPOUND_STRING("Copies ally's ability."),
        .aiRating = 0,
        .cantBeCopied = TRUE,
        .cantBeTraced = TRUE,
    },

    [ABILITY_POWER_OF_ALCHEMY] =
    {
        .description = COMPOUND_STRING("Copies ally's ability."),
        .aiRating = 0,
        .cantBeCopied = TRUE,
        .cantBeTraced = TRUE,
    },

    [ABILITY_BEAST_BOOST] =
    {
        .description = COMPOUND_STRING("KOs boost best stat."),
        .aiRating = 7,
    },

    [ABILITY_RKS_SYSTEM] =
    {
        .description = COMPOUND_STRING("Memories change its type."),
        .aiRating = 8,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .cantBeSuppressed = TRUE,
        .cantBeOverwritten = TRUE,
    },

    [ABILITY_ELECTRIC_SURGE] =
    {
        .description = COMPOUND_STRING("Field becomes Electric."),
        .aiRating = 8,
    },

    [ABILITY_PSYCHIC_SURGE] =
    {
        .description = COMPOUND_STRING("Field becomes weird."),
        .aiRating = 8,
    },

    [ABILITY_MISTY_SURGE] =
    {
        .description = COMPOUND_STRING("Field becomes misty."),
        .aiRating = 8,
    },

    [ABILITY_GRASSY_SURGE] =
    {
        .description = COMPOUND_STRING("Field becomes grassy."),
        .aiRating = 8,
    },

    [ABILITY_FULL_METAL_BODY] =
    {
        .description = COMPOUND_STRING("Prevents stat reduction."),
        .aiRating = 4,
    },

    [ABILITY_SHADOW_SHIELD] =
    {
        .description = COMPOUND_STRING("Halves damage at full HP."),
        .aiRating = 8,
    },

    [ABILITY_PRISM_ARMOR] =
    {
        .description = COMPOUND_STRING("Weakens “supereffective”."),
        .aiRating = 6,
    },

    [ABILITY_NEUROFORCE] =
    {
        .description = COMPOUND_STRING("Ups “supereffective”."),
        .aiRating = 6,
    },

    [ABILITY_INTREPID_SWORD] =
    {
        .description = COMPOUND_STRING("Ups Attack on entry."),
        .aiRating = 3,
    },

    [ABILITY_DAUNTLESS_SHIELD] =
    {
        .description = COMPOUND_STRING("Ups Defense on entry."),
        .aiRating = 3,
    },

    [ABILITY_LIBERO] =
    {
        .description = COMPOUND_STRING("Changes type to move's."),
    },

    [ABILITY_BALL_FETCH] =
    {
        .description = COMPOUND_STRING("Fetches failed Poké Ball."),
        .aiRating = 0,
    },

    [ABILITY_COTTON_DOWN] =
    {
        .description = COMPOUND_STRING("Lower Speed of all when hit."),
        .aiRating = 3,
    },

    [ABILITY_PROPELLER_TAIL] =
    {
        .description = COMPOUND_STRING("Ignores foe's redirection."),
        .aiRating = 2,
    },

    [ABILITY_MIRROR_ARMOR] =
    {
        .description = COMPOUND_STRING("Reflect stat decreases."),
        .aiRating = 6,
        .breakable = TRUE,
    },

    [ABILITY_GULP_MISSILE] =
    {
        .description = COMPOUND_STRING("If hit, spits prey from sea."),
        .aiRating = 3,
        .cantBeCopied = TRUE,
        .cantBeSuppressed = TRUE,
        .cantBeOverwritten = TRUE,
        .failsOnImposter = TRUE,
    },

    [ABILITY_STALWART] =
    {
        .description = COMPOUND_STRING("Ignores foe's redirection."),
        .aiRating = 2,
    },

    [ABILITY_STEAM_ENGINE] =
    {
        .description = COMPOUND_STRING("Fire or Water hits up Speed."),
        .aiRating = 3,
    },

    [ABILITY_PUNK_ROCK] =
    {
        .description = COMPOUND_STRING("Ups and resists sound."),
        .aiRating = 2,
        .breakable = TRUE,
    },

    [ABILITY_SAND_SPIT] =
    {
        .description = COMPOUND_STRING("Creates a sandstorm if hit."),
        .aiRating = 5,
    },

    [ABILITY_ICE_SCALES] =
    {
        .description = COMPOUND_STRING("Halves special damage."),
        .aiRating = 7,
        .breakable = TRUE,
    },

    [ABILITY_RIPEN] =
    {
        .description = COMPOUND_STRING("Doubles effect of Berries."),
        .aiRating = 4,
    },

    [ABILITY_ICE_FACE] =
    {
        .description = COMPOUND_STRING("Hail or Snow renew free hit."),
        .aiRating = 4,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .cantBeSuppressed = TRUE,
        .cantBeOverwritten = TRUE,
        .breakable = TRUE,
        .failsOnImposter = TRUE,
    },

    [ABILITY_POWER_SPOT] =
    {
        .description = COMPOUND_STRING("Powers up ally moves."),
        .aiRating = 2,
    },

    [ABILITY_MIMICRY] =
    {
        .description = COMPOUND_STRING("Changes type on terrain."),
        .aiRating = 2,
    },

    [ABILITY_SCREEN_CLEANER] =
    {
        .description = COMPOUND_STRING("Removes walls of light."),
        .aiRating = 3,
    },

    [ABILITY_STEELY_SPIRIT] =
    {
        .description = COMPOUND_STRING("Boosts ally's Steel moves."),
        .aiRating = 2,
    },

    [ABILITY_PERISH_BODY] =
    {
        .description = COMPOUND_STRING("Foe faints in 3 turns if hit."),
        .aiRating = -1,
    },

    [ABILITY_WANDERING_SPIRIT] =
    {
        .description = COMPOUND_STRING("Trade abilities on contact."),
        .aiRating = 2,
    },

    [ABILITY_GORILLA_TACTICS] =
    {
        .description = COMPOUND_STRING("Ups Attack and locks move."),
        .aiRating = 4,
    },

    [ABILITY_NEUTRALIZING_GAS] =
    {
        .description = COMPOUND_STRING("All Abilities are nullified."),
        .aiRating = 5,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .failsOnImposter = TRUE,
    },

    [ABILITY_PASTEL_VEIL] =
    {
        .description = COMPOUND_STRING("Protects team from poison."),
        .aiRating = 4,
        .breakable = TRUE,
    },

    [ABILITY_HUNGER_SWITCH] =
    {
        .description = COMPOUND_STRING("Changes form each turn."),
        .aiRating = 2,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .failsOnImposter = TRUE,
    },

    [ABILITY_QUICK_DRAW] =
    {
        .description = COMPOUND_STRING("Moves first occasionally."),
        .aiRating = 4,
    },

    [ABILITY_UNSEEN_FIST] =
    {
        .description = COMPOUND_STRING("Contact evades protection."),
        .aiRating = 6,
    },

    [ABILITY_CURIOUS_MEDICINE] =
    {
        .description = COMPOUND_STRING("Remove ally's stat changes."),
        .aiRating = 3,
    },

    [ABILITY_TRANSISTOR] =
    {
        .description = COMPOUND_STRING("Ups Electric-type moves."),
        .aiRating = 6,
    },

    [ABILITY_DRAGONS_MAW] =
    {
        .description = COMPOUND_STRING("Ups Dragon-type moves."),
        .aiRating = 6,
    },

    [ABILITY_CHILLING_NEIGH] =
    {
        .description = COMPOUND_STRING("KOs boost Attack stat."),
        .aiRating = 7,
    },

    [ABILITY_GRIM_NEIGH] =
    {
        .description = COMPOUND_STRING("KOs boost Sp. Atk stat."),
        .aiRating = 7,
    },

    [ABILITY_AS_ONE_ICE_RIDER] =
    {
        .description = COMPOUND_STRING("Unnerve and Chilling Neigh."),
        .aiRating = 10,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .cantBeSuppressed = TRUE,
        .cantBeOverwritten = TRUE,
    },

    [ABILITY_AS_ONE_SHADOW_RIDER] =
    {
        .description = COMPOUND_STRING("Unnerve and Grim Neigh."),
        .aiRating = 10,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .cantBeSuppressed = TRUE,
        .cantBeOverwritten = TRUE,
    },

    [ABILITY_LINGERING_AROMA] =
    {
        .description = COMPOUND_STRING("Spreads with contact."),
        .aiRating = 5,
    },

    [ABILITY_SEED_SOWER] =
    {
        .description = COMPOUND_STRING("Affects terrain when hit."),
        .aiRating = 5,
    },

    [ABILITY_THERMAL_EXCHANGE] =
    {
        .description = COMPOUND_STRING("Fire hits up Attack."),
        .aiRating = 4,
        .breakable = TRUE,
    },

    [ABILITY_ANGER_SHELL] =
    {
        .description = COMPOUND_STRING("Gets angry at half HP."),
        .aiRating = 3,
    },

    [ABILITY_PURIFYING_SALT] =
    {
        .description = COMPOUND_STRING("Protected by pure salts."),
        .aiRating = 6,
        .breakable = TRUE,
    },

    [ABILITY_WELL_BAKED_BODY] =
    {
        .description = COMPOUND_STRING("Strengthened by Fire."),
        .aiRating = 5,
        .breakable = TRUE,
    },

    [ABILITY_WIND_RIDER] =
    {
        .description = COMPOUND_STRING("Ups Attack if hit by wind."),
        .aiRating = 4,
        .breakable = TRUE,
    },

    [ABILITY_GUARD_DOG] =
    {
        .description = COMPOUND_STRING("Cannot be intimidated."),
        .aiRating = 5,
        .breakable = TRUE,
    },

    [ABILITY_ROCKY_PAYLOAD] =
    {
        .description = COMPOUND_STRING("Powers up Rock moves."),
        .aiRating = 6,
    },

    [ABILITY_WIND_POWER] =
    {
        .description = COMPOUND_STRING("Gets charged by wind."),
        .aiRating = 4,
    },

    [ABILITY_ZERO_TO_HERO] =
    {
        .description = COMPOUND_STRING("Changes form on switch out."),
        .aiRating = 10,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .cantBeSuppressed = TRUE,
        .cantBeOverwritten = TRUE,
        .failsOnImposter = TRUE,
    },

    [ABILITY_COMMANDER] =
    {
        .description = COMPOUND_STRING("Commands from Dondozo."),
        .aiRating = 10,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .cantBeSuppressed = TRUE,
    },

    [ABILITY_ELECTROMORPHOSIS] =
    {
        .description = COMPOUND_STRING("Gets Charged when hit."),
        .aiRating = 5,
    },

    [ABILITY_PROTOSYNTHESIS] =
    {
        .description = COMPOUND_STRING("Sun boosts best stat."),
        .aiRating = 7,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .failsOnImposter = TRUE,
    },

    [ABILITY_QUARK_DRIVE] =
    {
        .description = COMPOUND_STRING("Elec. field ups best stat."),
        .aiRating = 7,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .failsOnImposter = TRUE,
    },

    [ABILITY_GOOD_AS_GOLD] =
    {
        .description = COMPOUND_STRING("Avoids status problems."),
        .aiRating = 8,
        .breakable = TRUE,
    },

    [ABILITY_VESSEL_OF_RUIN] =
    {
        .description = COMPOUND_STRING("Lowers foes' sp. damage."),
        .aiRating = 5,
        .breakable = TRUE,
    },

    [ABILITY_SWORD_OF_RUIN] =
    {
        .description = COMPOUND_STRING("Lowers foes' Defense."),
        .aiRating = 5,
        .breakable = TRUE,
    },

    [ABILITY_TABLETS_OF_RUIN] =
    {
        .description = COMPOUND_STRING("Lowers foes' damage."),
        .aiRating = 5,
        .breakable = TRUE,
    },

    [ABILITY_BEADS_OF_RUIN] =
    {
        .description = COMPOUND_STRING("Lowers foes' Sp. Defense."),
        .aiRating = 5,
        .breakable = TRUE,
    },

    [ABILITY_ORICHALCUM_PULSE] =
    {
        .description = COMPOUND_STRING("Summons sunlight in battle."),
        .aiRating = 8,
    },

    [ABILITY_HADRON_ENGINE] =
    {
        .description = COMPOUND_STRING("Field becomes Electric."),
        .aiRating = 8,
    },

    [ABILITY_OPPORTUNIST] =
    {
        .description = COMPOUND_STRING("Copies foe's stat change."),
        .aiRating = 5,
    },

    [ABILITY_CUD_CHEW] =
    {
        .description = COMPOUND_STRING("Eats a used berry again."),
        .aiRating = 4,
    },

    [ABILITY_SHARPNESS] =
    {
        .description = COMPOUND_STRING("Strengthens slicing moves."),
        .aiRating = 7,
    },

    [ABILITY_SUPREME_OVERLORD] =
    {
        .description = COMPOUND_STRING("Inherits fallen's strength."),
        .aiRating = 6,
    },

    [ABILITY_COSTAR] =
    {
        .description = COMPOUND_STRING("Copies ally's stat changes."),
        .aiRating = 5,
    },

    [ABILITY_TOXIC_DEBRIS] =
    {
        .description = COMPOUND_STRING("Throws poison spikes if hit."),
        .aiRating = 4,
    },

    [ABILITY_ARMOR_TAIL] =
    {
        .description = COMPOUND_STRING("Protects from priority."),
        .aiRating = 5,
        .breakable = TRUE,
    },

    [ABILITY_EARTH_EATER] =
    {
        .description = COMPOUND_STRING("Eats ground to heal HP."),
        .aiRating = 7,
        .breakable = TRUE,
    },

    [ABILITY_MYCELIUM_MIGHT] =
    {
        .description = COMPOUND_STRING("Status moves never fail."),
        .aiRating = 2,
    },

    [ABILITY_HOSPITALITY] =
    {
        .description = COMPOUND_STRING("Restores ally's HP."),
        .aiRating = 5,
    },

    [ABILITY_MINDS_EYE] =
    {
        .description = COMPOUND_STRING("Keen Eye and Scrappy."),
        .aiRating = 8,
        .breakable = TRUE,
    },

    [ABILITY_EMBODY_ASPECT_TEAL_MASK] =
    {
        .description = COMPOUND_STRING("Raises Speed."),
        .aiRating = 6,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .failsOnImposter = TRUE,
    },

    [ABILITY_EMBODY_ASPECT_HEARTHFLAME_MASK] =
    {
        .description = COMPOUND_STRING("Raises Attack."),
        .aiRating = 6,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .failsOnImposter = TRUE,
    },

    [ABILITY_EMBODY_ASPECT_WELLSPRING_MASK] =
    {
        .description = COMPOUND_STRING("Raises Sp. Def."),
        .aiRating = 6,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .failsOnImposter = TRUE,
    },

    [ABILITY_EMBODY_ASPECT_CORNERSTONE_MASK] =
    {
        .description = COMPOUND_STRING("Raises Defense."),
        .aiRating = 6,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .failsOnImposter = TRUE,
    },

    [ABILITY_TOXIC_CHAIN] =
    {
        .description = COMPOUND_STRING("Moves can poison."),
        .aiRating = 8,
    },

    [ABILITY_SUPERSWEET_SYRUP] =
    {
        .description = COMPOUND_STRING("Lowers the foe's Evasion."),
        .aiRating = 5,
    },

    [ABILITY_TERA_SHIFT] =
    {
        .description = COMPOUND_STRING("Terasteralizes upon entry."),
        .aiRating = 10,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .cantBeSuppressed = TRUE,
        .cantBeOverwritten = TRUE,
        .failsOnImposter = TRUE,
    },

    [ABILITY_TERA_SHELL] =
    {
        .description = COMPOUND_STRING("Resistant to types at full HP."),
        .aiRating = 10,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .breakable = TRUE,
    },

    [ABILITY_TERAFORM_ZERO] =
    {
        .description = COMPOUND_STRING("Removes weather and terrain."),
        .aiRating = 10,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
    },

    [ABILITY_POISON_PUPPETEER] =
    {
        .description = COMPOUND_STRING("Confuses poisoned foes."),
        .aiRating = 8,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
    },
};
