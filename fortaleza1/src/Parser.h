#pragma once

#include "Types.h"
#include <string>
#include <vector>

namespace Fortaleza {

class Parser {
public:
    static std::string normalize(const std::string& input);
    static ParsedCommand parse(const std::string& line);
    static std::string stripArticles(const std::string& text);
    static bool matches(const std::string& input, const std::string& target);

private:
    static std::vector<std::string> splitWords(const std::string& str);
    static Verb identifyVerb(const std::string& word);
};

} // namespace Fortaleza
