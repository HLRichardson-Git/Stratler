
#pragma once

#include <string>

#include "../type/type.h"

struct Move {
    //std::string name;
    PokemonType type;
    int power, accuracy, pp;
};