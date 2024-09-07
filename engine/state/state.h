
# pragma once

#include <fstream>
#include <sstream>
#include <array>
#include <vector>
#include <algorithm>

#include "../pokemon/pokemon.h"

struct MoveDamage {
    Move move;
    double damage;
    Pokemon activePokemon;
    bool isViable = false;

    MoveDamage(const Move& m, double d, const Pokemon& pokemon) : move(m), damage(d), activePokemon(pokemon) {}
};

bool compareByDamage(const MoveDamage& a, const MoveDamage& b);

struct GameState {
    Pokemon playerPokemon;
    Pokemon opponentPokemon;
    std::vector<MoveDamage> playerMoves;
    std::vector<MoveDamage> opponentMoves;
    int playerHP;
    int opponentHP;
    bool isPlayerTurn;
};

struct MinimaxResult {
    int score;
    MoveDamage bestMoveDamage;
};

MinimaxResult minimax(const GameState& stateOfGame, int depth, bool isMaximizing);

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
    unsigned int currentPokemonIndex = 0;

    void loadFromFile(const std::string& filePath);
    void calculateTeamWeaknesses();

public:
    Team(const std::string& filePath) {
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
    void listTeam();

    Pokemon& getPokemon(int index) { return roster[index]; }
    Pokemon& getCurrentPokemon() { return roster[currentPokemonIndex]; }
    unsigned int getCurrentPokemonIndex() { return currentPokemonIndex; }

    void setCurrentPokemonIndex(unsigned int index) { if (index <= TEAM_SIZE) currentPokemonIndex = index; }
};

bool confirmChoice();

enum ActionType {
    ATTACK,
    SWITCH
};

/*struct TurnHistory {
    ActionType playerChoice;
    ActionType opponentChoice;
}
class Turn {
private:
    TurnHistory currentTurnHistory;
    ActionType getTurnOption();

public:
    Turn() {
        getTurnOption();
    }

    
};*/

class Game {
private:
    Team player;
    Team opponent;

    int turnCounter;
    //std::vector<Turn> history;

public:
    Game(const Team& player, const Team& opponent) 
        : turnCounter(0), player(player), opponent(opponent) {}

    void incrementTurn() { turnCounter++; }
    int getTurnCounter() const { return turnCounter; }

    Team& getPlayer() { return player; }
    Team& getOpponent() { return opponent; }
    Pokemon& getCurrentPlayerPokemon() { return player.getCurrentPokemon(); }
    Pokemon& getCurrentOpponentPokemon() { return opponent.getCurrentPokemon(); }

    void setPlayerCurrentPokemonIndex(int index) { player.setCurrentPokemonIndex(index); }
    void setOpponentCurrentPokemonIndex(int index) { opponent.setCurrentPokemonIndex(index); }

    std::vector<MoveDamage> calculateMoveDamages(Pokemon& attacker, const Pokemon& defender);
    std::vector<MoveDamage> rankMovesByDamage(int opponentPokemonIndex);
    void evaluateMoveViability(int opponentPokemonIndex);
    void evaluateMatchup(int opponentPokemonIndex);
    
    void startGame();
    //Turn doTurn();
    //void doTurn();
    void handleAttack(bool isPlayer);
    void handleSwitch(bool isPlayer);
    void promptForMove(bool isPlayer);
    void processTurn();
    void updateHealth();
    void playGame();
    bool isGameOver();
};