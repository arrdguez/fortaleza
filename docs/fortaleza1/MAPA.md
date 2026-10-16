# La Fortaleza 1 — Mapa (según el port C++)

> Fuente: `fortaleza1/src/WorldData.cpp`. 32 habitaciones (ids 0–31).
> **Ojo:** este mapa describe el *port*, no está verificado 1:1 contra `FORT1.EXE` (ver `DISENO.md` §6).

## Leyenda
- `-->` paso abierto · `==>` paso que requiere algo (clave/acertijo/objeto) · `x` muerte
- 🔑 clave o palabra · ❓ acertijo · 🛡 objeto obligatorio para cruzar (si no, muerte)

## Grafo

```mermaid
flowchart TD
    R0["0 Exterior"]
    R1["1 Salón de recepciones"]
    R2["2 Sala de juegos"]
    R3["3 Patio interior"]
    R4["4 Cuarto de espejos"]
    R5["5 Biblioteca"]
    R6["6 Pasillo"]
    R7["7 Alcoba de la bruja"]
    R8["8 Cuarto del guerrero"]
    R9["9 Laboratorio"]
    R10["10 Sala de armas"]
    R11["11 Baños de la Bestia"]
    R12["12 Jardín (hub)"]
    R13["13 Alcoba de la doncella"]
    R14["14 Sala de infusiones"]
    R15["15 Calabozos"]
    R16["16 Boca de la Bestia"]
    R17["17 Interior de la Bestia"]
    R18["18 PULMONES"]
    R19["19 ESTÓMAGO"]
    R20["20 CORAZÓN"]
    R21["21 CEREBRO"]
    R22["22 Almacenes"]
    R23["23 Páramo"]
    R24["24 Salón de cristal"]
    R25["25 Celda (trampa)"]
    R26["26 Puente de mármol"]
    R27["27 Antesala del Laberinto"]
    R28["28 Cueva del Minotauro"]
    R29["29 Salón de los elegidos"]
    R30["30 Pasillo laberinto A"]
    R31["31 Pasillo laberinto B"]

    R0 ==>|"🔑 abrete sesamo"| R1
    R1 --> R0
    R0 <--> R26
    R1 <--> R2
    R1 -->|"puerta azul"| R3
    R2 <--> R3
    R2 ==>|"❓ treinta y nueve"| R4
    R4 --> R2
    R4 ==>|"🔑 hueso de gato (romper espejo)"| R13
    R13 --> R4
    R3 <--> R5
    R5 ==>|"🔑 nombus rostomelaris"| R6
    R6 --> R5
    R5 -->|"libro"| R12
    R6 <--> R7
    R6 <--> R8
    R6 <--> R9
    R6 <--> R14
    R7 ==>|"🛡 candelabro (escaparate)"| R13
    R8 ==>|"🔑 hacha (puerta blindada)"| R10
    R10 --> R8
    R11 <--> R12
    R12 <--> R13
    R12 <--> R14
    R12 <--> R15
    R12 <--> R22
    R26 <--> R23
    R26 <--> R27
    R23 ==>|"🔑 agua"| R24
    R24 --> R23
    R24 <--> R16
    R16 <--> R17
    R17 ==>|"🛡 talisman de aire"| R18
    R17 ==>|"🛡 pastel de cerezas"| R19
    R17 ==>|"🛡 corazon de unicornio"| R20
    R18 --> R17
    R19 --> R17
    R20 --> R17
    R27 <--> R28
    R27 <--> R30
    R27 <--> R31
    R30 <--> R31
    R30 -->|"puerta derecha (tela)"| R25
    R31 <--> R29
    R29 ==>|"❓ cdfghjklmnopqruvwxyz"| R21
    R21 --> R29
```

## Tabla de habitaciones

| id | Lugar | Objetos (peso) | Criaturas → pide / da |
|---|---|---|---|
| 0 | Exterior | Roble(fijo), Maza 39, Pastel de cerezas 2 | Llamador de bronce → cigarro / "Rumpelstinskin" |
| 1 | Salón de recepciones | Retrato 1 | Mendigo → vaso de agua / pista doncella-espejo |
| 2 | Sala de juegos | Escoba 1, Inscripción(fija), Hilo de Ariadna 1 | — |
| 3 | Patio interior | Balanza 5 | Atenea → lanza / pista talismán · Arpía → paraguas / pista libro |
| 4 | Cuarto de espejos | Hueso de gato 1 | — |
| 5 | Biblioteca | Vaso de agua 1, Candelabro 1 | — |
| 6 | Pasillo | Antorcha 1 | — |
| 7 | Alcoba de la bruja | Polvo mágico 1, Poción para crecer 5 | Bruja → pastel / pista "Prohibido → luz" |
| 8 | Cuarto del guerrero | Vendajes 3, Grabado 3 | — |
| 9 | Laboratorio | Piedra filosofal 10, Máquina del tiempo 3 | Homúnculo → poción / pista candelabro |
| 10 | Sala de armas | Espada 5, Lanza 10, Arco 5, Daga 3, Ariete(fijo), Látigo 2 | — |
| 11 | Baños | Rosa 1, Inscripción 2, Espejo(fijo) | Troll → polvo mágico / pista unicornio |
| 12 | Jardín | Inscripción 1, Cedro(fijo) | — |
| 13 | Alcoba de la doncella | Cuadro 10, Corazón de unicornio 1 | Doncella → rosa / pista alfabeto |
| 14 | Sala de infusiones | Taza de café 1, Cigarro 1 | Anciano → café / pista espada+látigo |
| 15 | Calabozos | Paraguas 2, Talismán de aire 1 | Prisionero → vaso de agua / pista pastel |
| 16 | Boca de la Bestia | — | — |
| 17 | Interior de la Bestia | Inscripción(fija) | — |
| 18 | Pulmones | — | Centro pulmones (muere con **espada**) |
| 19 | Estómago | — | Centro estómago (muere con **látigo**) |
| 20 | Corazón | — | Centro corazón (muere con **daga**) |
| 21 | Cerebro | — | Centro cerebro (muere con **antorcha**) |
| 22 | Almacenes | Hacha 10 | Verdugo → piedra filosofal / pista "agua" |
| 23 | Páramo | — | — |
| 24 | Salón de cristal | Columna de cristal(fija) | — |
| 25 | Celda pequeña | Inscripción(fija) | **Trampa: fin de partida** |
| 26 | Puente de mármol | Martillo 2 | — |
| 27 | Antesala del Laberinto | — | — |
| 28 | Cueva del Minotauro | Antorcha 1…7 (2 c/u) | Minotauro (muere con espada) |
| 29 | Salón de los elegidos | — | — |
| 30–31 | Pasillos del Laberinto | — | — |

Capacidad de carga: **40 bolsas**.

## Ruta mínima de victoria (port actual)

1. `abrir puerta principal diciendo abrete sesamo` → 1 → 3 → 5 → `ir libro` → 12 (Jardín)
2. 22: `coger hacha` · 15: `coger talisman` · 13: `coger corazon de unicornio`
3. 14 → 6: `coger antorcha` → 8: `romper puerta con hacha` → 10: `coger espada`, `daga`, `latigo`
4. Volver a 0: `coger pastel` → 26 → 23: `abrir puerta de agua diciendo agua` → 24 → 16 → 17
5. 18/19/20: `matar centro con espada|latigo|daga`
6. 16 → 24 → 23 → 26 → 27 → 31 → 29: `abrir puerta dorada respondiendo cdfghjklmnopqruvwxyz`
7. 21: `matar centro del cerebro con antorcha` → **victoria**
