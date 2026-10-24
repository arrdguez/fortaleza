# Proyecto: Fortaleza Mecánica — Aventura Textual / Ficción Interactiva
> **Game Design Document (GDD) — Solo Developer Edition**  
> *Una aventura conversacional / RPG de texto interactivo inspirada en el misterio de La Fortaleza y la atmósfera melancólica de hojalata y acertijos de Machinarium.*

---

## 🎯 1. La Visión: El Poder del Texto y la Ficción Interactiva

Ser un solo desarrollador y no querer lidiar con arte gráfico complejo **no es una limitación, es una ventaja competitiva**. El texto permite una libertad creativa infinita: describir escenarios colosales, criaturas biomecánicas gigantescas y mecanismos imposibles sin gastar un centavo ni un minuto en modelado 3D o animación.

### Éxitos del Género en Steam y Móviles:
- **Roadwarden:** Uno de los juegos más aclamados de Steam (96% positivo). Es pura prosa evocativa, mapa ilustrado minimalista y acertijos lógicos.
- **A Dark Room:** Millones de descargas en PC y móviles con interfaz puramente textual y minimalista.
- **80 Days / Sorcery! (Inkle):** Aventuras de texto con decisiones, inventario y exploración no lineal.
- **La Fortaleza (I y II):** Las obras maestras originales de 1990/1991 que demostraron que solo con palabras y buenas mecánicas se puede atrapar al jugador.

---

## 💡 2. Cómo se traduce "Machinarium" a un Juego de Texto

No necesitas dibujar a los robots ni animar el óxido; la esencia de *Machinarium* vive en el **tono y los acertijos**:
1. **La Atmósfera:** Prosa descriptiva centrada en lo sensorial: el chirrido de los engranajes secos, el olor a aceite caliente y moho de cobre, la melancolía de autómatas viejos abandonados que siguen cumpliendo su tarea en bucle.
2. **Los Acertijos de Entorno:** Problemas mecánicos tangibles descritos con claridad: *"Hay tres palancas conectadas por una cadena oxidada... la válvula central silba expulsando vapor presurizado..."*
3. **El Toque Cómico/Tierno:** Pequeños detalles humanos en máquinas: un robot barrendero que se queja en pitidos de los tornillos que caen del techo, un autómata que juega al ajedrez con tuercas.

---

## 🗺️ 3. El "Mundo Abierto" en Ficción Interactiva

En un juego de texto, un **mundo abierto** es sumamente fácil y gratificante de construir:
- El mundo es un **grafo de lugares/salas interconectadas** (como un mapa de 50 a 100 nodos).
- El jugador puede moverse libremente entre nodos cardinales (`NORTE`, `SUR`, `SUBIR`, `ENTRAR`) o mediante un mapa interactivo con hipervínculos de texto.
- No hay pasillos vacíos: cada nodo tiene una descripción rica, objetos que examinar y secretos que descubrir.
- Tienes libertad total de ir a explorar el Sector de Vapor o bajar a la Fosa de Aceite en el orden que prefieras.

---

## 📱💻 4. Por qué es perfecto para Steam y Android

1. **Desarrollo 100% alcanzable para un solo creador:** Puedes escribirlo a tu ritmo. Tu única herramienta es tu imaginación y un procesador de texto / markdown.
2. **Cero problemas de rendimiento:** Pesa menos de 50 MB, arranca instantáneo en cualquier teléfono Android y en cualquier PC.
3. **Multiplataforma sin esfuerzo:** Si se implementa como texto interactivo (por ejemplo con interfaces limpias basadas en texto, markdown o Web/Godot UI minimalista), compilar para Android y Steam es casi automático.
