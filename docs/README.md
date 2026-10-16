# Proyecto Fortaleza — Deconstrucción y Modernización

Objetivo: extraer por completo *La Fortaleza 1* (1990) y *La Fortaleza 2: La venganza de la Bestia* (1991) de Miguel Enrique Cepero (Merchise Software, Cuba), documentarlas al detalle y sentar las bases para una **narrativa nueva**.

---

## Estructura del Repositorio

```
fortaleza/
├── docs/
│   ├── README.md                  # Este índice
│   ├── fortaleza1/
│   │   ├── MAPA.md                # Grafo de 32 salas, tabla de objetos/criaturas
│   │   ├── DISENO.md              # Análisis de arquitectura y mecánicas
│   │   ├── SOLUCION.md            # Guía rápida paso a paso para ganar
│   │   └── CUENTO.md              # Narrativa literaria de la victoria
│   └── fortaleza2/
│       ├── MAPA.md                # Grafo exhaustivo de las 55 salas extraídas
│       ├── DISENO.md              # Análisis de diseño, trama, giros y criptogramas
│       └── SOLUCION.md            # Guía paso a paso para vencer Fortaleza 2
│
├── tools/
│   ├── unlzexe.py                 # Desempaquetador LZEXE 0.91 (*FAB*)
│   └── tpstrings.py               # Extractor de cadenas Turbo Pascal CP437
│
├── fortaleza1/
│   ├── original/FORT1.EXE         # Binario DOS original (42 KB)
│   ├── unpacked/                  # FORT1_U.EXE descomprimido (124 KB) y strings
│   ├── rastros/pruebadesalva      # Rastro de prueba de comandos
│   └── src/                       # Port moderno C++17 de Fortaleza 1
│
└── fortaleza2/
    ├── original/FORT2.EXE         # Binario DOS original (52 KB)
    ├── unpacked/                  # FORT2_U.EXE descomprimido (133 KB) y world_data_clean.json
    └── src/                       # Port moderno C++17 de Fortaleza 2 (¡compilado y jugable!)
```

---

## Tabla Comparativa de Estado

| Aspecto | La Fortaleza 1 | La Fortaleza 2: La venganza de la Bestia |
|---|---|---|
| **Año / Autor** | 1990 (Manuel Cepero) | 1991 (Miguel E. Cepero / Merchise) |
| **Binario DOS Original** | ✅ `FORT1.EXE` | ✅ `FORT2.EXE` |
| **Desempaquetado** | ✅ `FORT1_U.EXE` | ✅ `FORT2_U.EXE` |
| **Extracción de Datos** | ✅ Cadenas y tablas | ✅ 55 salas, 199 entidades desensambladas |
| **Documentación Técnica** | ✅ `MAPA.md`, `DISENO.md`, `SOLUCION.md` | ✅ `MAPA.md`, `DISENO.md`, `SOLUCION.md` |
| **Port Moderno C++17** | ✅ `fortaleza1/src/fortaleza1` | ✅ `fortaleza2/src/fortaleza2` |
| **Mecánicas Clave** | 4 centros vitales, 40 bolsas peso | Balanza/pesaje, Gravedad invertida, Moebius, Cifrados Horantes |

---

## Compilación y Ejecución

Para compilar cualquiera de los dos juegos:
```bash
# Fortaleza 1:
cd fortaleza1/src && make
./fortaleza1

# Fortaleza 2:
cd fortaleza2/src && make
./fortaleza2
```
