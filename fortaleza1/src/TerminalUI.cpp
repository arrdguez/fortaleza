#include "TerminalUI.h"
#include <iostream>
#include <sstream>
#include <iomanip>

namespace Fortaleza {

// ANSI Color Codes
namespace Color {
    const std::string Reset   = "\033[0m";
    const std::string Bold    = "\033[1m";
    const std::string Dim     = "\033[2m";
    const std::string Red     = "\033[31m";
    const std::string Green   = "\033[32m";
    const std::string Yellow  = "\033[33m";
    const std::string Blue    = "\033[34m";
    const std::string Magenta = "\033[35m";
    const std::string Cyan    = "\033[36m";
    const std::string White   = "\033[37m";
    const std::string BgBlue  = "\033[44m";
}

TerminalUI::TerminalUI(bool use_color) : use_color_(use_color) {}

std::string TerminalUI::colorize(const std::string& text, const std::string& color_code) {
    if (!use_color_) return text;
    return color_code + text + Color::Reset;
}

void TerminalUI::clearScreen() {
    if (use_color_) {
        std::cout << "\033[2J\033[H";
    } else {
        std::cout << "\n\n========================================\n\n";
    }
}

void TerminalUI::wrapAndPrint(const std::string& text, int width, const std::string& indent) {
    std::istringstream iss(text);
    std::string word;
    std::string line = indent;

    while (iss >> word) {
        if (static_cast<int>(line.length() + word.length() + 1) > width) {
            std::cout << line << "\n";
            line = indent + word;
        } else {
            if (line != indent) line += " ";
            line += word;
        }
    }
    if (!line.empty() && line != indent) {
        std::cout << line << "\n";
    }
}

void TerminalUI::showBanner() {
    clearScreen();
    std::cout << colorize("╔════════════════════════════════════════════════════════════════════════════╗\n", Color::Cyan);
    std::cout << colorize("║", Color::Cyan)
              << colorize("                     L A   F O R T A L E Z A   I                     ", Color::Bold + Color::Yellow)
              << colorize("║\n", Color::Cyan);
    std::cout << colorize("║", Color::Cyan)
              << colorize("                    (c) 1990 Manuel Cepero - Cuba                    ", Color::White)
              << colorize("║\n", Color::Cyan);
    std::cout << colorize("║", Color::Cyan)
              << colorize("               Reconstrucción en C++ Moderno (2026)                  ", Color::Dim + Color::Cyan)
              << colorize("║\n", Color::Cyan);
    std::cout << colorize("╚════════════════════════════════════════════════════════════════════════════╝\n", Color::Cyan);
    std::cout << "\n";
}

int TerminalUI::showMenu() {
    while (true) {
        showBanner();
        std::cout << colorize("   MENU PRINCIPAL\n", Color::Bold + Color::Cyan);
        std::cout << "   ══════════════\n";
        std::cout << colorize("   [1] ", Color::Yellow) << "Jugar a La Fortaleza\n";
        std::cout << colorize("   [2] ", Color::Yellow) << "Gran Método Infalible Para Resolver Fortalezas (Manual)\n";
        std::cout << colorize("   [3] ", Color::Yellow) << "Créditos e Historia\n";
        std::cout << colorize("   [4] ", Color::Yellow) << "Salir al Sistema\n\n";
        std::cout << colorize("   Seleccione una opción [1-4]: ", Color::Bold + Color::White);

        std::string input;
        if (!std::getline(std::cin, input)) return 4;
        if (input == "1") return 1;
        if (input == "2") return 2;
        if (input == "3") return 3;
        if (input == "4") return 4;
    }
}

void TerminalUI::showManual(const std::vector<std::string>& pages) {
    for (size_t i = 0; i < pages.size(); ++i) {
        clearScreen();
        std::cout << colorize("╔════════════════════════════════════════════════════════════════════════════╗\n", Color::Cyan);
        std::cout << colorize("║", Color::Cyan)
                  << colorize("       GRAN METODO INFALIBLE PARA RESOLVER FORTALEZAS - Pagina " + std::to_string(i + 1) + "/" + std::to_string(pages.size()) + "       ", Color::Bold + Color::Yellow)
                  << colorize("║\n", Color::Cyan);
        std::cout << colorize("╚════════════════════════════════════════════════════════════════════════════╝\n\n", Color::Cyan);

        std::istringstream stream(pages[i]);
        std::string line;
        while (std::getline(stream, line)) {
            std::cout << "  " << line << "\n";
        }

        std::cout << "\n" << colorize("  Presione ENTER para continuar (o 'q' para volver al menú)... ", Color::Dim + Color::Cyan);
        std::string dummy;
        std::getline(std::cin, dummy);
        if (dummy == "q" || dummy == "Q") break;
    }
}

void TerminalUI::showCredits(const std::string& credits) {
    clearScreen();
    std::cout << colorize("╔════════════════════════════════════════════════════════════════════════════╗\n", Color::Cyan);
    std::cout << colorize("║", Color::Cyan)
              << colorize("                             C R E D I T O S                                 ", Color::Bold + Color::Yellow)
              << colorize("║\n", Color::Cyan);
    std::cout << colorize("╚════════════════════════════════════════════════════════════════════════════╝\n\n", Color::Cyan);

    std::istringstream stream(credits);
    std::string line;
    while (std::getline(stream, line)) {
        std::cout << "  " << line << "\n";
    }

    std::cout << "\n" << colorize("  Presione ENTER para regresar al menú principal... ", Color::Dim + Color::Cyan);
    std::string dummy;
    std::getline(std::cin, dummy);
}

void TerminalUI::drawHeader(const std::string& room_title, int current_weight, int max_weight, int destroyed_centers) {
    std::cout << colorize("╔════════════════════════════════════════════════════════════════════════════╗\n", Color::Cyan);

    // Format title
    std::string upper_title = room_title;
    for (char& c : upper_title) c = static_cast<char>(std::toupper(static_cast<unsigned char>(c)));

    std::ostringstream title_line;
    title_line << "  " << upper_title;
    std::string t_str = title_line.str();

    std::ostringstream stats_line;
    stats_line << "Carga: " << current_weight << "/" << max_weight << " bolsas | Centros: " << destroyed_centers << "/4  ";
    std::string s_str = stats_line.str();

    int padding = 76 - static_cast<int>(t_str.length() + s_str.length());
    if (padding < 1) padding = 1;

    std::cout << colorize("║", Color::Cyan)
              << colorize(t_str, Color::Bold + Color::Yellow)
              << std::string(padding, ' ')
              << colorize(s_str, Color::Bold + Color::White)
              << colorize("║\n", Color::Cyan);

    std::cout << colorize("╚════════════════════════════════════════════════════════════════════════════╝\n", Color::Cyan);
}

void TerminalUI::printNarrative(const std::string& text) {
    wrapAndPrint(text, 76, "  ");
}

void TerminalUI::printSuccess(const std::string& text) {
    std::cout << colorize("  ★ ", Color::Bold + Color::Green);
    wrapAndPrint(text, 74, "");
}

void TerminalUI::printWarning(const std::string& text) {
    std::cout << colorize("  ⚠ ", Color::Bold + Color::Yellow);
    wrapAndPrint(text, 74, "");
}

void TerminalUI::printError(const std::string& text) {
    std::cout << colorize("  ✖ ", Color::Bold + Color::Red);
    wrapAndPrint(text, 74, "");
}

void TerminalUI::printInfo(const std::string& text) {
    std::cout << colorize("  ℹ ", Color::Cyan);
    wrapAndPrint(text, 74, "");
}

void TerminalUI::printExits(const std::vector<std::string>& exits) {
    if (exits.empty()) return;
    std::cout << colorize("\n  Salidas y caminos visibles:\n", Color::Bold + Color::Cyan);
    for (const auto& exit : exits) {
        std::cout << colorize("    → ", Color::Cyan) << exit << "\n";
    }
}

void TerminalUI::printItems(const std::vector<std::pair<std::string, int>>& items) {
    if (items.empty()) return;
    std::cout << colorize("\n  Objetos en el lugar:\n", Color::Bold + Color::Green);
    for (const auto& item : items) {
        std::cout << colorize("    • ", Color::Green) << item.first
                  << colorize(" (" + std::to_string(item.second) + " bolsas)", Color::Dim + Color::White) << "\n";
    }
}

void TerminalUI::printCreatures(const std::vector<std::string>& creatures) {
    if (creatures.empty()) return;
    std::cout << colorize("\n  Presencias o seres:\n", Color::Bold + Color::Magenta);
    for (const auto& creature : creatures) {
        std::cout << colorize("    ♦ ", Color::Magenta) << creature << "\n";
    }
}

std::string TerminalUI::readCommand(const std::string& prompt) {
    std::cout << "\n" << colorize(prompt, Color::Bold + Color::Yellow);
    std::string input;
    if (!std::getline(std::cin, input)) {
        return "terminar";
    }
    return input;
}

} // namespace Fortaleza
