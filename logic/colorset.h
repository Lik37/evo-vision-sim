#pragma once

#include "color.h"

#include <bitset>
#include <vector>


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
