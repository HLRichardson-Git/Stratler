
#include <iostream>
#include <sstream>
#include <string>
#include <cmath>
#include <vector>
#include <regex>
#include <algorithm>
#include <unordered_map>

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

int Pokemon::calculateHP(int hp, int iv, int ev) {
    return floor((2 * hp + iv + floor(ev / 4)) * level / 100) + 100 + 10;
}

int Pokemon::calculateOtherStats(int base, int iv, int ev, float modifier) {
    //return floor((floor((2 * base + iv + floor(ev / 4.0)) * level / 100.0) + 5) * modifier);

    float intermediate = (2.0f * base + iv + floor(ev) / 4.0f) * level / 100.0f;
    return static_cast<int>(floor((intermediate + 5) * modifier));
}

void Pokemon::calculateStats() {
    const NatureModifiers& modifiers = natureModifiersMap.at(nature);

    stats.stats[0] = calculateHP(baseStats.stats[0], ivs.stats[0], evs.stats[0]); // HP
    stats.stats[1] = calculateOtherStats(baseStats.stats[1], ivs.stats[1], evs.stats[1], modifiers.attackModifier); // Atk
    stats.stats[2] = calculateOtherStats(baseStats.stats[2], ivs.stats[2], evs.stats[2], modifiers.defenseModifier); // Def
    stats.stats[3] = calculateOtherStats(baseStats.stats[3], ivs.stats[3], evs.stats[3], modifiers.specialAttackModifier); // SpA
    stats.stats[4] = calculateOtherStats(baseStats.stats[4], ivs.stats[4], evs.stats[4], modifiers.specialDefenseModifier); // SpD
    stats.stats[5] = calculateOtherStats(baseStats.stats[5], ivs.stats[5], evs.stats[5], modifiers.speedModifier); // Spe
}

double Pokemon::calculateTypeEffectiveness(PokemonType moveType, const std::vector<float>& opponentWeaknesses) {
    double effectiveness = opponentWeaknesses[static_cast<int>(moveType)];
    return effectiveness;
}

double Pokemon::calculateDamage(double power, double attack, double defense, double typeEffectiveness, bool isSTAB) {
    double numerator = ((2 * level / 5) + 2) * power * (attack / defense);
    double leftMost = (numerator / 50) + 2;
    
    double targets = 1.0; // 0.75 if move has more than one target, but for now this isn't supported
    double pb = 1.0; // 0.25 if the second strike is parental bond (whatever that is)
    double weather = 1.0; // TODO: take into account weather
    unsigned int glaiveRush = 1; // 2 if opponnent used Glaive Rush in the previous turn
    double critical = 1.0; // 1.5 if is a crit, don't know if I want to calculate for this though
    double random = 1.0; // usually a random value from 85 -> 100 then divided by 100, for now calculating highest possible value of 1.0
    double stab = (isSTAB) ? 1.5 : 1.0;
    double burn = 1.0; // 0.5 if attacker is burned and uses a physical move
    double other = 1.0; // Look into this, seems like it can be deep for not much payoff
    double zMove = 1.0; // 0.25 if is a Z-Move or Max Move and the target uses protect
    double teraShield = 1.0; // Only changes if the opponent is a Tera Raid Boss

    double total = leftMost * targets * pb * weather * glaiveRush * critical * random * stab * typeEffectiveness * burn * other * zMove * teraShield;
    return total;
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
    std::cout << std::endl;
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
    std::regex regexName(R"(\(([^)]+)\))");
    std::regex regexNature(R"((\w+)\s+Nature)");
    std::regex regexMoves(R"(- ([^\n]+))");

    // Extract Pokémon name
    std::smatch matchName;
    if (std::regex_search(input, matchName, regexName)) {
        this->name = matchName[1];
    }

    // Initialize EVs to 0
    evs.stats = {0, 0, 0, 0, 0, 0}; // Assuming stats order is HP, Atk, Def, SpA, SpD, Spe

    // Extract EVs
    std::string evsLine;
    std::istringstream inputStream(input);
    std::string line;
    while (std::getline(inputStream, line)) {
        if (line.find("EVs:") != std::string::npos) {
            evsLine = line.substr(4); // Remove "EVs: "
            break;
        }
    }

    if (!evsLine.empty()) {
        std::unordered_map<std::string, int> evMap = {
            {"HP", 0}, {"Atk", 0}, {"Def", 0}, {"SpA", 0}, {"SpD", 0}, {"Spe", 0}
        };

        // Tokenize the EVs line
        std::replace(evsLine.begin(), evsLine.end(), '/', ' '); // Replace "/" with space for easy tokenization
        std::istringstream evStream(evsLine);
        std::string token;
        while (evStream >> token) {
            // Handle tokens like "252", "SpA"
            if (std::isdigit(token[0])) {
                int value = std::stoi(token);
                evStream >> token; // Get the stat name
                evMap[token] = value;
            }
        }

        evs.stats[0] = evMap["HP"];
        evs.stats[1] = evMap["Atk"];
        evs.stats[2] = evMap["Def"];
        evs.stats[3] = evMap["SpA"];
        evs.stats[4] = evMap["SpD"];
        evs.stats[5] = evMap["Spe"];
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

double Pokemon::useMove(size_t moveIndex, Pokemon opponentPokemon) {
    if (moveIndex >= 4) {
       throw std::out_of_range("Invalid move index");
    }

    Move move = moves[moveIndex];
    bool isSTAB = (move.getType() == getType().getPrimaryType() || move.getType() == getType().getSecondaryType());

    int power = move.power;
    int attackStat = 0;
    int defenseStat = 0;
    double typeEffectiveness = calculateTypeEffectiveness(move.getType(), opponentPokemon.getWeaknesses());

    switch (move.getCategory()) {
        case STATUS:
            return 0;
            break;
        case PHYSICAL:
            attackStat = stats.getAttack();
            defenseStat = opponentPokemon.getStats().getDefense();
            break;
        case SPECIAL: 
            attackStat = stats.getSpecialAttack();
            defenseStat = opponentPokemon.getStats().getSpecialDefense();
            break;
        default:
            throw std::invalid_argument("Invalid move category given.");
    }

    double damage = calculateDamage(power, attackStat, defenseStat, typeEffectiveness, isSTAB);

    return damage;
}