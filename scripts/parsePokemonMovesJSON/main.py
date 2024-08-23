import json

category_translation = {
    "变化": "STATUS",
    "特殊": "SPECIAL",
    "物理": "PHYSICAL"
}

def load_moves(json_file):
    with open(json_file, 'r', encoding='utf-8') as f:
        return json.load(f)

def generate_cpp_map(moves):
    cpp_code = '''#pragma once

#include <map>
#include <string>

#include "../pokemon/move/move.h"
#include "../pokemon/type/type.h"

using MoveDatabase = std::map<std::string, Move>;

static const MoveDatabase move_database = {
'''
    
    for move in moves:
        name = move['ename']  # English name of the move
        type_str = move['type']  # Type of the move
        power = move['power'] if 'power' in move and move['power'] is not None else -1
        accuracy = move['accuracy'] if 'accuracy' in move and move['accuracy'] is not None else -1
        pp = move['pp'] if 'pp' in move and move['pp'] is not None else -1
        # Translate category from Chinese to English
        category = category_translation.get(move['category'], "UNKNOWN")

        cpp_code += f'    {{"{name}", {{"{name}", {type_str.upper()}, {category}, {power}, {accuracy}, {pp} }} }},\n'

    cpp_code += '''};
'''

    return cpp_code

def save_cpp_header(cpp_code, header_file):
    with open(header_file, 'w', encoding='utf-8') as f:
        f.write(cpp_code)

if __name__ == "__main__":
    json_file = 'data/moves.json'  # Replace with your JSON file path
    header_file = 'move_database.h'
    
    moves = load_moves(json_file)
    cpp_code = generate_cpp_map(moves)
    save_cpp_header(cpp_code, header_file)
    print(f"Header file '{header_file}' has been generated.")
