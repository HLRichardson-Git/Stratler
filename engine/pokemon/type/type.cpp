#include "type.h"

#include <iostream>

std::vector<float> Type::getCombinedWeakness() {
    std::vector<float> combinedWeaknesses(TYPE_AMOUNT, 1.0f);

    for (int i  = 0; i < TYPE_AMOUNT; i++) {
        combinedWeaknesses[i] = typeChart[i][static_cast<int>(primaryType)] * typeChart[i][static_cast<int>(secondaryType)];
    }

    return combinedWeaknesses;
}

/*std::string Type::typeToString(PokemonType type) {
    switch (type) {
        case PokemonType::NORMAL:   return "Normal";
        case PokemonType::FIRE:     return "Fire";
        case PokemonType::WATER:    return "Water";
        case PokemonType::GRASS:    return "Grass";
        case PokemonType::ELECTRIC: return "Electric";
        case PokemonType::ICE:      return "Ice";
        case PokemonType::FIGHTING: return "Fighting";
        case PokemonType::POISON:   return "Poison";
        case PokemonType::GROUND:   return "Ground";
        case PokemonType::FLYING:   return "Flying";
        case PokemonType::PSYCHIC:  return "Psychic";
        case PokemonType::BUG:      return "Bug";
        case PokemonType::ROCK:     return "Rock";
        case PokemonType::GHOST:    return "Ghost";
        case PokemonType::DARK:     return "Dark";
        case PokemonType::DRAGON:   return "Dragon";
        case PokemonType::STEEL:    return "Steel";
        case PokemonType::FAIRY:    return "Fairy";
        case PokemonType::NONE:     return "None";
        default:                    return "Unknown";
    }
}*/