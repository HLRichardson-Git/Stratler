
#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <regex>

#include "pokemon.h"

void Pokemon::findPokemonData(const std::string& name) {
    auto it = pokedex.find(name);
    if (it != pokedex.end()) {
        types = it->second.types;
        baseStats.setStats(it->second.stats);
    } else {
        std::cout << "Error: Pokemon '" << name << "' not found in database." << std::endl;
        // Set default values if not found
        types = Type(PokemonType::NONE, PokemonType::NONE);
        baseStats.setStats({0, 0, 0, 0, 0, 0});
    }
}

int Pokemon::calculateHP(int hp, int ev) {
    return floor((2 * hp + 31 + floor(ev / 4)) * 100 / 100) + 100 + 10;
}

int Pokemon::calculateOtherStats(int base, int iv, int ev, float modifier) {
    return floor((floor((2 * base + iv + floor(ev / 4)) * 100 / 100) + 5) * modifier);
}

void Pokemon::calculateStats() {
    const NatureModifiers& modifiers = natureModifiersMap.at(nature);

    stats.stats[0] = calculateHP(baseStats.stats[0] , evs.stats[0]);
    stats.stats[1] = calculateOtherStats(baseStats.stats[1], 31, evs.stats[1], modifiers.attackModifier); // Attack
    stats.stats[2] = calculateOtherStats(baseStats.stats[2], 31, evs.stats[2], modifiers.defenseModifier); // Defense
    stats.stats[3] = calculateOtherStats(baseStats.stats[3], 31, evs.stats[3], modifiers.specialAttackModifier); // Special Attack
    stats.stats[4] = calculateOtherStats(baseStats.stats[4], 31, evs.stats[4], modifiers.specialDefenseModifier); // Special Defense
    stats.stats[5] = calculateOtherStats(baseStats.stats[5], 31, evs.stats[5], modifiers.speedModifier); // Speed
}

void Pokemon::displayInfo() {
    std::cout << "Name: " << name << std::endl;
    std::cout << "Primary Type: " << types.typeToString(types.getPrimaryType()) << std::endl;
    std::cout << "Secondary Type: " << types.typeToString(types.getSecondaryType()) << std::endl;
    std::cout << "Stats:" << std::endl;
    std::cout << "  HP: " << stats.stats[0] << std::endl;
    std::cout << "  Attack: " << stats.stats[1] << std::endl;
    std::cout << "  Defense: " << stats.stats[2] << std::endl;
    std::cout << "  Special Attack: " << stats.stats[3] << std::endl;
    std::cout << "  Special Defense: " << stats.stats[4] << std::endl;
    std::cout << "  Speed: " << stats.stats[5] << std::endl;
    std::cout << "Moves:" << std::endl;
    std::cout << "- " << moves[0].getName() << std::endl;
    std::cout << "- " << moves[1].getName() << std::endl;
    std::cout << "- " << moves[2].getName() << std::endl;
    std::cout << "- " << moves[3].getName() << std::endl;
}

void Pokemon::displayMoves() {
    for (size_t i = 0; i < 4; i++) {
        moves[i].displayMove();
    }
}

void Pokemon::displayWeaknesses() {
    std::vector<float> weaknesses = types.getCombinedWeakness();
    for (int i = 0; i < TYPE_AMOUNT; i++) {
        std::cout << typeNames[i] << " : " << weaknesses[i] << std::endl;
    }
}

void Pokemon::setMove(const std::string& moveName, size_t index) {
    auto it = move_database.find(moveName);
    if (it != move_database.end()) {
        moves[index] = it->second;
    } else {
        std::cout << "Error: Move '" << moveName << "' not found in the database." << std::endl;
    }
}

void Pokemon::parseInfo(const std::string& input) {
    // Regex to capture the necessary parts
    std::regex regexName(R"(\(([^)]+)\))");
    std::regex regexEVs(R"(EVs: (\d+) HP / (\d+) Atk / (\d+) Def / (\d+) SpA / (\d+) SpD / (\d+) Spe)");
    std::regex regexNature(R"(([^ ]+) Nature)");
    std::regex regexMoves(R"(- ([^\n]+))");

    // Extract Pokémon name
    std::smatch matchName;
    if (std::regex_search(input, matchName, regexName)) {
        this->name = matchName[1];
    }

    // Extract EVs
    std::smatch matchEVs;
    if (std::regex_search(input, matchEVs, regexEVs)) {
        evs.stats[0] = std::stoi(matchEVs[1]); // HP
        evs.stats[1] = std::stoi(matchEVs[2]); // Atk
        evs.stats[2] = std::stoi(matchEVs[3]); // Def
        evs.stats[3] = std::stoi(matchEVs[4]); // SpA
        evs.stats[4] = std::stoi(matchEVs[5]); // SpD
        evs.stats[5] = std::stoi(matchEVs[6]); // Spe
    }

    // Extract nature
    std::smatch matchNature;
    if (std::regex_search(input, matchNature, regexNature)) {
        std::string natureStr = matchNature[1];
        for (std::map<Nature, NatureModifiers>::const_iterator it = natureModifiersMap.begin(); it != natureModifiersMap.end(); ++it) {
            if (natureToString(it->first) == natureStr) {
                this->nature = it->first;
                break;
            }
        }
    }

    /*// Extract moves
    std::smatch matchMoves;
    std::vector<std::string> moveList;
    auto moveStart = input.cbegin();
    while (std::regex_search(moveStart, input.cend(), matchMoves, regexMoves)) {
        moveList.push_back(matchMoves[1]);
        moveStart = matchMoves.suffix().first;
    }

    // Ensure we have exactly 4 moves
    for (int i = 0; i < 4; ++i) {
        if (i < moveList.size())
            this->moves[i] = moveList[i];
    }*/
   // Extract moves
    std::smatch matchMoves;
    std::vector<std::string> moveList;
    auto moveStart = input.cbegin();
    size_t moveIndex = 0; // Index for the move slots
    while (std::regex_search(moveStart, input.cend(), matchMoves, regexMoves)) {
        if (moveIndex < moves.size()) {
            setMove(matchMoves[1], moveIndex);
            ++moveIndex;
        }
        moveStart = matchMoves.suffix().first;
    }

    // Calculate stats again with updated EVs and nature
    this->calculateStats(); // Assuming level 100 for the example
}