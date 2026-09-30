#pragma once

#include <cstdint>
#include <bitset>
#include <vector>
#include <utility>
#include <ostream>


enum class Patterns { NONE, FRIEND, ENEMY };


class Color
{
    uint8_t hue;

public:
    Color(uint8_t hue);

    uint8_t getHue() const;

    bool operator==(const Color& other) const;
    bool operator!=(const Color& other) const;
    bool operator< (const Color& other) const;
    bool operator> (const Color& other) const;
    bool operator<=(const Color& other) const;
    bool operator>=(const Color& other) const;

    Color operator+(const Color& other) const;
    Color operator-(const Color& other) const;
};
std::ostream& operator<<(std::ostream& os, const Color& c);


class Colorset
{
    std::bitset<256> value;

public:
    Colorset();
    Colorset(const std::bitset<256>& value);
    Colorset(const std::vector<std::pair<Color, Color>>& areas);

    bool get(const Color& color) const;
    void add(const Color& color);
    void del(const Color& color);

    Colorset operator&(const Colorset& other) const;
    Colorset operator|(const Colorset& other) const;

    std::vector<std::pair<Color, Color>> findBorders() const;
};
std::ostream& operator<<(std::ostream& os, const Colorset& cs);


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
Color mutateColor(const Color &oldColor, const Color &max = Color(1)) { 
    return mutateColor(oldColor, Color(1), max);
}

Colorset mutateColorset(const Colorset &colorset, const Color &min, const Color &max);
Colorset mutateColorset(const Colorset &colorset, const Color &max = Color(1)) {
    return mutateColorset(colorset, Color(1), max); 
}

Genome mutateGenome(const Genome& oldGenome, const Color &min, const Color &max);
Genome mutateGenome(const Genome& oldGenome, const Color &max = Color(1)) {
    return mutateGenome(oldGenome, Color(1), max); 
}
