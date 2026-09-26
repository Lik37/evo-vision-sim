#include <cstdint>
#include <bitset>
#include <random>
#include <vector>
#include <utility>


enum class Patterns {
    NONE,
    FRIEND,
    ENEMY
};


class Color 
{
    uint8_t hue;

public:

    Color(uint8_t hue) : hue(hue) {}

    uint8_t getHue() const { return hue; }


    bool operator==(const Color& other) const {
        return hue == other.hue;
    }
    bool operator!=(const Color& other) const {
        return hue != other.hue;
    }
    bool operator<(const Color& other) const {
        return hue < other.hue;
    }
    bool operator>(const Color& other) const {
        return hue > other.hue;
    }
    bool operator<=(const Color& other) const {
        return hue <= other.hue;
    }
    bool operator>=(const Color& other) const {
        return hue >= other.hue;
    }

    Color operator+(const Color& other) const {
        return Color(hue + other.hue);
    }
    Color operator-(const Color& other) const {
        return Color(hue - other.hue);
    }

};


class Colorset
{
    std::bitset<256> value;

public:
    Colorset() : value() {}

    Colorset(const std::bitset<256> &value) : value(value) {}

    Colorset(const std::vector<std::pair<Color, Color>> &areas) {
        for (auto area : areas) {
            for (Color color = area.first; color != area.second + 1; color = color + 1) {
                add(color);
            }
        }
    }


    bool get(const Color &color) const {
        return value[color.getHue()];
    }
    void add(const Color &color) {
        value[color.getHue()] = true;
    }
    void del(const Color &color) {
        value[color.getHue()] = false;
    }

    Colorset operator&(const Colorset& other) const {
        return Colorset(value & other.value);
    }


    std::vector<std::pair<Color, Color>> findBorders() const {
        std::vector<std::pair<Color, Color>> areasBorders;
        
        if (value[0])
            areasBorders.push_back({0, 0});
        for(size_t i = 0; i < 256 - 1; i++) {
            if (value[i]) {
                areasBorders.back().second = i;
            }
            else if (value[i+1]) {
                areasBorders.push_back({i+1, i+1});
            }
        }
        
        return areasBorders;
    }
};


class Genome
{

public:

    Color color;
    Colorset familys;
    Colorset enemys;


    Genome(const Color &color, const Colorset &familys, const Colorset &enemys) : 
        color(color), familys(familys), enemys(enemys) {}


    Patterns getPattern(const Color cellColor) const {
        if (enemys.get(cellColor))
            return Patterns::ENEMY;
        else if (familys.get(cellColor))
            return Patterns::FRIEND;
        return Patterns::NONE;
    }
};



Genome mergeGenomes(const Genome &genome1, const Genome &genome2) 
{   
    Color newColor = (rand() % 2 ? genome1 : genome2).color;

    Colorset newFamilys = genome1.familys & genome2.familys;
    Colorset newEnemys = genome1.enemys & genome2.enemys;
  
    return Genome(newColor, newFamilys, newEnemys);
}


Color mutateColor(const Color &oldColor) 
{
    return oldColor + Color(rand() % 2 ? -1 : 1);
}


Colorset mutateColorset(const Colorset &colorset) 
{
    auto areasBorders = colorset.findBorders();
    if (areasBorders.size()) 
    {
        size_t indArea = rand() % areasBorders.size();

        if (rand() % 2) {
            // добавление цвета
            if (rand() % 2) {
                areasBorders[indArea].first = areasBorders[indArea].first - 1;
            } else {
                areasBorders[indArea].second = areasBorders[indArea].second + 1;
            }
        } else {
            // удаление цвета
            if (rand() % 2) {
                areasBorders[indArea].first = areasBorders[indArea].first + 1;
            } else {
                areasBorders[indArea].second = areasBorders[indArea].second - 1;
            }
            // удаление области
            if (areasBorders[indArea].first > areasBorders[indArea].second) {
                areasBorders.erase(indArea);
            }
        }

        return Colorset(areasBorders);
    }
    else
    {
        Color color = rand();
        Colorset colorset;
        colorset.add(color);
        return colorset;
    }
}


Genome mutateGenome(const Genome &oldGenome) 
{
    if (rand() % 2) {
        // мутация цвета
        return Genome(mutateColor(oldGenome.color), oldGenome.familys, oldGenome.enemys);
    } 
    else {
        // мутация зрения      
        if (rand() % 2) {
            return Genome(oldGenome.color, mutateColorset(oldGenome.familys), oldGenome.enemys);
        } else {
            return Genome(oldGenome.color, oldGenome.familys, mutateColorset(oldGenome.enemys));
        }
    }
}
