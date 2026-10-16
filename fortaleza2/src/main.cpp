#include "Game.h"
#include "TerminalUI.h"
#include "WorldData.h"
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
    bool use_color = true;
    std::string trace_file = "";

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "--plain" || arg == "-p") {
            use_color = false;
        } else if (arg == "--help" || arg == "-h") {
            std::cout << "Uso: " << argv[0] << " [opciones] [fichero_rastro]\n\n"
                      << "Opciones:\n"
                      << "  -p, --plain      Desactiva colores ANSI\n"
                      << "  -h, --help       Muestra esta ayuda\n"
                      << "  fichero_rastro   Ejecuta automáticamente una lista de comandos\n\n"
                      << "Ejemplo:\n"
                      << "  " << argv[0] << " solucion.txt\n";
            return 0;
        } else if (trace_file.empty()) {
            trace_file = arg;
        }
    }

    Fortaleza2::TerminalUI ui(use_color);

    if (!trace_file.empty()) {
        Fortaleza2::Game game(ui);
        game.executeScript(trace_file);
        if (game.isRunning()) {
            game.start();
        }
        return 0;
    }

    while (true) {
        int choice = ui.showMenu();
        if (choice == 1) {
            Fortaleza2::Game game(ui);
            game.start();
        } else if (choice == 2) {
            ui.showManual(Fortaleza2::WorldData::getManualPages());
        } else if (choice == 3) {
            ui.showCredits(Fortaleza2::WorldData::getCredits());
        } else if (choice == 4) {
            std::cout << "\n¡Hasta la próxima aventura en La Fortaleza II!\n\n";
            break;
        }
    }

    return 0;
}
