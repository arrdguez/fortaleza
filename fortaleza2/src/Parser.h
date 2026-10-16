#pragma once

#include "Types.h"
#include <string>
#include <vector>

namespace Fortaleza2 {

class Parser {
public:
    static std::string normalize(const std::string& input);
    static std::vector<std::string> splitWords(const std::string& str);
    static std::string stripArticles(const std::string& text);
    static bool matches(const std::string& input, const std::string& target);
    static Verb identifyVerb(const std::string& word);
    static ParsedCommand parse(const std::string& line);
};

} // namespace Fortaleza2
