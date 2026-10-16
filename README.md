# Proyecto La Fortaleza (I & II)

> **Deconstrucción, Documentación Completa y Modernización en C++17**  
> Basado en las aventuras conversacionales originales creadas por **Miguel Enrique Cepero** (1990/1991), Merchise Software, Cuba.

---

## 📖 Descripción General

Este repositorio preserva, documenta y porta de forma moderna en C++17 las dos clásicas aventuras de texto de la informática cubana:

1. **La Fortaleza (1990):** 32 habitaciones interconectadas en el cuerpo y laberintos de la Bestia.
2. **La Fortaleza II: La venganza de la Bestia (1991):** 55 habitaciones, sistema de gravedad invertida, pesaje con balanza, la prueba de los anillos de los Horantes, la cinta de Möbius y el descubrimiento del engaño de la falsa hija del hechicero.

---

## 🚀 Requisitos de Compilación

Para compilar el proyecto solo se necesita un compilador moderno con soporte para **C++17**:
- **GCC (g++)** 8.0 o superior
- **Clang (clang++)** 7.0 o superior
- **MSVC** (Visual Studio 2019 o superior) en Windows
- Herramienta de compilación: **GNU Make** o **CMake** (3.12+)

En sistemas basados en Debian / Ubuntu:
```bash
sudo apt update && sudo apt install build-essential cmake
```

En macOS (con Homebrew o Xcode Command Line Tools):
```bash
xcode-select --install
```

---

## 🛠️ Cómo Descargar y Compilar

### 1. Clonar el repositorio
```bash
git clone <URL_DEL_REPOSITORIO>
cd fortaleza
```

### 2. Compilar fácilmente

#### Opción A: Usando el Makefile Principal (Recomendado en Linux / macOS)
Compila ambos juegos con un solo comando desde la raíz del proyecto:
```bash
make
```

O compila de forma independiente:
```bash
make fortaleza1   # Compila solo Fortaleza 1
make fortaleza2   # Compila solo Fortaleza 2
```

Para limpiar artefactos de compilación:
```bash
make clean
```

#### Opción B: Usando CMake (Multiplataforma: Linux / macOS / Windows)
```bash
cmake -B build
cmake --build build
```
Los binarios compilados se encontrarán en `build/bin/`.

#### Opción C: Compilación directa con g++
Si no deseas usar make ni cmake:
```bash
# Fortaleza 1:
g++ -std=c++17 -O2 fortaleza1/src/*.cpp -o fortaleza1_game

# Fortaleza 2:
g++ -std=c++17 -O2 fortaleza2/src/*.cpp -o fortaleza2_game
```

---

## 🎮 Cómo Jugar

Una vez compilado, puedes iniciar cualquiera de los juegos:

```bash
# Fortaleza 1:
./fortaleza1/src/fortaleza1
# O usando: make run1

# Fortaleza 2:
./fortaleza2/src/fortaleza2
# O usando: make run2
```

### Comandos y Vocabulario Principal
- **Moverse:** `IR <lugar/puerta>`, `ATRAVESAR <puerta>`, `CRUZAR <puente>`
- **Inspeccionar:** `MIRAR`, `VER`, `OBSERVAR <cosa>`, `LEER <inscripción/carta>`
- **Inventario y objetos:** `COGER <objeto>`, `SOLTAR <objeto>`, `INVENTARIO` (o `INV`)
- **Acciones:** `ROMPER <objeto> CON <herramienta>`, `MATAR <criatura> CON <arma>`
- **Interacción:** `PREGUNTAR <personaje>`, `DAR <objeto> A <personaje>`
- **Abrir con clave:** `ABRIR <puerta> DICIENDO <clave>` o `ABRIR <puerta> RESPONDIENDO <respuesta>`
- **Especiales Fortaleza 2:** `PESAR <objeto>` (requiere Balanza), `PORCIENTO` (progreso del juego)
- **Sistema:** `SALVAR`, `EJECUTAR` (cargar), `AYUDA`, `TERMINAR`

---

## 📂 Estructura del Repositorio

```
fortaleza/
├── Makefile                   # Makefile unificado en la raíz para compilar todo
├── CMakeLists.txt             # Configuración CMake estándar multiplataforma
├── .gitignore                 # Exclusión de binarios .exe, temporales y objetos
├── README.md                  # Esta guía de compilación y documentación
│
├── docs/                      # Documentación completa y mapas
│   ├── README.md              # Índice de documentación
│   ├── fortaleza1/
│   │   ├── MAPA.md            # Grafo Mermaid de 32 salas, tabla de objetos/criaturas
│   │   ├── DISENO.md          # Arquitectura y mecánicas
│   │   ├── SOLUCION.md        # Guía paso a paso para ganar
│   │   └── CUENTO.md          # Narrativa novelada de la victoria
│   └── fortaleza2/
│       ├── MAPA.md            # Grafo Mermaid exhaustivo de 55 salas y conexiones
│       ├── DISENO.md          # Análisis de trama, giros, acertijos y criptogramas
│       ├── ESTADO.md          # Estado de desarrollo y notas
│       └── SOLUCION.md        # Solución rápida paso a paso
│
├── fortaleza1/
│   ├── original/              # FORT1.EXE original (ignorado en git)
│   ├── unpacked/              # Cadenas extraídas (strings.tsv)
│   ├── rastros/               # Rastros y pruebas de comandos
│   └── src/                   # Código fuente C++17 y Makefile local
│
├── fortaleza2/
│   ├── original/              # FORT2.EXE original (ignorado en git)
│   ├── unpacked/              # Cadenas y JSON de salas y entidades
│   └── src/                   # Código fuente C++17 y Makefile local
│
└── tools/
    ├── unlzexe.py             # Desempaquetador de ejecutables DOS LZEXE 0.91
    └── tpstrings.py           # Extractor de cadenas Turbo Pascal CP437
```

---

## 📜 Créditos y Autoría
- **Autor original:** Miguel Enrique Cepero (Merchise Software, Cuba, 1990–1991).
- **Editor de comandos original:** Jorge Romero (*vac-ace*).
- **Deconstrucción, ingeniería inversa y port C++17 (2026):** Proyecto de preservación cultural y modernización de ficción interactiva.
