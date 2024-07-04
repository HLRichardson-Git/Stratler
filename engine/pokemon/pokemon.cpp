
#include <iostream>
#include <vector>

#include "pokemon.h"

PokemonData Pokemon::findPokemonData(const std::string& name) {
        auto it = pokedex.find(name);
        if (it != pokedex.end()) {
            return it->second;
        } else {
            std::cout << "Error: Pokemon '" << name << "' not found in database." << std::endl;
            // Return default PokemonData for not found Pokémon
            return PokemonData(PokemonType::NONE, PokemonType::NONE, {0, 0, 0, 0, 0, 0});
        }
    }

void Pokemon::displayInfo() {
    std::cout << "Name: " << name << std::endl;
    std::cout << "Primary Type: " << details.types.typeToString(details.types.getPrimaryType()) << std::endl; // Example display
    std::cout << "Secondary Type: " << details.types.typeToString(details.types.getSecondaryType()) << std::endl; // Example display
    std::cout << "Stats:" << std::endl;
    std::cout << "  HP: " << details.stats[0] << std::endl;
    std::cout << "  Attack: " << details.stats[1] << std::endl;
    std::cout << "  Defense: " << details.stats[2] << std::endl;
    std::cout << "  Special Attack: " << details.stats[3] << std::endl;
    std::cout << "  Special Defense: " << details.stats[4] << std::endl;
    std::cout << "  Speed: " << details.stats[5] << std::endl;
}

void Pokemon::displayWeaknesses() {
    std::vector<float> weaknesses = details.types.getCombinedWeakness();
    for (int i = 0; i < TYPE_AMOUNT; i++) {
        std::cout << typeNames[i] << " : " << weaknesses[i] << std::endl;
    }
}