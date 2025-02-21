#include "global.h"
#include "overrides.h"
#include "constants/moves.h"
#include "constants/abilities.h"

/* Moves */
const u32 kMovesNamesOffsets[MOVES_COUNT_ALL];
const u8 kMovesNamesBuffer[16384] = { 0xff };

/* Pokemons */
const u32 kSpeciesNamesOffsets[1026];
const u8 kSpeciesNamesBuffer[16384] = { 0xff };

/* Abilities */
const u32 kAbilitiesNamesOffsets[ABILITIES_COUNT];
const u8 kAbilitiesNamesBuffer[8192] = { 0xff };

const u16 kFirstBattlePokemon = SPECIES_ZIGZAGOON;
const u16 kStarterMons[] = { SPECIES_TREECKO, SPECIES_TORCHIC, SPECIES_MUDKIP };

/* TM/HM moves */
const u16 kItemMoves[108] = { MOVE_NONE };
const u32 kItemMovesKey = 0xdeadbeef;
