
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
    game.calculateBestMove(1, 0, 0);
    //game.calculateBestMove(0, 1, 0);
}
