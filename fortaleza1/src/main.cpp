#include "Game.h"
#include "TerminalUI.h"
#include "WorldData.h"
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
    bool use_color = true;
    std::string trace_file = "";

    // Parse command line arguments
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "--plain" || arg == "-p") {
            use_color = false;
        } else if (arg == "--help" || arg == "-h") {
            std::cout << "Uso: " << argv[0] << " [opciones] [fichero_rastro]\n\n"
                      << "Opciones:\n"
                      << "  -p, --plain      Desactiva colores ANSI (modo texto puro)\n"
                      << "  -h, --help       Muestra esta ayuda\n"
                      << "  fichero_rastro   Ejecuta automáticamente una lista de comandos guardados\n\n"
                      << "Ejemplo:\n"
                      << "  " << argv[0] << " solucion.txt\n";
            return 0;
        } else if (trace_file.empty()) {
            trace_file = arg;
        }
    }

    Fortaleza::TerminalUI ui(use_color);

    if (!trace_file.empty()) {
        // Direct trace replay mode
        Fortaleza::Game game(ui);
        game.executeScript(trace_file);
        if (game.isRunning()) {
            game.start();
        }
        return 0;
    }

    // Main Interactive Menu
    while (true) {
        int choice = ui.showMenu();
        if (choice == 1) {
            Fortaleza::Game game(ui);
            game.start();
        } else if (choice == 2) {
            ui.showManual(Fortaleza::WorldData::getManualPages());
        } else if (choice == 3) {
            ui.showCredits(Fortaleza::WorldData::getCredits());
        } else if (choice == 4) {
            std::cout << "\n¡Hasta la próxima aventura en La Fortaleza!\n\n";
            break;
        }
    }

    return 0;
}
