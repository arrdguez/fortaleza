#include "WorldData.h"

namespace Fortaleza {

std::string WorldData::getIntroTitle() {
    return "============================================================\n"
           "                     L A   F O R T A L E Z A                \n"
           "                (c) 1990 Manuel Cepero - Cuba               \n"
           "============================================================\n";
}

std::string WorldData::getCredits() {
    return "LA FORTALEZA 1\n"
           "Diseño original, programación y textos: Manuel Cepero (1990)\n"
           "Reconstrucción y modernización en C++: Antigravity AI (2026)\n\n"
           "Dedicado a todos los aventureros que exploraron los oscuros pasillos\n"
           "de la Fortaleza y desafiaron los cuatro centros vitales de la Bestia.\n";
}

std::vector<std::string> WorldData::getManualPages() {
    return {
        "GRAN METODO INFALIBLE PARA RESOLVER FORTALEZAS (Parte 1)\n"
        "por Manuel Cepero\n\n"
        "Regla 1: Desconfíe de todo lo que vea. Las cosas no siempre son lo que parecen.\n"
        "Regla 2: Examine cada rincón con cuidado usando los comandos 'mirar' y 'ver'.\n"
        "Regla 3: Tenga presente que el peso que puede cargar es limitado. No intente\n"
        "         llevarse todo lo que encuentre.\n"
        "Regla 4: Aprenda a clasificar lo que encuentre en tres categorías:\n"
        "         (1) Cosas inanimadas: Se pueden coger, a no ser que pesen demasiado.\n"
        "             En ese caso aparecerá el mensaje: 'Sería mucho peso.'\n"
        "         (2) Cosas que esconden otras cosas: No pueden cogerse. Debe romperlas\n"
        "             con algún objeto específico para descubrir lo que ocultan.\n"
        "         (3) Criaturas vivas: Se dividen en aliados y enemigos.",

        "GRAN METODO INFALIBLE PARA RESOLVER FORTALEZAS (Parte 2)\n\n"
        "Regla 5: Con las criaturas aliadas, interrogue primero para saber qué necesitan.\n"
        "         Entrégueles el objeto deseado con el comando 'dar' y vuelva a\n"
        "         interrogarlas: le revelarán información vital para su travesía.\n"
        "         Con los enemigos, no tenga piedad: use 'matar [enemigo] con [arma]'.\n"
        "         Al morir, sus últimas palabras suelen ser confesiones valiosas.\n\n"
        "Regla 6: Las uniones (puertas, caminos, pasadizos) pueden estar abiertas o cerradas.\n"
        "         Para abrirlas use 'abrir [puerta] con [llave o palabra]'.\n"
        "         Si requieren una palabra mágica, use 'abrir [puerta] diciendo [palabras]'.\n"
        "         Si exigen un acertijo, use 'abrir [puerta] respondiendo [respuesta]'.\n\n"
        "Regla 7: Ciertas puertas solo pueden atravesarse si lleva consigo un objeto\n"
        "         protector. Sin él, la muerte puede ser instantánea.",

        "GRAN METODO INFALIBLE PARA RESOLVER FORTALEZAS (Parte 3)\n"
        "Vocabulario y Sintaxis de Comandos:\n\n"
        "■ Moverse: IR, ATRAVESAR, CRUZAR, ENTRAR\n"
        "  Ejemplos: ir puerta / atravesar puente / entrar tunel\n\n"
        "■ Observar: MIRAR (el lugar o un objeto), VER, LEER (inscripciones o libros)\n"
        "  Ejemplos: mirar / mirar roble / leer inscripcion\n\n"
        "■ Tomar y Dejar: COGER, TOMAR, SOLTAR, DEJAR\n"
        "  Ejemplos: coger espada / tomar taza de cafe / dejar maza / dejar todo\n\n"
        "■ Destruir: ROMPER, FORZAR [objeto] CON [herramienta]\n"
        "  Ejemplos: romper espejo con hueso de gato / forzar puerta con hacha\n\n"
        "■ Dar: DAR, REGALAR [objeto] A [personaje]\n"
        "  Ejemplos: dar cigarro a llamador / dar pastel de cerezas a troll",

        "GRAN METODO INFALIBLE PARA RESOLVER FORTALEZAS (Parte 4)\n\n"
        "■ Combatir: MATAR, ASESINAR [enemigo] CON [arma]\n"
        "  Ejemplos: matar minotauro con espada / matar corazon con daga\n\n"
        "■ Conversar: INTERROGAR, PREGUNTAR [personaje]\n"
        "  Ejemplos: interrogar bruja / preguntar doncella\n\n"
        "■ Inventario: INVENTARIO, INV, I\n"
        "  Muestra sus pertenencias y el peso acumulado en bolsas de arena.\n\n"
        "■ Salvar y Ejecutar Rastro: SALVAR, EJECUTAR\n"
        "  Permite guardar todos los pasos en un fichero de texto y reproducirlos\n"
        "  automáticamente en cualquier momento. ¡La herramienta suprema del aventurero!"
    };
}

std::vector<Room> WorldData::createWorld() {
    std::vector<Room> rooms(32);

    // ==========================================
    // Room 0: Exterior de la fortaleza
    // ==========================================
    rooms[0].id = 0;
    rooms[0].title = "el exterior de la fortaleza";
    rooms[0].description = "Las paredes son muy negras y al parecer, no tienen ventanas. Usted trata de ver el final de las torres, pero las nubes no se lo permiten.";
    rooms[0].items = {
        {"Roble", "Está completamente seco y lleno de mordiscos. Tiene las siguientes palabras talladas en el tronco: \"Las palabras mágicas para abrir la puerta son obvias.\"", 200, false},
        {"Maza", "Es muy pesada.", 39, true},
        {"Pastel de cerezas", "¿Qué hace un pastel de cerezas en un lugar como este?", 2, true}
    };
    rooms[0].creatures = {
        {"Llamador de bronce", "Es de bronce macizo y tiene forma de leon.", "cigarro",
         "¿Me puede regalar un cigarro?",
         "Hay un nombre que vas a necesitar mucho: Rumpelstinskin.", "", "", false, false, false}
    };
    rooms[0].doors = {
        {"Puerta principal", "Inmensa y oprimente.", 1,
         "Su sombra desaparece lentamente al cruzar la puerta. Siente cómo el miedo se le enreda en los zapatos.",
         "La puerta está firmemente cerrada.", "abrete sesamo", false, false, "", "", ""},
        {"Puente de marmol", "Conduce hacia la distancia sobre el abismo.", 26,
         "Usted cruza con cautela el puente de mármol.", "", "", true, false, "", "", ""}
    };

    // ==========================================
    // Room 1: Salón de recepciones
    // ==========================================
    rooms[1].id = 1;
    rooms[1].title = "el Salón de recepciones";
    rooms[1].description = "Parece hecho para criaturas cientos de veces más grandes que los humanos. Está desierto, pero usted siente que es observado.";
    rooms[1].items = {
        {"Retrato", "Es de Hitchcock (un anacronismo). Usted recuerda instintivamente algunas películas que le erizaron la piel: Psicosis, Los pájaros y Los treinta y nueve escalones.", 1, true}
    };
    rooms[1].creatures = {
        {"Mendigo", "Un anciano andrajoso acurrucado en una esquina.", "vaso de agua",
         "Dame agua, por favor...",
         "Busca a la doncella al lado del espejo que romperás con un hueso. Ella te dirá dónde está el final de la Bestia.",
         "", "", false, false, false}
    };
    rooms[1].doors = {
        {"Puerta principal", "Conduce de regreso al exterior.", 0,
         "Usted sale de regreso al exterior de la fortaleza.", "", "", true, false, "", "", ""},
        {"Puerta verde", "Una puerta de madera pintada de verde oscuro.", 2,
         "Usted atraviesa la puerta verde hacia la sala de juegos.", "", "", true, false, "", "", ""},
        {"Puerta azul", "Una pesada puerta azulada.", 3,
         "Usted cruza la puerta azul hacia el patio interior.", "", "", true, false, "", "", ""}
    };

    // ==========================================
    // Room 2: Sala de juegos
    // ==========================================
    rooms[2].id = 2;
    rooms[2].title = "la Sala de juegos";
    rooms[2].description = "Usted trata de imaginar cómo eran los juegos del salón. Hay doce mesas y cada una tiene doce erizos.";
    rooms[2].items = {
        {"Escoba", "Es una escoba voladora.", 1, true},
        {"Inscripcion", "Dice: \"Cuando hayas llegado casi al final, tendrás que regresar. (A no ser que hayas leído mucho y tengas buena memoria.)\"", 10, false},
        {"Hilo de Ariadna", "Debe tener varios kilómetros de largo.", 1, true}
    };
    rooms[2].doors = {
        {"Puerta verde", "Conduce de regreso al Salón de recepciones.", 1,
         "Usted regresa al Salón de recepciones.", "", "", true, false, "", "", ""},
        {"Puerta azul", "Conduce al patio interior.", 3,
         "Usted pasa al patio interior.", "", "", true, false, "", "", ""},
        {"Escalera", "Usted trata de ver hasta dónde llega, pero no puede.", 4,
         "Usted sube por la escalera. No se explica cómo, siendo tan larga, solo tiene treinta y nueve escalones.",
         "La escalera parece bloquearse en una paradoja dimensional.", "treinta y nueve",
         false, true, "¿Cuántos peldaños tienen todas las escaleras del mundo?", "treinta y nueve", ""}
    };

    // ==========================================
    // Room 3: Patio interior
    // ==========================================
    rooms[3].id = 3;
    rooms[3].title = "el Patio interior";
    rooms[3].description = "El patio tiene forma de caracol. Cada uno o dos pasos se levanta una columna de mármol negro y se confunde en la altura con los árboles. Usted siente el crujido de las hojas secas bajo sus zapatos.";
    rooms[3].items = {
        {"Balanza", "Una balanza de bronce muy precisa.", 5, true}
    };
    rooms[3].creatures = {
        {"Estatua de Atenea", "Hecha por Fidias, siete años después de su muerte. Le falta la lanza.", "lanza",
         "¡Sal de mi presencia, estúpido mortal!",
         "Para llegar a los pulmones de la Bestia debes tener el talisman de aire.",
         "", "", false, false, false},
        {"Arpia", "Está desayunando con cara de pocos amigos.", "paraguas",
         "¡Kraaa! ¡Odio que me interrumpan!",
         "En la biblioteca hay un libro que conduce al jardín.",
         "", "", false, false, false}
    };
    rooms[3].doors = {
        {"Puerta azul", "Conduce a la Sala de juegos.", 2,
         "Usted entra a la Sala de juegos.", "", "", true, false, "", "", ""},
        {"Puerta de roble", "Una puerta maciza que conduce a la biblioteca.", 5,
         "Usted entra a la biblioteca.", "", "", true, false, "", "", ""}
    };

    // ==========================================
    // Room 4: Cuarto de espejos
    // ==========================================
    rooms[4].id = 4;
    rooms[4].title = "el Cuarto de espejos";
    rooms[4].description = "Hay tantos espejos que no puede reconocer si usted es real o es una imagen de sí mismo.";
    rooms[4].items = {
        {"Hueso de gato", "Un hueso fino y misterioso.", 1, true}
    };
    rooms[4].doors = {
        {"Escalera", "La escalera que baja hacia la sala de juegos.", 2,
         "Usted desciende con cuidado por la escalera.", "", "", true, false, "", "", ""},
        {"Espejo", "Un enorme espejo ornamentado en la pared oriental.", 13,
         "Al romperse el cristal, una abertura secreta le permite pasar a la alcoba contigua.",
         "El cristal del espejo es sólido y refleja infinitas imágenes suyas.", "hueso de gato",
         false, false, "", "", ""}
    };

    // ==========================================
    // Room 5: Biblioteca
    // ==========================================
    rooms[5].id = 5;
    rooms[5].title = "la Biblioteca";
    rooms[5].description = "Hay miles de libros en este lugar. Todos tienen alguna hoja marcada con una servilleta.";
    rooms[5].items = {
        {"Vaso de agua", "El agua es clara y fresca.", 1, true},
        {"Candelabro", "Un candelabro dorado con tres velas aromáticas.", 1, true}
    };
    rooms[5].doors = {
        {"Puerta de roble", "Regresa al patio interior.", 3,
         "Usted regresa al patio interior.", "", "", true, false, "", "", ""},
        {"Pasillo", "Un arco que da a un largo y sombrío pasillo.", 6,
         "Usted avanza por el pasillo.", "Un campo de fuerza susurra: 'Contraseña requerida'.",
         "nombus rostomelaris", false, false, "", "", ""},
        {"Libro", "Un tomo antiguo encuadernado en cuero verde.", 12,
         "Al tirar del libro, una estantería gira revelando un pasadizo hacia el jardín.",
         "", "", true, false, "", "", ""}
    };

    // ==========================================
    // Room 6: Pasillo
    // ==========================================
    rooms[6].id = 6;
    rooms[6].title = "Pasillo";
    rooms[6].description = "Tiene tres puertas al lado y una al final.";
    rooms[6].items = {
        {"Antorcha", "Arde con una llama amarilla constante que ilumina las tinieblas.", 1, true}
    };
    rooms[6].doors = {
        {"Puerta de la biblioteca", "Regresa a la biblioteca.", 5,
         "Usted entra a la biblioteca.", "", "", true, false, "", "", ""},
        {"Puerta de la bruja", "Una puerta de madera carcomida con símbolos extraños.", 7,
         "Usted entra a la alcoba de la bruja.", "", "", true, false, "", "", ""},
        {"Puerta del guerrero", "Una puerta de roble con refuerzos de hierro.", 8,
         "Usted entra al cuarto del guerrero.", "", "", true, false, "", "", ""},
        {"Puerta del laboratorio", "Una puerta metálica fría al tacto.", 9,
         "Usted entra al laboratorio de la Bestia.", "", "", true, false, "", "", ""},
        {"Puerta oriental", "Conduce a la sala de infusiones.", 14,
         "Usted entra a la sala de infusiones.", "", "", true, false, "", "", ""}
    };

    // ==========================================
    // Room 7: Alcoba de la bruja
    // ==========================================
    rooms[7].id = 7;
    rooms[7].title = "la Alcoba de la bruja";
    rooms[7].description = "Hasta un ciego descubriría que aquí habita una bruja. El cuarto tiene una ventana, pero usted no recuerda haberla visto desde afuera.";
    rooms[7].items = {
        {"Polvo magico", "Un saquito con polvo brillante de colores cambiantes.", 1, true},
        {"Pocion para crecer", "Un frasco de vidrio con un líquido efervescente.", 5, true}
    };
    rooms[7].creatures = {
        {"Bruja", "Una mujer anciana de ojos penetrantes revolviendo un caldero.", "pastel de cerezas",
         "¿Quién osa interrumpir mis encantamientos?",
         "Escucha bien, hijo. Cuando te digan \"Prohibido\", invoca la luz. Recuerda que la palabra crea a su significado.",
         "", "", false, false, false}
    };
    rooms[7].doors = {
        {"Puerta", "Regresa al pasillo principal.", 6,
         "Usted sale al pasillo.", "", "", true, false, "", "", ""},
        {"Escaparate", "Un gran armario antiguo de madera tallada.", 13,
         "Usted cae durante varios minutos y, gracias al candelabro, cuando toca el suelo no se hace daño. Llega a la alcoba de la doncella.",
         "Usted cae en la oscuridad absoluta y se estrella contra el fondo de piedra... ¡Ha muerto!",
         "", true, false, "", "", "candelabro"}
    };

    // ==========================================
    // Room 8: Cuarto del guerrero
    // ==========================================
    rooms[8].id = 8;
    rooms[8].title = "el Cuarto del guerrero";
    rooms[8].description = "El cuarto está muy ordenado. A usted le sorprende que no hayan armas.";
    rooms[8].items = {
        {"Vendajes", "Tiras de lino limpias.", 3, true},
        {"Grabado", "Muestra a un guerrero empuñando una espada frente a un minotauro.", 3, true}
    };
    rooms[8].doors = {
        {"Puerta al pasillo", "Regresa al pasillo.", 6,
         "Usted regresa al pasillo.", "", "", true, false, "", "", ""},
        {"Puerta blindada", "Una pesada puerta que bloquea el paso hacia la sala de armas.", 10,
         "Con gran esfuerzo y el filo del hacha, logra quebrar el cerrojo y abrir la puerta.",
         "La puerta está trancada por dentro. Necesita algo contundente como un hacha para forzarla.",
         "hacha", false, false, "", "", ""}
    };

    // ==========================================
    // Room 9: Laboratorio de la Bestia
    // ==========================================
    rooms[9].id = 9;
    rooms[9].title = "el Laboratorio de la Bestia";
    rooms[9].description = "Hay muchos frascos. A usted le llaman la atención los últimos: están llenos de homúnculos.";
    rooms[9].items = {
        {"Piedra filosofal", "Usted es el primer humano en ver la quinta esencia.", 10, true},
        {"Maquina del tiempo", "Es muy parecida a una máquina de moler carne.", 3, true}
    };
    rooms[9].creatures = {
        {"Homunculo", "Un diminuto ser encerrado en un frasco de cristal.", "pocion para crecer",
         "¡¡Quiero crecer!! ¡Dame la poción!",
         "Para atravesar por el escaparate de la bruja, debes llevar un candelabro. Y al hacerlo vas a conocer algo importante.",
         "", "", false, false, false}
    };
    rooms[9].doors = {
        {"Puerta al pasillo", "Regresa al pasillo.", 6,
         "Usted sale al pasillo.", "", "", true, false, "", "", ""}
    };

    // ==========================================
    // Room 10: Sala de armas
    // ==========================================
    rooms[10].id = 10;
    rooms[10].title = "la Sala de armas";
    rooms[10].description = "Este lugar parece salido del sueño de un guerrero.";
    rooms[10].items = {
        {"Espada", "Forjada en acero toledano, afilada como un relámpago.", 5, true},
        {"Lanza", "Punta de bronce bien equilibrada.", 10, true},
        {"Arco", "Hecho de tejo flexible con cuerda de tripa.", 5, true},
        {"Daga", "Hoja corta y triangular, ideal para atravesar armaduras.", 3, true},
        {"Ariete", "Demasiado grande y pesado para llevar.", 30, false},
        {"Latigo", "Parece una culebra trenzada de cuero resistente.", 2, true}
    };
    rooms[10].doors = {
        {"Puerta al cuarto del guerrero", "Regresa al cuarto del guerrero.", 8,
         "Usted regresa al cuarto del guerrero.", "", "", true, false, "", "", ""}
    };

    // ==========================================
    // Room 11: Baños de la Bestia
    // ==========================================
    rooms[11].id = 11;
    rooms[11].title = "los Baños de la Bestia";
    rooms[11].description = "El baño es tan grande que usted no puede ver las paredes que lo limitan.";
    rooms[11].items = {
        {"Rosa", "Una rosa roja que despide un aroma embriagador.", 1, true},
        {"Inscripcion", "Dice: \"La última habitación está al principio.\"", 2, true},
        {"Espejo", "Un enorme espejo opaco empotrado en la roca.", 20, false}
    };
    rooms[11].creatures = {
        {"Troll", "Un troll gigante y verrugoso sentado cerca de las aguas termales.", "polvo magico",
         "¡Groooar! ¡No te acerques si no tienes magia para mí!",
         "El corazón de unicornio te protegerá en el corazón de la Bestia.",
         "", "", false, false, false}
    };
    rooms[11].doors = {
        {"Arco hacia el jardin", "Conduce al jardín de la fortaleza.", 12,
         "Usted pasa al inmenso jardín.", "", "", true, false, "", "", ""}
    };

    // ==========================================
    // Room 12: El Jardín
    // ==========================================
    rooms[12].id = 12;
    rooms[12].title = "el Jardín";
    rooms[12].description = "Se podrían construir varias ciudades en su interior.";
    rooms[12].items = {
        {"Inscripcion", "Grabada en una losa: \"El fuego purifica lo que el agua no puede apagar.\"", 1, true},
        {"Cedro", "Un árbol milenario cuyas ramas tocan el techo rocoso.", 41, false}
    };
    rooms[12].doors = {
        {"Puerta a los banos", "Conduce a los Baños de la Bestia.", 11,
         "Usted entra a los Baños de la Bestia.", "", "", true, false, "", "", ""},
        {"Puerta a la alcoba", "Conduce a la alcoba de la doncella.", 13,
         "Usted entra a la alcoba de la doncella.", "", "", true, false, "", "", ""},
        {"Puerta a infusiones", "Conduce a la sala de infusiones.", 14,
         "Usted entra a la sala de infusiones.", "", "", true, false, "", "", ""},
        {"Puerta a calabozos", "Conduce a los calabozos húmedos.", 15,
         "Usted desciende a los calabozos.", "", "", true, false, "", "", ""},
        {"Puerta a almacenes", "Conduce a los almacenes de la fortaleza.", 22,
         "Usted entra a los almacenes.", "", "", true, false, "", "", ""}
    };

    // ==========================================
    // Room 13: Alcoba de la doncella
    // ==========================================
    rooms[13].id = 13;
    rooms[13].title = "la Alcoba de la doncella";
    rooms[13].description = "Es una habitación muy pequeña y húmeda.";
    rooms[13].items = {
        {"Cuadro", "Pintura de un paisaje campestre soleado.", 10, true},
        {"Corazon de unicornio", "Brilla con una luz pura y cálida.", 1, true}
    };
    rooms[13].creatures = {
        {"Doncella", "Una joven de ojos tristes sentada en el borde de un jergón.", "rosa",
         "¿Quién eres? ¿Vienes a salvarme o a atormentarme?",
         "La última habitación está al principio. ¡Y ten cuidado con la Bestia! Para vencer su cerebro necesitarás las letras que no forman su nombre.",
         "", "", false, false, false}
    };
    rooms[13].doors = {
        {"Puerta al jardin", "Conduce al jardín exterior.", 12,
         "Usted sale al jardín.", "", "", true, false, "", "", ""},
        {"Espejo roto", "El marco del espejo roto que comunica con el cuarto de espejos.", 4,
         "Usted pasa a través del marco roto hacia el cuarto de espejos.", "", "", true, false, "", "", ""}
    };

    // ==========================================
    // Room 14: Sala de infusiones
    // ==========================================
    rooms[14].id = 14;
    rooms[14].title = "la Sala de infusiones";
    rooms[14].description = "Hay varias mesas regadas por el suelo. Usted tiene la impresión de que ningún humano ha estado en ese lugar anteriormente.";
    rooms[14].items = {
        {"Taza de cafe", "El café todavía despide un vapor aromático.", 1, true},
        {"Cigarro", "Un cigarro puro hecho con hojas selectas.", 1, true}
    };
    rooms[14].creatures = {
        {"Anciano sabio", "Un anciano meditando tranquilamente frente a una mesa baja.", "taza de cafe",
         "Un poco de café caliente me vendría muy bien en esta soledad...",
         "¡Imnus humiscuol rastomislakis!! Con la espada matarás a los pulmones de la Bestia. Pero recuerda: para el estómago necesitarás un látigo.",
         "", "", false, false, false}
    };
    rooms[14].doors = {
        {"Puerta al pasillo", "Conduce de regreso al pasillo.", 6,
         "Usted sale al pasillo.", "", "", true, false, "", "", ""},
        {"Puerta al jardin", "Conduce al jardín.", 12,
         "Usted sale al jardín.", "", "", true, false, "", "", ""}
    };

    // ==========================================
    // Room 15: Calabozos
    // ==========================================
    rooms[15].id = 15;
    rooms[15].title = "los Calabozos";
    rooms[15].description = "Son tan húmedos que usted no resistiría ni unas horas dentro de ellos.";
    rooms[15].items = {
        {"Paraguas", "Está cerrado pero en perfecto estado.", 2, true},
        {"Talisman de aire", "Está hecho de cinco vientos amarrados con un hilo mágico.", 1, true}
    };
    rooms[15].creatures = {
        {"Prisionero", "Un hombre encadenado a la pared, con los labios resecos.", "vaso de agua",
         "¡Agua!... por favor... me muero de sed...",
         "Al entrar al estómago de la Bestia, lleva contigo un pastel de cerezas para calmar los jugos ácidos. Y no olvides: ¡Rumpelstinskin abre grandes secretos!",
         "", "", false, false, false}
    };
    rooms[15].doors = {
        {"Escalera hacia el jardin", "Sube hacia el jardín.", 12,
         "Usted asciende hacia el jardín.", "", "", true, false, "", "", ""}
    };

    // ==========================================
    // Room 16: Boca de la Bestia
    // ==========================================
    rooms[16].id = 16;
    rooms[16].title = "Boca de la Bestia";
    rooms[16].description = "Es como una boca humana, pero del tamaño de una casa. Los dientes son como estalagmitas y el aliento es fétido.";
    rooms[16].items = {};
    rooms[16].doors = {
        {"Garganta", "Conduce al interior de la criatura.", 17,
         "Usted desciende resbalando por la viscosa garganta hacia las entrañas de la Bestia.",
         "", "", true, false, "", "", ""},
        {"Puerta hacia el salon de cristal", "Conduce al Salón de cristal.", 24,
         "Usted cruza hacia el Salón de cristal.", "", "", true, false, "", "", ""}
    };

    // ==========================================
    // Room 17: Interior de la Bestia
    // ==========================================
    rooms[17].id = 17;
    rooms[17].title = "Interior de la Bestia";
    rooms[17].description = "Usted puede sentir los latidos del corazón de la Bestia, al igual que su respiración o el ruido de los líquidos revueltos en su estómago.";
    rooms[17].items = {
        {"Inscripcion", "Grabada en la pared carnosa: \"Cuatro son sus centros vitales: Pulmones, Estómago, Corazón y Cerebro. Destruye los cuatro y la fortaleza caerá.\"", 10, false}
    };
    rooms[17].doors = {
        {"Boca", "Regresa a la boca de la Bestia.", 16,
         "Usted trepa de regreso a la boca.", "", "", true, false, "", "", ""},
        {"Conducto a los pulmones", "Un pasaje cavernoso por el que soplan ráfagas huracanadas.", 18,
         "Protegido por el talismán de aire, usted resiste los vendavales y entra a los pulmones.",
         "Un vendaval infernal le arranca la respiración y lo arroja contra las rocas. ¡Necesita el talismán de aire!",
         "", true, false, "", "", "talisman de aire"},
        {"Conducto al estomago", "Un conducto descendente que gotea ácidos corrosivos.", 19,
         "Usted entra al estómago de la Bestia.",
         "Los jugos gástricos son demasiado voraces. ¡Necesita alimentar a la fiera con un pastel para pasar!",
         "", true, false, "", "", "pastel de cerezas"},
        {"Conducto al corazon", "Un túnel pulsante que late con un estruendo ensordecedor.", 20,
         "El calor abrasador del corazón intenta quemarle el alma, pero el corazón de unicornio lo protege.",
         "El calor y la presión son intolerables. ¡Necesita la protección mágica del corazón de unicornio!",
         "", true, false, "", "", "corazon de unicornio"}
    };

    // ==========================================
    // Room 18: Pulmones de la Bestia (Organ 1)
    // ==========================================
    rooms[18].id = 18;
    rooms[18].title = "Pulmones de la Bestia";
    rooms[18].description = "Sopla un aire tan fuerte que usted se ha tirado al suelo.";
    rooms[18].creatures = {
        {"Centro de los pulmones", "Una masa cavernosa que se infla y desinfla con furia.", "",
         "¡Un rugido de viento sacude todo a su alrededor!",
         "¡Usted ha destruido los pulmones! Solo con un látigo podrás destruir el estómago.",
         "espada", "¡Usted ha destruido los pulmones! Solo con un látigo podrás destruir el estómago.",
         false, false, true}
    };
    rooms[18].doors = {
        {"Conducto de regreso", "Regresa al interior de la Bestia.", 17,
         "Usted regresa al interior de la criatura.", "", "", true, false, "", "", ""}
    };

    // ==========================================
    // Room 19: Estómago de la Bestia (Organ 2)
    // ==========================================
    rooms[19].id = 19;
    rooms[19].title = "el Estómago de la Bestia";
    rooms[19].description = "Hay varios esqueletos humanos sumergidos en charcos de ácido burbujeante.";
    rooms[19].creatures = {
        {"Centro del estomago", "Un nodo de tejido muscular que secreta bilis y ácidos venenosos.", "",
         "Un siseo repugnante acompaña cada contracción de las paredes.",
         "¡Usted ha destruido el estómago! Solo con una daga podrás matar el corazón.",
         "latigo", "¡Usted ha destruido el estómago! Solo con una daga podrás matar el corazón.",
         false, false, true}
    };
    rooms[19].doors = {
        {"Conducto de regreso", "Regresa al interior de la Bestia.", 17,
         "Usted regresa al interior de la criatura.", "", "", true, false, "", "", ""}
    };

    // ==========================================
    // Room 20: Corazón de la Bestia (Organ 3)
    // ==========================================
    rooms[20].id = 20;
    rooms[20].title = "el Corazón de la Bestia";
    rooms[20].description = "Todo palpita rítmicamente. Usted siente cómo los latidos se adueñan del lugar, especialmente de su propio corazón.";
    rooms[20].creatures = {
        {"Centro del corazon", "Un inmenso órgano rojo oscuro bombeando ríos de sangre hirviente.", "",
         "El latido retumba en sus huesos con la fuerza de un terremoto.",
         "¡Usted ha destruido el corazón! Busca el cerebro de la bestia lejos de aquí. Solo el fuego puede destruirlo.",
         "daga", "¡Usted ha destruido el corazón! Busca el cerebro de la bestia lejos de aquí. Solo el fuego puede destruirlo.",
         false, false, true}
    };
    rooms[20].doors = {
        {"Conducto de regreso", "Regresa al interior de la Bestia.", 17,
         "Usted regresa al interior de la criatura.", "", "", true, false, "", "", ""}
    };

    // ==========================================
    // Room 21: Cerebro de la Bestia (Organ 4)
    // ==========================================
    rooms[21].id = 21;
    rooms[21].title = "el Cerebro de la Bestia";
    rooms[21].description = "Es como un tarjetero gigante. Cada idea está escrita en una tarjeta y, cuando es necesario, la tarjeta es sacada por una mano invisible y leída al resto de la Bestia.";
    rooms[21].creatures = {
        {"Centro del cerebro", "El núcleo pensante de la entidad, un laberinto fosforescente de sinapsis y tarjetas vivientes.", "",
         "Voces cósmicas susurran en miles de idiomas a la vez.",
         "¡¡¡EL CEREBRO DE LA BESTIA ARDE EN LLAMAS!!! Toda la fortaleza comienza a temblar en su agonía final.",
         "antorcha", "¡¡¡EL CEREBRO DE LA BESTIA ARDE EN LLAMAS!!! Toda la fortaleza comienza a temblar en su agonía final.",
         false, false, true}
    };
    rooms[21].doors = {
        {"Puerta dorada", "Regresa al Salón de los elegidos.", 29,
         "Usted sale hacia el Salón de los elegidos.", "", "", true, false, "", "", ""}
    };

    // ==========================================
    // Room 22: Almacenes de la Fortaleza
    // ==========================================
    rooms[22].id = 22;
    rooms[22].title = "los Almacenes de la Fortaleza";
    rooms[22].description = "Están llenos de carne humana. Usted aparta el cadáver de una mujer para poder observar bien el lugar.";
    rooms[22].items = {
        {"Hacha", "Un hacha de leñador pesada con filo de doble cara.", 10, true}
    };
    rooms[22].creatures = {
        {"Verdugo", "Un hombre corpulento cubierto con una capucha de cuero ensangrentada.", "piedra filosofal",
         "¡Vete si no quieres terminar colgado de un gancho!",
         "Cuidado con el túnel y la puerta de tela. Solo conducen a la muerte. Si buscas cruzar el páramo, la palabra mágica es 'Agua'.",
         "", "", false, false, false}
    };
    rooms[22].doors = {
        {"Puerta al jardin", "Regresa al jardín.", 12,
         "Usted sale al jardín.", "", "", true, false, "", "", ""}
    };

    // ==========================================
    // Room 23: Extenso páramo
    // ==========================================
    rooms[23].id = 23;
    rooms[23].title = "un extenso páramo";
    rooms[23].description = "Hay muy poca vegetación y el suelo es pantanoso. Usted nunca imaginó que el interior de la fortaleza fuera tan grande.";
    rooms[23].items = {};
    rooms[23].doors = {
        {"Puente de marmol", "Regresa hacia el puente de mármol.", 26,
         "Usted sube al puente de mármol.", "", "", true, false, "", "", ""},
        {"Puerta de agua", "Una barrera de vapor y lodo con una runa grabada.", 24,
         "Al pronunciar la palabra mágica, el vapor se disipa y aparece el paso al Salón de cristal.",
         "El fango hirviente le impide el paso. Necesita pronunciar la palabra mágica correcta.",
         "agua", false, false, "", "", ""}
    };

    // ==========================================
    // Room 24: Salón de cristal
    // ==========================================
    rooms[24].id = 24;
    rooms[24].title = "Salón de cristal";
    rooms[24].description = "Es como un caleidoscopio gigante. Cada varios segundos las paredes cambian de color y usted siente como si lo hubieran trasladado a otro lugar.";
    rooms[24].items = {
        {"Columna de cristal", "En el centro se alza una columna de cristal que resuena con una frecuencia divina. Solo la antorcha con el número divino (Antorcha 3) puede romperla.", 50, false}
    };
    rooms[24].doors = {
        {"Boca de la Bestia", "Un túnel que conduce directo a las fauces de la Bestia.", 16,
         "Usted entra a la boca de la Bestia.", "", "", true, false, "", "", ""},
        {"Puerta al paramo", "Conduce de regreso al páramo.", 23,
         "Usted regresa al páramo.", "", "", true, false, "", "", ""}
    };

    // ==========================================
    // Room 25: Celda pequeña (Death Trap)
    // ==========================================
    rooms[25].id = 25;
    rooms[25].title = "celda pequeña";
    rooms[25].description = "No hay forma alguna de salir. Las paredes son lisas como el hielo y no tienen juntas ni puertas.";
    rooms[25].items = {
        {"Inscripcion", "Grabada en la piedra: \"Aquí terminan las ambiciones de los insensatos.\"", 41, false}
    };
    rooms[25].doors = {}; // No exits! Trap room!

    // ==========================================
    // Room 26: Puente de mármol
    // ==========================================
    rooms[26].id = 26;
    rooms[26].title = "un puente de mármol";
    rooms[26].description = "Es muy largo y estrecho.";
    rooms[26].items = {
        {"Martillo", "Un martillo de herrero sólido.", 2, true}
    };
    rooms[26].doors = {
        {"Exterior", "Regresa al exterior de la fortaleza.", 0,
         "Usted regresa al exterior de la fortaleza.", "", "", true, false, "", "", ""},
        {"Paramo", "Conduce al extenso páramo.", 23,
         "Usted desciende al páramo.", "", "", true, false, "", "", ""},
        {"Antesala del laberinto", "Conduce a la antesala del Laberinto.", 27,
         "Usted avanza hacia la antesala del Laberinto.", "", "", true, false, "", "", ""}
    };

    // ==========================================
    // Room 27: Antesala del Laberinto
    // ==========================================
    rooms[27].id = 27;
    rooms[27].title = "la Antesala del Laberinto";
    rooms[27].description = "Es una habitación muy confortable, pero usted siente algo malvado flotando en el aire.";
    rooms[27].doors = {
        {"Puente", "Regresa al puente de mármol.", 26,
         "Usted regresa al puente.", "", "", true, false, "", "", ""},
        {"Cueva del Minotauro", "Una entrada sombría de la que emanan gruñidos animales.", 28,
         "Usted entra con sigilo a la cueva del Minotauro.", "", "", true, false, "", "", ""},
        {"Pasillo occidental", "Un pasillo estrecho del Laberinto.", 30,
         "Usted se interna en el Laberinto.", "", "", true, false, "", "", ""},
        {"Pasillo oriental", "Otro pasillo del Laberinto.", 31,
         "Usted avanza por los pasillos del Laberinto.", "", "", true, false, "", "", ""}
    };

    // ==========================================
    // Room 28: Cueva del Minotauro
    // ==========================================
    rooms[28].id = 28;
    rooms[28].title = "la cueva del Minotauro";
    rooms[28].description = "Hay siete antorchas numeradas del 1 al 7 clavadas en los muros de roca.";
    rooms[28].items = {
        {"Antorcha 1", "Arde con fuego blanco.", 2, true},
        {"Antorcha 2", "Arde con fuego azul.", 2, true},
        {"Antorcha 3", "La antorcha divina, arde con una llama dorada inextinguible.", 2, true},
        {"Antorcha 4", "Arde con fuego verde.", 2, true},
        {"Antorcha 5", "Arde con fuego púrpura.", 2, true},
        {"Antorcha 6", "Arde con fuego naranja.", 2, true},
        {"Antorcha 7", "Arde con fuego carmesí.", 2, true}
    };
    rooms[28].creatures = {
        {"Minotauro", "Un ser monstruoso con cuerpo de gigante y cabeza de toro embravecido.", "",
         "¡¡¡MUUUOOOAAARGHHH!!! ¡Carne fresca!",
         "Con su último aliento el monstruo brama: '¡La tercera antorcha es la divina... romperá el cristal del destino!'",
         "espada", "Con su último aliento el monstruo brama: '¡La tercera antorcha es la divina... romperá el cristal del destino!'",
         false, false, true}
    };
    rooms[28].doors = {
        {"Antesala", "Regresa a la antesala del Laberinto.", 27,
         "Usted regresa a la antesala.", "", "", true, false, "", "", ""}
    };

    // ==========================================
    // Room 29: Salón de los elegidos
    // ==========================================
    rooms[29].id = 29;
    rooms[29].title = "el Salón de los elegidos";
    rooms[29].description = "Usted se enorgullece: muy pocas personas han llegado hasta este salón. El cerebro de la Bestia está detrás de la puerta.";
    rooms[29].items = {};
    rooms[29].doors = {
        {"Puerta dorada", "Es de oro macizo. Tiene una inscripción que exige el mayor alfabeto que no contenga a la Bestia.", 21,
         "Usted ha entrado al Cerebro de la Bestia!",
         "La puerta dorada vibra y rechaza su respuesta.", "cdfghjklmnopqruvwxyz",
         false, true, "Invente un alfabeto (el mayor que pueda) con el que no pueda crearse a la Bestia.", "cdfghjklmnopqruvwxyz", ""},
        {"Pasillo del laberinto", "Conduce de regreso al laberinto.", 31,
         "Usted regresa al laberinto.", "", "", true, false, "", "", ""}
    };

    // ==========================================
    // Room 30: Pasillo del Laberinto
    // ==========================================
    rooms[30].id = 30;
    rooms[30].title = "un pasillo del Laberinto";
    rooms[30].description = "El techo está tan pegado al suelo que usted tiene que andar agachado. Hay tres puertas simétricas.";
    rooms[30].doors = {
        {"Puerta central", "Conduce a la antesala del Laberinto.", 27,
         "Usted regresa a la antesala.", "", "", true, false, "", "", ""},
        {"Puerta izquierda", "Conduce a otro tramo del laberinto.", 31,
         "Usted avanza por el laberinto.", "", "", true, false, "", "", ""},
        {"Puerta derecha", "Una puerta de tela sospechosa.", 25,
         "Usted cae irremediablemente en una celda sin salida.", "", "", true, false, "", "", ""}
    };

    // ==========================================
    // Room 31: Pasillo del Laberinto
    // ==========================================
    rooms[31].id = 31;
    rooms[31].title = "un pasillo del Laberinto";
    rooms[31].description = "Hay una puerta que le conducirá a la antesala del Laberinto.";
    rooms[31].doors = {
        {"Puerta a la antesala", "Regresa a la antesala.", 27,
         "Usted regresa a la antesala.", "", "", true, false, "", "", ""},
        {"Puerta al salon de los elegidos", "Una puerta imponente custodiada por runas.", 29,
         "Usted cruza el umbral hacia el Salón de los elegidos.", "", "", true, false, "", "", ""},
        {"Pasillo", "Comunica con el otro pasillo del laberinto.", 30,
         "Usted avanza por el pasillo.", "", "", true, false, "", "", ""}
    };

    return rooms;
}

} // namespace Fortaleza
