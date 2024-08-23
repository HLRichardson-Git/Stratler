
# pragma once

#include <fstream>
#include <sstream>
#include <array>
#include <vector>

#include "../pokemon/pokemon.h"

enum Side {
    UNKNOWN,
    PLAYER,
    OPPONENT
};

const size_t TEAM_SIZE = 6;
class Team {
private:
    std::array<Pokemon, TEAM_SIZE> roster;
    std::array<std::vector<float>, TEAM_SIZE> teamWeaknesses;

    void loadFromFile(const std::string& filePath);

    void calculateTeamWeaknesses();

public:

    Team(const Side& playerChoice) {
        std::string filePath = "";
        switch (playerChoice) {
            case PLAYER:
                filePath = "../data/player_teams/playerTeam.txt";
                break;
            case OPPONENT:
                filePath = "../data/player_teams/opponentTeam.txt";
                break;
            default:
                throw std::invalid_argument("Invalid player choice given.");
        }
        loadFromFile(filePath);
        calculateTeamWeaknesses();
    }

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
        calculateTeamWeaknesses();
    }

    void displayTeamsWeaknesses();
    void displayTeamInfo();

    Pokemon& getPokemon(int index) { return roster[index]; };
};

class Game {
private:
    int turnCounter;
    Team player;
    Team opponent;

public:
    Game(const Team& player, const Team& opponent) 
        : turnCounter(0), player(player), opponent(opponent) {}

    void incrementTurn() { turnCounter++; }
    
    int getTurnCounter() const { return turnCounter; }

    Team& getPlayer() { return player; }
    Team& getOpponent() { return opponent; }

    void doTurn();
    void calculateBestMove(int playerPokemonIndex, int opponentPokemonIndex, int depth);
};

enum ActionType {
    ATTACK,
    SWITCH
};

class Turn {
private:
    ActionType actionType;

public:
    Turn(ActionType actionType)
        : actionType(actionType) {
        if (actionType == ATTACK) {

        } else if (actionType == SWITCH) {

        }
    }

    ActionType getActionType() const { return actionType; }
};