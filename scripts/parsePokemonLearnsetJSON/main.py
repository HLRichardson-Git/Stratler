import json

def load_learnsets(json_file):
    with open(json_file, 'r', encoding='utf-8') as f:
        return json.load(f)

def generate_cpp_map(learnsets):
    cpp_code = '''#pragma once

#include <map>
#include <string>
#include <unordered_set>

using MoveSet = std::unordered_set<std::string>;
using LearnsetsDatabase = std::map<std::string, MoveSet>;

static const LearnsetsDatabase learnsets_database = {
'''

    for pokemon, moves_data in learnsets.items():
        move_set = set()

        # Iterate through each category of moves (level, tm, egg, tutor, etc.)
        for category, moves in moves_data.items():
            if category == 'level':
                # Include moves from the 'level' category, ignoring level numbers
                move_set.update(moves.values())
            else:
                # Check if moves is a list or dictionary and extract move names accordingly
                if isinstance(moves, dict):
                    for move_list in moves.values():
                        if isinstance(move_list, list):
                            move_set.update(move_list)
                        else:
                            move_set.add(move_list)
                elif isinstance(moves, list):
                    move_set.update(moves)

        # Convert move_set to C++ unordered_set initialization
        cpp_code += f'    {{"{pokemon}", {{"'
        cpp_code += '", "'.join(move_set)
        cpp_code += '"}},\n'

    cpp_code += '''};

'''

    return cpp_code

def save_cpp_header(cpp_code, header_file):
    with open(header_file, 'w', encoding='utf-8') as f:
        f.write(cpp_code)

if __name__ == "__main__":
    json_file = 'data/gen6Learnset.json'  # Replace with your JSON file path
    header_file = 'learnsets_database.h'
    
    learnsets = load_learnsets(json_file)
    cpp_code = generate_cpp_map(learnsets)
    save_cpp_header(cpp_code, header_file)
    print(f"Header file '{header_file}' has been generated.")
