
#include "engine/state/state.h"
#include "engine/pokemon/pokemon.h"
#include "util/table/table.h"

#include <iostream>

const std::string playerTeamPath = "../data/player_teams/playerTeam.txt";
const std::string opponentTeamPath = "../data/player_teams/opponentTeam.txt";

void playTurn(Game& game) {
    int playerIndex, opponentIndex;

    game.getPlayer().listTeam();
    std::cout << "Enter the index of your active Pokemon (0-5): "; std::cin >> playerIndex;

    game.getOpponent().listTeam();
    std::cout << "Enter the index of opponent's active Pokemon (0-5): "; std::cin >> opponentIndex;

    game.setPlayerCurrentPokemonIndex(playerIndex);
    game.setOpponentCurrentPokemonIndex(opponentIndex);

    std::cout << "Evaluating the best move against: " << game.getOpponent().getPokemon(opponentIndex).getName() << std::endl;
    game.evaluateMatchup(opponentIndex);

    // Optionally consider switching
    std::string switchChoice;
    std::cout << "Would you like to consider switching? (yes/no): ";
    std::cin >> switchChoice;

    // Optionally display the turn number
    std::cout << "Turn " << game.getTurnCounter() << " complete.\n";

    game.incrementTurn();
}

int main(){
    Team teamA(playerTeamPath);
    Team teamB(opponentTeamPath);
    Game game(teamA, teamB);
    
    std::cout << "Welcome to the Pokemon Showdown Assistant Bot!\n";

    /*while (true) {
        std::string continueGame;
        playTurn(game);
        
        std::cout << "Would you like to play another turn? (yes/no): ";
        std::cin >> continueGame;
        if (continueGame == "no") {
            break;
        }
    }*/
    game.playGame();
    
    /*teamA.displayTeamInfo();
    teamB.displayTeamInfo();

    std::cout << "Values may be wrong since these values do not account for items" << std::endl;
    //std::vector<MoveDamage> temp = game.rankMovesByDamage(0);
    //game.evaluateMoveViability(1);
    //game.evaluateMatchup(0);
    for (int i = 0; i < 6; i++) {
        std::cout << "Against opponent pokemon: " << teamB.getPokemon(i).getName() << std::endl;
        std::cout << "The optimal player move is:" << std::endl;
        game.evaluateMatchup(i);
        std::cout << std::endl;
    }*/

   return 0;
}
