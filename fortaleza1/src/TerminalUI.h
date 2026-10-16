#pragma once

#include <string>
#include <vector>

namespace Fortaleza {

class TerminalUI {
public:
    TerminalUI(bool use_color = true);

    void clearScreen();
    void showBanner();
    int showMenu();
    void showManual(const std::vector<std::string>& pages);
    void showCredits(const std::string& credits);

    void drawHeader(const std::string& room_title, int current_weight, int max_weight, int destroyed_centers);
    void printNarrative(const std::string& text);
    void printSuccess(const std::string& text);
    void printWarning(const std::string& text);
    void printError(const std::string& text);
    void printInfo(const std::string& text);
    void printExits(const std::vector<std::string>& exits);
    void printItems(const std::vector<std::pair<std::string, int>>& items);
    void printCreatures(const std::vector<std::string>& creatures);

    std::string readCommand(const std::string& prompt = "¿Qué haces ahora? > ");

    void setUseColor(bool color) { use_color_ = color; }

private:
    bool use_color_{true};

    std::string colorize(const std::string& text, const std::string& color_code);
    void wrapAndPrint(const std::string& text, int width = 76, const std::string& indent = "  ");
};

} // namespace Fortaleza
