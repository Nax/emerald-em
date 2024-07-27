#include <shuffler/SpeciesGroups.h>

const SpeciesSet* SpeciesGroups::find(const std::vector<SpeciesSet>& groups, uint16_t species)
{
    for (auto& g : groups)
    {
        if (g.find(species) != g.end())
            return &g;
    }
    return nullptr;
}
