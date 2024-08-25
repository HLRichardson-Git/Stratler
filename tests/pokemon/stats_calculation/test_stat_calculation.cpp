
#include "gtest/gtest.h"
#include <iostream>

#include "state/state.h"
#include "vectors/pokemon_stats_vectors.h"

TEST(TeamStatsTest, CheckStatsAgainstKnownValues) {
    Team team("../../tests/pokemon/stats_calculation/vectors/test_team.txt");

    for(int i = 0; i < 6; i++) {
        const auto& name = team.getPokemon(i).getName();
        auto it = testVectors.find(name);

        ASSERT_NE(it, testVectors.end()) << "Pokemon " << name << " not found in test vectors";

        const PokemonStats& expectedStats = it->second;
        const PokemonStats& computedStats = team.getPokemon(i).getStats();

        EXPECT_EQ(computedStats.getHP(), expectedStats.getHP()) << "HP mismatch for " << name;
        EXPECT_EQ(computedStats.getAttack(), expectedStats.getAttack()) << "Attack mismatch for " << name;
        EXPECT_EQ(computedStats.getDefense(), expectedStats.getDefense()) << "Defense mismatch for " << name;
        EXPECT_EQ(computedStats.getSpecialAttack(), expectedStats.getSpecialAttack()) << "Special Attack mismatch for " << name;
        EXPECT_EQ(computedStats.getSpecialDefense(), expectedStats.getSpecialDefense()) << "Special Defense mismatch for " << name;
        EXPECT_EQ(computedStats.getSpeed(), expectedStats.getSpeed()) << "Speed mismatch for " << name;
    }
}