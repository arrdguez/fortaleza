#pragma once

#include <string>
#include <vector>

namespace Fortaleza2 {

class TerminalUI {
public:
    explicit TerminalUI(bool use_color = true);

    void clearScreen();
    void printTitle(const std::string& text);
    void printNarrative(const std::string& text);
    void printInfo(const std::string& text);
    void printSuccess(const std::string& text);
    void printWarning(const std::string& text);
    void printError(const std::string& text);

    void drawHeader(const std::string& room_title, int current_weight, int max_weight, double percentage);
    void printExits(const std::vector<std::string>& exits);
    void printItems(const std::vector<std::pair<std::string, int>>& items);
    void printCreatures(const std::vector<std::string>& creatures);

    std::string readCommand(const std::string& prompt = "¿Qué haces ahora? > ");
    int showMenu();
    void showManual(const std::vector<std::string>& pages);
    void showCredits(const std::string& credits);
    void showEpilogue();

private:
    bool use_color_{true};

    const std::string RESET = "\033[0m";
    const std::string BOLD = "\033[1m";
    const std::string CYAN = "\033[36m";
    const std::string YELLOW = "\033[33m";
    const std::string GREEN = "\033[32m";
    const std::string RED = "\033[31m";
    const std::string MAGENTA = "\033[35m";
    const std::string BLUE = "\033[34m";
};

} // namespace Fortaleza2
