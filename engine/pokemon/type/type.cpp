#include "type.h"

#include <iostream>

std::vector<float> Type::getCombinedWeakness() {
    std::vector<float> combinedWeaknesses(TYPE_AMOUNT, 1.0f);

    if (secondaryType == NONE) {
        // Only primary type is considered
        for (int i = 0; i < TYPE_AMOUNT; ++i) {
            combinedWeaknesses[i] = typeChart[i][static_cast<int>(primaryType)];
        }
    } else {
        // Both primary and secondary types are considered
        for (int i = 0; i < TYPE_AMOUNT; ++i) {
            combinedWeaknesses[i] = typeChart[i][static_cast<int>(primaryType)] * typeChart[i][static_cast<int>(secondaryType)];
        }
    }

    return combinedWeaknesses;
}