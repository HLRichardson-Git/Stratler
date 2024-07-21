
#pragma once

#include <map>

/*enum Natures {
    Adamant,
    Bashful,
    Bold,
    Brave,
    Calm,
    Careful,
    Docile,
    Gentle,

};*/
enum class Nature {
    Hardy, Lonely, Brave, Adamant, Naughty,
    Bold, Docile, Relaxed, Impish, Lax,
    Timid, Hasty, Serious, Jolly, Naive,
    Modest, Mild, Quiet, Bashful, Rash,
    Calm, Gentle, Sassy, Careful, Quirky
};

const std::string natureNames[25] = {
    "Hardy", "Lonely", "Brave", "Adamant", "Naughty",
    "Bold", "Docile", "Relaxed", "Impish", "Lax",
    "Timid", "Hasty", "Serious", "Jolly", "Naive",
    "Modest", "Mild", "Quiet", "Bashful", "Rash",
    "Calm", "Gentle", "Sassy", "Careful", "Quirky"
};

struct NatureModifiers {
    float attackModifier;
    float defenseModifier;
    float specialAttackModifier;
    float specialDefenseModifier;
    float speedModifier;
};

std::string natureToString(Nature nature);

const std::map<Nature, NatureModifiers> natureModifiersMap = {
    {Nature::Hardy,  {1.0f, 1.0f, 1.0f, 1.0f, 1.0f}},
    {Nature::Lonely, {1.1f, 0.9f, 1.0f, 1.0f, 1.0f}},
    {Nature::Brave,  {1.1f, 1.0f, 1.0f, 1.0f, 0.9f}},
    {Nature::Adamant,{1.1f, 1.0f, 0.9f, 1.0f, 1.0f}},
    {Nature::Naughty,{1.1f, 1.0f, 1.0f, 0.9f, 1.0f}},
    {Nature::Bold,   {0.9f, 1.1f, 1.0f, 1.0f, 1.0f}},
    {Nature::Docile, {1.0f, 1.0f, 1.0f, 1.0f, 1.0f}},
    {Nature::Relaxed,{1.0f, 1.1f, 1.0f, 1.0f, 0.9f}},
    {Nature::Impish, {1.0f, 1.1f, 0.9f, 1.0f, 1.0f}},
    {Nature::Lax,    {1.0f, 1.1f, 1.0f, 0.9f, 1.0f}},
    {Nature::Timid,  {0.9f, 1.0f, 1.0f, 1.0f, 1.1f}},
    {Nature::Hasty,  {1.0f, 0.9f, 1.0f, 1.0f, 1.1f}},
    {Nature::Serious,{1.0f, 1.0f, 1.0f, 1.0f, 1.0f}},
    {Nature::Jolly,  {1.0f, 1.0f, 0.9f, 1.0f, 1.1f}},
    {Nature::Naive,  {1.0f, 1.0f, 1.0f, 0.9f, 1.1f}},
    {Nature::Modest, {0.9f, 1.0f, 1.1f, 1.0f, 1.0f}},
    {Nature::Mild,   {1.0f, 0.9f, 1.1f, 1.0f, 1.0f}},
    {Nature::Quiet,  {1.0f, 1.0f, 1.1f, 1.0f, 0.9f}},
    {Nature::Bashful,{1.0f, 1.0f, 1.0f, 1.0f, 1.0f}},
    {Nature::Rash,   {1.0f, 1.0f, 1.1f, 0.9f, 1.0f}},
    {Nature::Calm,   {0.9f, 1.0f, 1.0f, 1.1f, 1.0f}},
    {Nature::Gentle, {1.0f, 0.9f, 1.0f, 1.1f, 1.0f}},
    {Nature::Sassy,  {1.0f, 1.0f, 1.0f, 1.1f, 0.9f}},
    {Nature::Careful,{1.0f, 1.0f, 0.9f, 1.1f, 1.0f}},
    {Nature::Quirky, {1.0f, 1.0f, 1.0f, 1.0f, 1.0f}}
};