
#pragma once

#include <iostream>
#include <string>

#include "../type/type.h"

struct Move {
    std::string name;
    PokemonType type;
    int power, accuracy, pp;

    Move() : name(""), type(PokemonType::NONE), power(0), accuracy(0), pp(0) {}
    Move(const std::string& moveName) 
        : name(moveName), type(PokemonType::NONE), power(0), accuracy(0), pp(0) {}
    Move(const std::string& moveName, PokemonType type, int power, int accuracy, int pp) 
        : name(moveName), type(type), power(power), accuracy(accuracy), pp(pp) {}

    std::string getName() const { return name; }
    void setName(const std::string& moveName) { name = moveName; }
    void displayMove() { std::cout << "Move: " << name << ", Type: " << typeNames[type] << ", Power: " << power
                                    << ", Accuracy: " << accuracy << ", PP: " << pp << std::endl; 
    };
};