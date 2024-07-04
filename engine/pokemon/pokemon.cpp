
#include <iostream>
#include <vector>

#include "pokemon.h"

void Pokemon::displayInfo() {
        std::cout << "Name: " << name << "\n";
        std::cout << "Primary Type: " << type.typeToString(type.getPrimaryType()) << "\n";
        if (type.getSecondaryType() != PokemonType::NONE) {
            std::cout << "Secondary Type: " << type.typeToString(type.getSecondaryType()) << "\n";
        } else {
            std::cout << "Secondary Type: None\n";
        }
}

void Pokemon::displayWeaknesses() {
    std::vector<float> weaknesses = type.getCombinedWeakness();
    for (int i = 0; i < TYPE_AMOUNT; i++) {
        std::cout << typeNames[i] << " : " << weaknesses[i] << std::endl;
    }
}