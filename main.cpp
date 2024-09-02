
#include "engine/state/state.h"
#include "engine/pokemon/pokemon.h"
#include "util/table/table.h"

#include <iostream>

const std::string playerTeamPath = "../../data/player_teams/playerTeam.txt";
const std::string opponentTeamPath = "../../data/player_teams/opponentTeam.txt";

int main(){
    Team teamA(playerTeamPath);
    Team teamB(opponentTeamPath);

    Game game(teamA, teamB);
    //Game game(teamB, teamA);

    //teamA.displayTeamsWeaknesses();
    teamA.displayTeamInfo();
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
    }
}
