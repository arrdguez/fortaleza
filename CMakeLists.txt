cmake_minimum_required(VERSION 3.12)
project(LaFortaleza VERSION 2.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Opciones de compilación
if(MSVC)
    add_compile_options(/W4 /utf-8)
else()
    add_compile_options(-Wall -Wextra -O2)
endif()

# Directorio de salida común para binarios
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# ==============================================================================
# La Fortaleza 1
# ==============================================================================
set(F1_SOURCES
    fortaleza1/src/main.cpp
    fortaleza1/src/Game.cpp
    fortaleza1/src/Parser.cpp
    fortaleza1/src/WorldData.cpp
    fortaleza1/src/TerminalUI.cpp
)
add_executable(fortaleza1 ${F1_SOURCES})
target_include_directories(fortaleza1 PRIVATE fortaleza1/src)

# ==============================================================================
# La Fortaleza 2: La venganza de la Bestia
# ==============================================================================
set(F2_SOURCES
    fortaleza2/src/main.cpp
    fortaleza2/src/Game.cpp
    fortaleza2/src/Parser.cpp
    fortaleza2/src/WorldData.cpp
    fortaleza2/src/TerminalUI.cpp
)
add_executable(fortaleza2 ${F2_SOURCES})
target_include_directories(fortaleza2 PRIVATE fortaleza2/src)
