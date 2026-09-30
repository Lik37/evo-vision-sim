#include "genome.h"

#include <cstdlib>



Color::Color(uint8_t hue) : hue(hue) {}

uint8_t Color::getHue() const { return hue; }

bool Color::operator==(const Color& other) const {
    return hue == other.hue;
}
bool Color::operator!=(const Color& other) const {
    return hue != other.hue;
}
bool Color::operator<(const Color& other) const {
    return hue < other.hue;
}
bool Color::operator>(const Color& other) const {
    return hue > other.hue;
}
bool Color::operator<=(const Color& other) const {
    return hue <= other.hue;
}
bool Color::operator>=(const Color& other) const {
    return hue >= other.hue;
}
Color Color::operator+(const Color& other) const {
    return Color(hue + other.hue);
}
Color Color::operator-(const Color& other) const {
    return Color(hue - other.hue);
}

std::ostream& operator<<(std::ostream& os, const Color& c) {
    os << static_cast<int>(c.getHue());
    return os;
}



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



Genome::Genome(const Color &color, const Colorset &familys, const Colorset &enemys) : 
    color(color), familys(familys), enemys(enemys) {}

Patterns Genome::getPattern(const Color cellColor) const {
    if (enemys.get(cellColor))
        return Patterns::ENEMY;
    else if (familys.get(cellColor))
        return Patterns::FRIEND;
    return Patterns::NONE;
}

std::ostream& operator<<(std::ostream& os, const Genome& g) {
    os << "c:" << g.color << " f:" << g.familys << " e:" << g.enemys;
    return os;
}



Colorset mergeColorsets(const Colorset& сolorset1, const Colorset& сolorset2)
{
    int split = rand() % 256;

    std::bitset<256> mask1;
    for (int i = 0; i < split; ++i)
        mask1.set(i);
    
    if (rand() % 2)
        mask1 = ~mask1;
        
    std::bitset<256> mask2 = ~mask1;

    return Colorset((сolorset1 & mask1) | (сolorset2 & mask2));
}

Genome mergeGenomes(const Genome &genome1, const Genome &genome2) 
{   
    Color newColor = (rand() % 2 ? genome1 : genome2).color;

    Colorset newFamilys = mergeColorsets(genome1.familys, genome2.familys);
    Colorset newEnemys = mergeColorsets(genome1.enemys, genome2.enemys);
  
    return Genome(newColor, newFamilys, newEnemys);
}

Color mutateColor(const Color &oldColor, const Color &min, const Color &max) 
{
    const Color deltaColor(min.getHue() + rand()%(max.getHue() - min.getHue() + 1));
    if (rand() % 2)
        return oldColor + deltaColor;
    else
        return oldColor - deltaColor;
}

Colorset mutateColorset(const Colorset &colorset, const Color &min, const Color &max) 
{   
    auto areasBorders = colorset.findBorders();

    if ( !(areasBorders.empty()) ) 
    {
        const size_t indArea = rand() % areasBorders.size();
        const Color deltaColor(min.getHue() + rand()%(max.getHue() - min.getHue() + 1));

        // добавление цвета
        if (rand() % 2) {
            if (rand() % 2) {
                if (areasBorders[indArea].first >= deltaColor) {
                    areasBorders[indArea].first = areasBorders[indArea].first - deltaColor;
                } else {
                    areasBorders.push_back({areasBorders[indArea].first - deltaColor, Color(255)});
                    areasBorders[indArea].first = Color(0);
                }
            } else {
                if (areasBorders[indArea].second <= Color(255) - deltaColor) {
                    areasBorders[indArea].second = areasBorders[indArea].second + deltaColor;
                } else {
                    areasBorders.push_back({Color(0), areasBorders[indArea].second + deltaColor});
                    areasBorders[indArea].second = Color(255);
                }
            }
        // удаление цвета
        } else {
            if (areasBorders[indArea].second - areasBorders[indArea].first > deltaColor) {
                if (rand() % 2) {
                    areasBorders[indArea].first = areasBorders[indArea].first + deltaColor;
                } else {
                    areasBorders[indArea].second = areasBorders[indArea].second - deltaColor;
                }
            // удаление
            } else {
                areasBorders[indArea] = areasBorders.back();
                areasBorders.pop_back();
            }
        }

        return Colorset(areasBorders);
    }
    else
    {
        Color color = Color(static_cast<uint8_t>(rand()));
        Colorset colorset;
        colorset.add(color);
        return colorset;
    }
}

Genome mutateGenome(const Genome &oldGenome, const Color &min, const Color &max) 
{
    if (rand() % 2) {
        // мутация цвета
        return Genome(mutateColor(oldGenome.color, min, max), oldGenome.familys, oldGenome.enemys);
    } 
    else {
        // мутация зрения      
        if (rand() % 2) {
            return Genome(oldGenome.color, mutateColorset(oldGenome.familys, min, max), oldGenome.enemys);
        } else {
            return Genome(oldGenome.color, oldGenome.familys, mutateColorset(oldGenome.enemys, min, max));
        }
    }
}
