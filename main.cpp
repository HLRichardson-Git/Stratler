
#include "engine/pokemon/pokemon.h"
#include "util/table/table.h"

#include <iostream>

int main(){
    Pokemon first("Excadrill", GROUND, STEEL);
    Pokemon second("Kyurem-Black", DRAGON, ICE);
    Pokemon third("Gallade-Mega", PSYCHIC, FIGHTING);
    Pokemon fourth("Zapdos", ELECTRIC, FLYING);
    Pokemon fifth("Tentacruel", WATER, POISON);
    Pokemon sixth("Talonflame", FIRE, FLYING);

    std::vector<std::string> headers = {"Normal", "Fire", "Water", "Electric", "Grass", "Ice", "Fighting",
                 "Poison", "Ground", "Flying", "Psychic", "Bug", "Rock", "Ghost", "Dragon", "Dark", "Steel", "Fairy"};

    std::vector<float> excadrillWeaknesses = first.getWeaknesses();
    std::vector<float> kyuremBlackWeaknesses = second.getWeaknesses();
    std::vector<float> galladeMegakWeaknesses = third.getWeaknesses();
    std::vector<float> zapdosWeaknesses = fourth.getWeaknesses();
    std::vector<float> tentacruelWeaknesses = fifth.getWeaknesses();
    std::vector<float> talonflamekWeaknesses = sixth.getWeaknesses();

    Table table;
    // Adding headers
    table.addHeader("Type", headers);
    // Adding rows for combined weaknesses
    table.addRow(first.getName(), excadrillWeaknesses);
    table.addRow(second.getName(), kyuremBlackWeaknesses);
    table.addRow(third.getName(), galladeMegakWeaknesses);
    table.addRow(fourth.getName(), zapdosWeaknesses);
    table.addRow(fifth.getName(), tentacruelWeaknesses);
    table.addRow(sixth.getName(), talonflamekWeaknesses);

    table.print();
}
