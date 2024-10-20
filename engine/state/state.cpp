
#include <iostream>
#include <string>
#include <regex>
#include <unordered_map>

#include "state.h"
#include "../../util/table/table.h"

bool compareByDamage(const MoveDamage& a, const MoveDamage& b) {
    return a.damage > b.damage;
}

MinimaxResult minimax(const GameState& stateOfGame, int depth, bool isMaximizing) {
    // Base conditions: Check if a Pokémon fainted or depth limit reached
    if (stateOfGame.playerHP <= 0) {
        return { std::numeric_limits<int>::min(), MoveDamage(Move(), 0.0, stateOfGame.playerPokemon) };  // Player is defeated
    }
    if (stateOfGame.opponentHP <= 0) {
        return { std::numeric_limits<int>::max(), MoveDamage(Move(), 0.0, stateOfGame.opponentPokemon) };  // Opponent is defeated
    }
    if (depth == 0) {
        // Heuristic: Return the difference in HP (higher is better for player)
        int heuristicValue = stateOfGame.playerHP - stateOfGame.opponentHP;
        return { heuristicValue, MoveDamage(Move(), 0.0, stateOfGame.playerPokemon) };
    }

    // Maximizing player's turn
    if (isMaximizing) {
        int bestScore = std::numeric_limits<int>::min();
        MoveDamage bestMoveDamage(Move(), 0.0, stateOfGame.playerPokemon);  // Default move

        // Loop through all moves the player can use
        for (const auto& moveDamage : stateOfGame.playerMoves) {
            GameState newState = stateOfGame;  // Clone the current game state for this move

            // If the player is switching (not the active Pokémon), opponent attacks first
            if (!newState.isPlayerTurn) {
                // Apply opponent's move first
                newState.playerHP -= stateOfGame.opponentMoves[0].damage;  // Assume opponent uses their best move
                if (newState.playerHP <= 0) {
                    return { std::numeric_limits<int>::min(), MoveDamage(Move(), 0.0, stateOfGame.playerPokemon) };
                }
            }
            // Apply the player's move
            newState.opponentHP -= moveDamage.damage;

            if (newState.opponentHP <= 0) {
                return { std::numeric_limits<int>::max(), MoveDamage(Move(), 0.0, stateOfGame.playerPokemon) };  // Player fainted
            }

            // Switch turns and recursively evaluate
            newState.isPlayerTurn = false;
            MinimaxResult result = minimax(newState, depth - 1, false);

            // Keep track of the best result
            if (result.score > bestScore) {
                bestScore = result.score;
                bestMoveDamage = moveDamage;
            }
        }

        return { bestScore, bestMoveDamage };

    } else {  // Minimizing opponent's turn
        int bestScore = std::numeric_limits<int>::max();
        MoveDamage bestMoveDamage(Move(), 0.0, stateOfGame.opponentPokemon);  // Default move

        // Loop through all moves the opponent can use
        for (const auto& moveDamage : stateOfGame.opponentMoves) {
            GameState newState = stateOfGame;

            // If the opponent is switching, the player attacks first
            if (newState.isPlayerTurn) {
                // Apply player's move first
                newState.opponentHP -= stateOfGame.playerMoves[0].damage;  // Assume player uses their best move
                //if (newState.opponentHP <= 0) continue;  // Opponent fainted, skip this move
                if (newState.opponentHP <= 0) {
                    return { std::numeric_limits<int>::max(), MoveDamage(Move(), 0.0, stateOfGame.playerPokemon) };  // Opponent fainted
                }

            }

            // Apply opponent's move
            newState.playerHP -= moveDamage.damage;  // Opponent's move

            // Check if the player's Pokémon will faint after this move
            if (newState.playerHP <= 0) {
                return { std::numeric_limits<int>::min(), MoveDamage(Move(), 0.0, stateOfGame.playerPokemon) };  // Player fainted
            }

            // Switch turns and recursively evaluate
            newState.isPlayerTurn = true;
            MinimaxResult result = minimax(newState, depth - 1, true);

            // Keep track of the worst result (opponent tries to minimize player's score)
            if (result.score < bestScore) {
                bestScore = result.score;
                bestMoveDamage = moveDamage;
            }
        }

        return { bestScore, bestMoveDamage };
    }
}


void Team::loadFromFile(const std::string& filePath) {
        std::ifstream file(filePath);
        if (!file.is_open()) {
            std::cerr << "Error: Could not open file " << filePath << std::endl;
            return;
        }

        std::string line;
        std::string pokemonInfo;
        std::vector<std::string> pokemonBlocks;

        // Read the file line by line
        while (std::getline(file, line)) {
            if (line.empty()) {
                // Each empty line indicates the end of a Pokémon block
                if (!pokemonInfo.empty()) {
                    pokemonBlocks.push_back(pokemonInfo);
                    pokemonInfo.clear();
                }
            } else {
                pokemonInfo += line + "\n";
            }
        }
        // Add the last Pokémon block if there's no trailing empty line
        if (!pokemonInfo.empty()) {
            pokemonBlocks.push_back(pokemonInfo);
        }

        file.close();

        // Create Pokémon from each block
        size_t counter = 0;
        for (const std::string& block : pokemonBlocks) {
            std::regex regexName(R"(([^ @]+) @)");
            std::smatch matchName;
            std::string pokemonName;

            if (std::regex_search(block, matchName, regexName)) {
                pokemonName = matchName[1];
            }

            // Initialize the Pokémon with the name
            Pokemon pokemon(pokemonName);
            pokemon.parseInfo(block);

            roster[counter] = pokemon;
            counter++;
        }
    }

void Team::calculateTeamWeaknesses() {
    for (int i = 0 ; i < TEAM_SIZE; i++) {
        teamWeaknesses[i] = roster[i].types.getCombinedWeakness();
    }
}

void Team::displayTeamsWeaknesses() {
    const std::vector<std::string> headers = {
        "Normal", "Fire", "Water", "Electric", "Grass", "Ice", "Fighting", "Poison", "Ground", 
        "Flying", "Psychic", "Bug", "Rock", "Ghost", "Dragon", "Dark", "Steel", "Fairy"
    };
    
    Table table;
    table.addHeader("Type", headers);
    table.addRow(roster[0].getName(), teamWeaknesses[0]);
    table.addRow(roster[1].getName(), teamWeaknesses[1]);
    table.addRow(roster[2].getName(), teamWeaknesses[2]);
    table.addRow(roster[3].getName(), teamWeaknesses[3]);
    table.addRow(roster[4].getName(), teamWeaknesses[4]);
    table.addRow(roster[5].getName(), teamWeaknesses[5]);
    table.print();
}

void Team::displayTeamInfo() {
    getPokemon(0).displayInfo();
    getPokemon(1).displayInfo();
    getPokemon(2).displayInfo();
    getPokemon(3).displayInfo();
    getPokemon(4).displayInfo();
    getPokemon(5).displayInfo();
}

void Team::listTeam() {
    std::cout << "0: " << getPokemon(0).getName() << std::endl;
    std::cout << "1: " << getPokemon(1).getName() << std::endl;
    std::cout << "2: " << getPokemon(2).getName() << std::endl;
    std::cout << "3: " << getPokemon(3).getName() << std::endl;
    std::cout << "4: " << getPokemon(4).getName() << std::endl;
    std::cout << "5: " << getPokemon(5).getName() << std::endl;
}   

void Game::updatePokemonHealthFromFile(const std::string& filePath) {
    std::ifstream inputFile(filePath);
    if (!inputFile.is_open()) {
        std::cerr << "Error: Could not open file " << filePath << std::endl;
        return;
    }

    std::unordered_map<std::string, double> healthMap;
    std::string line;

    while (std::getline(inputFile, line)) {
        // Skip empty lines or comments (lines starting with '#')
        if (line.empty() || line[0] == '#') {
            continue;
        }

        std::istringstream iss(line);
        std::string pokemonName;
        double healthPercentage;

        if (!(iss >> pokemonName >> healthPercentage)) {
            std::cerr << "Error: Invalid format in line: " << line << std::endl;
            continue;  // Skip invalid lines
        }

        healthMap[pokemonName] = healthPercentage;
    }

    inputFile.close();

    // Update player's Pokémon health
    for (int i = 0; i < TEAM_SIZE; ++i) {
        Pokemon& playerPokemon = player.getPokemon(i);
        std::string pokemonName = playerPokemon.getName();
        
        if (healthMap.find(pokemonName) != healthMap.end()) {
            double newHP = playerPokemon.getStats().getHP() * (healthMap[pokemonName] / 100.0);
            playerPokemon.setHP(newHP);
        }
    }
}

std::vector<MoveDamage> Game::calculateMoveDamages(Pokemon& attacker, const Pokemon& defender) {
    std::vector<MoveDamage> moveDamageList;
    int defenderHP = defender.getStats().getHP();

    for (int i = 0; i < 4; i++) {
        Move move = attacker.getMove(i);
        double damage = attacker.useMove(i, defender);
        double damagePercentage = (damage / defenderHP) * 100;
        moveDamageList.emplace_back(move, damagePercentage, attacker);
    }

    return moveDamageList;
}

std::vector<MoveDamage> Game::rankMovesByDamage(Pokemon& playerPokemon, const Pokemon& opponentPokemon) {
    std::vector<MoveDamage> moveDamages = calculateMoveDamages(playerPokemon, opponentPokemon);
    // Sort moves by damage in descending order (highest damage first)
    std::sort(moveDamages.begin(), moveDamages.end(), compareByDamage);

    return moveDamages;
}

std::vector<PokemonMoveRanking> Game::evaluateBestMoves(bool isPlayerTurnStart) {
    std::vector<PokemonMoveRanking> moveRankings;
    Pokemon& opponentPokemon = opponent.getCurrentPokemon();

    //for (const Pokemon& pokemon : player.getPokemon()) {
    for (int i = 0; i < TEAM_SIZE; i++) {
        Pokemon playerPokemon = player.getPokemon(i);
        // Skip fainted Pokémon
        if (playerPokemon.getStats().getHP() <= 0) continue;

        bool willSwitchIn = (i != player.getCurrentPokemonIndex());

        // Set up the initial game state
        GameState newState {
            playerPokemon,
            opponentPokemon,
            rankMovesByDamage(playerPokemon, opponentPokemon),
            rankMovesByDamage(opponentPokemon, playerPokemon),
            playerPokemon.getStats().getHP(),
            opponentPokemon.getStats().getHP(),
            willSwitchIn ? false : isPlayerTurnStart
        };

        // Get the best move for this Pokémon against the opponent
        MinimaxResult result = minimax(newState, /* depth */ 4, true);

        // Penalize the score for switching in
        if (willSwitchIn && (result.score > std::numeric_limits<int>::min() + 10)) {
            result.score -= 10;  // Apply a switch penalty
        }

        // Store the Pokémon, its best move, and the evaluation score
        PokemonMoveRanking ranking = {playerPokemon, result.bestMoveDamage, result.score};
        moveRankings.push_back(ranking);
    }

    // Sort the list by the evaluation score, descending (higher score = better move)
    std::sort(moveRankings.begin(), moveRankings.end(), [](const PokemonMoveRanking& a, const PokemonMoveRanking& b) {
        return a.score > b.score;
    });

    return moveRankings;  // Return the ranked list of Pokémon and their best moves
}

void Game::processTurn() {
    unsigned int playerIndex, opponentIndex;

    std::cout << "Please input your active Pokemon:" << std::endl;
    getPlayer().listTeam();
    std::cin >> playerIndex;

    std::cout << "Please input the opponent's active Pokemon:" << std::endl;
    getOpponent().listTeam();
    std::cin >> opponentIndex;


    // Set current Pokémon for both player and opponent
    getPlayer().setCurrentPokemonIndex(playerIndex);
    getOpponent().setCurrentPokemonIndex(opponentIndex);

    //updatePokemonHealthFromFile("../../data/player_teams/playerTeamHealth.txt");

    // Now that you have the updated state, evaluate the best move
    std::vector<PokemonMoveRanking> rankings = evaluateBestMoves(true);

    // Display the ranked list to the player
    for (const auto& ranking : rankings) {
        std::cout << "Pokemon: " << ranking.pokemon.getName() 
                << " - Best Move: " << ranking.bestMove.move.getName() 
                << " - Damage: " << ranking.bestMove.damage 
                << " - Score: " << ranking.score << std::endl;
    }
}

void Game::playGame() {
    while (true) {
        std::cout << "\n == Turn " << turnCounter + 1 << " ==" << std::endl;
        processTurn();

        incrementTurn();
        std::cout << "Press Enter to continue to the next turn...";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Clear any previous input
        std::cin.get();
    }
}