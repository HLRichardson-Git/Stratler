
#include "engine/state/state.h"
#include "engine/pokemon/pokemon.h"
#include "util/table/table.h"

#include <iostream>

int main(){
    Team teamA("Sceptile", "Kyurem-Black", "Talonflame", "Slowbro", "Tyranitar", "Excadrill");

    teamA.displayTeamsWeaknesses();
    teamA.getPokemon(0).displayInfo();
}
