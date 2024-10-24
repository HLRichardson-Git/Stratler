
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

    MoveDamage(const Move& m, double d, const Pokemon pokemon) : move(m), damage(d), activePokemon(pokemon) {}
};

bool compareByDamage(const MoveDamage& a, const MoveDamage& b);

struct PokemonMoveRanking {
    Pokemon pokemon;      // The Pokémon making the move
    MoveDamage bestMove;  // The best move this Pokémon can make
    int score;            // The evaluation score of this move
};
struct GameState {
    Pokemon& playerPokemon;
    Pokemon& opponentPokemon;
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

//bool hasGoodEnoughMove(const GameState& stateOfGame);
MinimaxResult minimax(GameState& stateOfGame, int depth, bool isMaximizing);

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

class Game {
private:
    Team& player;
    Team& opponent;

    int turnCounter;

public:
    Game(Team& player, Team& opponent) 
        : turnCounter(0), player(player), opponent(opponent) {}

    void Game::updatePokemonHealthFromFile(const std::string& filePath);

    void incrementTurn() { turnCounter++; }
    int getTurnCounter() const { return turnCounter; }

    Team& getPlayer() { return player; }
    Team& getOpponent() { return opponent; }
    Pokemon& getCurrentPlayerPokemon() { return player.getCurrentPokemon(); }
    Pokemon& getCurrentOpponentPokemon() { return opponent.getCurrentPokemon(); }

    void setPlayerCurrentPokemonIndex(int index) { player.setCurrentPokemonIndex(index); }
    void setOpponentCurrentPokemonIndex(int index) { opponent.setCurrentPokemonIndex(index); }

    std::vector<MoveDamage> calculateMoveDamages(Pokemon& attacker, const Pokemon& defender);
    std::vector<MoveDamage> rankMovesByDamage(Pokemon& playerPokemon, const Pokemon& opponentPokemon);
    std::vector<PokemonMoveRanking> evaluateBestMoves(bool isPlayerTurnStart);
    
    void startGame();
    void processTurn();
    void playGame();
};