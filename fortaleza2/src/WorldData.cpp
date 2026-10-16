#include "WorldData.h"

namespace Fortaleza2 {

std::string WorldData::getIntroTitle() {
    return "============================================================\n"
           "               L A   F O R T A L E Z A   I I                \n"
           "               La Venganza de la Bestia (1991)              \n"
           "                    (c) Merchise Software                   \n"
           "============================================================\n";
}

std::string WorldData::getKafkaQuote() {
    return "\"En la lucha entre tú y el mundo, ve de parte del mundo.\"\n"
           "                                         -- Franz Kafka\n";
}

std::string WorldData::getCredits() {
    return "LA FORTALEZA II: La Venganza de la Bestia\n"
           "Diseño original, programación y textos: Miguel Enrique Cepero (1991)\n"
           "Merchise Software - Cuba\n"
           "Editor de comandos por: Jorge Romero (vac-ace)\n"
           "Reconstrucción y modernización en C++17 (2026)\n";
}

std::vector<std::string> WorldData::getManualPages() {
    return {
        "GRAN METODO INFALIBLE PARA RESOLVER FORTALEZAS (Parte 1)\n\n"
        "Regla 1: Tenga siempre lápiz y papel a mano.\n"
        "Regla 2: Asegúrese de que el lápiz tenga punta en todo momento.\n"
        "Regla 3: Vaya llevando un diagrama donde represente los distintos lugares\n"
        "         que visite y las relaciones entre ellos (puertas, etc).\n"
        "Regla 4: Trate de observar todas las cosas: cosas inanimadas, vivas y puertas.\n",
        "GRAN METODO INFALIBLE PARA RESOLVER FORTALEZAS (Parte 2)\n\n"
        "Regla 5: Clasificación de elementos:\n"
        "         (1) Cosas inanimadas: Se pueden coger si no pesan demasiado.\n"
        "         (2) Cosas que esconden otras cosas: Se deben romper con un objeto específico.\n"
        "         (3) Criaturas vivas: Amigos (interrogar, dar objeto, volver a interrogar)\n"
        "             y Enemigos (matar con el arma adecuada; confiesan al morir).\n"
        "         (4) Uniones: Puertas, puentes, caminos y pasadizos.\n",
        "GRAN METODO INFALIBLE PARA RESOLVER FORTALEZAS (Parte 3)\n\n"
        "Regla 6: Puertas abiertas y cerradas. Use 'abrir' con clave, palabra mágica o acertijo.\n"
        "Regla 7: Ciertas uniones exigen llevar un objeto protector para no morir.\n"
        "         ¡Otras uniones prohíben llevar ciertos objetos!\n"
        "Regla 8: Acumule pertenencias en lugares céntricos para no viajar de más.\n",
        "VOCABULARIO Y COMANDOS:\n\n"
        "■ Moverse: IR, ATRAVESAR, CRUZAR [unión]\n"
        "■ Observar: MIRAR, VER, OBSERVAR, LEER [objeto/lugar]\n"
        "■ Manipular: COGER, TOMAR, SOLTAR, DEJAR [objeto]\n"
        "■ Destruir: ROMPER, FORZAR, DESTROZAR [objeto] CON [herramienta]\n"
        "■ Combatir: MATAR, ASESINAR [enemigo] CON [arma]\n"
        "■ Conversar: INTERROGAR, PREGUNTAR [personaje]\n"
        "■ Regalar: DAR, REGALAR [objeto] A [personaje]\n"
        "■ Abrir: ABRIR [puerta] DICIENDO/RESPONDIENDO/CON [clave]\n"
        "■ Medir: PESAR [objeto] (requiere balanza), PORCIENTO (progreso)\n"
        "■ Utilidades: INVENTARIO, SALVAR, EJECUTAR, AYUDA, TERMINAR\n"
    };
}

std::vector<Room> WorldData::createWorld() {
    std::vector<Room> rooms(55);

    // Room 0: una habitación para huéspedes
    rooms[0].id = 0;
    rooms[0].title = "una habitación para huéspedes";
    rooms[0].description = "Está tan oscura que usted cree que las paredes y el techo se han avalanzado sobre su cuerpo. En la pared que tiene delante se distingue un plateado hilo de luz. Es el filo de una puerta.";
    rooms[0].doors = {
        {"Puerta", "En realidad, lo que usted puede distinguir es el delicado filón de luz que deja escapar la unión de la puerta y el marco.", 1, "Usted cierra los ojos, cegado por la luz.", "", "", true, false, "", "", ""},
    };

    // Room 1: el pasillo
    rooms[1].id = 1;
    rooms[1].title = "el pasillo";
    rooms[1].description = "Hay seis puertas distribuidas simétricamente. Las paredes son de mármol blanco, pero usted tiene la certeza de que hay algo terrible encerrado detrás de toda esa pulcritud.";
    rooms[1].creatures = {
        {"Grifo", "Usted no logra distinguir si es un león o un águila. Parece dormido.", "", "", "", "Daga", "El grifo se contorsiona tratando de arrancarse la daga y grita: \"¡Aura!\".", false, false, true},
    };
    rooms[1].doors = {
        {"Puerta", "Es de madera trabajada, una verdadera obra de arte.", 0, "Usted entra a la oscuridad nuevamente.", "", "", true, false, "", "", ""},
        {"Puerta de espinos", "Está erizada de espinas. Usted tiene miedo hasta de acercarse.", 5, "Usted entra lentamente, tratando de no rozar la puerta.", "", "", true, false, "", "", ""},
        {"Puerta de metal", "Es de acero bruñido. Tiene encima un cartel que dice \"Cocina. Cúbrase la nariz.\"", 6, "Al pasar siente un olor muy fuerte, que lo envuelve y lo asfixia. Usted sobrevive gracias al pañuelo que lleva consigo.", "", "", true, false, "", "", "Pañuelo"},
        {"Puerta Negra", "Usted ve unas delgadas cortinas de humo saliendo por debajo de la puerta.", 2, "Usted tose fuertemente, ha entrado al Salón de Fumar.", "", "", true, false, "", "", ""},
        {"Puerta Azul", "Es más pequeña que las puertas restantes.", 3, "Usted entra a la alcoba de la hija del Hechicero.", "", "", false, true, "¿Cuál es el nombre de la hija del Hechicero?", "Aura", ""},
        {"Puerta de oro", "Usted nunca había visto tanto oro fundido en una misma pieza.", 7, "El resplandor del oro lo ciega por un momento. Usted ha salido a las terrazas.", "", "", true, false, "", "", ""},
    };

    // Room 2: el Salón de Fumar
    rooms[2].id = 2;
    rooms[2].title = "el Salón de Fumar";
    rooms[2].description = "Hay sesenta y seis sillas en el salón. Al lado de cada silla crece un tentáculo rosado con un pitillo en el extremo. Los pitillos humean.";
    rooms[2].items = {
        {"Balanza", "La balanza tiene el plato en forma de mano. La aguja es muy delgada, hecha con varios bigotes de gato trenzados. ", 1, true},
        {"Inscripción", "La inscripción dice:\nLa muerte es un acto de la vida. Yo, la Bestia, he de morir como he vivido. Esta es mi venganza, y tú mismo serás el instrumento que la lleve a cabo. La naturaleza humana es el arma más poderosa que puede utilizarse contra el hombre.", 1, true},
    };
    rooms[2].doors = {
        {"Puerta Negra", "La puerta por este lado está muy manchada por el humo.", 1, "Usted sale del Salón de Fumar. A fin puede respirar normalmente.", "", "", true, false, "", "", ""},
    };

    // Room 3: el cuarto de la hija del Hechicero
    rooms[3].id = 3;
    rooms[3].title = "el cuarto de la hija del Hechicero";
    rooms[3].description = "Se pregunta cómo luciría la hija de un hechicero. En las paredes hay cientos de retratos, todos de muchachas diferentes. ¿Cuál será la real?... ¿O todas son una misma?";
    rooms[3].items = {
        {"Pañuelo", "Tiene bordadas una A y una S.", 1, true},
        {"Carta", "La carta dice:\n\"¡Dios te salve, mi única esperanza! \nMi padre me ha encerrado en la Torre de Cristal, que está más allá del segundo río. El sabe que solo yo podría mostrarte el camino de salida. Búscame.\"", 1, true},
    };
    rooms[3].doors = {
        {"Puerta Azul", "Conduce al pasillo.", 1, "Usted sale al pasillo.", "", "", true, false, "", "", ""},
        {"Agujero", "Parece una guarida de ratones.", 4, "Usted se agacha y (con grandes dolores en todos los huesos) atraviesa el agujero.", "", "", true, false, "", "", ""},
    };

    // Room 4: la casa de muñecas
    rooms[4].id = 4;
    rooms[4].title = "la casa de muñecas";
    rooms[4].description = "Es tan pequeña como cualquier casa de muñecas. Usted no comprende cómo pudo entrar. Hay un baúl en el fondo.";
    rooms[4].doors = {
        {"Agujero", "Es la salida de la casa de muñecas.", 3, "Usted regresa a la alcoba.", "", "", true, false, "", "", ""},
        {"Ventana", "Es de un cristal muy grueso. Usted trata de ver al otro lado, pero la ventana es tan opaca que solo puede divisar algunas sombras moviéndose.", 12, "Pasadizo", "", "Corta-cristales", false, false, "", "", ""},
        {"Puerta del baúl", "Parece muy antigua. Usted está seguro de que ahí hay \"gato encerrado\".", 9, "¡Usted ha caído dentro del baúl!", "MIAU", "", false, false, "", "", ""},
    };

    // Room 5: el cuarto del Leñador
    rooms[5].id = 5;
    rooms[5].title = "el cuarto del Leñador";
    rooms[5].description = "Las paredes, el suelo y el techo están hechos de madera. Usted camina con cuidado: hay espinas por todas partes.";
    rooms[5].items = {
        {"Daga", "La empuñadura tiene forma de dragón.", 1, true},
        {"Botella de vino", "Parece una botella de agua sucia.", 1, true},
        {"Hacha", "Está muy mohosa.", 1, true},
    };
    rooms[5].doors = {
        {"Puerta de espinos", "Al igual que del otro lado, está erizada de espinas.", 1, "Usted sale lentamente, tratando de no rozar la puerta.", "", "", true, false, "", "", ""},
    };

    // Room 6: la Cocina
    rooms[6].id = 6;
    rooms[6].title = "la Cocina";
    rooms[6].description = "En realidad, se parece mucho más a un matadero. El olor a sangre coagulada y carroña no le permite apartar el pañuelo de la nariz. Hay unas marcas de sangre en la pared que le llaman mucho la atención: fueron hechas por una mano de siete dedos.";
    rooms[6].items = {
        {"Receta", "Es una receta de cocina. Dice:\n  5 Ojos de rana\n  1 Mano de gigante\n  2 Cucharadas de puré de lombrices\n  1 Hígado de muchacha virgen\n  9 Libras de azúcar\n  1 Tanque de agua del pantano verde\nUsted recuerda haber probado esto en alguna parte.", 1, true},
        {"Muslo de carnero", "Más bien parece el muslo de una persona.", 1, true},
        {"Pescado", "¿Qué tiempo llevará en este lugar?", 1, true},
    };
    rooms[6].doors = {
        {"Puerta de metal", "Conduce al pasillo.", 1, "Al salir puede apartar el pañuelo de la nariz.", "", "", true, false, "", "", "Pañuelo"},
    };

    // Room 7: las Terrazas
    rooms[7].id = 7;
    rooms[7].title = "las Terrazas";
    rooms[7].description = "No puede reprimir su asombro: las terrazas están invertidas. Usted se siente muy natural parado cabeza abajo. Se escucha el correr de un río.";
    rooms[7].items = {
        {"Reloj de arena", "Usted escucha un callado tic-tac.", 1, true},
        {"Silla", "Es una silla para tomar el sol. Usted tiene la certeza de que había alguien sentado en ella cuando entró a las terrazas.", 1, true},
    };
    rooms[7].doors = {
        {"Puerta de oro", "Usted nunca había visto tanto oro fundido en una misma pieza.", 1, "Usted regresa al pasillo. El resplandor del oro lo ciega por un momento.", "", "", true, false, "", "", ""},
        {"Escalera de caracol", "Parece la bajada a un oído gigante.", 10, "El viento helado que viene del fondo de la escalera lo envuelve en continuos temblores.", "", "", true, false, "", "", ""},
    };

    // Room 8: el calabozo del Monstruo
    rooms[8].id = 8;
    rooms[8].title = "el calabozo del Monstruo";
    rooms[8].description = "Las paredes son de barro. Hay cientos de cadenas embotadas en el techo, moviéndose constantemente, como si las arrastrara un viento de acero.";
    rooms[8].items = {
        {"Inscripción", "La inscripción dice:\n\"No alimente al monstruo.\"", 1, true},
    };
    rooms[8].creatures = {
        {"Monstruo", "El Monstruo está encadenado a la pared. Usted aparta la vista rápidamente. Nunca había visto tanta fealdad concentrada en una criatura.", "Muslo de carnero", "¡Grrrr! ¡Hambre!", "¡Tú cuidarte de Hechicero! ¡Hechicero ser malo! ¡Malo! ¡Muy malo!\nHechicero puso yo feo. A tú no poner feo... ¡A tú arrancal tripa, sacal ojo, rompel hueso y echal dragrón hambroso!\nYo consejo tú: Busca espada Marmidosa... ¡y pincha todo!", "", "", false, false, false},
    };
    rooms[8].doors = {
        {"Escalera de caracol", "Conduce a las terrazas", 7, "Su condicionamiento euclidiano le impide comprender cómo es posible que una misma escalera sea origen y destino de tres lugares distintos a la vez.\nUsted ha subido a las terrazas.", "", "", true, false, "", "", ""},
    };

    // Room 9: el interior del baúl
    rooms[9].id = 9;
    rooms[9].title = "el interior del baúl";
    rooms[9].description = "Ahora sí está confundido. El baúl es inmensamente mayor que la casa de muñecas, a pesar de que está dentro de ella. Luce como una habitación cualquiera.";
    rooms[9].items = {
        {"Inscripción", "La inscripción dice:\n\"No todos los dragones merecen la muerte.\"", 1, true},
        {"Piedra verde", "Es increíblemente sólida.", 1, true},
    };
    rooms[9].creatures = {
        {"Gato", "Está concentrado en sacarle las últimas partículas de carne a una cabeza de pescado.", "Pescado", "¡No molestes!", "La piedra verde te servirá para romper la segunda muralla.", "", "", false, false, false},
    };
    rooms[9].doors = {
        {"Puerta del baúl", "Está en el techo.", 4, "Usted sale del baúl y vuelve a sentir la estrechez de la casa de muñecas.", "", "", true, false, "", "", ""},
    };

    // Room 10: una orilla del Río Negro
    rooms[10].id = 10;
    rooms[10].title = "una orilla del Río Negro";
    rooms[10].description = "Las aguas del Río Negro hacen honor a su nombre. Más que aguas parecen una mezcla de muerte y olvido. ";
    rooms[10].items = {
        {"Bote", "Es el célebre bote de Caronte.", 1, true},
    };
    rooms[10].creatures = {
        {"Caronte", "Una capucha negra esconde su rostro. Por una de las mangas de su vestimenta asoma una mano descarnada casi hasta el hueso. Usted se alegra de no poder ver su cara.", "Reloj de arena", "Tráeme el reloj de arena, pero víralo antes de entregármelo. ", "Dentro del blanco está la llave de la muralla.", "", "", false, false, false},
    };
    rooms[10].doors = {
        {"Escalera de caracol", "Contrariamente a lo que usted espera, la escalera en este lugar asciende hasta el calabozo del Monstruo.", 8, "Usted sube durante unos minutos y llega al calabozo del Monstruo.", "", "", true, false, "", "", ""},
        {"Río Negro", "Es el Estigia.", 11, "Usted se sumerge en las oscuras aguas del Estigia (tiene miedo de montar el bote de Caronte). Pocos mortales se han atrevido a tanto. Al poco rato está del otro lado.", "", "", true, false, "", "", ""},
    };

    // Room 11: una orillas del Río Negro
    rooms[11].id = 11;
    rooms[11].title = "una orillas del Río Negro";
    rooms[11].description = "La espesa niebla casi no deja ver las terrazas al otro lado.";
    rooms[11].doors = {
        {"Río Negro", "Es el Estigia.", 10, "Usted regresa nadando a la otra orilla.", "", "", true, false, "", "", ""},
        {"Arbol de marfil", "Es infinitamente blanco.", 11, "Maza", "", "Hacha", false, false, "", "", ""},
        {"Muralla", "Al lado de esta, la Gran Muralla China es el juego de un niño en la arena.", 12, "Avenida de hierro", "", "Maza", false, false, "", "", ""},
    };

    // Room 12: los Jardines del Hechicero
    rooms[12].id = 12;
    rooms[12].title = "los Jardines del Hechicero";
    rooms[12].description = "Son tan extensos que usted no puede ver dónde terminan. Todos los árboles tienen el mismo tamaño y la misma forma. El jardín parece un gran juego de espejos.";
    rooms[12].items = {
        {"Piedra", "Es una piedra común. Usted se pregunta qué hace en la Fortaleza, donde todo es tan exótico.", 1, true},
    };
    rooms[12].creatures = {
        {"Jardinero", "Es un anciano pequeño y encorvado.", "Hacha", "El jardinero no le presta atención. Está muy ocupado cortando un abeto con una navaja.", "En tu camino encontrarás varios anillos. Debes guardar el que tú consideres más apropiado, el que se ajuste más a tu espíritu y a tu empresa. Los otros anillos solo te traerán peligros y muerte. Elige bien.", "", "", false, false, false},
    };
    rooms[12].doors = {
        {"Avenida de hierro", "Toda la avenida está rodeada de árboles de metal. Usted se cubre los oídos tratando de escapar de los chirridos provocados por el viento en las hojas.", 11, "Usted camina durante varios minutos hasta regresar al río.", "", "", true, false, "", "", ""},
        {"Puerta de madera", "Es una puerta bastante vulgar. Conduce al comedor.", 13, "Usted entra al comedor.", "", "", true, false, "", "", ""},
        {"Puerta amarilla", "Conduce al cuarto del tesoro.", 16, "Usted entra al cuarto del tesoro. Los resplandores de las piedras preciosas lo ciegan por unos instantes.", "Omicuos Ihanti", "", false, false, "", "", ""},
        {"Puerta de tela", "La tela de la puerta es tan dura como cualquier acero.", 14, "Usted entra a las habitaciones del sastre.", "", "", true, false, "", "", ""},
        {"Puerta verde", "Conduce a las habitaciones del jardinero.", 15, "Usted entra a las habitaciones del jardinero.", "", "", true, false, "", "", ""},
        {"Puerta roja", "Conduce al salón de las velas. La puerta está caliente.", 17, "Usted entra al salón de las velas.", "", "", true, false, "", "", ""},
    };

    // Room 13: el Comedor
    rooms[13].id = 13;
    rooms[13].title = "el Comedor";
    rooms[13].description = "La mesa es tan alta que usted no puede ver lo que hay servido. Alguien se lamenta allá arriba.";
    rooms[13].doors = {
        {"Puerta de Madera", "Usted distingue algunas manchas de salsa en la puerta. Parece los comensales acostumbran a lanzarse la comida.", 12, "Usted sale del comedor.", "", "", true, false, "", "", ""},
        {"Túnel", "Usted se pregunta qué hace un túnel en un comedor. ¡No intente cruzar desprotegido!", 48, "Casi a mitad de camino usted es atacado por una bandada de murciélagos gigantes. Gracias al arco, usted logra ahuyentarlos.", "\u0000\u0000\u0000", "", true, false, "", "", "Arco"},
        {"Huevo", "Por el tamaño debe ser el huevo de un dinosaurio. Y de uno grande.", 13, "Dinosaurio", "", "Piedra", false, false, "", "", ""},
    };

    // Room 14: la Sastrería
    rooms[14].id = 14;
    rooms[14].title = "la Sastrería";
    rooms[14].description = "Parece la casa de una araña gigantesca. Hay hilos por todas partes.";
    rooms[14].items = {
        {"Muñeco diabólico", "Es un artefacto de brujería. Representa a un hombre joven y tiene un alfiler clavado en una pierna.", 1, true},
        {"Aguja", "Es una aguja de plata, tan larga que usted se pregunta cómo el sastre puede coser con ella.", 1, true},
    };
    rooms[14].doors = {
        {"Puerta de Tela", "La tela de la puerta es tan dura como cualquier acero.", 12, "Usted regresa al jardín.", "", "", true, false, "", "", ""},
    };

    // Room 15: el cuarto del jardinero
    rooms[15].id = 15;
    rooms[15].title = "el cuarto del jardinero";
    rooms[15].description = "Es una habitación muy modesta. A usted le sorprende que los instrumentos no sean de jardinería, sino de fabricar espejos.";
    rooms[15].items = {
        {"Corta-cristales", "Tiene un diamante en la punta.", 1, true},
        {"Sombrero", "Es muy grande. Al jardinero no debe servirle.", 1, true},
    };
    rooms[15].doors = {
        {"Puerta verde", "Conduce al jardín.", 12, "Usted sale de las habitaciones del jardinero.", "", "", true, false, "", "", ""},
    };

    // Room 16: la habitación de los tesoros
    rooms[16].id = 16;
    rooms[16].title = "la habitación de los tesoros";
    rooms[16].description = "Nunca había visto tanta riqueza. Las paredes están forradas de láminas de platino y hasta el fuego de las antorchas es de oro. Usted no comprende de dónde viene la luz.";
    rooms[16].items = {
        {"Rosa diamante", "Es increíblemete hermosa.", 1, true},
        {"Anillo de oro", "El anillo es sencillo. Solo un aro, sin ningún tipo de adorno.", 1, true},
        {"Arpa", "Es un arpa de diciocho cuerdas.", 1, true},
        {"Bolsa", "Está llena de oro.", 1, true},
    };
    rooms[16].doors = {
        {"Puerta amarilla", "Conduce al jardín.", 12, "Usted regresa a los jardines.", "", "", true, false, "", "", ""},
    };

    // Room 17: el salón de las velas
    rooms[17].id = 17;
    rooms[17].title = "el salón de las velas";
    rooms[17].description = "Deben ser varios kilómetros sembrados de velas. En el centro hay un círculo vacío.";
    rooms[17].creatures = {
        {"Dragon", "A usted se le erizan los pelos de la nuca de tan solo mirarlo. Es una criatura extremadamente hermosa y terrible a la vez.", "Daga", "No desea hablar con usted.", "Las palabras mágicas para entrar en el cuarto del tesoro son: \"Omicuos Ihanti\".", "", "", false, false, false},
    };
    rooms[17].doors = {
        {"Puerta roja", "Conduce a los jardines.", 12, "Usted regresa a los jardines.", "", "", true, false, "", "", ""},
        {"Puerta blanca", "Conduce al cuarto de juguetes.", 19, "Usted entra al cuarto de juguetes.", "", "", true, false, "", "", ""},
        {"Escalera", "Baja hasta el cuarto del Inmortal.", 18, "Usted desciende las escaleras y entra al cuarto del Inmortal.", "", "", true, false, "", "", ""},
    };

    // Room 18: el cuarto del Inmortal
    rooms[18].id = 18;
    rooms[18].title = "el cuarto del Inmortal";
    rooms[18].description = "Esta habitación luce más vieja que el resto de la Fortaleza. Hay muchas cosas colgadas de la pared: retratos, cartas, reconocimientos, estandartes y muchas telas de arañas.";
    rooms[18].items = {
        {"Inscripción", "¿Quién quiere vivir para siempre?", 1, true},
    };
    rooms[18].creatures = {
        {"Inmortal", "No parece tener ninguna edad en específico. Hay mucho cansancio en la expresión de su rostro.", "", "", "", "Arco", "El Inmortal lo mira agradecido y le dice antes de morir:\n\"No confundas la tercera muralla con la tercera barrera que tienes que romper. La tercera barrera está en tí mismo.\"", false, false, true},
    };
    rooms[18].doors = {
        {"Escalera", "Lleva hasta el salón de las velas.", 17, "Usted sube lentamente hasta ver el resplandor de las velas otra vez.", "", "", true, false, "", "", ""},
    };

    // Room 19: el cuarto de juguetes
    rooms[19].id = 19;
    rooms[19].title = "el cuarto de juguetes";
    rooms[19].description = "Hay miles de juguetes regados por todas partes. Usted siente deseos de volver a ser un niño.";
    rooms[19].items = {
        {"Saltador", "Es un tronco de abeto con un resorte en el extremo inferior.", 1, true},
        {"Sonajero", "Es un jugete para recién nacidos.", 1, true},
        {"Talismán de Nieve", "Hay una pequeña tormenta de nieve encerrada en el cristal", 1, true},
    };
    rooms[19].doors = {
        {"Puerta blanca", "Conduce al salón de las velas.", 17, "Usted sale del cuarto de juguetes.", "", "", true, false, "", "", ""},
        {"Puerta de piedra", "Es muy antigua. Probablemente sea más vieja que el propio cuarto de juguetes. ", 20, "Usted sale del cuarto de juguetes y entra a las ruinas.", "", "", true, false, "", "", ""},
    };

    // Room 20: las Ruinas
    rooms[20].id = 20;
    rooms[20].title = "las Ruinas";
    rooms[20].description = "Este lugar debe haber sido abandonado hace siglos. Usted trata de imaginar cómo eran las construcciones originalmente, pero no lo consigue. Al sur se extiende un desierto y al oeste se encuentra la casa del Ogro.";
    rooms[20].doors = {
        {"Puerta de piedra", "Está muy a tono con el lugar. Las ruinas están más cerca de ser el juego del viento en las piedras que cualquier otra cosa. ", 19, "Usted sale de las ruinas y regresa al cuarto de juguetes.", "", "", true, false, "", "", ""},
        {"Puerta de hierro", "Es la entrada a la casa del Ogro.", 21, "Usted entra a la casa del Ogro.", "", "", true, false, "", "", ""},
        {"Escalera", "Desde el final asciende un aire frío y húmedo.", 26, "Los peldaños están llenos de musgo. Usted desciende cuidadosamente hasta llegar a los subterráneos.", "", "", true, false, "", "", ""},
        {"Desierto", "Promete ser largo y abrasador.", 33, "Usted camina duarante muchos días. El sol y el roce de la arena llagan todo su cuerpo. Por las noches, el viento helado del desierto no lo deja dormir. La sed invade su cuerpo y su mente.\nY cuando cree que nunca llegará descubre que está en un Oasis.", "", "", true, false, "", "", ""},
    };

    // Room 21: el Salón de Recepciones
    rooms[21].id = 21;
    rooms[21].title = "el Salón de Recepciones";
    rooms[21].description = "Todo está muy sucio y descuidado. Un fuerte olor a carroña le hace perder el equilibrio por momentos. Seguramente el Ogro usa este lugar para recibir a sus enemigos.";
    rooms[21].items = {
        {"Anillo de bronce", "Es más pesado que los demás anillos.", 1, true},
    };
    rooms[21].doors = {
        {"Puerta de hierro", "Usted no comprende cómo puede estar tan sucia. Conduce a las ruinas.", 20, "Usted regresa a las ruinas.", "", "", true, false, "", "", ""},
        {"Puerta gris", "Conduce al patio.", 23, "Usted sale al patio.", "", "", true, false, "", "", ""},
    };

    // Room 22: el cuarto de un pintor
    rooms[22].id = 22;
    rooms[22].title = "el cuarto de un pintor";
    rooms[22].description = "Hay muchos cuadros en las paredes, pero ninguno está terminado.";
    rooms[22].items = {
        {"Lienzo", "Es un cuadro muy extraño. Tiene dibujadas tres líneas que se cortan entre sí en puntos distintos.", 1, true},
        {"Grabado", "En el grabado aparece usted cruzando un puente con el propio grabado en la mano. Una estructura en abismo interesante.", 1, true},
    };
    rooms[22].doors = {
        {"Puerta azul", "Conduce al patio.", 23, "Usted sale al patio.", "", "", true, false, "", "", ""},
    };

    // Room 23: el Patio Interior
    rooms[23].id = 23;
    rooms[23].title = "el Patio Interior";
    rooms[23].description = "Por el patio están diseminados varios árboles gigantescos, todos sin hojas. Parece como si el invierno reinase siempre en este lugar.";
    rooms[23].doors = {
        {"Puerta gris", "Conduce al Salón de Recepciones.", 21, "Usted sale al Salón de Recepciones.", "", "", true, false, "", "", ""},
        {"Puerta azul", "Conduce al cuarto del pintor.", 22, "Usted entra al cuarto del pintor. El olor del óleo golpea sus narices.", "", "", true, false, "", "", ""},
        {"Puerta verde", "Conduce al cuarto del juglar.", 24, "Usted entra al cuarto del juglar.", "", "", true, false, "", "", ""},
        {"Puerta negra", "Conduce a la alcoba del Ogro.", 25, "Usted entra la alcoba del Ogro.", "", "", true, false, "", "", ""},
    };

    // Room 24: las habitaciones del Juglar
    rooms[24].id = 24;
    rooms[24].title = "las habitaciones del Juglar";
    rooms[24].description = "El ambiente de la habitación le induce a creer que el juglar no era exactamente lo que se llama una persona alegre.";
    rooms[24].items = {
        {"Cuerda", "Esta cuerda era usada por el juglar en los actos de equilibrismo. Tiene un gancho atado en uno de sus extremos.", 1, true},
    };
    rooms[24].creatures = {
        {"Juglar", "Usted lo observa detenidamente. Su cara es tan larga y tan triste que se asemeja a la de un caballo.", "Arpa", "¡Qué aburrimiento!", "Lleva algo de la fragua de Vulcano al bajar a las Catacumbas.", "", "", false, false, false},
    };
    rooms[24].doors = {
        {"Puerta verde", "Conduce al patio.", 23, "Usted sale al patio.", "", "", true, false, "", "", ""},
        {"Escalera", "Conduce a las Catacumbas.", 27, "Casi al llegar al final, los peldaños se abrieron dejando abierto un precipicio lleno de lava. Por suerte, el escudo de Aquiles quedó trabado en un saliente y usted pudo regresar a la superficie.", "\u0000\u0000\u0000", "", true, false, "", "", "Escudo de Aquiles"},
    };

    // Room 25: la alcoba del Ogro
    rooms[25].id = 25;
    rooms[25].title = "la alcoba del Ogro";
    rooms[25].description = "El aire se ha hecho casi irrespirable. Ahora usted comprende de dónde venía el mal olor reinante en el Salón de Recepciones. Nunca antes había estado en un lugar tan repulsivo.";
    rooms[25].items = {
        {"Inscripción", "¡BUUUU!", 1, true},
    };
    rooms[25].creatures = {
        {"Ogro", "Es una repugnante mezcla de hombre, cerdo y buitre. Parece dormido.", "", "", "", "Cubo de agua", "El Ogro despierta sobresaltado. El agua lo quema como si fuese ácido. Antes de volverse un charco de pasta pestilente le grita, víctima de un rencor casi infantil:\n\"¡No saldrás del lago con Marmidosa tan fácilmente!\"\nEl cubo de agua vuelve a llenarse.", false, false, true},
    };
    rooms[25].doors = {
        {"Puerta negra", "Conduce al patio.", 23, "Usted sale al patio.", "", "", true, false, "", "", ""},
    };

    // Room 26: los Subterráneos
    rooms[26].id = 26;
    rooms[26].title = "los Subterráneos";
    rooms[26].description = "Deben ser contemporáneos de las Ruinas. Usted siente como la humedad lo invade y le perfora los huesos.";
    rooms[26].items = {
        {"Antorcha", "Es muy brillante y despide mucho calor.", 1, true},
    };
    rooms[26].doors = {
        {"Escalera", "Asciende hasta las ruinas.", 20, "Los peldaños están llenos de musgo. Usted asciende cuidadosamente hasta regresar a las ruinas.", "", "", true, false, "", "", ""},
        {"Túnel", "Conduce a las catacumbas. Usted huele alguna trampa.", 27, "Al dar el tercer paso, usted activó un mecanismo que lanzó un dardo envenenado hacia su pecho. Usted sobrevive gracias al escudo de Aquiles.", "\u0000\u0000\u0000", "", true, false, "", "", "Escudo de Aquiles"},
    };

    // Room 27: las Catacumbas
    rooms[27].id = 27;
    rooms[27].title = "las Catacumbas";
    rooms[27].description = "Nunca antes había visto tantos esqueletos juntos. Más que enterrados en ese lugar, parecían haber muerto ahí. En el fondo usted divisa un hueco sin cadáver con una inscripción. La inscripción dice: \"Este es para tí\".";
    rooms[27].items = {
        {"Esqueleto de Murciélago", "Usted se alegra de que sea solo el esqueleto. Mide tres metros de ala a ala.", 1, true},
    };
    rooms[27].doors = {
        {"Túnel", "Conduce a los subterráneos. Usted recuerda que debe llevar el Escudo de Aquiles.", 26, "Al dar el tercer paso, usted activó un mecanismo que lanzó un dardo envenenado hacia su pecho. Usted sobrevive gracias al escudo de Aquiles.", "\u0000\u0000\u0000", "", true, false, "", "", "Escudo de Aquiles"},
        {"Escalera", "Conduce a una de las habitaciones de la casa del Ogro.", 24, "Casi al llegar al final, los peldaños se abrieron dejando abierto un precipicio lleno de lava. Por suerte, el escudo de Aquiles quedó trabado en un saliente y usted pudo regresar a la superficie.", "\u0000\u0000\u0000", "", true, false, "", "", "Escudo de Aquiles"},
        {"Pasadizo", "Parece más seguro que la escalera y el túnel.", 28, "Usted cruza esperando algo terrible, pero no sucede nada.", "", "", true, false, "", "", ""},
    };

    // Room 28: el punto donde comienzan unas enormes cataratas
    rooms[28].id = 28;
    rooms[28].title = "el punto donde comienzan unas enormes cataratas";
    rooms[28].description = "Un repentino acceso de vértigo hace que sus rodillas se doblen. A menos de un pie de donde usted se encuentra el agua se precipita hacia el abismo.";
    rooms[28].items = {
        {"Anillo de plata", "Es muy brillante.", 1, true},
    };
    rooms[28].doors = {
        {"Pasadizo", "Conduce a las Catacumbas.", 27, "Usted regresa a las Catacumbas sin mayores contratiempos.", "", "", true, false, "", "", ""},
        {"Catarata", "Usted siente mareos de tan solo pensar en ella.", 30, "Usted hace un acopio de valor, cierra los ojos y se lanza al abismo. Al cabo de varias horas, usted cae en un profundo lago.", "", "", true, false, "", "", ""},
    };

    // Room 29: los bajos de las cataratas
    rooms[29].id = 29;
    rooms[29].title = "los bajos de las cataratas";
    rooms[29].description = "Hay un ruido ensordecedor, como si millones de tambores redoblaran al lado de sus tímpanos. Usted siente como si su cabeza fuese a explotar.";

    // Room 30: fondo del Lago
    rooms[30].id = 30;
    rooms[30].title = "fondo del Lago";
    rooms[30].description = "Contrariamente a lo que le dijeron en su infancia, usted puede respirar debajo del agua. Usted siente una paz extraña al estar en el fondo del Lago, tal vez debida a posibles asociaciones subconcientes con su pasado embrionario, en el vientre de su madre.";
    rooms[30].items = {
        {"Inscripción", "La inscripción dice:\n\"Has llegado hasta Marmidosa, la rival de Excalibur. Hazla parte de tu mano y ella será parte de tu andar. Tómala, está detrás de la grieta.\"", 1, true},
    };
    rooms[30].creatures = {
        {"Doncella del Lago", "Es tan hermosa que usted casi se ahoga. Usted siente ganas de quedarse en el Lago durante el resto de su vida.", "Talismán de Nieve", "La doncella le mira con cierto aire de complicidad y exclama: ¡La cueva de cristal es tan hermosa! Si pudiera entrar al menos una vez...", "Las dos partes del manuscrito están guardadas en la Torre de Cristal. Y cuando vayas en busca de la segunda parte, lleva el triángulo contigo.", "", "", false, false, false},
    };
    rooms[30].doors = {
        {"Grieta", "Usted logra ver algunos destellos de una luz muy fuerte al otro lado.", 31, "Usted cruza sin problemas, protegido con el Talismán de Nieve.", "\u0000\u0000\u0000", "", true, false, "", "", "Talismán de Nieve"},
        {"Reja", "Los barrotes de la reja son muy gruesos. Al otro lado se divisa una escalera.", 34, "Escalera", "", "Tenazas", false, false, "", "", ""},
        {"Sendero dorado", "Es muy hermoso.", 32, "Usted sale del Lago.", "\u0000\u0000\u0000", "", true, false, "", "", "Marmidosa"},
    };

    // Room 31: la Cueva de Cristal
    rooms[31].id = 31;
    rooms[31].title = "la Cueva de Cristal";
    rooms[31].description = "Hay resplandores de cristales por todas partes. En este lugar el agua se ha hecho más densa y le resulta difícil respirar.";
    rooms[31].items = {
        {"Marmidosa", "Es algo más allá de la comprensión humana. Usted se siente orgulloso de haberla encontrado antes del Hechicero, que lleva siglos buscándola.", 1, true},
    };
    rooms[31].doors = {
        {"Grieta", "Es la salida de la Cueva de Cristal.", 30, "Usted sale de la Cueva de Cristal.", "", "", true, false, "", "", ""},
    };

    // Room 32: la orilla del Lago
    rooms[32].id = 32;
    rooms[32].title = "la orilla del Lago";
    rooms[32].description = "Frente a usted se extiende el Lago, de aguas claras y tranquilas.";
    rooms[32].doors = {
        {"Sendero dorado", "Es muy hermoso.", 30, "Usted se sumerge en el lago.", "\u0000\u0000\u0000", "", true, false, "", "", "Marmidosa"},
        {"Camino", "El camino se pierde como una serpiente en la rectitud del horizonte.", 35, "Usted nota como el paisaje va cambiando a medida que avanza. Cada vez se va pareciendo más a un desierto.", "", "", true, false, "", "", ""},
    };

    // Room 33: un Oasis
    rooms[33].id = 33;
    rooms[33].title = "un Oasis";
    rooms[33].description = "Es un oasis tradicional, con varias palmeras de dátiles y un pequeño estanque de agua turbia en el centro.";
    rooms[33].items = {
        {"Cubo de agua", "Es un balde de madera, lleno de agua hasta el tope.", 1, true},
    };
    rooms[33].creatures = {
        {"Pordiosero", "Usted no sabe si es en realidad un pordiosero, o alguien que acaba de atravesar el desierto.", "Bolsa", "El pordiosero guarda silencio y extiende su mano pidiendo una limosna.", "Si el Ogro se baña, se muere.", "", "", false, false, false},
    };
    rooms[33].doors = {
        {"Desierto", "Usted se estremece al recordar la última vez que atravesó el desierto.", 20, "Usted camina duarante muchos días. El sol y el roce de la arena llagan todo su cuerpo. Por las noches, el viento helado del desierto no lo deja dormir. La sed invade su cuerpo y su mente.\nPero al final logra regresar a las ruinas.", "", "", true, false, "", "", ""},
        {"Ruta de los camellos", "Está formada por miles de pisadas de camellos. Seguramente conduce a algún lugar agradable.", 34, "Usted avanza siguiendo las huellas que oscilan de un lado a otro y hasta describen círculos. Todo parece indicar que los camellos estaban ebrios.\nUsted arriba a la Catedral.", "", "", true, false, "", "", ""},
    };

    // Room 34: la Catedral
    rooms[34].id = 34;
    rooms[34].title = "la Catedral";
    rooms[34].description = "Es un lugar impresionante. Las paredes crecen hasta una altura increíble y se unen en una serie de simétricas torres. Usted se siente oprimido por la arquitectura, como si en realidad estuviese ante los ojos de Dios, en el día del juicio final.";
    rooms[34].items = {
        {"Rosario", "Es un rosario bastante común.", 1, true},
    };
    rooms[34].creatures = {
        {"Obispo", "Es un anciano de aspecto venerable.", "Silla", "El Obispo lo mira y fuerza una sonrisa. Está muy cansado para conversar y en toda la Catedral no hay donde sentarse.", "Solo con el Talismán de Nieve podrás entrar hasta Marmidosa.", "", "", false, false, false},
    };
    rooms[34].doors = {
        {"Ruta de los camellos", "Es la única vía de regresar a las ruinas. ", 33, "Luego de varios días de camino; usted regresa, más muerto que vivo, al Oasis.", "", "", true, false, "", "", ""},
        {"Puerta", "Es la salida de la Catedral.", 35, "Usted sale de la Catedral y el viento seco del desierto le golpea la cara.", "", "", true, false, "", "", ""},
    };

    // Room 35: el Desierto otra vez
    rooms[35].id = 35;
    rooms[35].title = "el Desierto otra vez";
    rooms[35].description = "El calor lo asfixia. Usted no comprende cómo es posible que el clima varíe tanto de un lugar a otro de la Fortaleza.";
    rooms[35].items = {
        {"Inscripción", "Dice:\n\"El Obispo le recomendó cierto objeto para protegerse a la hora de coger a Marmidosa. ¡No intente cruzar el camino en esta dirección con dicho objeto encima!\"", 1, true},
        {"Escudo de Aquiles", "Usted nunca había visto algo tan hermoso.\nEste escudo formaba parte de la nueva armadura que Hefestos le hizo a Aquiles cuando la anterior cayó en manos de los troyanos al morir Patroclo.", 1, true},
    };
    rooms[35].doors = {
        {"Camino", "El camino se pierde como una serpiente en la rectitud del horizonte. ", 32, "Usted nota como el paisaje va cambiando a medida que avanza. El desierto va perdiendo terreno y cada vez hay más vegetación.", "\u0000\u0000\u0000", "", true, false, "", "", "Talismán de Nieve "},
        {"Puerta", "Es la puerta de salida de la Catedral.", 34, "Usted entra a la Catedral", "", "", true, false, "", "", ""},
        {"Muralla", "Es algo más pequeña que la muralla anterior.", 36, "Avenida de las flores", "", "Piedra verde", false, false, "", "", ""},
    };

    // Room 36: un extenso valle
    rooms[36].id = 36;
    rooms[36].title = "un extenso valle";
    rooms[36].description = "Siente deseos de construir una casa y quedarse a vivir en el valle. Por todos lados crece una especie de árbol frutal que, valiéndose de dos manos que salen de su tronco, es capaz de cultivarse ella misma.";
    rooms[36].items = {
        {"Bolsa de semillas", "La bolsa está llena de semillas de los árboles que crecen en el valle.", 1, true},
    };
    rooms[36].creatures = {
        {"Camello", "Está muy viejo y maltratado. Tiene las pezuñas llenas de arena.", "Botella de vino", "¡Dame más!", "Las dos últimas letras del segundo nombre de la Hija del Hechicero son \"KA\".", "", "", false, false, false},
    };
    rooms[36].doors = {
        {"Avenida de las flores", "Toda la avenida está sembrada de flores carnívoras.", 35, "Usted regresa corriendo al desierto.", "", "", true, false, "", "", ""},
        {"Montañas", "Las montañas rodean todo el sur del Valle. Parece el espinazo de un dragón gigantesco.", 37, "Luego de varios días de camino usted llega al punto más alto de la cordillera.", "", "", true, false, "", "", ""},
    };

    // Room 37: la cima del Pico Negro
    rooms[37].id = 37;
    rooms[37].title = "la cima del Pico Negro";
    rooms[37].description = "Nunca antes había estado a tanta altura. Usted se pregunta por qué la montaña es llamada \"El Pico Negro\" si en realidad está cubierta de nieve.";
    rooms[37].doors = {
        {"Montañas", "Desde este lugar, las montañas lucen como grades piedras envueltasen nubes.", 36, "Luego de varios días de camino usted regresa al valle.", "", "", true, false, "", "", ""},
        {"Precipicio", "Usted se inclina en el borde del precipicio, pero no consigue ver el fondo.", 39, "Usted logra sobreponerse al temblor de sus manos, se aferra al saltador y se lanza al vacío. Al tercer día de caída, el muelle del saltador rebota suavemente en el suelo.", "\u0000\u0000\u0000", "", true, false, "", "", "Saltador"},
        {"Ladera", "La ladera desciende suavemente hasta un campo sembrado.", 41, "Usted desciende cuidadosamente hasta las tierras del Labrador.", "", "", true, false, "", "", ""},
        {"Puerta de Madera", "Es la entrada a la choza del Monje.", 38, "Usted entra a la choza del Monje.", "", "", true, false, "", "", ""},
    };

    // Room 38: la choza de un monje
    rooms[38].id = 38;
    rooms[38].title = "la choza de un monje";
    rooms[38].description = "El suelo está muy limpio, al igual que los muebles y las ventanas. Hay una gran cantidad de cuentas regadas por el suelo.";
    rooms[38].creatures = {
        {"Monje", "Parece ser bastante joven.", "Rosario", "El monje no le responde. Está muy ocupado recogiendo las cuentas del suelo.", "Para descender por el precipicio debes llevar algo que amortigüe el golpe al final.", "", "", false, false, false},
    };
    rooms[38].doors = {
        {"Puerta de Madera", "Conduce a la cima del Pico Negro.", 37, "Usted sale de la choza del Monje.", "", "", true, false, "", "", ""},
    };

    // Room 39: la Ciudad Abandonada
    rooms[39].id = 39;
    rooms[39].title = "la Ciudad Abandonada";
    rooms[39].description = "A pesar de ser más antigua que las ruinas, la ciudad se conserva intacta. Usted oye el ruido de la gente en las calles y siente los olores de los alimentos en las cocinas, pero no son más que ilusiones. La ciudad está abandonada desde hace siglos.";
    rooms[39].items = {
        {"Inscripción", "Dice:\n\"Aquí habitaron los horantes durante mucho tiempo, hasta que La Bestia ocupó el lugar. Ellos levantaron cada pared de la Fortaleza, solo ellos saben como salir.\"", 1, true},
    };
    rooms[39].doors = {
        {"Túnel", "Conduce a las ruinas.", 20, "Usted camina hasta regresar a las ruinas.", "", "", true, false, "", "", ""},
        {"Escalera", "Usted se pregunta a dónde conducirá.", 36, "Usted sube hasta regresar al Valle.", "", "", true, false, "", "", ""},
        {"Puerta de Hierro", "Es la entrada de la casa del sabio.", 40, "Usted ha entrado a la casa del sabio.", "", "", true, false, "", "", ""},
        {"Estatua de Cristal", "Usted no logra descubrir qué representa.", 39, "Horante", "", "Corta-Cristales", false, false, "", "", ""},
    };

    // Room 40: la choza del Sabio
    rooms[40].id = 40;
    rooms[40].title = "la choza del Sabio";
    rooms[40].description = "El lugar se ajusta perfectamente a su concepto de desorden. Usted se pregunta cómo el sabio puede vivir en semejante caos. Hay varios esqueletos, al parecer, una colección incipiente.";
    rooms[40].items = {
        {"Cinta de Moebius", "Es una cinta de papel con una torcedura y ambos extremos pegados.", 1, true},
        {"Péndulo", "El péndulo oscila levemente, colgado de un punto invisible del espacio.", 1, true},
    };
    rooms[40].creatures = {
        {"Sabio", "Es sabio es un hombre pequeño. Lleva unos espejuelos que cubren casi todo su rostro", "Esqueleto de Murciélago", "El sabio está muy distraído haciendo un anillo de papel algo torcido. ", "De todas las cosas sobre la tierra, la que más me fascina es la cinta de Moebius. Empiezas a recorrerla por adentro y cuando vienes a ver... ¡estás afuera!", "", "", false, false, false},
    };
    rooms[40].doors = {
        {"Puerta de Hierro", "Conduce a la Ciudad Abandonada.", 39, "Usted regresa a la Ciudad Abandonada.", "", "", true, false, "", "", ""},
    };

    // Room 41: un campo cultivado
    rooms[41].id = 41;
    rooms[41].title = "un campo cultivado";
    rooms[41].description = "Todos los sembrados parecen bastante descuidados. Probablemente el labrador no sea capaz de atender una cantidad tan grande de tierra al mismo tiempo.";
    rooms[41].items = {
        {"Tenazas", "Parecen ser muy fuertes.", 1, true},
    };
    rooms[41].creatures = {
        {"Labrador", "Es un hobre robusto y muy maltratado por el trabajo en el campo.", "Bolsa de semillas", "¡Qué cansancio! Creo que es demasiada tierra para una sola persona.", "El Labrador lo mira y le dice:\n\"No siempre las cosas son lo que parecen. La realidad tiene muchas caras y nunca sabemos si estamos mirando la verdadera. Mantén tu mente abierta\".", "", "", false, false, false},
    };
    rooms[41].doors = {
        {"Ladera", "Es por dónde único se puede subir al Pico Negro de este lado de la cordillera.", 37, "Usted asciende el Pico Negro.", "", "", true, false, "", "", ""},
        {"Río", "La corriente es tan fuerte que arrastraría hasta la embarcación más pesada.", 42, "Usted lanza la soga con el garfio hasta la otra orilla y forma una especie de cuerda floja. Luego cruza el río haciendo una impresionante demostración de equilibrio.", "\u0000\u0000\u0000", "", true, false, "", "", "Cuerda"},
    };

    // Room 42: el exterior de la Torre de Cristal
    rooms[42].id = 42;
    rooms[42].title = "el exterior de la Torre de Cristal";
    rooms[42].description = "La Torre de Cristal crece vertiginosamente hasta perderse entre las nubes.";
    rooms[42].doors = {
        {"Río", "La corriente es tan fuerte que arrastraría hasta la embarcación más pesada.", 41, "Usted lanza la soga con el garfio hasta la otra orilla y forma una especie de cuerda floja. Luego cruza el río haciendo una impresionante demostración de equilibrio.", "\u0000\u0000\u0000", "", true, false, "", "", "Cuerda"},
        {"Ebano", "Es muy alto.", 42, "NADA", "", "NADA", false, false, "", "", ""},
        {"Puerta de Hierro", "Es la entrada a los calabozos.", 46, "Usted entra a los calabozos.", "", "", true, false, "", "", ""},
        {"Escalera de Caracol", "Sube hasta el tope de la la Torre de Cristal.", 43, "Usted asciende durante varias horas.", "", "", true, false, "", "", ""},
    };

    // Room 43: la punta de la Torre de Cristal
    rooms[43].id = 43;
    rooms[43].title = "la punta de la Torre de Cristal";
    rooms[43].description = "Probablemente se encuentre a varios kilómetros de altura. Usted se alegra de que no hayan ventanas en el lugar.";
    rooms[43].doors = {
        {"Escalera de Caracol", "Conduce a la parte inferior de la Torre de Cristal.", 42, "Usted regresa a la orilla del río.", "", "", true, false, "", "", ""},
        {"Esfera", "Tiene aproximadamente tres metros de diámetro y parece ser de carne. Es algo realmente insólito.", 43, "Tablilla de Madera", "", "Marmidosa", false, false, "", "", ""},
        {"Puerta de Cristal", "Es de un cristal muy grueso y opaco.", 44, "Usted entra a la alcoba.", "", "", false, true, "¿Cuál es el nombre completo de la hija del Hechicero?", "Aura Srka", ""},
    };

    // Room 44: la alcoba de la hija del Hechicero
    rooms[44].id = 44;
    rooms[44].title = "la alcoba de la hija del Hechicero";
    rooms[44].description = "Esta es la alcoba donde la hija del Hechicero se alojaba temporalmente. Es muy cómoda y tiene muchos cuadros iguales al que usted lleva.";
    rooms[44].items = {
        {"Espejo", "Está roto.", 1, true},
    };
    rooms[44].doors = {
        {"Puerta de Cristal", "Es la salida de la alcoba.", 43, "Usted sale de la alcoba.", "", "", true, false, "", "", ""},
        {"Carta", "La carta dice:\n\"Mi querido salvador:\n¿Por qué has demorado tanto? Hace mucho que mi padre me llevó al Abismo Infranqueable. Ahora no podré marcharme contigo. La único que puedes hacer para salir es matarlo con Marmidosa. Por favor, trata de que no sufra.\"", 45, "Puerta Secreta", "", "", false, false, "", "", ""},
    };

    // Room 45: la Alcoba Secreta
    rooms[45].id = 45;
    rooms[45].title = "la Alcoba Secreta";
    rooms[45].description = "Es mucho mayor que la otra alcoba. Es casi seguro que la hija del Hechicero viva en este lugar permanentemente.";
    rooms[45].creatures = {
        {"Hija del Hechicero", "Usted está a punto de desmayarse. La hija del Hechicero no es exactamente como usted esperaba. En realidad se parece más a una serpiente de quince metros y tres cabezas, con la piel llena de gruesas escamas.", "", "", "", "Aguja", "Usted clava fuertemente la aguja entre las escamas. Las cabezas le miran llenas de ira y hay una que exclama: \"¡Mata a todos los que te mintieron si quieres salir!\"", false, false, true},
    };
    rooms[45].doors = {
        {"Puerta Secreta", "Conduce a la alcoba.", 44, "Usted regresa a la alcoba.", "\u0000\u0000\u0000", "", false, false, "", "", ""},
    };

    // Room 46: los Calabozos
    rooms[46].id = 46;
    rooms[46].title = "los Calabozos";
    rooms[46].description = "Los calabozos están formados por varios pasillos paralelos, llenos de celdas a ambos lados.";
    rooms[46].creatures = {
        {"Carcelero", "Parece un hombre rudo y cumplidor de sus deberes.", "", "", "", "Marmidosa", "ARRRGG!!! ¡Te será muy difícil abrir la celda, porque la palabra mágica es el nombre de la primera criatura que viste al salir del cuarto de huéspedes! \nUsted sonríe porque sabe que el problema es fácil.", false, false, true},
    };
    rooms[46].doors = {
        {"Puerta de Hierro", "Es la salida de los calabozos. Conduce a la orilla del río.", 42, "Usted regresa al río.", "", "", true, false, "", "", ""},
        {"Reja", "Conduce a la celda. Los barrotes son tan gruesos que la reja es prácticamente una puerta maciza.", 47, "Usted estornuda. Ha entrado a la celda.", "Grifo", "", false, false, "", "", ""},
        {"Puerta Gris", "Conduce a la sala de La Prueba.", 48, "Usted entra a la sala de La Prueba.", "", "", true, false, "", "", ""},
    };

    // Room 47: una celda
    rooms[47].id = 47;
    rooms[47].title = "una celda";
    rooms[47].description = "Debe ser un verdadero suplicio el estar encerrado aquí. Todo el suelo está cubierto de afiladas hojas, excepto en una esquina, donde se supone que esté el prisionero.";
    rooms[47].creatures = {
        {"Encapuchado", "Es una criatura realmente asombrosa. Toda su anatomía parece regida por el número siete. Siete brazos, siete pies, siete dedos en cada una de las siete manos.", "Receta", "Pareces haber estado viajando. Seguramente has visto algo que me pertenece por ahí... ¿podrías traérmelo?", "El nombre de la hija del Hechicero tiene ocho letras, una está repetida tres veces y otra dos.", "", "", false, false, false},
    };
    rooms[47].doors = {
        {"Reja", "Es la salida de la celda.", 46, "Usted sale de la celda.", "Grifo", "", false, false, "", "", ""},
    };

    // Room 48: la Antesala de la Prueba
    rooms[48].id = 48;
    rooms[48].title = "la Antesala de la Prueba";
    rooms[48].description = "Es un salón circular. La luz del sol entra por unos vitrales rojos y el lugar luce como pintado con sangre.";
    rooms[48].items = {
        {"Inscripción", "Dice:\n\"En este punto comienza la prueba de los anillos. Continúa con el que hayas elegido y deja los demás.\"", 1, true},
        {"Arco", "Con este arco mataron a Hycrk, uno de los doce inmortales.", 1, true},
    };
    rooms[48].doors = {
        {"Puerta Gris", "Conduce a los calabozos.", 46, "Usted entra a los calabozos.", "", "", true, false, "", "", ""},
        {"Túnel", "Parece ser muy largo. Usted no se atrevería a cruzarlo sin el arco.", 13, "Casi a mitad de camino usted es atacado por una bandada de murciélagos gigantes. Gracias al arco, usted logra ahuyentarlos.", "\u0000\u0000\u0000", "", true, false, "", "", "Arco"},
        {"Puerta Verde", "Es la primera puerta de la prueba. ", 49, "Usted cierra los ojos y cruza la puerta. Dejar el anillo de oro fue una idea excelente.", "\u0000\u0000\u0000", "", true, false, "", "", "Anillo de oro"},
    };

    // Room 49: el Salón Verde
    rooms[49].id = 49;
    rooms[49].title = "el Salón Verde";
    rooms[49].description = "Es un salón de pruebas tradicional. Este tipo de salón fue usado ampliamente por los horantes para educar a sus hijos.";
    rooms[49].doors = {
        {"Puerta Verde", "Conduce al primer salón.", 48, "Usted atraviesa la puerta sin dificultades.", "\u0000\u0000\u0000", "", true, false, "", "", "Anillo de oro"},
        {"Puerta Azul", "Es la segunda puerta de la prueba.", 50, "Usted piensa durante unos segundos antes de avanzar. Hizo bien en dejar el anillo de plata.", "\u0000\u0000\u0000", "", true, false, "", "", "Anillo de plata"},
    };

    // Room 50: el Salón Azul
    rooms[50].id = 50;
    rooms[50].title = "el Salón Azul";
    rooms[50].description = "Es un salón de pruebas tradicional. Este tipo de salón fue usado ampliamente por los horantes para educar a sus hijos.";
    rooms[50].doors = {
        {"Puerta Azul", "Conduce al salón verde.", 49, "Usted atraviesa la puerta sin dificultades.", "\u0000\u0000\u0000", "", true, false, "", "", "Anillo de plata"},
        {"Puerta Blanca", "Es la tercera puerta de la prueba.", 51, "Usted levanta los ojos buscando valor y da los primeros pasos. Usted se alegra de no haber traído el anillo de bronce.", "\u0000\u0000\u0000", "", true, false, "", "", "Anillo de bronce"},
    };

    // Room 51: el Salón Blanco
    rooms[51].id = 51;
    rooms[51].title = "el Salón Blanco";
    rooms[51].description = "Es un salón de pruebas tradicional. Este tipo de salón fue usado ampliamente por los horantes para educar a sus hijos. Es el último de la prueba.";
    rooms[51].doors = {
        {"Puerta Blanca", "Conduce al salón azul.", 50, "Usted atraviesa la puerta sin dificultades.", "\u0000\u0000\u0000", "", true, false, "", "", "Anillo de bronce"},
        {"Puerta triangular", "Es la última puerta de la prueba.", 52, "Esta vez usted no se detiene a pensarlo y avanza decididamente. Todo parece indicar que eligió el anillo correcto: la cinta de Moebius.", "\u0000\u0000\u0000", "", true, false, "", "", "Cinta de Moebius"},
    };

    // Room 52: los límites de la Fortaleza
    rooms[52].id = 52;
    rooms[52].title = "los límites de la Fortaleza";
    rooms[52].description = "A su derecha crece la tercera muralla, hasta una altura irracional. Usted no puede creer que aquí termine la Fortaleza. Del otro lado de la muralla se escucha (usted no entiende cómo) el canto de los pájaros y el sonido del viento en los árboles.";
    rooms[52].creatures = {
        {"Guardián", "Está muy viejo para vigilar algo. Probablemente alguien lo haya olvidado en este lugar. Está muy quemado por el sol.", "Sombrero", "¡Qué calor!", "El anciano le cuenta una historia incoherente sobre un héroe que derrota a una serpiente gigante armado de una aguja.", "", "", false, false, false},
    };
    rooms[52].doors = {
        {"Puerta triangular", "Conduce al salón blanco.", 51, "Usted atraviesa la puerta sin dificultades y regresa al salón blanco.", "\u0000\u0000\u0000", "", true, false, "", "", "Cinta de Moebius"},
        {"Puente", "Está hecho de madera y soga. Bajo él se abre, infinito, el Abismo Infranqueable. Del otro lado se divisa una pirámide.", 53, "Usted logra cruzar el puente gracias a la protección del grabado.", "\u0000\u0000\u0000", "", true, false, "", "", "Grabado"},
        {"Muralla", "Es la tercera muralla con que usted tropieza en su camino. algo le dice que también es la última.", 52, "NADA", "", "NADA", false, false, "", "", ""},
    };

    // Room 53: la Pirámide del Hechicero
    rooms[53].id = 53;
    rooms[53].title = "la Pirámide del Hechicero";
    rooms[53].description = "Es una construcción gigantesca, a base de piedras. Al parecer, las piedras fueron colocadas sin orden alguno, olvidando las ventanas. El lugar está iluminado con numerosas antorchas.";
    rooms[53].doors = {
        {"Puente", "De este lado se puede apreciar mejor lo frágil que es el puente y lo infinito que es el Abismo.", 52, "Usted logra cruzar el puente gracias a la protección del grabado.", "\u0000\u0000\u0000", "", true, false, "", "", "Grabado"},
        {"Columna de Hielo", "Es una ancha estructura de hielo pegada a la pared.", 54, "Puerta de Roble", "", "Antorcha", false, false, "", "", ""},
    };

    // Room 54: las Habitaciones del Hechicero
    rooms[54].id = 54;
    rooms[54].title = "las Habitaciones del Hechicero";
    rooms[54].description = "Las habitaciones del Hechicero están dentro de una pirámide interior. Todo es igual a la gran pirámide, pero en una escala menor. Hay miles de espadas colgadas de la pared.";
    rooms[54].creatures = {
        {"Hechicero", "Es un hombre inmenso, de barba blanca. Viste una túnica negra y sostiene una vara con una caravela en su mano.", "Marmidosa", "No desea hablar con usted.", "El Hechicero le sonríe y le dice: \n\"No soy tu enemigo. Es mi hija quien ha elaborado este diabólico plan para eliminarnos. Rompe la carta que te dejó en la Torre de Cristal y ocurrirá un milagro.\"", "", "", false, false, false},
    };
    rooms[54].doors = {
        {"Puerta de Roble", "Es de un roble tan sólido que mellaría cualquier acero.", 53, "Usted sale de las habitaciones del Hechicero.", "", "", true, false, "", "", ""},
    };

    return rooms;
}

} // namespace Fortaleza2