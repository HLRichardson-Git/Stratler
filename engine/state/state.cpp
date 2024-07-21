
#include "state.h"
#include "../../util/table/table.h"

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