import json

def load_pokedex(json_file):
    with open(json_file, 'r', encoding='utf-8') as f:
        return json.load(f)

def generate_cpp_map(pokedex):
    cpp_code = '''#pragma once

#include <map>
#include <string>
#include <array>

#include "../pokemon/type/type.h"

struct PokemonData {
    PokemonType primaryType;
    PokemonType secondaryType;
    std::array<int, 6> stats; // HP, Attack, Defense, Special Attack, Special Defense, Speed

    PokemonData(const std::string& t1, const std::string& t2, const std::array<int, 6>& s)
        : type1(t1), type2(t2), stats(s) {}
};

using PokemonDatabase = std::map<std::string, PokemonData>;

static const PokemonDatabase pokedex = {
'''

    for pokemon in pokedex:
        name = pokemon['name']['english']
        types = pokemon.get('type', [])
        type1 = types[0] if len(types) > 0 else "None"
        type2 = types[1] if len(types) > 1 else "None"
        base_stats = pokemon.get('base', {})
        stats_array = [
            base_stats.get('HP', 0),
            base_stats.get('Attack', 0),
            base_stats.get('Defense', 0),
            base_stats.get('Sp. Attack', 0),
            base_stats.get('Sp. Defense', 0),
            base_stats.get('Speed', 0)
        ]
        
        cpp_code += f'    {{"{name}", PokemonData({type1.upper()}, {type2.upper()}, {{{", ".join(map(str, stats_array))}}})}},\n'

    cpp_code += '''};

'''

    return cpp_code

def save_cpp_header(cpp_code, header_file):
    with open(header_file, 'w', encoding='utf-8') as f:
        f.write(cpp_code)

if __name__ == "__main__":
    json_file = 'data/pokedex.json'  # Replace with your JSON file path
    header_file = 'pokemon_database.h'
    
    pokedex = load_pokedex(json_file)
    cpp_code = generate_cpp_map(pokedex)
    save_cpp_header(cpp_code, header_file)
    print(f"Header file '{header_file}' has been generated.")
