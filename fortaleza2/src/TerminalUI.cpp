#include "TerminalUI.h"
#include <iostream>
#include <iomanip>

namespace Fortaleza2 {

TerminalUI::TerminalUI(bool use_color) : use_color_(use_color) {}

void TerminalUI::clearScreen() {
    std::cout << "\033[2J\033[1;1H";
}

void TerminalUI::printTitle(const std::string& text) {
    if (use_color_) std::cout << BOLD << CYAN << text << RESET << "\n";
    else std::cout << text << "\n";
}

void TerminalUI::printNarrative(const std::string& text) {
    std::cout << "  " << text << "\n";
}

void TerminalUI::printInfo(const std::string& text) {
    if (use_color_) std::cout << CYAN << "  ℹ " << text << RESET << "\n";
    else std::cout << "  " << text << "\n";
}

void TerminalUI::printSuccess(const std::string& text) {
    if (use_color_) std::cout << GREEN << BOLD << "  ✓ " << text << RESET << "\n";
    else std::cout << "  " << text << "\n";
}

void TerminalUI::printWarning(const std::string& text) {
    if (use_color_) std::cout << YELLOW << "  ▲ " << text << RESET << "\n";
    else std::cout << "  " << text << "\n";
}

void TerminalUI::printError(const std::string& text) {
    if (use_color_) std::cout << RED << BOLD << "  ✗ " << text << RESET << "\n";
    else std::cout << "  " << text << "\n";
}

void TerminalUI::drawHeader(const std::string& room_title, int current_weight, int max_weight, double percentage) {
    std::cout << "\n";
    if (use_color_) {
        std::cout << BOLD << BLUE << "================================================================================" << RESET << "\n";
        std::cout << BOLD << CYAN << "  Lugar: " << room_title << RESET;
        std::cout << YELLOW << " | Peso: " << current_weight << "/" << max_weight << " bolsas" << RESET;
        std::cout << MAGENTA << " | Recorrido: " << std::fixed << std::setprecision(1) << percentage << "%" << RESET << "\n";
        std::cout << BOLD << BLUE << "================================================================================" << RESET << "\n";
    } else {
        std::cout << "================================================================================\n";
        std::cout << "  Lugar: " << room_title << " | Peso: " << current_weight << "/" << max_weight 
                  << " bolsas | Recorrido: " << std::fixed << std::setprecision(1) << percentage << "%\n";
        std::cout << "================================================================================\n";
    }
}

void TerminalUI::printExits(const std::vector<std::string>& exits) {
    if (exits.empty()) return;
    std::cout << "\n";
    if (use_color_) std::cout << BOLD << YELLOW << "  Uniones o salidas visibles:" << RESET << "\n";
    else std::cout << "  Uniones o salidas visibles:\n";
    for (const auto& exit : exits) {
        std::cout << "    → " << exit << "\n";
    }
}

void TerminalUI::printItems(const std::vector<std::pair<std::string, int>>& items) {
    if (items.empty()) return;
    std::cout << "\n";
    if (use_color_) std::cout << BOLD << GREEN << "  Objetos en el lugar:" << RESET << "\n";
    else std::cout << "  Objetos en el lugar:\n";
    for (const auto& item : items) {
        std::cout << "    • " << item.first << " (" << item.second << " bolsas)\n";
    }
}

void TerminalUI::printCreatures(const std::vector<std::string>& creatures) {
    if (creatures.empty()) return;
    std::cout << "\n";
    if (use_color_) std::cout << BOLD << MAGENTA << "  Presencias o seres:" << RESET << "\n";
    else std::cout << "  Presencias o seres:\n";
    for (const auto& c : creatures) {
        std::cout << "    ◆ " << c << "\n";
    }
}

std::string TerminalUI::readCommand(const std::string& prompt) {
    std::cout << "\n";
    if (use_color_) std::cout << BOLD << "¿Qué haces ahora? > " << RESET;
    else std::cout << prompt;
    std::string line;
    std::getline(std::cin, line);
    return line;
}

int TerminalUI::showMenu() {
    clearScreen();
    std::cout << "\n";
    printTitle("============================================================");
    printTitle("               L A   F O R T A L E Z A   I I                ");
    printTitle("               La Venganza de la Bestia (1991)              ");
    printTitle("                    (c) Merchise Software                   ");
    printTitle("============================================================");
    std::cout << "\n";
    printNarrative("\"En la lucha entre tú y el mundo, ve de parte del mundo.\"");
    printNarrative("                                        -- Franz Kafka");
    std::cout << "\n";
    std::cout << "  1. Comenzar Aventura\n";
    std::cout << "  2. Instrucciones / Consejos (Método Infalible)\n";
    std::cout << "  3. Créditos\n";
    std::cout << "  4. Terminar\n\n";

    while (true) {
        std::string choice = readCommand("Seleccione opción [1-4] > ");
        if (choice == "1") return 1;
        if (choice == "2") return 2;
        if (choice == "3") return 3;
        if (choice == "4") return 4;
        printError("Opción no válida.");
    }
}

void TerminalUI::showManual(const std::vector<std::string>& pages) {
    for (size_t i = 0; i < pages.size(); ++i) {
        clearScreen();
        std::cout << "\n";
        printTitle("--- CONSEJOS Y METODO INFALIBLE (Pág " + std::to_string(i + 1) + " de " + std::to_string(pages.size()) + ") ---");
        std::cout << "\n" << pages[i] << "\n\n";
        readCommand("[Presione ENTER para continuar]");
    }
}

void TerminalUI::showCredits(const std::string& credits) {
    clearScreen();
    std::cout << "\n";
    printTitle("--- CREDITOS DE LA FORTALEZA II ---");
    std::cout << "\n" << credits << "\n\n";
    readCommand("[Presione ENTER para volver al menú]");
}

void TerminalUI::showEpilogue() {
    clearScreen();
    std::cout << "\n\n";
    printSuccess("==============================================================================");
    printSuccess("                      ¡ H A S   E S C A P A D O !                             ");
    printSuccess("==============================================================================");
    std::cout << "\n";
    printNarrative("De repente las paredes comienzan a desvanecerse.");
    printNarrative("Usted no quiere dar crédito a sus ojos: ¡Ha logrado salir de la Fortaleza!\n");
    printTitle("                                 EPÍLOGO                                      ");
    printNarrative("Usted mira al cielo agradecido y besa la tierra.");
    printNarrative("Después de que la emoción del primer momento hubo pasado, usted se sienta");
    printNarrative("sobre una piedra al borde de la carretera (recuerde que ha regresado a la");
    printNarrative("civilización) y comienza a pensar. \"¿Para qué salí?\", se pregunta, \"si el");
    printNarrative("exterior nunca me gustó tanto\".\n");
    printNarrative("Usted recuerda a la Doncella del Lago, y piensa en la vida que hubiera podido");
    printNarrative("llevar junto a ella. Piensa también en el Hechicero, un poderoso amigo, y en");
    printNarrative("la remota y hermosa posibilidad de hacer renacer la civilización de los horantes.");
    printNarrative("Ahora, sin la Bestia y sin la Hija del Hechicero, la Fortaleza podría ser");
    printNarrative("convertida en un verdadero paraíso.\n");
    printNarrative("¿Quién está al otro extremo de los hilos que manejan al hombre?");
    printNarrative("¿Quién nos hace confundir lo que somos y lo que queremos ser?");
    printNarrative("¿Quién es el responsable de nuestros errores? ¿Quién sino nosotros mismos?\n");
    printNarrative("Usted vuelve la cabeza hacia el lugar que ocupó la Fortaleza.");
    printNarrative("Ahora lo comprende todo claramente: esta era la venganza de la Bestia:");
    printNarrative("dejarlo vivir, pero fuera de la Fortaleza.\n");
    printSuccess("==============================================================================");
    printInfo("  \"¿Quería un final feliz? Espere la próxima versión.\"  -- M. Cepero");
    printSuccess("==============================================================================\n");
}

} // namespace Fortaleza2
