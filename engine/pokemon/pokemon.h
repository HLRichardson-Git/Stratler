#pragma once

#include "type/type.h"

class Pokemon {
private:
    std::string name;
    Type type;

public:

    Pokemon(const std::string& name, PokemonType primaryType) : name(name), type(primaryType) {}

    Pokemon(const std::string& name, PokemonType primaryType, PokemonType secondaryType)
        : name(name), type(primaryType, secondaryType) {}

    void displayInfo();
    void displayWeaknesses();

    std::vector<float> getWeaknesses() {return type.getCombinedWeakness(); };

    std::string getName() const { return name; };
};