#include "genome.h"
#include "math.h"

#include <cstdint>


// enum class Order {
//     HERBIVORE,
//     PREDATOR
// };


enum class MoveDirect {
    NONE,
    LEFT,
    UP,
    LEFT,
};

struct Creature
{
    uint16_t id;
    Genome genome;
    
    Point pos;

    uint16_t stamina;
};

struct Predator : Creature
{

};

struct Herbivore : Creature
{
    
};
