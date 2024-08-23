
#include "engine/state/state.h"
#include "engine/pokemon/pokemon.h"
#include "util/table/table.h"

#include <iostream>

std::string mawileInput = 
        "nickname (Mawile) @ Mawilite\n"
        "Ability: Intimidate\n"
        "EVs: 248 HP / 16 Atk / 0 Def / 0 SpA / 244 SpD / 0 Spe\n"
        "Adamant Nature\n"
        "- Iron Head\n"
        "- Play Rough\n"
        "- Sucker Punch\n"
        "- Baton Pass\n";

int main(){
    //Team teamA("Sceptile", "Kyurem-Black", "Talonflame", "Slowbro", "Tyranitar", "Excadrill");
    Team teamA(Side::PLAYER);
    teamA.displayTeamInfo();
    Team teamB("Mawile", "Zapdos", "Ferrothorn", "Garchomp", "Ditto", "Toxicroak");
    //teamA.getPokemon(1).parseInfo(kyuremInput);
    teamB.getPokemon(0).parseInfo(mawileInput);

    Game game(teamA, teamB);
    //Game game(teamB, teamA);

    //teamA.displayTeamsWeaknesses();
    //teamA.getPokemon(1).displayInfo();
    //teamA.displayTeamInfo();
    teamB.getPokemon(0).displayInfo();

    std::cout << "Values may be wrong since these values do not account for items" << std::endl;
    game.calculateBestMove(1, 0, 0);
    //game.calculateBestMove(0, 1, 0);
}
