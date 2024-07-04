
# pragma once

#include <array>
#include <vector>

#include "../pokemon/pokemon.h"

const size_t TEAM_SIZE = 6;
class Team {
private:
    std::array<Pokemon, TEAM_SIZE> roster;
    std::array<std::vector<float>, TEAM_SIZE> teamWeaknesses;

    void calculateTeamWeaknesses();

public:

    Team(
        const std::string& p0, 
        const std::string& p1, 
        const std::string& p2, 
        const std::string& p3, 
        const std::string& p4, 
        const std::string& p5
    )
        : roster( { 
            Pokemon(p0), 
            Pokemon(p1), 
            Pokemon(p2), 
            Pokemon(p3), 
            Pokemon(p4), 
            Pokemon(p5) 
            }
        ) {
        calculateTeamWeaknesses(); // automatically calculate a new teams weaknesses
    }

    void displayTeamsWeaknesses();

    Pokemon getPokemon(int index) { return roster[index]; };
};