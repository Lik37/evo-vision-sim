#pragma once

#include "color.h"
#include "colorset.h"

#include <cstdint>
#include <bitset>
#include <vector>
#include <utility>
#include <ostream>


enum class Patterns { NONE, FRIEND, ENEMY };


class Genome
{
public:
    Color color;
    Colorset familys;
    Colorset enemys;

    Genome(const Color& color, const Colorset& familys, const Colorset& enemys);

    Patterns getPattern(const Color cellColor) const;
};
std::ostream& operator<<(std::ostream& os, const Genome& g);


Colorset mergeColorsets(const Colorset& сolorset1, const Colorset& сolorset2);
Genome mergeGenomes(const Genome& genome1, const Genome& genome2);

Color mutateColor(const Color &oldColor, const Color &min, const Color &max);
inline Color mutateColor(const Color &oldColor, const Color &max = Color(1)) { 
    return mutateColor(oldColor, Color(1), max);
}

Colorset mutateColorset(const Colorset &colorset, const Color &min, const Color &max);
inline Colorset mutateColorset(const Colorset &colorset, const Color &max = Color(1)) {
    return mutateColorset(colorset, Color(1), max); 
}

Genome mutateGenome(const Genome& oldGenome, const Color &min, const Color &max);
inline Genome mutateGenome(const Genome& oldGenome, const Color &max = Color(1)) {
    return mutateGenome(oldGenome, Color(1), max); 
}
