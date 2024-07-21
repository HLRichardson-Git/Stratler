
#include <string>

#include "nature.h"

std::string natureToString(Nature nature) { 
    return natureNames[static_cast<int>(nature)]; 
}