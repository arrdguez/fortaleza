#pragma once

#include "Types.h"
#include "TerminalUI.h"
#include <vector>
#include <string>

namespace Fortaleza {

class Game {
public:
    Game(TerminalUI& ui);

    void start();
    void executeScript(const std::string& script_filename);
    bool executeCommand(const std::string& raw_command);

    bool isRunning() const { return is_running_; }
    int getCurrentRoomId() const { return current_room_id_; }
    int getDestroyedCentersCount() const;

private:
    TerminalUI& ui_;
    std::vector<Room> rooms_;
    int current_room_id_{0};
    std::vector<Item> inventory_;
    int max_weight_{40};
    int current_weight_{0};
    bool is_running_{true};
    bool game_over_{false};
    bool won_game_{false};

    // Beast state
    bool pulmones_destruidos_{false};
    bool estomago_destruido_{false};
    bool corazon_destruido_{false};
    bool cerebro_destruido_{false};

    // Special puzzles
    bool minotauro_muerto_{false};
    bool columna_cristal_rota_{false};
    bool espejo_roto_{false};

    // Trace file
    std::vector<std::string> command_history_;

    void showRoom();
    void recalculateWeight();
    bool hasItem(const std::string& item_name) const;
    Item* findItemInInventory(const std::string& name);
    Item* findItemInRoom(const std::string& name);
    Door* findDoorInRoom(const std::string& name);
    Creature* findCreatureInRoom(const std::string& name);

    // Command handlers
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
    void handleComer(const ParsedCommand& cmd);
    void handleBeber(const ParsedCommand& cmd);
    void handleInventario();
    void handleSalvarRastro();
    void handleEjecutarRastro(const std::string& filename = "");
    void checkWinCondition();
};

} // namespace Fortaleza
