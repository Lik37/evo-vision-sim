#include "colorset.h"


Colorset::Colorset() : value() {}

Colorset::Colorset(const std::bitset<256> &value) : value(value) {}

Colorset::Colorset(const std::vector<std::pair<Color, Color>> &areas) {
    for (auto area : areas) {
        for (Color c = area.first; c < area.second; c = c + 1) {
            add(Color(c));
        }
        add(Color(area.second));
    }
}

bool Colorset::get(const Color &color) const {
    return value[color.getHue()];
}

void Colorset::add(const Color &color) {
    value[color.getHue()] = true;
}

void Colorset::del(const Color &color) {
    value[color.getHue()] = false;
}

Colorset Colorset::operator&(const Colorset& other) const {
    return Colorset(value & other.value);
}
Colorset Colorset::operator|(const Colorset& other) const {
    return Colorset(value | other.value);
}

std::vector<std::pair<Color, Color>> Colorset::findBorders() const {
    std::vector<std::pair<Color, Color>> areasBorders;
    
    if (value[0])
        areasBorders.push_back({0, 0});
    for(size_t i = 1; i < 256; i++) {
        if (value[i]) {
            if (value[i-1])
                areasBorders.back().second = Color(i);
            else
                areasBorders.push_back({Color(i), Color(i)});
        }
    }
    
    return areasBorders;
}

std::ostream& operator<<(std::ostream& os, const Colorset& cs) {
    auto areas = cs.findBorders();
    os << "{";
    for (auto area : areas)
        os << "[" << area.first << "-" << area.second << "]";
    os << "}";
    return os;
}

