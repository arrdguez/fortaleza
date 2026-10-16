#include "Game.h"
#include "WorldData.h"
#include "Parser.h"
#include <fstream>
#include <iostream>

namespace Fortaleza {

Game::Game(TerminalUI& ui) : ui_(ui) {
    rooms_ = WorldData::createWorld();
    current_room_id_ = 0;
    recalculateWeight();
}

int Game::getDestroyedCentersCount() const {
    int count = 0;
    if (pulmones_destruidos_) ++count;
    if (estomago_destruido_) ++count;
    if (corazon_destruido_) ++count;
    if (cerebro_destruido_) ++count;
    return count;
}

void Game::recalculateWeight() {
    current_weight_ = 0;
    for (const auto& item : inventory_) {
        current_weight_ += item.weight;
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

    ui_.drawHeader(r.title, current_weight_, max_weight_, getDestroyedCentersCount());
    std::cout << "\n";
    ui_.printNarrative(r.description);

    // List visible doors
    std::vector<std::string> exit_names;
    for (const auto& d : r.doors) {
        std::string s = d.name;
        if (d.is_open) s += " (abierta)";
        exit_names.push_back(s);
    }
    ui_.printExits(exit_names);

    // List visible items
    std::vector<std::pair<std::string, int>> item_pairs;
    for (const auto& it : r.items) {
        item_pairs.push_back({it.name, it.weight});
    }
    ui_.printItems(item_pairs);

    // List visible creatures
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
    ui_.printSuccess("¡Bienvenido a la Fortaleza!");
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

    // Record non-trivial commands to trace
    if (cmd.verb != Verb::Mirar && cmd.verb != Verb::Ver && cmd.verb != Verb::Inventario &&
        cmd.verb != Verb::Ayuda && cmd.verb != Verb::Salvar && cmd.verb != Verb::Ejecutar &&
        cmd.verb != Verb::Desconocido) {
        command_history_.push_back(raw_command);
    }

    switch (cmd.verb) {
        case Verb::Ir:
            handleIr(cmd);
            break;
        case Verb::Mirar:
            handleMirar(cmd);
            break;
        case Verb::Ver:
            handleVer(cmd);
            break;
        case Verb::Coger:
            handleCoger(cmd);
            break;
        case Verb::Soltar:
            handleSoltar(cmd);
            break;
        case Verb::Matar:
            handleMatar(cmd);
            break;
        case Verb::Romper:
            handleRomper(cmd);
            break;
        case Verb::Dar:
            handleDar(cmd);
            break;
        case Verb::Interrogar:
            handleInterrogar(cmd);
            break;
        case Verb::Abrir:
            handleAbrir(cmd);
            break;
        case Verb::Comer:
            handleComer(cmd);
            break;
        case Verb::Beber:
            handleBeber(cmd);
            break;
        case Verb::Inventario:
            handleInventario();
            break;
        case Verb::Salvar:
            handleSalvarRastro();
            break;
        case Verb::Ejecutar:
            handleEjecutarRastro();
            break;
        case Verb::Ayuda:
            ui_.showManual(WorldData::getManualPages());
            showRoom();
            break;
        case Verb::Fin:
            ui_.printInfo("Ha decidido abandonar la Fortaleza. Hasta la próxima.");
            is_running_ = false;
            return false;
        case Verb::Desconocido:
        default:
            ui_.printError("No entiendo lo que quieres hacer. Escribe 'ayuda' para ver el vocabulario.");
            break;
    }

    checkWinCondition();
    return is_running_;
}

void Game::handleIr(const ParsedCommand& cmd) {
    if (cmd.direct_object.empty()) {
        ui_.printWarning("¿Hacia dónde quieres ir o qué unión deseas cruzar?");
        return;
    }

    Door* door = findDoorInRoom(cmd.direct_object);
    if (!door) {
        // Check if user specified a room title keyword
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

    // Check if door is open
    if (!door->is_open) {
        if (!door->locked_message.empty()) {
            ui_.printWarning(door->locked_message);
        } else {
            ui_.printWarning("La unión '" + door->name + "' está cerrada. Debe abrirla primero.");
        }
        return;
    }

    // Check required item to cross safely
    if (!door->required_item_to_cross.empty()) {
        if (!hasItem(door->required_item_to_cross)) {
            if (current_room_id_ == 7) {
                // Falling down wardrobe without candelabro
                ui_.printError("Usted cae en la oscuridad absoluta del pozo y se estrella contra el fondo de piedra...");
                ui_.printError("¡Ha muerto! Fin de la partida.");
                is_running_ = false;
                return;
            } else if (door->target_room == 18) {
                // Lungs without talisman de aire
                ui_.printError("Un vendaval infernal le arranca la respiración y lo arroja contra los muros de roca... ¡Ha muerto!");
                is_running_ = false;
                return;
            } else if (door->target_room == 19) {
                // Stomach without cake
                ui_.printError("Los jugos gástricos de la Bestia lo disuelven en cuestión de segundos... ¡Ha muerto!");
                is_running_ = false;
                return;
            } else if (door->target_room == 20) {
                // Heart without unicorn heart
                ui_.printError("La presión y el calor volcánico del corazón le hacen estallar el pecho... ¡Ha muerto!");
                is_running_ = false;
                return;
            }
        }
    }

    // Check trap room 25
    if (door->target_room == 25) {
        current_room_id_ = 25;
        ui_.clearScreen();
        ui_.printError("¡Ha caído en una celda sin salida! Las paredes lisas le impiden trepar. Ha quedado atrapado para siempre.");
        showRoom();
        is_running_ = false;
        return;
    }

    // Traversal success
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

    // Examine item in room
    Item* it = findItemInRoom(cmd.direct_object);
    if (!it) it = findItemInInventory(cmd.direct_object);
    if (it) {
        ui_.printInfo(it->description);
        return;
    }

    // Examine door in room
    Door* d = findDoorInRoom(cmd.direct_object);
    if (d) {
        ui_.printInfo(d->description);
        if (d->is_riddle && !d->is_open) {
            ui_.printWarning("Tiene un acertijo grabado: " + d->riddle_question);
        }
        return;
    }

    // Examine creature in room
    Creature* c = findCreatureInRoom(cmd.direct_object);
    if (c) {
        ui_.printInfo(c->description);
        return;
    }

    ui_.printError("No veo ningún '" + cmd.direct_object + "' aquí para mirar.");
}

void Game::handleVer(const ParsedCommand& cmd) {
    // Synonymous with Mirar/Leer
    handleMirar(cmd);
}

void Game::handleCoger(const ParsedCommand& cmd) {
    if (cmd.direct_object.empty()) {
        ui_.printWarning("¿Qué deseas coger?");
        return;
    }

    Item* it = findItemInRoom(cmd.direct_object);
    if (!it) {
        if (findItemInInventory(cmd.direct_object)) {
            ui_.printWarning("Ya llevas '" + cmd.direct_object + "' en tu inventario.");
        } else {
            ui_.printError("No hay ningún '" + cmd.direct_object + "' aquí para coger.");
        }
        return;
    }

    if (!it->can_pick_up) {
        ui_.printError("Usted no puede cargar con eso.");
        return;
    }

    if (current_weight_ + it->weight > max_weight_) {
        ui_.printWarning("Sería demasiado peso. Su capacidad máxima es de " + std::to_string(max_weight_) + " bolsas.");
        return;
    }

    // Add to inventory
    inventory_.push_back(*it);
    recalculateWeight();

    // Remove from room
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
        ui_.printWarning("¿Qué deseas soltar?");
        return;
    }

    if (cmd.direct_object == "todo") {
        if (inventory_.empty()) {
            ui_.printInfo("No llevas nada para soltar.");
            return;
        }
        for (const auto& it : inventory_) {
            rooms_[current_room_id_].items.push_back(it);
        }
        inventory_.clear();
        recalculateWeight();
        ui_.printSuccess("Ha soltado todas sus pertenencias en el suelo.");
        return;
    }

    Item* it = findItemInInventory(cmd.direct_object);
    if (!it) {
        ui_.printError("No tienes ningún '" + cmd.direct_object + "' en tu inventario.");
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
    ui_.printSuccess("Ha soltado: " + item_name + ".");
}

void Game::handleMatar(const ParsedCommand& cmd) {
    if (cmd.direct_object.empty()) {
        ui_.printWarning("¿A quién o qué deseas matar?");
        return;
    }

    Creature* c = findCreatureInRoom(cmd.direct_object);
    if (!c) {
        ui_.printError("No hay nadie con ese nombre aquí para atacar.");
        return;
    }

    if (c->is_dead) {
        ui_.printInfo(c->name + " ya está muerto.");
        return;
    }

    std::string weapon = cmd.modifier;
    if (weapon.empty()) {
        // Auto-select best matching weapon from inventory
        if (!c->lethal_weapon.empty() && hasItem(c->lethal_weapon)) {
            weapon = c->lethal_weapon;
        }
    }

    if (!c->lethal_weapon.empty()) {
        if (weapon.empty() || !Parser::matches(weapon, c->lethal_weapon)) {
            ui_.printWarning("Tus ataques no le hacen daño. Necesitas un arma específica para acabar con " + c->name + ".");
            return;
        }
        if (!hasItem(weapon)) {
            ui_.printError("No tienes '" + weapon + "' en tu inventario.");
            return;
        }
    }

    // Creature is slain!
    c->is_dead = true;
    ui_.printSuccess("¡Has derrotado a " + c->name + "!");

    if (!c->dying_confession.empty()) {
        ui_.printNarrative("En sus últimos instantes de vida agonizante, pronuncia:\n\"" + c->dying_confession + "\"");
    }

    // Specific combat effects
    if (c->name == "Centro de los pulmones") {
        pulmones_destruidos_ = true;
    } else if (c->name == "Centro del estomago") {
        estomago_destruido_ = true;
    } else if (c->name == "Centro del corazon") {
        corazon_destruido_ = true;
    } else if (c->name == "Centro del cerebro") {
        cerebro_destruido_ = true;
    } else if (c->name == "Minotauro") {
        minotauro_muerto_ = true;
        ui_.printInfo("Al caer el Minotauro, las siete antorchas quedan libres para ser examinadas y cogidas.");
    }
}

void Game::handleRomper(const ParsedCommand& cmd) {
    if (cmd.direct_object.empty()) {
        ui_.printWarning("¿Qué deseas romper?");
        return;
    }

    std::string target = cmd.direct_object;
    std::string tool = cmd.modifier;

    // Room 4: Romper espejo con hueso de gato
    if (current_room_id_ == 4 && (target == "espejo" || target == "cristal")) {
        if (!hasItem("hueso de gato") && !Parser::matches(tool, "hueso de gato")) {
            ui_.printWarning("El cristal es mágico. Se necesita un objeto específico para romperlo.");
            return;
        }
        espejo_roto_ = true;
        Door* d = findDoorInRoom("espejo");
        if (d) d->is_open = true;
        ui_.printSuccess("¡El espejo estalla en mil pedazos! Detrás de él queda al descubierto una abertura que conduce a la alcoba de la doncella.");
        return;
    }

    // Room 8: Forzar / romper puerta blindada con hacha
    if (current_room_id_ == 8 && (target == "puerta" || target == "puerta blindada")) {
        if (!hasItem("hacha") && !Parser::matches(tool, "hacha")) {
            ui_.printWarning("La puerta blindada solo puede ser forzada con un arma de gran impacto como un hacha.");
            return;
        }
        Door* d = findDoorInRoom("puerta blindada");
        if (d) d->is_open = true;
        ui_.printSuccess("Con golpes certeros de su hacha, destroza el cerrojo de la puerta blindada. El paso a la sala de armas queda abierto.");
        return;
    }

    // Room 24: Romper columna de cristal con Antorcha 3
    if (current_room_id_ == 24 && (target == "columna" || target == "columna de cristal")) {
        if (!hasItem("antorcha 3") && !Parser::matches(tool, "antorcha 3")) {
            ui_.printWarning("Solo el número sagrado (Antorcha 3) puede resonar con la frecuencia del cristal.");
            return;
        }
        columna_cristal_rota_ = true;
        Door* d = findDoorInRoom("boca de la bestia");
        if (d) d->is_open = true;
        ui_.printSuccess("Al tocar la columna con la Antorcha divina, una onda expansiva pulveriza el cristal abriendo el camino a la boca de la Bestia.");
        return;
    }

    ui_.printError("No puedes romper '" + target + "' de esa forma.");
}

void Game::handleDar(const ParsedCommand& cmd) {
    if (cmd.direct_object.empty() || cmd.indirect_object.empty()) {
        ui_.printWarning("Usa la sintaxis: dar [objeto] a [personaje].");
        return;
    }

    Creature* c = findCreatureInRoom(cmd.indirect_object);
    if (!c) {
        ui_.printError("No veo a '" + cmd.indirect_object + "' aquí para darle nada.");
        return;
    }

    Item* it = findItemInInventory(cmd.direct_object);
    if (!it) {
        ui_.printError("No tienes ningún '" + cmd.direct_object + "' en tu inventario.");
        return;
    }

    if (!c->requested_item.empty() && Parser::matches(it->name, c->requested_item)) {
        c->is_satisfied = true;
        ui_.printSuccess("Le has entregado " + it->name + " a " + c->name + ".");

        // Remove item from inventory
        std::string it_name = it->name;
        for (auto iter = inventory_.begin(); iter != inventory_.end(); ++iter) {
            if (Parser::matches(it_name, iter->name)) {
                inventory_.erase(iter);
                break;
            }
        }
        recalculateWeight();

        // Deliver reward/dialogue
        if (!c->reward.empty()) {
            ui_.printNarrative(c->name + " te dice agradecido:\n\"" + c->reward + "\"");
        }
    } else {
        ui_.printInfo(c->name + " mira el objeto con desinterés y lo rechaza.");
    }
}

void Game::handleInterrogar(const ParsedCommand& cmd) {
    if (cmd.direct_object.empty()) {
        ui_.printWarning("¿A quién deseas interrogar?");
        return;
    }

    Creature* c = findCreatureInRoom(cmd.direct_object);
    if (!c) {
        ui_.printError("No hay nadie con ese nombre aquí para interrogar.");
        return;
    }

    if (c->is_dead) {
        ui_.printInfo(c->name + " está muerto y ya no puede hablar.");
        return;
    }

    if (c->is_satisfied && !c->reward.empty()) {
        ui_.printNarrative(c->name + " repite para ti:\n\"" + c->reward + "\"");
    } else if (!c->dialogue.empty()) {
        ui_.printNarrative(c->name + " te responde:\n\"" + c->dialogue + "\"");
    } else {
        ui_.printInfo(c->name + " no tiene nada que decirte.");
    }
}

void Game::handleAbrir(const ParsedCommand& cmd) {
    if (cmd.direct_object.empty()) {
        ui_.printWarning("¿Qué unión o puerta deseas abrir?");
        return;
    }

    Door* d = findDoorInRoom(cmd.direct_object);
    if (!d) {
        ui_.printError("No veo ninguna puerta llamada '" + cmd.direct_object + "' aquí.");
        return;
    }

    if (d->is_open) {
        ui_.printInfo("'" + d->name + "' ya está abierta.");
        return;
    }

    // Check riddle or password
    std::string answer = cmd.modifier;
    if (d->is_riddle) {
        if (answer.empty()) {
            ui_.printWarning("La puerta exige una respuesta. Acertijo: " + d->riddle_question);
            ui_.printInfo("Use: abrir " + d->name + " respondiendo [su respuesta]");
            return;
        }
        if (Parser::matches(answer, d->riddle_answer)) {
            d->is_open = true;
            ui_.printSuccess("¡Respuesta correcta! La unión '" + d->name + "' se abre de par en par.");
        } else {
            ui_.printError("La puerta rechaza su respuesta: '" + answer + "'.");
        }
        return;
    }

    if (!d->required_key.empty()) {
        // Can be opened with key item or password string
        bool key_match = (!answer.empty() && Parser::matches(answer, d->required_key)) ||
                         hasItem(d->required_key);

        if (key_match) {
            d->is_open = true;
            ui_.printSuccess("¡La unión '" + d->name + "' ha sido abierta con éxito!");
        } else {
            ui_.printError("La unión permanece cerrada. Se requiere una llave o palabra clave.");
        }
        return;
    }

    // Door without lock
    d->is_open = true;
    ui_.printSuccess("Ha abierto '" + d->name + "'.");
}

void Game::handleComer(const ParsedCommand& cmd) {
    Item* it = findItemInInventory(cmd.direct_object);
    if (!it) {
        ui_.printError("No tienes ningún alimento con ese nombre.");
        return;
    }
    if (it->name == "Pastel de cerezas") {
        ui_.printWarning("Comerse el rico pastel de cerezas no parece una buena idea... quizás una criatura lo necesite más que usted.");
    } else {
        ui_.printInfo("No parece muy comestible.");
    }
}

void Game::handleBeber(const ParsedCommand& cmd) {
    Item* it = findItemInInventory(cmd.direct_object);
    if (!it && Parser::matches(cmd.direct_object, "agua")) {
        it = findItemInInventory("vaso de agua");
    }
    if (it && it->name == "Vaso de agua") {
        ui_.printWarning("El agua fresca calma la garganta, pero es un bien muy preciado en la Fortaleza. Podría necesitarla más adelante.");
    } else {
        ui_.printInfo("No hay nada apropiado para beber.");
    }
}

void Game::handleInventario() {
    ui_.drawHeader("INVENTARIO DE PERTENENCIAS", current_weight_, max_weight_, getDestroyedCentersCount());
    if (inventory_.empty()) {
        ui_.printInfo("No llevas ningún objeto contigo.");
        return;
    }

    std::cout << "\n";
    for (const auto& it : inventory_) {
        std::cout << "    • " << it.name << "  (" << it.weight << " bolsas)\n";
        ui_.printNarrative("      " + it.description);
    }
    std::cout << "\n  Peso total acumulado: " << current_weight_ << " de " << max_weight_ << " bolsas.\n";
}

void Game::handleSalvarRastro() {
    std::string filename = ui_.readCommand("¿Nombre del fichero rastro? > ");
    if (filename.empty()) return;

    std::ofstream out(filename);
    if (!out) {
        ui_.printError("No se pudo crear el fichero rastro: " + filename);
        return;
    }

    out << "{ Fichero Rastro de La Fortaleza 1 }\n";
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
        ui_.printError("No se pudo abrir el fichero rastro: " + fname);
        return;
    }

    ui_.printInfo("Ejecutando rastro desde: " + fname + "...");
    std::string line;
    int executed = 0;

    // Reset game world to beginning before replay
    rooms_ = WorldData::createWorld();
    current_room_id_ = 0;
    inventory_.clear();
    command_history_.clear();
    pulmones_destruidos_ = false;
    estomago_destruido_ = false;
    corazon_destruido_ = false;
    cerebro_destruido_ = false;
    recalculateWeight();

    while (std::getline(in, line) && is_running_) {
        std::string trimmed = Parser::normalize(line);
        if (!trimmed.empty()) {
            executeCommand(trimmed);
            ++executed;
        }
    }
    ui_.printSuccess("Ejecución de rastro completada. Comandos procesados: " + std::to_string(executed));
    showRoom();
}

void Game::executeScript(const std::string& script_filename) {
    handleEjecutarRastro(script_filename);
}

void Game::checkWinCondition() {
    if (pulmones_destruidos_ && estomago_destruido_ && corazon_destruido_ && cerebro_destruido_ && !won_game_) {
        won_game_ = true;
        ui_.clearScreen();
        std::cout << "\n\n";
        ui_.printSuccess("══════════════════════════════════════════════════════════════════════");
        ui_.printSuccess("                 ¡ V I C T O R I A   T O T A L !                      ");
        ui_.printSuccess("══════════════════════════════════════════════════════════════════════");
        ui_.printNarrative(
            "Con el cerebro de la Bestia consumido por el fuego sagrado y sus cuatro\n"
            "centros vitales totalmente destruidos, la abominación colapsa en un rugido\n"
            "ensordecedor que hace temblar los cimientos de la tierra.\n\n"
            "Las negras torres de La Fortaleza se derrumban piedra sobre piedra y la\n"
            "luz del sol vuelve a bañar las tierras tras siglos de oscuridad.\n\n"
            "¡Felicidades, noble aventurero! Has completado La Fortaleza 1 de Manuel Cepero."
        );
        ui_.printSuccess("══════════════════════════════════════════════════════════════════════\n");
    }
}

} // namespace Fortaleza
