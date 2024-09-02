
#include <regex>

#include "state.h"
#include "../../util/table/table.h"

bool compareByDamage(const MoveDamage& a, const MoveDamage& b) {
    return a.damage > b.damage;
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

/*void Game::calculateBestMove(int playerPokemonIndex, int opponentPokemonIndex, int depth) {
    for (int i = 0; i < 4; i++) {
        //Team tempOpponentTeam = opponent;

        // Simulate the move
        double damage = player.getPokemon(playerPokemonIndex).useMove(i, opponent.getPokemon(opponentPokemonIndex));

        // Display the move name and damage
        //Move move = player.getPokemon(playerPokemonIndex).getMove(i);
        std::cout << "Move: " << player.getPokemon(playerPokemonIndex).getMove(i).getName() << ", Estimated Damage: " << damage << std::endl;
    }

}*/

/*void Game::calculateBestMove(int opponentPokemonIndex) {
    std::vector<MoveDamage> allMovesWithDamage;

    // Loop through each Pokémon in the player's team
    for (int i = 0; i < TEAM_SIZE; i++) {
        Pokemon& currentPokemon = player.getPokemon(i);
        std::string& pokemonName = currentPokemon.getName();

        // Loop through each move of the Pokémon
        for (int j = 0; j < 4; j++) {
            // Calculate damage of the move
            double damage = currentPokemon.useMove(j, opponent.getPokemon(opponentPokemonIndex));

            // Store the move, its damage, and the Pokémon's name
            allMovesWithDamage.emplace_back(currentPokemon.getMove(j), damage, pokemonName);
        }
    }

    // Sort the moves by damage in descending order
    std::sort(allMovesWithDamage.begin(), allMovesWithDamage.end(), compareByDamage);

    // Display the ranked moves
    for (const auto& moveDamage : allMovesWithDamage) {
        std::cout << "Pokemon: " << moveDamage.pokemonName 
                  << ", Move: " << moveDamage.move.getName() 
                  << ", Estimated Damage: " << moveDamage.damage 
                  << std::endl;
    }
}*/

/*void Game::calculateBestMove(int opponentPokemonIndex) {
    std::vector<MoveDamage> moveDamageList;

    // Loop through all of the player's Pokémon
    for (int playerPokemonIndex = 0; playerPokemonIndex < TEAM_SIZE; ++playerPokemonIndex) {
        Pokemon& playerPokemon = player.getPokemon(playerPokemonIndex);

        // Loop through all 4 moves of the Pokémon
        for (int i = 0; i < 4; i++) {
            Move move = playerPokemon.getMove(i);
            
            // Calculate the damage the move would do to the opponent's Pokémon
            double damage = playerPokemon.useMove(i, opponent.getPokemon(opponentPokemonIndex));

            // Add the move, damage, and Pokémon name to the list
            moveDamageList.emplace_back(move, damage, playerPokemon.getName());
        }
    }

    // Sort the moves by damage in descending order
    std::sort(moveDamageList.begin(), moveDamageList.end(), compareByDamage);

    // Display the sorted moves
    for (const auto& md : moveDamageList) {
        std::cout << md.pokemonName << " vs " << opponent.getPokemon(opponentPokemonIndex).getName()
                  << ", Move: " << md.move.getName() << ", Estimated Damage: " << md.damage << std::endl;
    }
}*/

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

    /*for (const auto& md : allMoves) {
        std::cout << md.activePokemon.getName() << " vs " << opponentPokemon.getName()
                  << ", Move: " << md.move.getName() << ", Estimated Damage: " 
                  << md.damage << "% of HP" << std::endl;
    }*/

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
            // TODO: They could be faster, but we need to go in depth and see if the player can kill before the
            //       opponent kills out pokemon.
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