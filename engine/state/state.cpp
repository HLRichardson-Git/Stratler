
#include <iostream>
#include <string>
#include <regex>

#include "state.h"
#include "../../util/table/table.h"

bool compareByDamage(const MoveDamage& a, const MoveDamage& b) {
    return a.damage > b.damage;
}

MinimaxResult minimax(const GameState& stateOfGame, int depth, bool isMaximizing) {
    if (stateOfGame.playerHP <= 0) {
        // Player is defeated
        return { std::numeric_limits<int>::min(), MoveDamage(Move(), 0.0, Pokemon()) };
    }
    if (stateOfGame.opponentHP <= 0) {
        // Opponent is defeated
        return { std::numeric_limits<int>::max(), MoveDamage(Move(), 0.0, Pokemon()) };
    }
    if (depth == 0) {
        // Depth limit reached, return heuristic value
        return { stateOfGame.playerHP - stateOfGame.opponentHP, MoveDamage(Move(), 0.0, Pokemon()) };
    }

    if (isMaximizing) {
        int bestScore = std::numeric_limits<int>::min();
        MoveDamage bestMoveDamage(Move(), 0.0, Pokemon()); // Initialize with default values
        for (const auto& moveDamage : stateOfGame.playerMoves) {
            GameState newState = stateOfGame;
            newState.opponentHP -= moveDamage.damage; // Apply player's move damage
            newState.isPlayerTurn = false; // Switch turn
            MinimaxResult result = minimax(newState, depth - 1, false);
            if (result.score > bestScore) {
                bestScore = result.score;
                bestMoveDamage = moveDamage; // Track the best move and Pokémon
            }
        }
        return { bestScore, bestMoveDamage };
    } else {
        int bestScore = std::numeric_limits<int>::max();
        MoveDamage bestMoveDamage(Move(), 0.0, Pokemon()); // Initialize with default values
        for (const auto& moveDamage : stateOfGame.opponentMoves) {
            GameState newState = stateOfGame;
            newState.playerHP -= moveDamage.damage; // Apply opponent's move damage
            newState.isPlayerTurn = true; // Switch turn
            MinimaxResult result = minimax(newState, depth - 1, true);
            if (result.score < bestScore) {
                bestScore = result.score;
                bestMoveDamage = moveDamage; // Track the best move and Pokémon
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

bool confirmChoice() {
    std::string input;
    while (true) {
        std::cout << "Confirm choice (y/n): ";
        std::getline(std::cin, input);

        // Check if the input is exactly one character and is either 'y' or 'n'
        if (input.length() == 1 && (input[0] == 'y' || input[0] == 'n')) {
            return input[0] == 'y';  // Return true if 'y', false if 'n'
        }

        std::cout << "Invalid input. Please enter 'y' or 'n'.\n";
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

std::vector<MoveDamage> Game::rankMovesByDamage(int opponentPokemonIndex) {
    std::vector<MoveDamage> allMoves;
    Pokemon& opponentPokemon = opponent.getPokemon(opponentPokemonIndex);

    // Loop through all of the player's Pokémon
    for (int playerPokemonIndex = 0; playerPokemonIndex < TEAM_SIZE; ++playerPokemonIndex) {
        Pokemon& playerPokemon = player.getPokemon(playerPokemonIndex);

        std::vector<MoveDamage> moveDamages = calculateMoveDamages(playerPokemon, opponentPokemon);

        allMoves.insert(allMoves.end(), moveDamages.begin(), moveDamages.end());
    }

    // Sort the moves by damage percentage in descending order
    std::sort(allMoves.begin(), allMoves.end(), compareByDamage);

    return allMoves;
}

void Game::evaluateMoveViability(int opponentPokemonIndex) {
    std::vector<MoveDamage> rankedMoves = rankMovesByDamage(opponentPokemonIndex);
    Pokemon& opponentPokemon = opponent.getPokemon(opponentPokemonIndex);

    for (MoveDamage& moveDamage : rankedMoves) {
        Pokemon playerPokemon = moveDamage.activePokemon;

        // If a move does 0 damage, but is not a status move then the opponent is immune
        if (moveDamage.move.category != STATUS && moveDamage.damage == 0.0) {
            moveDamage.isViable = false;
            continue;
        }

        // Check if the player's Pokémon is faster
        if (playerPokemon.getStats().getSpeed() > opponentPokemon.getStats().getSpeed()) {
            moveDamage.isViable = true;
            continue;
        }

        // If not faster, check if the Pokémon can survive a hit
        std::vector<MoveDamage> opponentBestMoves = calculateMoveDamages(opponentPokemon, playerPokemon);
        bool canSurvive = false;
        for (const auto& opponentMoveDamage : opponentBestMoves) {
            if (opponentMoveDamage.damage < 100.0) {
                canSurvive = true;
            } else {
                canSurvive = false;
                break;
            }
        }
        moveDamage.isViable = canSurvive;
    }

    std::vector<MoveDamage> viableMoves;
    for (const auto& moveDamage : rankedMoves) {
        if (moveDamage.isViable) {
            viableMoves.push_back(moveDamage);
        }
    }

    // Sort viable moves by damage in descending order
    std::sort(viableMoves.begin(), viableMoves.end(), compareByDamage);

    for (const auto& md : viableMoves) {
    std::cout << md.activePokemon.getName() << " vs " << opponentPokemon.getName()
                << ", Move: " << md.move.getName() << ", Estimated Damage: " 
                << md.damage << "% of HP" << std::endl;
    }
}

void Game::evaluateMatchup(int opponentPokemonIndex) {
    std::vector<MoveDamage> playerMoves = rankMovesByDamage(opponentPokemonIndex);
    Pokemon& opponentPokemon = opponent.getPokemon(opponentPokemonIndex);
    
    // Initialize player Pokemon and their moves
    GameState initialState;
    initialState.playerPokemon = player.getPokemon(0);
    initialState.opponentPokemon = opponentPokemon;
    initialState.playerMoves = playerMoves;
    initialState.opponentMoves = calculateMoveDamages(opponentPokemon, initialState.playerPokemon);
    initialState.playerHP = initialState.playerPokemon.getStats().getHP();
    initialState.opponentHP = initialState.opponentPokemon.getStats().getHP();
    initialState.isPlayerTurn = true; // Assuming the player starts

    // Run the minimax algorithm
    MinimaxResult result = minimax(initialState, 3, true); // 3 is the depth, adjust as needed

    std::cout << "Minimax result score: " << result.score << std::endl;
    std::cout << "Optimal move: " << result.bestMoveDamage.move.getName() << std::endl;
    std::cout << "Optimal Pokemon: " << result.bestMoveDamage.activePokemon.getName() << std::endl;
}

void Game::startGame() {
    unsigned int playerIndex, opponentIndex;
    std::string input;

    do {
        getPlayer().listTeam();
        std::cout << "Which Pokemon will you start with? "; std::cin >> playerIndex;
    
        getOpponent().listTeam();
        std::cout << "Which Pokemon did your opponent start with? "; std::cin >> opponentIndex;

        std::cout << "Is " << getPlayer().getPokemon(playerIndex).getName() << " vs " << getOpponent().getPokemon(opponentIndex).getName() << " correct?" << std::endl;
    } while (!confirmChoice());

    getPlayer().setCurrentPokemonIndex(playerIndex);
    getOpponent().setCurrentPokemonIndex(opponentIndex);
}

void Game::handleAttack(bool isPlayer) {
    int moveIndex;
    std::cout << (isPlayer ? "Choose your move:" : "Opponents move is...") << std::endl;
    for (size_t i = 0; i < 4; ++i) {
        std::cout << i << ": " << (isPlayer ? getPlayer().getCurrentPokemon().getMove(i).getName() : getOpponent().getCurrentPokemon().getMove(i).getName()) << std::endl;
    }
    std::cin >> moveIndex;
}

void Game::handleSwitch(bool isPlayer) {
    int pokemonIndex;
    std::cout << (isPlayer ? "Choose your pokemon:" : "Opponent is switching pokemon...") << std::endl;
    for (size_t i = 0; i < 6; ++i) {
        std::cout << i << ": " << (isPlayer ? getPlayer().getPokemon(i).getName() : getOpponent().getPokemon(i).getName()) << std::endl;
    }
    std::cin >> pokemonIndex;
    if (isPlayer) {
        getPlayer().setCurrentPokemonIndex(pokemonIndex);
    } else {
        getOpponent().setCurrentPokemonIndex(pokemonIndex);
    }
}

void Game::promptForMove(bool isPlayer) {
    std::cout << (isPlayer ? "What will your (PLAYER) move be?" : "What will the OPPONENT do?") << std::endl;
    std::cout << "1. Attack" << std::endl;
    std::cout << "2. Switch" << std::endl;

    int choice;
    std::cin >> choice;

    switch (choice) {
        case 1:
            handleAttack(isPlayer);
            break;
        case 2:
            handleSwitch(isPlayer);
            break;
        default:
            std::cout << "Invalid choice, please try again." << std::endl;
            promptForMove(isPlayer);
            break;
    }
}


void Game::processTurn() {
    evaluateMatchup(getOpponent().getCurrentPokemonIndex());
    promptForMove(true);  // Player's turn
    promptForMove(false); // Opponent's turn
}

void Game::updateHealth() {
    std::cout << "Your " << getCurrentPlayerPokemon().getName() <<"'s HP: " << getCurrentPlayerPokemon().getStats().getHP() << std::endl;
    std::cout << "Opponent's " << getCurrentOpponentPokemon().getName() << "'s HP: " << getCurrentOpponentPokemon().getStats().getHP() << std::endl;
    
    // Ask for damage dealt and received
    std::cout << "How much damage did you deal to the opponent?" << std::endl;
    int playerDamage;
    std::cin >> playerDamage;

    std::cout << "How much damage did the opponent deal to you?" << std::endl;
    int opponentDamage;
    std::cin >> opponentDamage;

    // Update Pokémon health based on the actual damage
    int playerHP = getCurrentPlayerPokemon().getStats().getHP() - opponentDamage;
    int opponentHP = getCurrentOpponentPokemon().getStats().getHP() - playerDamage;
    
    // Update Pokémon stats (assuming you have methods for this)
    getCurrentPlayerPokemon().setHP(playerHP);
    getCurrentOpponentPokemon().setHP(opponentHP);

    std::cout << "Updated players " << getCurrentPlayerPokemon().getName() << "'s HP: " << getCurrentPlayerPokemon().getStats().getHP() << std::endl;
    std::cout << "Updated opponent's " << getCurrentOpponentPokemon().getName() << "'s HP: " << getCurrentOpponentPokemon().getStats().getHP() << std::endl;
}

void Game::playGame() {
    startGame();
    while (!isGameOver()) {
        std::cout << "\n == Turn " << turnCounter + 1 << " ==" << std::endl;
        processTurn();
        updateHealth();
        incrementTurn();
    }
}

bool Game::isGameOver() {
    bool gameOver = false;
    std::cout << "Is the game over? ";
    gameOver = confirmChoice();
    return gameOver;
}