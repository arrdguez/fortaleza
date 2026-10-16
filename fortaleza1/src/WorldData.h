#pragma once

#include "Types.h"
#include <vector>
#include <string>

namespace Fortaleza {

class WorldData {
public:
    static std::vector<Room> createWorld();
    static std::vector<std::string> getManualPages();
    static std::string getCredits();
    static std::string getIntroTitle();
};

} // namespace Fortaleza
