#pragma once

#include <iostream>
#include <algorithm>

#include "move/move.h"
#include "type/type.h"
#include "nature/nature.h"
#include "../pokedex/pokemon_database.h"
#include "../pokedex/move_database.h"

class Pokemon {
private:
    std::string name;
    Type types;
    size_t level = 100;
    // TODO: Add items
    PokemonStats baseStats;
    PokemonStats evs;
    PokemonStats ivs = {31, 31, 31, 31, 31, 31};
    PokemonStats stats;
    Nature nature;
    std::array<Move, 4> moves;
    std::vector<float> combinedWeakness;
    int maxHP;

    void findPokemonData(const std::string& name);
    int calculateHP(int hp, int iv, int ev);
    int calculateOtherStats(int base, int iv, int ev, float modifier);
    void calculateStats();
    double calculateTypeEffectiveness(PokemonType moveType, const std::vector<float>& opponentWeaknesses);
    double calculateDamage(double power, double attack, double defense, double typeEffectiveness, bool isSTAB);

    friend class Team;
public:

    Pokemon() : name("Unknown"), nature(Nature::Bashful), types(), baseStats(), evs(), stats(), moves(), maxHP() {}

    Pokemon(const std::string& name) : name(name), nature(Nature::Bashful), types(), baseStats(), evs(), stats(), moves() {
        findPokemonData(name);
        calculateStats();
        maxHP = stats.getHP();
        combinedWeakness = types.getCombinedWeakness();
    }

    // TODO: After items are added, make sure we initialize the item here from the parsed file
    Pokemon(const std::string& name, const PokemonStats& evs, Nature nature, const std::array<std::string, 4>& moveNames)
        : name(name), evs(evs), nature(nature), types(), baseStats(), stats(), moves() {

        findPokemonData(name); // This both validates that a given pokemon is in the database and loads the baseStats

        for (size_t i = 0; i < moveNames.size(); ++i) {
            setMove(moveNames[i], i);
        }

        calculateStats();
        maxHP = stats.getHP();
        combinedWeakness = types.getCombinedWeakness();
    }

    // Copy constructor
    Pokemon(const Pokemon& other) 
        : name(other.name), types(other.types), level(other.level), baseStats(other.baseStats), evs(other.evs),
          ivs(other.ivs), stats(other.stats), nature(other.nature), moves(other.moves),
          combinedWeakness(other.combinedWeakness), maxHP(other.maxHP) {}

    Pokemon& operator=(const Pokemon& other) {
        if (this != &other) {
            // Copy all the fields
            name = other.name;
            types = other.types;
            level = other.level;
            baseStats = other.baseStats;
            evs = other.evs;
            ivs = other.ivs;
            stats = other.stats;
            nature = other.nature;
            moves = other.moves;
            maxHP = other.maxHP;
            combinedWeakness = other.combinedWeakness;
        }
        return *this;
    }

    void displayInfo();
    void displayMoves();
    void displayWeaknesses();

    std::vector<float> getWeaknesses() { return combinedWeakness; }
    std::string getName() const { return name; }
    PokemonStats& getEvs() { return evs; }
    PokemonStats getStats() const { return stats; }
    Nature getNature() const { return nature; }
    Type getType() const { return types; }
    Move getMove(size_t position) const { return moves[position]; }

    inline void setStats(std::array<int, 6> givenStats) { baseStats.setStats(givenStats); }
    void setMove(const std::string& moveName, size_t index);
    void setHP(int health) { stats.setHP(health); }
    void setPercentageHP(int percentage) { 
        percentage = std::max(0, std::min(100, percentage));
        int health = (maxHP * percentage) / 100;
        stats.setHP(health);
    }
    void reduceHP(int damage) { stats.setHP(stats.getHP() - damage); }

    void parseInfo(const std::string& input);
    double useMove(size_t moveIndex, Pokemon opponentPokemon);
};