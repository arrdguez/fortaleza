#pragma once

#include "Types.h"
#include "TerminalUI.h"
#include <vector>
#include <string>

namespace Fortaleza2 {

class Game {
public:
    explicit Game(TerminalUI& ui);

    void start();
    bool executeCommand(const std::string& raw_command);
    void executeScript(const std::string& script_filename);
    bool isRunning() const { return is_running_; }

    double getExplorationPercentage() const;

private:
    void showRoom();
    void recalculateWeight();
    bool hasItem(const std::string& item_name) const;

    Item* findItemInInventory(const std::string& name);
    Item* findItemInRoom(const std::string& name);
    Door* findDoorInRoom(const std::string& name);
    Creature* findCreatureInRoom(const std::string& name);

    void handleIr(const ParsedCommand& cmd);
    void handleMirar(const ParsedCommand& cmd);
    void handleVer(const ParsedCommand& cmd);
    void handleCoger(const ParsedCommand& cmd);
    void handleSoltar(const ParsedCommand& cmd);
    void handleMatar(const ParsedCommand& cmd);
    void handleRomper(const ParsedCommand& cmd);
    void handleDar(const ParsedCommand& cmd);
    void handleInterrogar(const ParsedCommand& cmd);
    void handleAbrir(const ParsedCommand& cmd);
    void handlePesar(const ParsedCommand& cmd);
    void handlePorciento();
    void handleInventario();
    void handleSalvarRastro();
    void handleEjecutarRastro(const std::string& filename = "");

    void checkWinCondition();

    TerminalUI& ui_;
    std::vector<Room> rooms_;
    std::vector<Item> inventory_;
    std::vector<std::string> command_history_;
    int current_room_id_{0};
    int current_weight_{0};
    int max_weight_{40};
    bool is_running_{true};
    bool won_game_{false};

    // Story flags
    bool grifo_muerto_{false};
    bool ogro_muerto_{false};
    bool serpiente_muerta_{false};
    bool carta_rota_{false};
    bool col_hielo_derretida_{false};
    bool marmidosa_entregada_{false};
};

} // namespace Fortaleza2
