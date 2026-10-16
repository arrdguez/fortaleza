# ==============================================================================
# Makefile Principal - Proyecto La Fortaleza (1 & 2)
# ==============================================================================

CXX ?= g++
CXXFLAGS ?= -std=c++17 -Wall -Wextra -O2

.PHONY: all fortaleza1 fortaleza2 clean run1 run2 help

# Meta por defecto: compilar ambos juegos
all: fortaleza1 fortaleza2
	@echo "============================================================"
	@echo " Compilación completada con éxito."
	@echo " Ejecutables listos:"
	@echo "   - Fortaleza 1: ./fortaleza1/src/fortaleza1  (o 'make run1')"
	@echo "   - Fortaleza 2: ./fortaleza2/src/fortaleza2  (o 'make run2')"
	@echo "============================================================"

fortaleza1:
	@echo "--> Compilando La Fortaleza 1..."
	$(MAKE) -C fortaleza1/src

fortaleza2:
	@echo "--> Compilando La Fortaleza 2: La venganza de la Bestia..."
	$(MAKE) -C fortaleza2/src

clean:
	@echo "--> Limpiando binarios y archivos objeto..."
	$(MAKE) -C fortaleza1/src clean
	$(MAKE) -C fortaleza2/src clean
	rm -rf bin build

run1: fortaleza1
	./fortaleza1/src/fortaleza1

run2: fortaleza2
	./fortaleza2/src/fortaleza2

help:
	@echo "Uso del Makefile:"
	@echo "  make              - Compila Fortaleza 1 y Fortaleza 2"
	@echo "  make fortaleza1   - Compila únicamente Fortaleza 1"
	@echo "  make fortaleza2   - Compila únicamente Fortaleza 2"
	@echo "  make clean        - Elimina ejecutables y archivos objeto"
	@echo "  make run1         - Compila y ejecuta Fortaleza 1"
	@echo "  make run2         - Compila y ejecuta Fortaleza 2"
