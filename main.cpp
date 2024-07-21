
#include "engine/state/state.h"
#include "engine/pokemon/pokemon.h"
#include "util/table/table.h"

#include <iostream>

std::string input = 
        "nickname (Kyurem-Black) @ Life Orb\n"
        "Ability: Teravolt\n"
        "EVs: 0 HP / 4 Atk / 0 Def / 252 SpA / 0 SpD / 252 Spe\n"
        "Mild Nature\n"
        "- Ice Beam\n"
        "- Earth Power\n"
        "- Fusion Bolt\n"
        "- Roost\n";

int main(){
    Team teamA("Sceptile", "Kyurem-Black", "Talonflame", "Slowbro", "Tyranitar", "Excadrill");

    teamA.displayTeamsWeaknesses();
    teamA.getPokemon(1).parseInfo(input);
    teamA.getPokemon(1).displayInfo();
    teamA.getPokemon(1).displayMoves();
}
