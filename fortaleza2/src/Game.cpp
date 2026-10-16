#include "Game.h"
#include "WorldData.h"
#include "Parser.h"
#include <fstream>
#include <iostream>

namespace Fortaleza2 {

Game::Game(TerminalUI& ui) : ui_(ui) {
    rooms_ = WorldData::createWorld();
    current_room_id_ = 0;
    recalculateWeight();
}

double Game::getExplorationPercentage() const {
    int visited = 0;
    for (const auto& r : rooms_) {
        if (r.visited) ++visited;
    }
    return (static_cast<double>(visited) / static_cast<double>(rooms_.size())) * 100.0;
}

void Game::recalculateWeight() {
    current_weight_ = 0;
    for (const auto& it : inventory_) {
        current_weight_ += it.weight;
    }
}

bool Game::hasItem(const std::string& item_name) const {
    for (const auto& it : inventory_) {
        if (Parser::matches(item_name, it.name)) return true;
    }
    return false;
}

Item* Game::findItemInInventory(const std::string& name) {
    for (auto& it : inventory_) {
        if (Parser::matches(name, it.name)) return &it;
    }
    return nullptr;
}

Item* Game::findItemInRoom(const std::string& name) {
    for (auto& it : rooms_[current_room_id_].items) {
        if (Parser::matches(name, it.name)) return &it;
    }
    return nullptr;
}

Door* Game::findDoorInRoom(const std::string& name) {
    for (auto& d : rooms_[current_room_id_].doors) {
        if (Parser::matches(name, d.name)) return &d;
    }
    return nullptr;
}

Creature* Game::findCreatureInRoom(const std::string& name) {
    for (auto& c : rooms_[current_room_id_].creatures) {
        if (Parser::matches(name, c.name)) return &c;
    }
    return nullptr;
}

void Game::showRoom() {
    Room& r = rooms_[current_room_id_];
    r.visited = true;

    ui_.drawHeader(r.title, current_weight_, max_weight_, getExplorationPercentage());
    std::cout << "\n";
    ui_.printNarrative(r.description);

    std::vector<std::string> exit_names;
    for (const auto& d : r.doors) {
        std::string s = d.name;
        if (d.is_open) s += " (abierta)";
        exit_names.push_back(s);
    }
    ui_.printExits(exit_names);

    std::vector<std::pair<std::string, int>> item_pairs;
    for (const auto& it : r.items) {
        item_pairs.push_back({it.name, it.weight});
    }
    ui_.printItems(item_pairs);

    std::vector<std::string> creature_names;
    for (const auto& c : r.creatures) {
        if (!c.is_dead) {
            creature_names.push_back(c.name);
        }
    }
    ui_.printCreatures(creature_names);
}

void Game::start() {
    ui_.clearScreen();
    ui_.printSuccess("¡Bienvenido a La Fortaleza II: La Venganza de la Bestia!");
    ui_.printInfo("Escriba 'ayuda' para ver los comandos o 'terminar' para salir.\n");
    showRoom();

    while (is_running_) {
        std::string input = ui_.readCommand();
        if (!executeCommand(input)) {
            break;
        }
    }
}

bool Game::executeCommand(const std::string& raw_command) {
    if (raw_command.empty()) return true;

    ParsedCommand cmd = Parser::parse(raw_command);

    if (cmd.verb != Verb::Mirar && cmd.verb != Verb::Ver && cmd.verb != Verb::Inventario &&
        cmd.verb != Verb::Ayuda && cmd.verb != Verb::Salvar && cmd.verb != Verb::Ejecutar &&
        cmd.verb != Verb::Pesar && cmd.verb != Verb::Porciento && cmd.verb != Verb::Desconocido) {
        command_history_.push_back(raw_command);
    }

    switch (cmd.verb) {
        case Verb::Ir:         handleIr(cmd); break;
        case Verb::Mirar:      handleMirar(cmd); break;
        case Verb::Ver:        handleVer(cmd); break;
        case Verb::Coger:      handleCoger(cmd); break;
        case Verb::Soltar:     handleSoltar(cmd); break;
        case Verb::Matar:      handleMatar(cmd); break;
        case Verb::Romper:     handleRomper(cmd); break;
        case Verb::Dar:        handleDar(cmd); break;
        case Verb::Interrogar: handleInterrogar(cmd); break;
        case Verb::Abrir:      handleAbrir(cmd); break;
        case Verb::Pesar:      handlePesar(cmd); break;
        case Verb::Porciento:  handlePorciento(); break;
        case Verb::Inventario: handleInventario(); break;
        case Verb::Salvar:     handleSalvarRastro(); break;
        case Verb::Ejecutar:   handleEjecutarRastro(); break;
        case Verb::Ayuda:
            ui_.showManual(WorldData::getManualPages());
            showRoom();
            break;
        case Verb::Fin:
            ui_.printInfo("Lamento informarle que usted ha muerto.");
            is_running_ = false;
            return false;
        case Verb::Desconocido:
        default:
            ui_.printError("No le comprendo. Escriba 'ayuda' para consultar las reglas.");
            break;
    }

    checkWinCondition();
    return is_running_;
}

void Game::handleIr(const ParsedCommand& cmd) {
    if (cmd.direct_object.empty()) {
        ui_.printWarning("¿Hacia dónde desea ir o qué unión desea cruzar?");
        return;
    }

    Door* door = findDoorInRoom(cmd.direct_object);
    if (!door) {
        for (auto& d : rooms_[current_room_id_].doors) {
            const Room& target = rooms_[d.target_room];
            if (Parser::matches(cmd.direct_object, target.title)) {
                door = &d;
                break;
            }
        }
    }

    if (!door) {
        ui_.printError("No veo cómo ir hacia '" + cmd.direct_object + "' desde aquí.");
        return;
    }

    if (!door->is_open) {
        if (!door->locked_message.empty()) {
            ui_.printWarning(door->locked_message);
        } else {
            ui_.printWarning("Imposible de cruzar. Debe abrir primero.");
        }
        return;
    }

    // Protection check
    if (!door->required_item_to_cross.empty()) {
        if (!hasItem(door->required_item_to_cross)) {
            if (door->name == "Puerta de metal" && current_room_id_ == 1) {
                ui_.printError("El hedor venenoso de la cocina lo envuelve y lo asfixia... ¡Ha muerto desprotegido!");
                is_running_ = false;
                return;
            } else if (door->name == "Túnel" && current_room_id_ == 13) {
                ui_.printError("Una bandada de murciélagos gigantes lo ataca en la oscuridad... ¡Ha muerto desprotegido!");
                is_running_ = false;
                return;
            } else if (door->name == "Precipicio" && current_room_id_ == 37) {
                ui_.printError("Usted cae en el vacío y se estrella contra las rocas... ¡Ha muerto!");
                is_running_ = false;
                return;
            } else if (door->name == "Río" && current_room_id_ == 41) {
                ui_.printError("La corriente implacable del río lo arrastra hacia las profundidades... ¡Ha muerto ahogado!");
                is_running_ = false;
                return;
            } else if (door->name == "Puente" && current_room_id_ == 52) {
                ui_.printError("Sin la protección del grabado, una fuerza cósmica del Abismo Infranqueable lo absorbe hacia la nada...");
                is_running_ = false;
                return;
            }
        }
    }

    // Check Rings Test: forbidden items in test rooms
    if (door->target_room == 49 && hasItem("Anillo de oro")) {
        ui_.printError("Usted llevaba un objeto que le impidió cruzar: el Anillo de oro no puede entrar al Salón Verde. ¡Ha perecido!");
        is_running_ = false;
        return;
    }
    if (door->target_room == 50 && hasItem("Anillo de plata")) {
        ui_.printError("Usted llevaba un objeto que le impidió cruzar: el Anillo de plata no puede entrar al Salón Azul. ¡Ha perecido!");
        is_running_ = false;
        return;
    }
    if (door->target_room == 51 && hasItem("Anillo de bronce")) {
        ui_.printError("Usted llevaba un objeto que le impidió cruzar: el Anillo de bronce no puede entrar al Salón Blanco. ¡Ha perecido!");
        is_running_ = false;
        return;
    }
    if (door->target_room == 52 && current_room_id_ == 51) {
        if (!hasItem("Cinta de Moebius")) {
            ui_.printError("La puerta triangular rechaza su espíritu: ¡debió conservar la Cinta de Moebius!");
            is_running_ = false;
            return;
        }
    }

    if (!door->message_enter.empty()) {
        ui_.printSuccess(door->message_enter);
    }

    current_room_id_ = door->target_room;
    std::cout << "\n";
    showRoom();
}

void Game::handleMirar(const ParsedCommand& cmd) {
    if (cmd.direct_object.empty() || cmd.direct_object == "lugar" || cmd.direct_object == "habitacion") {
        ui_.clearScreen();
        showRoom();
        return;
    }

    Item* it = findItemInRoom(cmd.direct_object);
    if (!it) it = findItemInInventory(cmd.direct_object);
    if (it) {
        ui_.printInfo(it->description);
        return;
    }

    Door* d = findDoorInRoom(cmd.direct_object);
    if (d) {
        ui_.printInfo(d->description);
        if (d->is_riddle && !d->is_open) {
            ui_.printWarning("Debe resolver este acertijo: " + d->riddle_question);
        }
        return;
    }

    Creature* c = findCreatureInRoom(cmd.direct_object);
    if (c) {
        ui_.printInfo(c->description);
        return;
    }

    ui_.printError("No existe '" + cmd.direct_object + "' en este lugar.");
}

void Game::handleVer(const ParsedCommand& cmd) {
    handleMirar(cmd);
}

void Game::handleCoger(const ParsedCommand& cmd) {
    if (cmd.direct_object.empty()) {
        ui_.printWarning("¿Qué desea coger?");
        return;
    }

    Item* it = findItemInRoom(cmd.direct_object);
    if (!it) {
        if (findItemInInventory(cmd.direct_object)) {
            ui_.printWarning("Ya lleva eso consigo.");
        } else {
            ui_.printError("No existe '" + cmd.direct_object + "' en este lugar.");
        }
        return;
    }

    if (!it->can_pick_up) {
        ui_.printError("Usted no puede cargar con eso.");
        return;
    }

    if (current_weight_ + it->weight > max_weight_) {
        ui_.printWarning("Sería demasiado peso. Capacidad máxima: " + std::to_string(max_weight_) + " bolsas.");
        return;
    }

    inventory_.push_back(*it);
    recalculateWeight();

    auto& r_items = rooms_[current_room_id_].items;
    for (auto iter = r_items.begin(); iter != r_items.end(); ++iter) {
        if (Parser::matches(it->name, iter->name)) {
            r_items.erase(iter);
            break;
        }
    }

    ui_.printSuccess("Ha cogido: " + it->name + " (" + std::to_string(it->weight) + " bolsas).");
}

void Game::handleSoltar(const ParsedCommand& cmd) {
    if (cmd.direct_object.empty()) {
        ui_.printWarning("¿Qué desea soltar?");
        return;
    }

    if (cmd.direct_object == "todo") {
        if (inventory_.empty()) {
            ui_.printInfo("Usted no lleva nada consigo.");
            return;
        }
        for (const auto& it : inventory_) {
            rooms_[current_room_id_].items.push_back(it);
        }
        inventory_.clear();
        recalculateWeight();
        ui_.printSuccess("Usted deja todas sus pertenencias en el suelo.");
        return;
    }

    Item* it = findItemInInventory(cmd.direct_object);
    if (!it) {
        ui_.printError("No lleva eso consigo.");
        return;
    }

    rooms_[current_room_id_].items.push_back(*it);
    std::string item_name = it->name;

    for (auto iter = inventory_.begin(); iter != inventory_.end(); ++iter) {
        if (Parser::matches(item_name, iter->name)) {
            inventory_.erase(iter);
            break;
        }
    }
    recalculateWeight();
    ui_.printSuccess("Ha dejado: " + item_name + ".");
}

void Game::handleMatar(const ParsedCommand& cmd) {
    if (cmd.direct_object.empty()) {
        ui_.printWarning("¿A quién desea matar?");
        return;
    }

    Creature* c = findCreatureInRoom(cmd.direct_object);
    if (!c) {
        ui_.printError("No hay nadie con ese nombre aquí.");
        return;
    }

    if (c->is_dead) {
        ui_.printInfo(c->name + " ya está muerto.");
        return;
    }

    std::string weapon = cmd.modifier;
    if (weapon.empty() && !c->lethal_weapon.empty() && hasItem(c->lethal_weapon)) {
        weapon = c->lethal_weapon;
    }

    if (!c->lethal_weapon.empty()) {
        if (weapon.empty() || !Parser::matches(weapon, c->lethal_weapon)) {
            ui_.printWarning("Sus esfuerzos son en vano. Necesita un arma adecuada para acabar con " + c->name + ".");
            return;
        }
        if (!hasItem(weapon)) {
            ui_.printError("No tiene '" + weapon + "' entre sus pertenencias.");
            return;
        }
    }

    c->is_dead = true;
    ui_.printSuccess("¡Ha derrotado a " + c->name + "!");

    if (!c->dying_confession.empty()) {
        ui_.printNarrative("En sus últimos momentos pronuncia:\n\"" + c->dying_confession + "\"");
    }

    if (c->name == "Grifo") {
        grifo_muerto_ = true;
    } else if (c->name == "Ogro") {
        ogro_muerto_ = true;
    } else if (c->name == "Hija del Hechicero") {
        serpiente_muerta_ = true;
        // Spawn Caliz in Room 45
        rooms_[45].items.push_back({
            "Cáliz",
            "Tiene grabadas las siguientes palabras:\n"
            "\"Lsmra elshrne o:\n"
            "  Rs imnee od e ao\n"
            "  Bt ecrnee aoil pet\n"
            "  Atrh ne urod usee\n"
            "  E nloeeiojnoa bn\n"
            "  Ecd eaulse acua elshrne\n"
            "  Epj el iadlhcieoe ucat\n"
            "  Pnuoe lslnd ua\"",
            5,
            true
        });
        ui_.printInfo("En el lugar que ocupaba la criatura ha aparecido un objeto: Cáliz.");
    }
}

void Game::handleRomper(const ParsedCommand& cmd) {
    if (cmd.direct_object.empty()) {
        ui_.printWarning("¿Qué desea romper?");
        return;
    }

    std::string target = cmd.direct_object;
    std::string tool = cmd.modifier;

    // Room 44: Romper carta
    if (current_room_id_ == 44 && Parser::matches(target, "carta")) {
        carta_rota_ = true;
        Door* d = findDoorInRoom("puerta secreta");
        if (d) d->is_open = true;
        ui_.printSuccess("¡Ha roto la carta! Se escucha un crujido sordo y una puerta secreta se abre en la pared.");
        return;
    }

    // Room 11: Romper muralla con Maza
    if (current_room_id_ == 11 && Parser::matches(target, "muralla")) {
        if (!hasItem("maza") && !Parser::matches(tool, "maza")) {
            ui_.printWarning("Necesita una herramienta contundente como una maza.");
            return;
        }
        Door* d = findDoorInRoom("muralla");
        if (d) d->is_open = true;
        ui_.printSuccess("¡Con un golpe devastador de la maza derriba la muralla, abriendo paso a los Jardines del Hechicero!");
        return;
    }

    // Room 53: Derretir / romper columna de hielo con antorcha
    if (current_room_id_ == 53 && (Parser::matches(target, "columna") || Parser::matches(target, "columna de hielo"))) {
        if (!hasItem("antorcha") && !Parser::matches(tool, "antorcha")) {
            ui_.printWarning("Solo el fuego de una antorcha puede deshacer la columna de hielo.");
            return;
        }
        col_hielo_derretida_ = true;
        Door* d = findDoorInRoom("puerta de roble");
        if (d) d->is_open = true;
        ui_.printSuccess("El fuego de la antorcha derrite la columna de hielo, liberando la puerta de roble del Hechicero.");
        return;
    }

    ui_.printError("Usted no puede romper '" + target + "' de esa forma.");
}

void Game::handleDar(const ParsedCommand& cmd) {
    if (cmd.direct_object.empty() || cmd.indirect_object.empty()) {
        ui_.printWarning("Uso: dar [objeto] a [personaje].");
        return;
    }

    Creature* c = findCreatureInRoom(cmd.indirect_object);
    if (!c) {
        ui_.printError("No veo a '" + cmd.indirect_object + "' aquí.");
        return;
    }

    Item* it = findItemInInventory(cmd.direct_object);
    if (!it) {
        ui_.printError("No tiene '" + cmd.direct_object + "' entre sus pertenencias.");
        return;
    }

    if (!c->requested_item.empty() && Parser::matches(it->name, c->requested_item)) {
        c->is_satisfied = true;
        ui_.printSuccess("Le ha entregado " + it->name + " a " + c->name + ".");

        std::string it_name = it->name;
        for (auto iter = inventory_.begin(); iter != inventory_.end(); ++iter) {
            if (Parser::matches(it_name, iter->name)) {
                inventory_.erase(iter);
                break;
            }
        }
        recalculateWeight();

        if (!c->reward.empty()) {
            ui_.printNarrative(c->name + " le dice agradecido:\n\"" + c->reward + "\"");
        }

        if (c->name == "Hechicero" && Parser::matches(it_name, "marmidosa")) {
            marmidosa_entregada_ = true;
        }
    } else {
        ui_.printInfo(c->name + " no acepta su regalo.");
    }
}

void Game::handleInterrogar(const ParsedCommand& cmd) {
    if (cmd.direct_object.empty()) {
        ui_.printWarning("¿A quién desea interrogar?");
        return;
    }

    Creature* c = findCreatureInRoom(cmd.direct_object);
    if (!c) {
        ui_.printError("No hay nadie con ese nombre aquí.");
        return;
    }

    if (c->is_dead) {
        ui_.printInfo(c->name + " está muerto y ya no puede hablar.");
        return;
    }

    if (c->is_satisfied && !c->reward.empty()) {
        ui_.printNarrative(c->name + " repite:\n\"" + c->reward + "\"");
    } else if (!c->dialogue.empty()) {
        ui_.printNarrative(c->name + " le responde:\n\"" + c->dialogue + "\"");
    } else {
        ui_.printInfo(c->name + " no desea hablar con usted.");
    }
}

void Game::handleAbrir(const ParsedCommand& cmd) {
    if (cmd.direct_object.empty()) {
        ui_.printWarning("¿Qué unión desea abrir?");
        return;
    }

    Door* d = findDoorInRoom(cmd.direct_object);
    if (!d) {
        ui_.printError("No existe ninguna unión llamada '" + cmd.direct_object + "' aquí.");
        return;
    }

    if (d->is_open) {
        ui_.printInfo("'" + d->name + "' ya está abierta.");
        return;
    }

    std::string answer = cmd.modifier;

    if (d->is_riddle) {
        if (answer.empty()) {
            ui_.printWarning("Debe resolver este acertijo: " + d->riddle_question);
            return;
        }
        if (Parser::matches(answer, d->riddle_answer)) {
            d->is_open = true;
            ui_.printSuccess("¡Ha descifrado el acertijo correctamente! '" + d->name + "' se abre.");
        } else {
            ui_.printError("Esa no es la respuesta.");
        }
        return;
    }

    if (!d->required_key.empty()) {
        bool key_ok = (!answer.empty() && Parser::matches(answer, d->required_key)) ||
                      hasItem(d->required_key);
        if (key_ok) {
            d->is_open = true;
            ui_.printSuccess("¡La unión '" + d->name + "' ha sido abierta!");
        } else {
            ui_.printError("No es la contraseña o no tiene la llave requerida.");
        }
        return;
    }

    d->is_open = true;
    ui_.printSuccess("Ha abierto '" + d->name + "'.");
}

void Game::handlePesar(const ParsedCommand& cmd) {
    if (!hasItem("balanza")) {
        ui_.printError("Usted no trae la balanza.");
        return;
    }

    if (cmd.direct_object.empty()) {
        ui_.printWarning("¿Qué objeto desea pesar?");
        return;
    }

    if (Parser::matches(cmd.direct_object, "balanza")) {
        ui_.printWarning("Usted trata infructuosamente de colocar la balanza sobre ella misma.");
        return;
    }

    Item* it = findItemInInventory(cmd.direct_object);
    if (!it) it = findItemInRoom(cmd.direct_object);
    if (!it) {
        ui_.printError("No hay '" + cmd.direct_object + "' aquí ni entre sus pertenencias.");
        return;
    }

    ui_.printInfo("Usted coloca " + it->name + " en el plato de la balanza.");
    ui_.printSuccess("La aguja indica " + std::to_string(it->weight) + " bolsas de arena del Río Negro.");
}

void Game::handlePorciento() {
    double pct = getExplorationPercentage();
    ui_.printInfo("Usted ha recorrido un " + std::to_string(static_cast<int>(pct)) + "% de la Fortaleza.");
}

void Game::handleInventario() {
    ui_.drawHeader("INVENTARIO DE PERTENENCIAS", current_weight_, max_weight_, getExplorationPercentage());
    if (inventory_.empty()) {
        ui_.printInfo("Usted no lleva nada consigo.");
        return;
    }
    std::cout << "\n";
    for (const auto& it : inventory_) {
        std::cout << "    • " << it.name << " (" << it.weight << " bolsas)\n";
        ui_.printNarrative("      " + it.description);
    }
    std::cout << "\n  Peso total acumulado: " << current_weight_ << " de " << max_weight_ << " bolsas.\n";
}

void Game::handleSalvarRastro() {
    std::string filename = ui_.readCommand("¿Nombre del fichero rastro? > ");
    if (filename.empty()) return;

    std::ofstream out(filename);
    if (!out) {
        ui_.printError("Error salvando fichero rastro: " + filename);
        return;
    }

    out << "{ Fichero Rastro de La Fortaleza II: La Venganza de la Bestia }\n";
    for (const auto& line : command_history_) {
        out << line << "\n";
    }
    ui_.printSuccess("Rastro guardado exitosamente (" + std::to_string(command_history_.size()) + " comandos) en: " + filename);
}

void Game::handleEjecutarRastro(const std::string& filename) {
    std::string fname = filename;
    if (fname.empty()) {
        fname = ui_.readCommand("¿Nombre del fichero rastro para ejecutar? > ");
    }
    if (fname.empty()) return;

    std::ifstream in(fname);
    if (!in) {
        ui_.printError("Fichero rastro no encontrado: " + fname);
        return;
    }

    ui_.printInfo("Ejecutando rastro desde: " + fname + "...");
    std::string line;
    int executed = 0;

    rooms_ = WorldData::createWorld();
    current_room_id_ = 0;
    inventory_.clear();
    command_history_.clear();
    grifo_muerto_ = false;
    ogro_muerto_ = false;
    serpiente_muerta_ = false;
    carta_rota_ = false;
    col_hielo_derretida_ = false;
    marmidosa_entregada_ = false;
    recalculateWeight();

    while (std::getline(in, line) && is_running_) {
        std::string trimmed = Parser::normalize(line);
        if (!trimmed.empty()) {
            executeCommand(trimmed);
            ++executed;
        }
    }
    ui_.printSuccess("Ejecución completada. Comandos procesados: " + std::to_string(executed));
    showRoom();
}

void Game::executeScript(const std::string& script_filename) {
    handleEjecutarRastro(script_filename);
}

void Game::checkWinCondition() {
    if (serpiente_muerta_ && marmidosa_entregada_ && !won_game_) {
        won_game_ = true;
        is_running_ = false;
        ui_.showEpilogue();
    }
}

} // namespace Fortaleza2
