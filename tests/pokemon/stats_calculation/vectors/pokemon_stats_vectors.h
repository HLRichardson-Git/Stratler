
#pragma once

#include "map"

#include "pokedex/pokemon_database.h"

using PokemonStatsTestVector = std::map<std::string, PokemonStats>;

static const PokemonStatsTestVector testVectors = {
     {"Sceptile", PokemonStats(281, 206, 167, 309, 185, 372)},
     {"Kyurem-Black", PokemonStats(391, 377, 212, 372, 216, 289)},
     {"Talonflame", PokemonStats(359, 287, 180, 165, 174, 288)},
     {"Slowbro", PokemonStats(394, 167, 330, 236, 216, 96)},
     {"Tyranitar", PokemonStats(341, 367, 257, 203, 236, 243)},
     {"Excadrill", PokemonStats(361, 369, 157, 122, 166, 302)}
};