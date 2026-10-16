#pragma once

#include <string>
#include <vector>
#include <memory>
#include <optional>
#include <unordered_map>
#include <algorithm>

namespace Fortaleza2 {

enum class Verb {
    Ir,          // ir, atravesar, cruzar, entrar
    Mirar,       // mirar, observar, examinar
    Ver,         // ver, leer
    Coger,       // coger, tomar, agarrar
    Soltar,      // soltar, dejar, tirar
    Matar,       // matar, asesinar, atacar
    Romper,      // romper, forzar, destrozar
    Dar,         // dar, regalar, ofrecer, entregar
    Interrogar,  // interrogar, preguntar, hablar
    Abrir,       // abrir
    Pesar,       // pesar (requiere balanza)
    Porciento,   // porciento (porcentaje de salas visitadas)
    Inventario,  // inventario, inv, i
    Salvar,      // salvar, salvar rastro
    Ejecutar,    // ejecutar, ejecutar rastro, cargar
    Ayuda,       // ayuda, help, ?
    Fin,         // terminar, abandonar, salir, fin, quit
    Desconocido
};

struct Item {
    std::string name;
    std::string description;
    int weight{1};
    bool can_pick_up{true};
};

struct Door {
    std::string name;
    std::string description;
    int target_room{0};
    std::string message_enter{""};
    std::string locked_message{""};
    std::string required_key{""};           // Key item or password
    bool is_open{false};
    bool is_riddle{false};
    std::string riddle_question{""};
    std::string riddle_answer{""};
    std::string required_item_to_cross{""}; // e.g. Pañuelo, Grabado, Arco
};

struct Creature {
    std::string name;
    std::string description;
    std::string requested_item{""};
    std::string dialogue{""};
    std::string reward{""};
    std::string lethal_weapon{""};          // e.g. Daga, Cubo de agua, Aguja
    std::string dying_confession{""};
    bool is_satisfied{false};
    bool is_dead{false};
    bool is_hostile{false};
};

struct Room {
    int id{0};
    std::string title;
    std::string description;
    std::vector<Item> items;
    std::vector<Door> doors;
    std::vector<Creature> creatures;
    bool visited{false};
};

struct ParsedCommand {
    Verb verb{Verb::Desconocido};
    std::string direct_object{""};
    std::string indirect_object{""};
    std::string modifier{""};
    std::string raw_input{""};
};

} // namespace Fortaleza2
