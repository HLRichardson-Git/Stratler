
#include "gtest/gtest.h"
#include <iostream>

#include "../engine/pokemon/type/type.h"
#include "data/combinedWeaknesses.h"

void testTypeWeaknesses(PokemonType primaryType, PokemonType secondaryType, const std::vector<std::vector<float>>& expectedWeaknesses) {
    PokemonType effectiveType = (secondaryType == primaryType) ? NONE : secondaryType;

    Type type(primaryType, effectiveType);
    std::vector<float> weaknesses = type.getCombinedWeakness();
    ASSERT_EQ(weaknesses.size(), TYPE_AMOUNT) << "Invalid size for combined weaknesses vector";
    
    for (size_t i = 0; i < TYPE_AMOUNT; ++i) {
        if (effectiveType == NONE) {
            EXPECT_FLOAT_EQ(weaknesses[i], expectedWeaknesses[secondaryType][i])
            << "Mismatch at index " << i << " for primary type " << type.typeToString(primaryType)
            << " and secondary type " << type.typeToString(secondaryType);
        } else {
            EXPECT_FLOAT_EQ(weaknesses[i], expectedWeaknesses[effectiveType][i])
            << "Mismatch at index " << i << " for primary type " << type.typeToString(primaryType)
            << " and secondary type " << type.typeToString(secondaryType);
        }
    }
}

// Test case for all secondary types with NORMAL as primary type
TEST(TypeTest, normalTypeWeaknesses) {
    PokemonType primaryType = NORMAL;

    for (int secondary = 0; secondary < TYPE_AMOUNT; ++secondary) {
        PokemonType secondaryType = static_cast<PokemonType>(secondary);
        testTypeWeaknesses(primaryType, secondaryType, normalCombinedWeaknesses);
    }

    EXPECT_TRUE(true); // if no tests failed in testTypeWeaknesses
}

// Test case for all secondary types with FIRE as primary type
TEST(TypeTest, fireTypeWeaknesses) {
    PokemonType primaryType = FIRE;

    for (int secondary = 0; secondary < TYPE_AMOUNT; ++secondary) {
        PokemonType secondaryType = static_cast<PokemonType>(secondary);
        testTypeWeaknesses(primaryType, secondaryType, fireCombinedWeaknesses);
    }

    EXPECT_TRUE(true); // if no tests failed in testTypeWeaknesses
}

// Test case for all secondary types with WATER as primary type
TEST(TypeTest, waterTypeWeaknesses) {
    PokemonType primaryType = WATER;

    for (int secondary = 0; secondary < TYPE_AMOUNT; ++secondary) {
        PokemonType secondaryType = static_cast<PokemonType>(secondary);
        testTypeWeaknesses(primaryType, secondaryType, waterCombinedWeaknesses);
    }

    EXPECT_TRUE(true); // if no tests failed in testTypeWeaknesses
}

// Test case for all secondary types with ELECTRIC as primary type
TEST(TypeTest, electricTypeWeaknesses) {
    PokemonType primaryType = ELECTRIC;

    for (int secondary = 0; secondary < TYPE_AMOUNT; ++secondary) {
        PokemonType secondaryType = static_cast<PokemonType>(secondary);
        testTypeWeaknesses(primaryType, secondaryType, electricCombinedWeaknesses);
    }

    EXPECT_TRUE(true); // if no tests failed in testTypeWeaknesses
}

// Test case for all secondary types with ELECTRIC as primary type
TEST(TypeTest, grassTypeWeaknesses) {
    PokemonType primaryType = GRASS;

    for (int secondary = 0; secondary < TYPE_AMOUNT; ++secondary) {
        PokemonType secondaryType = static_cast<PokemonType>(secondary);
        testTypeWeaknesses(primaryType, secondaryType, grassCombinedWeaknesses);
    }

    EXPECT_TRUE(true); // if no tests failed in testTypeWeaknesses
}

// Test case for all secondary types with ELECTRIC as primary type
TEST(TypeTest, iceTypeWeaknesses) {
    PokemonType primaryType = ICE;

    for (int secondary = 0; secondary < TYPE_AMOUNT; ++secondary) {
        PokemonType secondaryType = static_cast<PokemonType>(secondary);
        testTypeWeaknesses(primaryType, secondaryType, iceCombinedWeaknesses);
    }

    EXPECT_TRUE(true); // if no tests failed in testTypeWeaknesses
}

// Test case for all secondary types with FIGHTING as primary type
TEST(TypeTest, fightingTypeWeaknesses) {
    PokemonType primaryType = FIGHTING;

    for (int secondary = 0; secondary < TYPE_AMOUNT; ++secondary) {
        PokemonType secondaryType = static_cast<PokemonType>(secondary);
        testTypeWeaknesses(primaryType, secondaryType, fightingCombinedWeaknesses);
    }

    EXPECT_TRUE(true); // if no tests failed in testTypeWeaknesses
}

// Test case for all secondary types with POISON as primary type
TEST(TypeTest, poisonTypeWeaknesses) {
    PokemonType primaryType = POISON;

    for (int secondary = 0; secondary < TYPE_AMOUNT; ++secondary) {
        PokemonType secondaryType = static_cast<PokemonType>(secondary);
        testTypeWeaknesses(primaryType, secondaryType, poisonCombinedWeaknesses);
    }

    EXPECT_TRUE(true); // if no tests failed in testTypeWeaknesses
}

// Test case for all secondary types with GROUND as primary type
TEST(TypeTest, groundTypeWeaknesses) {
    PokemonType primaryType = GROUND;

    for (int secondary = 0; secondary < TYPE_AMOUNT; ++secondary) {
        PokemonType secondaryType = static_cast<PokemonType>(secondary);
        testTypeWeaknesses(primaryType, secondaryType, groundCombinedWeaknesses);
    }

    EXPECT_TRUE(true); // if no tests failed in testTypeWeaknesses
}

// Test case for all secondary types with FLYING as primary type
TEST(TypeTest, flyingTypeWeaknesses) {
    PokemonType primaryType = FLYING;

    for (int secondary = 0; secondary < TYPE_AMOUNT; ++secondary) {
        PokemonType secondaryType = static_cast<PokemonType>(secondary);
        testTypeWeaknesses(primaryType, secondaryType, flyingCombinedWeaknesses);
    }

    EXPECT_TRUE(true); // if no tests failed in testTypeWeaknesses
}

// Test case for all secondary types with PSYCHIC as primary type
TEST(TypeTest, psychicTypeWeaknesses) {
    PokemonType primaryType = PSYCHIC;

    for (int secondary = 0; secondary < TYPE_AMOUNT; ++secondary) {
        PokemonType secondaryType = static_cast<PokemonType>(secondary);
        testTypeWeaknesses(primaryType, secondaryType, psychicCombinedWeaknesses);
    }

    EXPECT_TRUE(true); // if no tests failed in testTypeWeaknesses
}

// Test case for all secondary types with BUG as primary type
TEST(TypeTest, bugTypeWeaknesses) {
    PokemonType primaryType = BUG;

    for (int secondary = 0; secondary < TYPE_AMOUNT; ++secondary) {
        PokemonType secondaryType = static_cast<PokemonType>(secondary);
        testTypeWeaknesses(primaryType, secondaryType, bugCombinedWeaknesses);
    }

    EXPECT_TRUE(true); // if no tests failed in testTypeWeaknesses
}

// Test case for all secondary types with ROCK as primary type
TEST(TypeTest, rockTypeWeaknesses) {
    PokemonType primaryType = ROCK;

    for (int secondary = 0; secondary < TYPE_AMOUNT; ++secondary) {
        PokemonType secondaryType = static_cast<PokemonType>(secondary);
        testTypeWeaknesses(primaryType, secondaryType, rockCombinedWeaknesses);
    }

    EXPECT_TRUE(true); // if no tests failed in testTypeWeaknesses
}

// Test case for all secondary types with GHOST as primary type
TEST(TypeTest, ghostTypeWeaknesses) {
    PokemonType primaryType = GHOST;

    for (int secondary = 0; secondary < TYPE_AMOUNT; ++secondary) {
        PokemonType secondaryType = static_cast<PokemonType>(secondary);
        testTypeWeaknesses(primaryType, secondaryType, ghostCombinedWeaknesses);
    }

    EXPECT_TRUE(true); // if no tests failed in testTypeWeaknesses
}

// Test case for all secondary types with DRAGON as primary type
TEST(TypeTest, dragonTypeWeaknesses) {
    PokemonType primaryType = DRAGON;

    for (int secondary = 0; secondary < TYPE_AMOUNT; ++secondary) {
        PokemonType secondaryType = static_cast<PokemonType>(secondary);
        testTypeWeaknesses(primaryType, secondaryType, dragonCombinedWeaknesses);
    }

    EXPECT_TRUE(true); // if no tests failed in testTypeWeaknesses
}

// Test case for all secondary types with DARK as primary type
TEST(TypeTest, darkTypeWeaknesses) {
    PokemonType primaryType = DARK;

    for (int secondary = 0; secondary < TYPE_AMOUNT; ++secondary) {
        PokemonType secondaryType = static_cast<PokemonType>(secondary);
        testTypeWeaknesses(primaryType, secondaryType, darkCombinedWeaknesses);
    }

    EXPECT_TRUE(true); // if no tests failed in testTypeWeaknesses
}

// Test case for all secondary types with STEEL as primary type
TEST(TypeTest, steelTypeWeaknesses) {
    PokemonType primaryType = STEEL;

    for (int secondary = 0; secondary < TYPE_AMOUNT; ++secondary) {
        PokemonType secondaryType = static_cast<PokemonType>(secondary);
        testTypeWeaknesses(primaryType, secondaryType, steelCombinedWeaknesses);
    }
 
    EXPECT_TRUE(true); // if no tests failed in testTypeWeaknesses
}

// Test case for all secondary types with FAIRY as primary type
TEST(TypeTest, fairyTypeWeaknesses) {
    PokemonType primaryType = FAIRY;

    for (int secondary = 0; secondary < TYPE_AMOUNT; ++secondary) {
        PokemonType secondaryType = static_cast<PokemonType>(secondary);
        testTypeWeaknesses(primaryType, secondaryType, fairyCombinedWeaknesses);
    }

    EXPECT_TRUE(true); // if no tests failed in testTypeWeaknesses
}