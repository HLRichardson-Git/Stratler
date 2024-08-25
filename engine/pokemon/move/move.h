
#pragma once

#include <iostream>
#include <string>

#include "../type/type.h"

const size_t CATEGORY_SIZE = 4;
enum Category {
    NO_CATEGORY,
    STATUS,
    SPECIAL,
    PHYSICAL
};

const std::string categoryStrings[CATEGORY_SIZE] = {
    "None", "Status", "Special", "Physical"
};

struct Move {
    std::string name;
    PokemonType type;
    Category category;
    int power, accuracy, pp;

    Move() : name(""), type(PokemonType::NONE), category(Category::NO_CATEGORY), power(0), accuracy(0), pp(0) {}
    Move(const std::string& moveName) 
        : name(moveName), type(PokemonType::NONE), category(Category::NO_CATEGORY), power(0), accuracy(0), pp(0) {}
    Move(const std::string& moveName, PokemonType type, Category category, int power, int accuracy, int pp) 
        : name(moveName), type(type), category(category), power(power), accuracy(accuracy), pp(pp) {}

    // Copy constructor
    Move(const Move& other) 
        : name(other.name), type(other.type), category(other.category), power(other.power), accuracy(other.accuracy), pp(other.pp) {}

    Move& operator=(const Move& other) {
        if (this != &other) { // Prevent self-assignment
            name = other.name;
            type = other.type;
            category = other.category;
            power = other.power;
            accuracy = other.accuracy;
            pp = other.pp;
        }
        return *this;
    }

    std::string getName() const { return name; }
    PokemonType getType() const { return type; }
    Category getCategory() const { return category; }
    void setName(const std::string& moveName) { name = moveName; }
    void displayMove() { std::cout << "Move: " << name << ", Type: " << typeNames[type] << ", Category: " << categoryStrings[category] << ", Power: " << power
                                    << ", Accuracy: " << accuracy << ", PP: " << pp << std::endl; 
    };
};