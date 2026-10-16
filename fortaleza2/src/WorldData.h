#pragma once

#include "Types.h"
#include <vector>
#include <string>

namespace Fortaleza2 {

class WorldData {
public:
    static std::string getIntroTitle();
    static std::string getKafkaQuote();
    static std::string getCredits();
    static std::vector<std::string> getManualPages();
    static std::vector<Room> createWorld();
};

} // namespace Fortaleza2
