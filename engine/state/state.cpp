
#include <regex>

#include "state.h"
#include "../../util/table/table.h"

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

void Game::calculateBestMove(int playerPokemonIndex, int opponentPokemonIndex, int depth) {
    /*double bestValue = -std::numeric_limits<double>::infinity();
    int bestMoveIndex = -1;

    for (int i = 0; i < playerTeam.getActivePokemon().getMoveCount(); i++) {
        Team tempOpponentTeam = opponentTeam;
        // Simulate the move
        playerTeam.getActivePokemon().useMove(i, tempOpponentTeam.getActivePokemon());
        double moveValue = minimax(playerTeam, tempOpponentTeam, false, depth);
        if (moveValue > bestValue) {
            bestValue = moveValue;
            bestMoveIndex = i;
        }
    }

    return bestMoveIndex;*/

    for (int i = 0; i < 4; i++) {
        //Team tempOpponentTeam = opponent;

        // Simulate the move
        double damage = player.getPokemon(playerPokemonIndex).useMove(i, opponent.getPokemon(opponentPokemonIndex));

        // Display the move name and damage
        //Move move = player.getPokemon(playerPokemonIndex).getMove(i);
        std::cout << "Move: " << player.getPokemon(playerPokemonIndex).getMove(i).getName() << ", Estimated Damage: " << damage << std::endl;
    }

}