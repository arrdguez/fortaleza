# La Fortaleza 2: La venganza de la Bestia — Documento de Diseño

## 1. Ficha Técnica
- **Título Original:** *La Fortaleza II: La venganza de la Bestia*
- **Autor:** Miguel Enrique Cepero (1990/1991), La Habana / Villa Clara, Cuba.
- **Grupo:** Merchise Software ("que no se dedica a hacer jueguitos solamente").
- **Cita Introductoria:** *"En la lucha entre tú y el mundo, ve de parte del mundo."* — Franz Kafka.
- **Motor Original:** Turbo Pascal 6.0 Orientado a Objetos (MS-DOS), empaquetado con LZEXE 0.91 (*FAB*).
- **Alcance del mundo:** 55 habitaciones, 54 objetos, 16 criaturas, 80 uniones.

---

## 2. Premisa Narrativa y Giro Dramático

Al final de *La Fortaleza 1*, el jugador creyó haber derrotado a la Bestia quemando su cerebro. 
Sin embargo, la muerte de la Bestia activó su trampa definitiva: **la venganza de la Bestia**.
La Fortaleza entera se disolvió en un caldo primordial y se reconstituyó. El jugador despierta atrapado de nuevo, sin memoria del tiempo transcurrido, y su misión ahora no es matar, sino **escapar con vida al exterior**.

### El Gran Giro (The Plot Twist)
A lo largo de la travesía, el jugador encuentra notas de auxilio supuestamente escritas por la "Hija del Hechicero" pidiéndole que la rescate de su padre tirano y le lleve la espada legendaria *Marmidosa* para matarlo.
Sin embargo:
1. **La Hija del Hechicero es en realidad un monstruo diabólico:** una serpiente gigante de tres cabezas y 15 metros oculta en la alcoba secreta de la Torre de Cristal. Su verdadero nombre completo es **Aura Srka** (revelado por pistas del camello y el encapuchado de 7 dedos).
2. **El Hechicero no es el enemigo:** Es el último gran guardián y protector de la sabiduría de los *Horantes*, la civilización ancestral que construyó la Fortaleza antes de la llegada de la Bestia.
3. **El verdadero enemigo fue la manipulación:** El Hechicero le revela la verdad: *"No soy tu enemigo. Es mi hija quien ha elaborado este diabólico plan para eliminarnos. Rompe la carta que te dejó en la Torre de Cristal y ocurrirá un milagro."*

---

## 3. Descifrado de Criptogramas Originales

### 3.1. El Cifrado del Cáliz (Las Marcas de los Horantes)
Grabado en el Cáliz dejado tras matar a la serpiente:
```text
Lsmra elshrne o:
Rs imnee od e ao
Bt ecrnee aoil pet
Atrh ne urod usee
E nloeeiojnoa bn
Ecd eaulse acua elshrne
Epj el iadlhcieoe ucat
Pnuoe lslnd ua
```
Descifrado mediante transposición en columnas:
> **"Las marcas de los horantes son:  
>  Rosa diamante en...  
>  Bote...  
>  Antorcha en...  
>  Escudo de Aquiles...  
>  Espejo...  
>  Péndulo..."**

### 3.2. El Cifrado de la Tablilla de Madera (Punta de la Torre de Cristal)
```text
"A acsd o oatssn
 Oadaat lfnodllg
 Oed aot nl rlaousa
 Nocae lcat ehépds
 Lail lgd ut léao
 Suod qie nl iddd o oats
 Seod ahj e ehcr ns uro
 Edl ne aó efmr"
```
Reordenando los caracteres por columnas se obtiene el texto que instruye cómo resolver el acertijo de la puerta de la Hija y el secreto de los anillos.

---

## 4. Mecánicas Clave del Motor de Fortaleza 2

1. **La Balanza y el Sistema de Pesaje:**
   - La Balanza tiene plato en forma de mano con aguja de bigotes de gato.
   - Permite pesar objetos usando el comando `pesar [objeto]` (1 bolsa = octava parte de un tubo de luz fría de agua).
2. **La Escalera No-Euclidiana (Terrazas):**
   - Una misma escalera sirve de origen y destino simultáneo para las Terrazas (7), el Calabozo del Monstruo (8) y el Río Negro (10).
3. **El Salto de la Catarata y el Saltador:**
   - Para descender del Pico Negro sin morir se necesita el **Saltador** (muelle que rebota al tercer día de caída).
   - Para lanzarse por las Cataratas al Lago se puede respirar bajo el agua gracias a asociaciones fetales/embrionarias subconscientes.
4. **La Prueba de los Anillos de los Horantes:**
   - La Fortaleza pone a prueba el espíritu del jugador con 4 salones:
     - Salón Verde: se debe soltar el **Anillo de oro**.
     - Salón Azul: se debe soltar el **Anillo de plata**.
     - Salón Blanco: se debe soltar el **Anillo de bronce**.
     - Puerta triangular: solo permite el paso a quien conserve la **Cinta de Moebius** (el anillo no orientable de una sola cara).
5. **Combate con Armas Específicas:**
   - Grifo: muere con la **Daga**.
   - Ogro: muere quemado al lanzarle el **Cubo de agua**.
   - Hija del Hechicero (Serpiente): muere ensartada con la **Aguja de plata**.
6. **El Epílogo Existencial:**
   - Al salir al exterior, el jugador se sienta en una piedra al borde de una carretera moderna. Comprende que la verdadera venganza de la Bestia fue desterrarlo a la civilización y dejarlo vivir sin la magia y la eternidad de la Fortaleza.
