#include "Parser.h"
#include <sstream>
#include <cctype>
#include <regex>

namespace Fortaleza {

std::string Parser::normalize(const std::string& input) {
    std::string clean;
    clean.reserve(input.size());

    // 1. Remove Pascal comments { ... }
    bool in_comment = false;
    for (size_t i = 0; i < input.size(); ++i) {
        if (input[i] == '{') {
            in_comment = true;
            continue;
        }
        if (input[i] == '}') {
            in_comment = false;
            continue;
        }
        if (!in_comment) {
            clean += input[i];
        }
    }

    // 2. Normalize UTF-8 and extended ASCII accents to standard lowercase ASCII
    std::string result;
    result.reserve(clean.size());

    for (size_t i = 0; i < clean.size(); ++i) {
        unsigned char c = static_cast<unsigned char>(clean[i]);
        if (c == 0xc3 && i + 1 < clean.size()) {
            unsigned char next = static_cast<unsigned char>(clean[++i]);
            switch (next) {
                case 0xa1: case 0x81: result += 'a'; break; // á, Á
                case 0xa9: case 0x89: result += 'e'; break; // é, É
                case 0xad: case 0x8d: result += 'i'; break; // í, Í
                case 0xb3: case 0x93: result += 'o'; break; // ó, Ó
                case 0xba: case 0x9a: result += 'u'; break; // ú, Ú
                case 0xbc: case 0x9c: result += 'u'; break; // ü, Ü
                case 0xb1: case 0x91: result += 'n'; break; // ñ, Ñ
                default: break;
            }
        } else if (c >= 0x80) {
            // CP437 or Latin-1 single byte handling
            switch (c) {
                case 0xa0: case 0x85: case 0xe1: result += 'a'; break; // á, à
                case 0x82: case 0x8a: case 0xe9: result += 'e'; break; // é, è
                case 0xa1: case 0x8d: case 0xed: result += 'i'; break; // í, ì
                case 0xa2: case 0x95: case 0xf3: result += 'o'; break; // ó, ò
                case 0xa3: case 0x97: case 0xfa: result += 'u'; break; // ú, ù
                case 0x81: case 0x9a: case 0xfc: result += 'u'; break; // ü, Ü
                case 0xa4: case 0xa5: case 0xf1: case 0xd1: result += 'n'; break; // ñ, Ñ
                default: break;
            }
        } else {
            result += static_cast<char>(std::tolower(c));
        }
    }

    // 3. Trim punctuation and collapse whitespace
    std::string final_str;
    bool last_space = true;
    for (char ch : result) {
        if (std::isalnum(static_cast<unsigned char>(ch))) {
            final_str += ch;
            last_space = false;
        } else if (std::isspace(static_cast<unsigned char>(ch))) {
            if (!last_space) {
                final_str += ' ';
                last_space = true;
            }
        }
    }

    if (!final_str.empty() && final_str.back() == ' ') {
        final_str.pop_back();
    }

    return final_str;
}

std::vector<std::string> Parser::splitWords(const std::string& str) {
    std::vector<std::string> words;
    std::istringstream iss(str);
    std::string w;
    while (iss >> w) {
        words.push_back(w);
    }
    return words;
}

std::string Parser::stripArticles(const std::string& text) {
    auto words = splitWords(text);
    std::string result;
    for (const auto& w : words) {
        if (w == "el" || w == "la" || w == "los" || w == "las" ||
            w == "un" || w == "una" || w == "unos" || w == "unas" ||
            w == "por" || w == "del" || w == "al" || w == "de") {
            continue;
        }
        if (!result.empty()) result += " ";
        result += w;
    }
    return result;
}

bool Parser::matches(const std::string& input, const std::string& target) {
    std::string norm_in = stripArticles(normalize(input));
    std::string norm_tgt = stripArticles(normalize(target));

    if (norm_in.empty() || norm_tgt.empty()) return false;
    if (norm_in == norm_tgt) return true;

    // Check if one contains the other or matches main keyword
    if (norm_tgt.find(norm_in) != std::string::npos || norm_in.find(norm_tgt) != std::string::npos) {
        return true;
    }
    return false;
}

Verb Parser::identifyVerb(const std::string& word) {
    if (word == "ir" || word == "atravesar" || word == "cruzar" || word == "entrar" || word == "caminar") return Verb::Ir;
    if (word == "mirar" || word == "observar" || word == "examinar") return Verb::Mirar;
    if (word == "ver" || word == "leer") return Verb::Ver;
    if (word == "coger" || word == "tomar" || word == "agarrar" || word == "recoger") return Verb::Coger;
    if (word == "soltar" || word == "dejar" || word == "tirar") return Verb::Soltar;
    if (word == "matar" || word == "asesinar" || word == "atacar") return Verb::Matar;
    if (word == "romper" || word == "forzar" || word == "destrozar" || word == "quebrar") return Verb::Romper;
    if (word == "dar" || word == "regalar" || word == "ofrecer" || word == "entregar") return Verb::Dar;
    if (word == "interrogar" || word == "preguntar" || word == "hablar") return Verb::Interrogar;
    if (word == "abrir") return Verb::Abrir;
    if (word == "comer" || word == "ingerir") return Verb::Comer;
    if (word == "beber") return Verb::Beber;
    if (word == "inventario" || word == "inv" || word == "i") return Verb::Inventario;
    if (word == "salvar") return Verb::Salvar;
    if (word == "ejecutar" || word == "cargar") return Verb::Ejecutar;
    if (word == "ayuda" || word == "help" || word == "?") return Verb::Ayuda;
    if (word == "terminar" || word == "salir" || word == "fin" || word == "quit") return Verb::Fin;

    return Verb::Desconocido;
}

ParsedCommand Parser::parse(const std::string& line) {
    ParsedCommand cmd;
    cmd.raw_input = line;

    std::string norm = normalize(line);
    if (norm.empty()) return cmd;

    auto words = splitWords(norm);
    if (words.empty()) return cmd;

    // Check two-word verbs: "salvar rastro", "ejecutar rastro"
    if (words.size() >= 2) {
        if (words[0] == "salvar" && words[1] == "rastro") {
            cmd.verb = Verb::Salvar;
            return cmd;
        }
        if (words[0] == "ejecutar" && words[1] == "rastro") {
            cmd.verb = Verb::Ejecutar;
            return cmd;
        }
    }

    cmd.verb = identifyVerb(words[0]);

    // If first word isn't a recognized verb, maybe the user directly typed a direction/door
    // e.g. "puerta principal", "norte", "sur"
    if (cmd.verb == Verb::Desconocido) {
        cmd.verb = Verb::Ir;
        cmd.direct_object = stripArticles(norm);
        return cmd;
    }

    // Remaining text after verb
    size_t first_space = norm.find(' ');
    std::string remainder = (first_space != std::string::npos) ? norm.substr(first_space + 1) : "";
    if (remainder.empty()) {
        return cmd;
    }

    // Specific verb syntax parsers
    if (cmd.verb == Verb::Dar) {
        // Syntax: "dar [objeto] a [personaje]"
        size_t a_pos = remainder.find(" a ");
        if (a_pos != std::string::npos) {
            cmd.direct_object = stripArticles(remainder.substr(0, a_pos));
            cmd.indirect_object = stripArticles(remainder.substr(a_pos + 3));
        } else {
            cmd.direct_object = stripArticles(remainder);
        }
    }
    else if (cmd.verb == Verb::Romper || cmd.verb == Verb::Matar) {
        // Syntax: "romper [objeto] con [herramienta]" or "matar [enemigo] con [arma]"
        size_t con_pos = remainder.find(" con ");
        if (con_pos != std::string::npos) {
            cmd.direct_object = stripArticles(remainder.substr(0, con_pos));
            cmd.modifier = stripArticles(remainder.substr(con_pos + 5));
        } else {
            cmd.direct_object = stripArticles(remainder);
        }
    }
    else if (cmd.verb == Verb::Abrir) {
        // Syntax: "abrir [puerta] diciendo [palabras]" / "respondiendo [resp]" / "con [clave]"
        std::vector<std::string> connectors = {" diciendo ", " respondiendo ", " con "};
        bool matched_conn = false;
        for (const auto& conn : connectors) {
            size_t pos = remainder.find(conn);
            if (pos != std::string::npos) {
                cmd.direct_object = stripArticles(remainder.substr(0, pos));
                // Don't strip articles from passwords/answers!
                cmd.modifier = normalize(remainder.substr(pos + conn.size()));
                matched_conn = true;
                break;
            }
        }
        if (!matched_conn) {
            cmd.direct_object = stripArticles(remainder);
        }
    }
    else {
        cmd.direct_object = stripArticles(remainder);
    }

    return cmd;
}

} // namespace Fortaleza
