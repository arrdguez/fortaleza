# La Fortaleza 1 — Documento para desarrolladores

## 1. Ficha
- **Original:** *La Fortaleza* (1990), Manuel Cepero, Cuba. Aventura conversacional en español para MS-DOS.
- **Binario:** `fortaleza1/original/FORT1.EXE` (42 887 B). Compilado con **Turbo Pascal 6** (`(c) 1983,90 Borland`) y **comprimido con un empaquetador EXE** (los textos aparecen fragmentados → hay que desempaquetar para extraerlos íntegros).
- **Port:** C++17, terminal ANSI, `fortaleza1/src/` (~2 200 líneas). Compila con `make` dentro de `src/`.

## 2. Premisa
Una fortaleza negra **es** una Bestia viva. El jugador entra, recoge pistas de criaturas y debe destruir sus **cuatro centros vitales**: Pulmones, Estómago, Corazón y Cerebro. Tono: surrealista, borgiano, con anacronismos y guiños (Hitchcock, Kafka, Ariadna, Rumpelstiltskin, "Los 39 escalones").

## 3. Arquitectura del port

| Archivo | Responsabilidad |
|---|---|
| `Types.h` | Modelo de datos: `Verb`, `Item`, `Door`, `Creature`, `Room`, `ParsedCommand` |
| `WorldData.cpp/.h` | **Todo el contenido**: 32 salas, textos, manual, créditos (datos *hardcoded*) |
| `Parser.cpp/.h` | Normaliza (acentos UTF‑8/CP437, comentarios `{}`), quita artículos, detecta verbo y conectores `a / con / diciendo / respondiendo` |
| `Game.cpp/.h` | Bucle, un `handleX` por verbo, estado de los 4 órganos, guardado/reproducción de rastro |
| `TerminalUI.cpp/.h` | Menú, cabecera, colores, paginación del manual |
| `main.cpp` | CLI: `--plain`, `--help`, `fortaleza1 <rastro>` |

### Modelo de datos
- **Item:** nombre, descripción, peso (en "bolsas"), `can_pick_up`. (`is_container`/`hidden_item` existen pero **no se usan**.)
- **Door ("unión"):** destino, abierta/cerrada, `required_key` (objeto **o** palabra), acertijo, `required_item_to_cross` (sin él → muerte).
- **Creature:** `requested_item` → `reward` (pista); `lethal_weapon` → `dying_confession`.

### Verbos
`ir/atravesar/cruzar/entrar`, `mirar/ver/leer`, `coger/tomar`, `soltar/dejar (todo)`, `matar … con`, `romper/forzar … con`, `dar … a`, `interrogar`, `abrir … diciendo|respondiendo|con`, `comer`, `beber`, `inventario`, `salvar`, `ejecutar`, `ayuda`, `terminar`. Si la primera palabra no es verbo se interpreta como `ir <texto>`.

### Sistema de "rastro"
Fichero de texto con un comando por línea (cabecera en comentario Pascal `{ … }`). `ejecutar` reinicia el mundo y reproduce. Ejemplo: `fortaleza1/rastros/pruebadesalva`.

## 4. Mecánicas clave
1. **Peso:** máximo 40 bolsas.
2. **Trueque de pistas:** dar el objeto pedido → la criatura revela una pista.
3. **Uniones protegidas:** escaparate (candelabro), pulmones (talismán), estómago (pastel), corazón (corazón de unicornio).
4. **Acertijos:** escalera = "treinta y nueve"; puerta dorada = alfabeto sin las letras de B‑E‑S‑T‑I‑A → `cdfghjklmnopqruvwxyz` (fragmento `jklvopqruvwxy` visible en `FORT1.EXE`, confirma el acertijo original).
5. **Muertes:** caer sin candelabro, órganos sin protección, celda 25.
6. **Victoria:** 4 flags `*_destruido_` en `true`.

## 5. Inconsistencias / bugs detectados (sin corregir)
| # | Problema | Dónde |
|---|---|---|
| 1 | La puerta "Boca de la Bestia" en 24 ya está **abierta** → romper la columna con Antorcha 3 es inútil | `WorldData.cpp` sala 24 |
| 2 | Las antorchas se pueden coger sin matar al Minotauro; `minotauro_muerto_` no bloquea nada | `Game.cpp` handleMatar |
| 3 | El cerebro muere con **cualquier** "antorcha" (substring match) | `Parser::matches` |
| 4 | Solo hay 1 pastel: Bruja lo pide y el estómago lo exige | salas 0, 7, 17 |
| 5 | El acertijo de la escalera no acepta "39" | sala 2 |
| 6 | Contraseña del pasillo `nombus rostomelaris` ≠ pista del anciano `imnus humiscuol rastomislakis` (¿cifrado? el campo `required_key` menciona "Caesar text") | salas 5, 14 |
| 7 | Laberinto trivial: antesala → pasillo oriental → elegidos directo | salas 27, 31 |
| 8 | Se puede matar a aliados sin arma (sin `lethal_weapon` = siempre muere) | handleMatar |
| 9 | Objetos sin uso: escoba, hilo de Ariadna, balanza, retrato, martillo, maza, vendajes, grabado, máquina del tiempo, cuadro, arco, ariete | varios |
| 10 | "Cosas que esconden cosas" (manual regla 4.2) no implementado | `Item.is_container` |
| 11 | Asimetría: puerta azul 1→3, pero 3→2 | salas 1, 3 |
| 12 | Muertes con lógica por id de sala *hardcoded* | `Game::handleIr` |

## 6. Fidelidad respecto al original ⚠️
Los textos del port parecen **reconstruidos**: el EXE está comprimido y solo se han podido ver fragmentos. Muchos detalles (columna de cristal, salas del laberinto, mensajes) podrían ser invención del port. Para "revelar todo" hace falta:
1. Identificar el empaquetador y desempaquetar `FORT1.EXE` (o volcar memoria desde DOSBox tras cargar).
2. Extraer tablas de cadenas de Turbo Pascal (strings con prefijo de longitud).
3. Contrastar sala por sala con `WorldData.cpp`.
