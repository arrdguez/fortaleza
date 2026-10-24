# Juego 1: La Fortaleza de Hojalata (Diseño y Guión Jugable)
> **Enfoque:** Simple, directo, aventura conversacional/interactiva estilo *La Fortaleza* clásica + acertijos de lógica, ingenio y mecanismos táctiles estilo *Machinarium*.  
> **Cero complicaciones académicas:** Pura observación, inventario, combinaciones ingeniosas y exploración de salas.

---

## 🤖 1. El Protagonista y sus Acciones

- **Nombre:** **Pip** (un pequeño robot de latón con ojos redondos de bombilla).
- **Cuerpo:** 
  - Su torso es de fuelle: **puede estirarse hacia arriba** para alcanzar cosas altas o **encogerse** para meterse por conductos estrechos.
  - Abre una compuerta en su barriga para guardar objetos en su inventario.
- **Cómo se Mueve y Juega:**
  - El juego describe la sala actual en texto evocador.
  - El jugador tiene acciones simples (ya sea escribiendo comandos como en *La Fortaleza* o tocando botones en pantalla):
    - `MIRAR [cosa]`
    - `COGER [objeto]`
    - `USAR [objeto] EN [mecanismo]`
    - `ESTIRARSE` / `ENCOGERSE`
    - `IR [NORTE / SUR / ESTE / OESTE / ARRIBA / ABAJO]`

---

## 🗺️ 2. El Prólogo / Primer Escenario: Las Entrañas Inferiores

```
           [ 03. La Cámara del Gran Engranaje ]
                            ▲
                            │ (Subir por la cadena)
           [ 02. El Conducto de Drenaje ]
                            ▲
                            │ (Atravesar rejilla)
           [ 01. La Fosa de Chatarra (Inicio) ]
```

---

### 📍 SALA 01: La Fosa de Chatarra (El Despertar)

**Descripción en pantalla:**
> *"Abres tus ojos de bombilla tras un parpadeo amarillo. Estás en el fondo de un foso húmedo, enterrado hasta la cintura en tuercas partidas y virutas de metal. Sobre ti, a unos tres metros de altura, cuelga una pasarela de hierro con una compuerta cerrada. El aire huele a grasa vieja y moho. Gotas de aceite caen rítmicamente desde el techo: plic... plic..."*

**Cosas visibles en la sala:**
1. **Un montón de chatarra:** Si lo registras, encuentras un **imán oxidado atado a un hilo de cobre**.
2. **Un viejo autómata desactivado:** Le falta una pierna y tiene una llave inglesa trabada en su espalda.
3. **Una tubería rota en la pared:** Gotea aceite espeso.
4. **Una palanca alta en la pared:** Está demasiado alta para alcanzarla de pie normal.

**Los Acertijos de Ingenio (Estilo Machinarium):**
- **Acertijo 1 (Alcanzar la palanca):**
  - Si intentas tirar de la palanca: *"Tus bracitos no llegan, te faltan dos cuartas"*.
  - *Solución:* Usas la acción `ESTIRARSE`. Pip alarga su cuello y torso telescópico como un acordeón y tira de la palanca. 
  - *Efecto:* La compuerta superior chirría, pero una rejilla de desagüe al ras del suelo se abre con un chasquido.
- **Acertijo 2 (El autómata y la llave inglesa):**
  - La llave inglesa está encajada y oxidada. Si tiras con las manos resbala.
  - *Solución:* Tomas una lata vacía del suelo, la llenas con las gotas de aceite de la tubería (`USAR LATA EN GOTERA`) y viertes el aceite en la espalda del robot. La llave se desliza suavemente a tu inventario.
- **Salir de la sala:** Usas la acción `ENCOGERSE` para entrar por la pequeña rejilla de desagüe abierta a ras de suelo hacia el Norte.

---

### 📍 SALA 02: El Conducto de Drenaje

**Descripción en pantalla:**
> *"Un túnel cilíndrico de chapa remachada. El suelo está inclinado y cubierto de agua fangosa. Frente a ti gira un ventilador de extracción con tres aspas afiladas que bloquea el paso hacia adelante. A un lado, hay un panel de fusibles con una tapa trabada por tres pernos."*

**Cosas visibles en la sala:**
1. **El ventilador gigante:** Gira a toda velocidad, impidiendo cruzar.
2. **El panel de fusibles:** Tiene tres pernos hexagonales.
3. **El agua fangosa:** En el fondo brilla algo metálico, pero el agua está electrificada por un cable pelado.

**Los Acertijos de Ingenio:**
- **Acertijo 1 (Desconectar la corriente del agua):**
  - El cable pelado cuelga de una abrazadera suelta.
  - Usas el **imán con hilo de cobre** para enganchar el cable desde lejos y pegarlo a una placa de tierra aislada. El agua deja de chispear.
  - Ahora coges del fondo del agua una **palanca de manivela**.
- **Acertijo 2 (Detener el ventilador):**
  - Con la **llave inglesa** desatornillas los pernos del panel.
  - Adentro hay un puzzle de 3 engranajes desalineados. Colocas la manivela y giras los engranajes hasta que las marcas rojas coincidan.
  - El ventilador se frena en seco con un crujido de vapor.
- **Salir de la sala:** Pasas entre las aspas quietas del ventilador hacia el Norte.

---

### 📍 SALA 03: La Cámara del Gran Engranaje (El Acceso a la Fortaleza)

**Descripción en pantalla:**
> *"Llegas a una caverna monumental dentro de la Bestia. Un engranaje de bronce del tamaño de un edificio gira lentamente en el centro, movido por un pistón hidráulico. Al otro lado del abismo se ve una puerta dorada con el símbolo de un sol dormido. Una pesada cadena de eslabones cuelga oscilando sobre el vacío."*

**Personaje / Encuentro:**
- Sentado al borde del abismo hay un **autómata barrendero** con una escoba de alambre. Está triste porque se le cayó su aceitera al fondo del abismo y sus articulaciones chirrían horriblemente.
- Si le hablas: Emite pitidos agudos y señala su codo atascado.
- Si le ofreces la lata con aceite sobrante: Da saltitos de alegría, te abraza y te entrega un **gancho de agarre** que tenía en su escoba.

**Acertijo:**
- Combinas el **gancho** con la **cuerda** de tu inventario.
- Esperas a que el brazo del pistón baje, lanzas el gancho para aferrarte a la cadena gigante y te dejas llevar al otro lado del abismo hacia la puerta dorada.

---

## 🎮 3. Por qué este formato funciona al 100%:

1. **Es idéntico al espíritu de La Fortaleza:** Salas, descripciones, objetos clásicos (aceite, llaves, cuerdas, engranajes, compuertas).
2. **Tiene la magia y ternura de Machinarium:** El robot que se estira y encoge, el barrendero triste que ayudas con aceite, puzles visuales y físicos comprensibles al instante sin estudiar fórmulas de física.
3. **Extremadamente fácil de programar para ti solo:** Son estados de texto, inventario y opciones (`[Estirarse]`, `[Usar llave inglesa]`, `[Hablar con el barrendero]`).
