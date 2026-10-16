# La Fortaleza 2: La venganza de la Bestia — Mapa Completo

> Extraído directamente de `FORT2.EXE` desempaquetado (55 habitaciones, IDs 0–54).
> Obra de Miguel Enrique Cepero (1990/1991), Merchise Software.

---

## 1. Zonas Principales de la Fortaleza 2

1. **La Mansión / Residencia Inicial (Salas 0–9):**
   - 0: Habitación para huéspedes (inicio)
   - 1: El pasillo (hub de 6 puertas)
   - 2: El Salón de Fumar (tentáculos, sillas, balanza)
   - 3: Cuarto de la hija del Hechicero
   - 4: Casa de muñecas y baúl dimensional
   - 5: Cuarto del Leñador
   - 6: La Cocina (matadero con marcas de mano de 7 dedos)
   - 7: Las Terrazas (gravedad invertida, escalera no euclidiana)
   - 8: Calabozo del Monstruo
   - 9: Interior del baúl

2. **El Río Negro y los Jardines (Salas 10–19):**
   - 10: Orilla del Río Negro (Caronte y su bote)
   - 11: Otra orilla del Río Negro (Muralla colosal, árbol de marfil)
   - 12: Los Jardines del Hechicero (hub central vegetal)
   - 13: El Comedor (mesa gigante, túnel con murciélagos)
   - 14: La Sastrería (telas de araña, aguja de plata)
   - 15: Cuarto del Jardinero
   - 16: Habitación de los tesoros (Omicuos Ihanti)
   - 17: Salón de las velas
   - 18: Cuarto del Inmortal
   - 19: Cuarto de juguetes

3. **Las Ruinas, Subterráneos y el Lago Subterráneo (Salas 20–32):**
   - 20: Las Ruinas (cruce entre desierto, catacumbas y juguetes)
   - 21: Salón de Recepciones del Ogro
   - 22: Cuarto del Pintor
   - 23: Patio Interior invernal
   - 24: Habitaciones del Juglar
   - 25: Alcoba del Ogro
   - 26: Los Subterráneos
   - 27: Las Catacumbas ("Este es para ti")
   - 28: Cataratas (inicio)
   - 29: Bajos de las cataratas
   - 30: Fondo del Lago (respiración acuática, Doncella del Lago)
   - 31: Cueva de Cristal (espada Marmidosa)
   - 32: Orilla del Lago

4. **El Desierto, la Catedral y las Montañas (Salas 33–41):**
   - 33: Un Oasis (pordiosero, palmeras de dátiles)
   - 34: La Catedral (Obispo)
   - 35: El Desierto
   - 36: Un extenso valle (árboles que se cultivan solos)
   - 37: Cima del Pico Negro (nieve y abismo)
   - 38: Choza del Monje (cuentas de rosario)
   - 39: La Ciudad Abandonada (eco de gente y cocinas)
   - 40: Choza del Sabio (Cinta de Moebius y esqueletos)
   - 41: Campo cultivado del Labrador

5. **La Torre de Cristal y la Alcoba Secreta (Salas 42–45):**
   - 42: Exterior de la Torre de Cristal (río caudaloso)
   - 43: Punta de la Torre de Cristal (tablilla con acertijo)
   - 44: Alcoba de la hija del Hechicero
   - 45: Alcoba Secreta (la verdadera hija: serpiente de 3 cabezas)

6. **Los Calabozos y la Prueba de los Horantes (Salas 46–51):**
   - 46: Los Calabozos (Carcelero)
   - 47: Celda de castigo (Encapuchado de 7 extremidades)
   - 48: Antesala de la Prueba (vitrales rojos)
   - 49: Salón Verde (dejar anillo de oro)
   - 50: Salón Azul (dejar anillo de plata)
   - 51: Salón Blanco (dejar anillo de bronce, pasar con Cinta de Moebius)

7. **El Abismo y la Pirámide del Hechicero (Salas 52–54):**
   - 52: Límites de la Fortaleza (Guardián, Tercera Muralla)
   - 53: Pirámide del Hechicero (columna de hielo)
   - 54: Habitaciones del Hechicero (Hechicero con vara de calavera)

---

## 2. Diagrama del Mapa (Grafo Mermaid)

### Leyenda
- `<-->` paso bidireccional abierto · `-->` paso unidireccional
- `==>` paso con requerimiento obligatorio (muerte si se infringe)
- 🔑 clave o palabra mágica · ❓ acertijo · 🛡 objeto necesario para pasar/sobrevivir
- ⚔️ combate con arma específica · 🔨 rotura/interacción con objeto

```mermaid
flowchart TD
    subgraph MANSION ["1. La Mansión y Pasillo (Salas 0–9)"]
        R0["0 Habitación de huéspedes"]
        R1["1 El Pasillo (Hub)"]
        R2["2 Salón de Fumar"]
        R3["3 Cuarto de la hija"]
        R4["4 Casa de muñecas"]
        R5["5 Cuarto del Leñador"]
        R6["6 La Cocina"]
        R7["7 Las Terrazas"]
        R8["8 Calabozo del Monstruo"]
        R9["9 Interior del baúl"]

        R0 <-->|"Puerta"| R1
        R1 <-->|"Puerta espinos"| R5
        R1 ==>|"🛡 Pañuelo (Puerta metal)"| R6
        R1 <-->|"Puerta Negra"| R2
        R1 ==>|"🔑 'Aura' (Puerta Azul)"| R3
        R3 <-->|"Agujero"| R4
        R4 ==>|"🔑 'MIAU' (Baúl)"| R9
        R1 <-->|"Puerta de oro"| R7
        R7 <-->|"Escalera caracol"| R8
    end

    subgraph RIO_JARDINES ["2. Río Negro y Jardines (Salas 10–19)"]
        R10["10 Orilla del Río Negro"]
        R11["11 Otra orilla Río Negro"]
        R12["12 Jardines del Hechicero (Hub)"]
        R13["13 El Comedor"]
        R14["14 La Sastrería"]
        R15["15 Cuarto del Jardinero"]
        R16["16 Habitación de los tesoros"]
        R17["17 Salón de las velas"]
        R18["18 Cuarto del Inmortal"]
        R19["19 Cuarto de juguetes"]

        R7 <-->|"Escalera"| R10
        R10 ==>|"🛡 Reloj invertido a Caronte"| R11
        R11 ==>|"🔨 Maza (romper Muralla)"| R12
        R4 -.->|"🔨 Corta-cristales (Ventana)"| R12
        R12 <-->|"Puerta de madera"| R13
        R12 <-->|"Puerta de tela"| R14
        R12 <-->|"Puerta verde"| R15
        R12 ==>|"🔑 'Omicuos Ihanti' (Puerta amarilla)"| R16
        R12 <-->|"Puerta roja"| R17
        R17 <-->|"Escalera"| R18
        R17 <-->|"Puerta blanca"| R19
        R18 <-->|"Puerta blanca"| R19
    end

    subgraph SUBTERRANEOS ["3. Ruinas, Subterráneos y Lago (Salas 20–32)"]
        R20["20 Las Ruinas"]
        R21["21 Salón de Recepciones"]
        R22["22 Cuarto del Pintor"]
        R23["23 Patio Interior"]
        R24["24 Habitaciones del Juglar"]
        R25["25 Alcoba del Ogro"]
        R26["26 Los Subterráneos"]
        R27["27 Las Catacumbas"]
        R28["28 Cataratas"]
        R30["30 Fondo del Lago"]
        R31["31 Cueva de Cristal"]
        R32["32 Orilla del Lago"]

        R19 <-->|"Puerta de piedra"| R20
        R20 <-->|"Puerta de hierro"| R21
        R21 <-->|"Puerta gris"| R23
        R23 <-->|"Puerta azul"| R22
        R23 <-->|"Puerta verde"| R24
        R23 <-->|"Puerta negra"| R25
        R20 <-->|"Escalera"| R26
        R26 ==>|"🛡 Escudo Aquiles (Túnel)"| R27
        R24 <-->|"Escalera"| R27
        R27 <-->|"Pasadizo"| R28
        R28 -->|"Salto al vacío"| R30
        R30 ==>|"🔑 Talismán de Nieve (Grieta)"| R31
        R30 ==>|"🛡 Marmidosa (Sendero dorado)"| R32
    end

    subgraph DESIERTO_MONTANAS ["4. Desierto, Catedral y Montañas (Salas 33–41)"]
        R33["33 Un Oasis"]
        R34["34 La Catedral"]
        R35["35 El Desierto"]
        R36["36 Extenso Valle"]
        R37["37 Cima del Pico Negro"]
        R38["38 Choza del Monje"]
        R39["39 Ciudad Abandonada"]
        R40["40 Choza del Sabio"]
        R41["41 Campo del Labrador"]

        R20 <-->|"Desierto"| R33
        R33 <-->|"Ruta camellos"| R34
        R30 ==>|"🔨 Tenazas (Reja)"| R34
        R34 <-->|"Puerta"| R35
        R32 <-->|"Camino"| R35
        R35 <-->|"Muralla"| R36
        R36 <-->|"Montañas"| R37
        R37 <-->|"Puerta madera"| R38
        R37 ==>|"🛡 Saltador (Precipicio)"| R39
        R37 <-->|"Ladera"| R41
        R39 <-->|"Túnel"| R20
        R39 <-->|"Escalera"| R36
        R39 <-->|"Puerta de hierro"| R40
    end

    subgraph TORRE_CRISTAL ["5. Torre de Cristal y Alcoba Secreta (Salas 42–45)"]
        R42["42 Exterior Torre Cristal"]
        R43["43 Punta Torre Cristal"]
        R44["44 Alcoba de la Hija"]
        R45["45 Alcoba Secreta"]

        R41 ==>|"🛡 Cuerda (Río)"| R42
        R42 <-->|"Escalera caracol"| R43
        R43 ==>|"🔑 'Aura Srka' (Puerta Cristal)"| R44
        R44 ==>|"🔨 Romper carta (Puerta Secreta)"| R45
        R45 -.->|"⚔️ Aguja vs Serpiente/Falsa Hija"| R45
    end

    subgraph PRUEBA_ANILLOS ["6. Calabozos y Prueba de Horantes (Salas 46–51)"]
        R46["46 Los Calabozos"]
        R47["47 Una Celda"]
        R48["48 Antesala de la Prueba"]
        R49["49 Salón Verde"]
        R50["50 Salón Azul"]
        R51["51 Salón Blanco"]

        R42 <-->|"Puerta hierro"| R46
        R46 ==>|"🔑 'Grifo' (Reja)"| R47
        R46 <-->|"Puerta gris"| R48
        R13 ==>|"🛡 Arco (Túnel murciélagos)"| R48
        R48 ==>|"🛡 Dejar Anillo Oro (Puerta Verde)"| R49
        R49 ==>|"🛡 Dejar Anillo Plata (Puerta Azul)"| R50
        R50 ==>|"🛡 Dejar Anillo Bronce (Puerta Blanca)"| R51
    end

    subgraph FINAL_ABISMO ["7. Abismo y Pirámide del Hechicero (Salas 52–54)"]
        R52["52 Límites de la Fortaleza"]
        R53["53 Pirámide del Hechicero"]
        R54["54 Habitaciones del Hechicero (Victoria)"]

        R51 ==>|"🛡 Pasar con Cinta Moebius"| R52
        R52 ==>|"🛡 Grabado (Puente del Abismo)"| R53
        R53 ==>|"🔥 Antorcha (Columna Hielo)"| R54
        R54 ==>|"🏆 Entregar Marmidosa al Hechicero"| R54
    end
```

---

## 3. Tabla Detallada de Habitaciones, Objetos y Criaturas

| ID | Nombre | Objetos / Peso | Criaturas (Pide / Confesión / Arma) | Salidas Principales |
|---|---|---|---|---|
| 0 | Habitación de huéspedes | — | — | Puerta → 1 |
| 1 | El pasillo | — | Grifo (muere con Daga → "¡Aura!") | Puerta → 0, Espinos → 5, Metal (Pañuelo) → 6, Negra → 2, Azul ("Aura") → 3, Oro → 7 |
| 2 | Salón de Fumar | Balanza (5), Inscripción (1) | — | Puerta Negra → 1 |
| 3 | Cuarto de la hija | Pañuelo (1), Carta (1) | — | Puerta Azul → 1, Agujero → 4 |
| 4 | Casa de muñecas | — | — | Agujero → 3, Ventana (Corta-cristales) → 12, Baúl ("MIAU") → 9 |
| 5 | Cuarto del Leñador | Daga (4), Botella de vino (15), Hacha (5) | — | Puerta de espinos → 1 |
| 6 | La Cocina | Receta (6), Muslo de carnero (16), Pescado (7) | — | Puerta de metal → 1 |
| 7 | Las Terrazas | Reloj de arena (14), Silla (5) | — | Puerta de oro → 1, Escalera → 8 y 10 |
| 8 | Calabozo del Monstruo | Inscripción (1) | Monstruo (Pide comida / Pista Marmidosa) | Escalera → 7 |
| 9 | Interior del baúl | Inscripción (1), Piedra verde (12) | Gato (Pide Pescado / Pista piedra verde) | Puerta del baúl → 4 |
| 10 | Orilla del Río Negro | Bote (1) | Caronte (Pide Reloj de arena invertido / Pista blanco) | Escalera → 8, Río Negro → 11 |
| 11 | Otra orilla Río Negro | Maza (4) | — | Río Negro → 10, Muralla (Maza) → 12, Árbol marfil (Hacha) |
| 12 | Jardines del Hechicero | Piedra (1) | Jardinero (Pide Hacha / Pista anillos) | Comedor → 13, Tesoro → 16, Sastrería → 14, Cuarto Jardinero → 15, Velas → 17, Avenida → 11 |
| 13 | El Comedor | Huevo (5), Tiranosaurio (10) | Cachorro dinosaurio (Sonajero / Pista gato) | Puerta → 12, Túnel (Arco) → 48, Huevo (Piedra) |
| 14 | La Sastrería | Muñeco diabólico (16), Aguja (5) | — | Puerta de tela → 12 |
| 15 | Cuarto del Jardinero | Sombrero (8), Rosa diamante (13) | — | Puerta verde → 12 |
| 16 | Habitación de los tesoros | Anillo de oro (13), Arpa (4), Bolsa de oro (5) | — | Puerta amarilla ("Omicuos Ihanti") → 12 |
| 17 | Salón de las velas | — | Dragón (Pide comida / Clave tesoro) | Puerta roja → 12, Escalera → 18 |
| 18 | Cuarto del Inmortal | — | Inmortal (Pide vino / Pista tercera barrera) | Escalera → 17, Puerta blanca → 19 |
| 19 | Cuarto de juguetes | Saltador (8), Sonajero (2), Talismán de Nieve (17) | — | Puerta blanca → 18, Puerta piedra → 20 |
| 20 | Las Ruinas | — | — | Juguetes → 19, Hierro → 21, Escalera → 26, Desierto → 33 |
| 21 | Salón de Recepciones | Anillo de bronce (16) | — | Ruinas → 20, Patio → 23, Pintor → 22, Juglar → 24 |
| 22 | Cuarto del Pintor | Lienzo (6), Grabado (7) | — | Salón Recepciones → 21 |
| 23 | Patio Interior | — | — | Recepciones → 21, Alcoba Ogro → 25 |
| 24 | Habitaciones del Juglar | Cuerda con gancho (6) | Juglar (Pide Arpa / Pista fragua de Vulcano) | Salón Recepciones → 21 |
| 25 | Alcoba del Ogro | — | Ogro (Muere con Cubo de agua / Pista Marmidosa) | Patio → 23, Catacumbas (Escudo Aquiles) → 27 |
| 26 | Los Subterráneos | Antorcha (8) | — | Ruinas → 20, Catacumbas (Escudo Aquiles) → 27 |
| 27 | Las Catacumbas | Esqueleto murciélago (23), Anillo de plata (15) | — | Subterráneos → 26, Catarata → 28 |
| 28 | Inicio de Cataratas | — | — | Salto al vacío → 30 (fondo del Lago) |
| 29 | Bajos de cataratas | — | — | Paso hacia el lago |
| 30 | Fondo del Lago | Inscripción (1) | Doncella del Lago (Pide Talismán Nieve / Pista manuscrito) | Grieta (Talismán Nieve) → 31, Reja (Tenazas) → 34, Sendero dorado (Marmidosa) → 32 |
| 31 | Cueva de Cristal | Marmidosa (espada legendaria) | — | Grieta → 30 |
| 32 | Orilla del Lago | — | — | Sendero dorado → 30, Camino → 35 |
| 33 | Un Oasis | Cubo de agua (12) | Pordiosero (Pide bolsa oro / "Si el Ogro se baña, se muere") | Ruinas → 20, Catedral (Camellos) → 34 |
| 34 | La Catedral | Rosario (7) | Obispo (Pide Silla / Pista Talismán Nieve) | Oasis → 33, Desierto → 35 |
| 35 | El Desierto | Escudo de Aquiles (17) | — | Avenida flores → 35, Montañas → 37, Lago → 32, Catedral → 34 |
| 36 | Extenso Valle | — | Camello (Pide semillas / Pista nombre hija: termina en "KA") | Montañas → 37, Ciudad Abandonada → 39 |
| 37 | Cima del Pico Negro | Bolsa de semillas (17) | — | Precipicio (Saltador) → 41, Valle → 36, Choza Monje → 38 |
| 38 | Choza del Monje | — | Monje (Pide Rosario / Pista saltador) | Pico Negro → 37 |
| 39 | Ciudad Abandonada | Tenazas (7) | Horante (Pide Muñeco diabólico sin aguja / Pista marcas) | Ruinas → 20, Valle → 36, Choza Sabio → 40 |
| 40 | Choza del Sabio | Cinta de Moebius (1), Péndulo (7) | Sabio (Pide Esqueleto murciélago / Pista Moebius) | Ciudad Abandonada → 39 |
| 41 | Campo del Labrador | — | Labrador (Pide Muslo carnero / Filosofía) | Pico Negro → 37, Río (Cuerda) → 42 |
| 42 | Exterior Torre Cristal | — | — | Río (Cuerda) → 41, Calabozos → 46, Escalera caracol → 43 |
| 43 | Punta Torre Cristal | Tablilla de madera (18) | — | Torre → 42, Puerta ("Aura Srka") → 44 |
| 44 | Alcoba de la Hija | Cuadros de muchachas | — | Torre → 43, Puerta Secreta (Romper carta) → 45 |
| 45 | Alcoba Secreta | Cáliz (con cifrado horante) | Hija del Hechicero (Serpiente 3 cabezas; muere con Aguja) | Puerta Secreta → 44 |
| 46 | Los Calabozos | — | Carcelero (Abre celda con palabra "Grifo") | Torre → 42, Celda → 47, Antesala Prueba → 48 |
| 47 | Una celda | — | Encapuchado (Pide Receta / Pista 8 letras de Aura) | Reja → 46 |
| 48 | Antesala de la Prueba | Inscripción (1), Arco (4) | — | Calabozos → 46, Comedor (Arco) → 13, Salón Verde (Dejar Oro) → 49 |
| 49 | Salón Verde | — | — | Salón Azul (Dejar Plata) → 50 |
| 50 | Salón Azul | — | — | Salón Blanco (Dejar Bronce) → 51 |
| 51 | Salón Blanco | — | — | Puerta triangular (Llevar Cinta de Moebius) → 52 |
| 52 | Límites de la Fortaleza | — | Guardián (Pide Sombrero / Pista aguja contra serpiente) | Salón Blanco → 51, Puente (Grabado) → 53 |
| 53 | Pirámide del Hechicero | — | — | Puente → 52, Columna de Hielo (Antorcha) → 54 |
| 54 | Habitaciones Hechicero | Miles de espadas | Hechicero (Pide Marmidosa / Revelación final) | Pirámide → 53 |
