#pragma once

#include <iostream>

#include "move/move.h"
#include "type/type.h"
#include "nature/nature.h"
#include "../pokedex/pokemon_database.h"
#include "../pokedex/move_database.h"

class Pokemon {
private:
    std::string name;
    Type types;
    PokemonStats baseStats;
    PokemonStats evs;
    PokemonStats ivs;
    PokemonStats stats;
    Nature nature;
    std::array<Move, 4> moves;

    //PokemonData findPokemonData(const std::string& name);
    void findPokemonData(const std::string& name);
    int calculateHP(int hp, int ev);
    int calculateOtherStats(int base, int iv, int ev, float modifier);
    void calculateStats();

    friend class Team;
public:

    Pokemon(const std::string& name) : name(name), nature(Nature::Bashful), types(), baseStats(), evs(), ivs(), stats(), moves() {
        findPokemonData(name);
        calculateStats();
    }

    void displayInfo();
    void displayMoves();
    void displayWeaknesses();

    std::vector<float> getWeaknesses() {return types.getCombinedWeakness(); };
    std::string getName() const { return name; };
    Move getMove(size_t position) { return moves[position]; };

    void setStats(std::array<int, 6> givenStats) { baseStats.setStats(givenStats); };
    void setMove(const std::string& moveName, size_t index);
    void parseInfo(const std::string& input);
};