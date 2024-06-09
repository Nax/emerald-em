#ifndef GROUPS_H
#define GROUPS_H

#include <cstdint>

struct SpeciesGroups
{
    static const uint16_t TaurosPaldean[];
    static const uint16_t Unown[];
    static const uint16_t Castform[];
    static const uint16_t Deoxys[];
    static const uint16_t Burmy[];
    static const uint16_t Wormadam[];
    static const uint16_t Cherrim[];
    static const uint16_t Shellos[];
    static const uint16_t Gastrodon[];
    static const uint16_t Rotom[];
    static const uint16_t RotomAppliances[];
    static const uint16_t Dialga[];
    static const uint16_t Palkia[];
    static const uint16_t Arceus[];
    static const uint16_t Basculin[];
    static const uint16_t Basculegion[];
    static const uint16_t DarmanitanNormal[];
    static const uint16_t DarmanitanGalarian[];
    static const uint16_t Deerling[];
    static const uint16_t Sawsbuck[];
    static const uint16_t Keldeo[];
    static const uint16_t Meloetta[];
    static const uint16_t Genesect[];
    static const uint16_t Greninja[];
    static const uint16_t Vivillon[];
    static const uint16_t Flabebe[];
    static const uint16_t Floette[];
    static const uint16_t Florges[];
    static const uint16_t Furfrou[];
    static const uint16_t Meowstic[];
    static const uint16_t Aegislash[];
    static const uint16_t Pumpkaboo[];
    static const uint16_t Gourgeist[];
    static const uint16_t Xerneas[];
    static const uint16_t Zygarde[];
    static const uint16_t Hoopa[];
    static const uint16_t Oricorio[];
    static const uint16_t Wishiwashi[];
    static const uint16_t Silvally[];
    static const uint16_t Minior[];
    static const uint16_t MiniorCore[];
    static const uint16_t MiniorMeteor[];
    static const uint16_t Mimikyu[];
    static const uint16_t Magearna[];
    static const uint16_t Cramorant[];
    static const uint16_t Toxtricity[];
    static const uint16_t Sinistea[];
    static const uint16_t Polteageist[];
    static const uint16_t Alcremie[];
    static const uint16_t Eiscue[];
    static const uint16_t Morpeko[];
    static const uint16_t Zacian[];
    static const uint16_t Zamazenta[];
    static const uint16_t Urshifru[];
    static const uint16_t Zarude[];
    static const uint16_t Maushold[];
    static const uint16_t Squawkabilly[];
    static const uint16_t Palafin[];
    static const uint16_t Tatsugiri[];
    static const uint16_t Dudunsparce[];
    static const uint16_t Poltchageist[];
    static const uint16_t Sinistcha[];
    static const uint16_t Ogerpon[];

    static const uint16_t* find(const uint16_t** groups, uint16_t species);
};

#endif
