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


Genome mergeGenomes(const Genome& genome1, const Genome& genome2);
Color  mutateColor(const Color& oldColor);
Colorset mutateColorset(const Colorset& colorset);
Genome mutateGenome(const Genome& oldGenome);