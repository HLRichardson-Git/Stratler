#pragma once

#include <iostream>

#include "type/type.h"
#include "../pokedex/pokemon_database.h"

class Pokemon {
private:
    std::string name;
    PokemonData details;

    PokemonData findPokemonData(const std::string& name);

    friend class Team;
public:

    Pokemon(const std::string& name)
        : name(name), details(findPokemonData(name)) {}

    void displayInfo();
    void displayWeaknesses();

    std::vector<float> getWeaknesses() {return details.types.getCombinedWeakness(); };

    std::string getName() const { return name; };
};