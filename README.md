# 💕 Amor? Depende de ti

> *Un juego de novela visual donde cada decision define el rumbo de una historia de amor adolescente.*

---

## 📝 Descripcion del Proyecto

**Amor? Depende de ti** es una novela visual desarrollada en C++ con SFML 3, donde el jugador vive una historia romantica a traves de 10 eventos clave. Cada decision tomada acumula puntos que determinan uno de los **finales posibles**, reflejando el tipo de relacion que construiste a lo largo del juego.

---

## 🎯 Objetivo del Juego

Vivir una historia de amor adolescente tomando decisiones en 10 momentos clave de la relacion. Cada eleccion suma puntos en secreto, y el tipo de relacion que el jugador construye con el tiempo determina cual de los finales disponibles obtiene al terminar el juego.

---

## 🎮 Controles

* **Clic izquierdo:** Seleccionar una opcion de dialogo
* **Boton "Pausa" o ESC:** Pausar el juego
* **Boton "< Volver":** Regresar al evento anterior y cambiar tu decision
* **Clic / Enter:** Continuar o cerrar pantallas

---

## ⚙️ Mecanicas

1. El jugador ingresa su nombre y el de su interes romantico
2. Elige su genero (Hombre / Mujer), lo cual determina que imagenes se muestran a lo largo del juego
3. En cada uno de los 10 eventos, debe elegir entre 3 opciones de dialogo
4. Cada opcion otorga una cantidad distinta de puntos de forma oculta para el jugador
5. Al completar los 10 eventos, el puntaje total (y el numero de opciones "Psicopata" elegidas) determina el final que se desbloquea
6. El jugador puede pausar en cualquier momento o regresar al evento anterior si se equivoca

---

## 🏆 Caracteristicas

* **10 eventos narrativos** con ilustraciones unicas para cada decision de genero
* **3 finales completamente diferentes:**
  1. **Final Romantico:** Logran superar las adversidades con madurez y terminan siendo felices juntos
  2. **Final de Costumbre:** El amor se apaga; se quedan juntos unicamente por rutina, miedo a la soledad y comodidad
  3. **Final Tragico:** El desenlace mas oscuro, donde la obsesion y la conducta toxica consumen la relacion
* **Sistema de pausa y retroceso** para cambiar decisiones pasadas
* **Barra de progreso** que indica el avance a traves de los 10 eventos
* **Musica de piano original** que acompana la experiencia
* **Pantalla de creditos** al finalizar la historia

---

## 👥 Equipo

* **Integrante 1:** Ximena Carolina Gonzalez Atienzo
* **Integrante 2:** Ana Sofia Rodriguez Sanchez

---

## 🛠️ Tecnologias

* **Motor/Framework:** SFML 3.0 (Simple and Fast Multimedia Library)
* **Lenguaje:** C++17
* **Build system:** CMake 3.10+
* **Compilador:** MinGW-w64 (GCC 15.2)
* **Plataforma:** Windows (MSYS2 / MinGW64)

---

## ⚙️ Compilacion (Windows con MSYS2)

### Requisitos previos

1. Instalar [MSYS2](https://www.msys2.org/)
2. Abrir **MSYS2 MINGW64** e instalar dependencias:

```bash
pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-cmake mingw-w64-x86_64-sfml
```

### Compilar el proyecto

```bash
cd "C:/ruta/a/AmorDependeDeTi"
mkdir build
cd build
cmake .. -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release
mingw32-make
```

El ejecutable se genera en `build/bin/amor_depende_de_ti.exe`.

### Copiar DLLs necesarias

```bash
cp /mingw64/bin/libsfml-graphics-3.dll /mingw64/bin/libsfml-window-3.dll \
   /mingw64/bin/libsfml-system-3.dll /mingw64/bin/libsfml-audio-3.dll \
   /mingw64/bin/libgcc_s_seh-1.dll /mingw64/bin/libstdc++-6.dll \
   /mingw64/bin/libwinpthread-1.dll /mingw64/bin/libfreetype-6.dll \
   /mingw64/bin/libbz2-1.dll /mingw64/bin/libpng16-16.dll \
   /mingw64/bin/zlib1.dll /mingw64/bin/libbrotlidec.dll \
   /mingw64/bin/libbrotlicommon.dll /mingw64/bin/libharfbuzz-0.dll \
   /mingw64/bin/libglib-2.0-0.dll /mingw64/bin/libgraphite2.dll \
   /mingw64/bin/libintl-8.dll /mingw64/bin/libiconv-2.dll \
   /mingw64/bin/libpcre2-8-0.dll /mingw64/bin/libopenal-1.dll \
   /mingw64/bin/libvorbis-0.dll /mingw64/bin/libvorbisfile-3.dll \
   /mingw64/bin/libvorbisenc-2.dll /mingw64/bin/libogg-0.dll \
   /mingw64/bin/libFLAC.dll \
   build/bin/
```

---

## 📁 Estructura del proyecto

```
AmorDependeDeTi/
├── .github/
|    ├── workflows/
|        ├── publish.yml           *GitHub Action (ya incluido)
├── src/
│   ├── main.cpp          # Punto de entrada
│   ├── Game.cpp          # Logica principal y renderizado
│   ├── Player.cpp        # Datos y puntuacion del jugador
│   └── EventManager.cpp  # Carga de los 10 eventos
├── include/
│   ├── Game.h
│   ├── Player.h
│   ├── Event.h
│   └── EventManager.h
├── assets/
│   ├── COVER.png                  # Portada
│   ├── capturaEH1.png             # Imagenes de eventos (EH = Hombre, EM = Mujer)
│   ├── Captura_EH2.png ... EH10
│   ├── capturaEM1.png
│   ├── Captura_EM2.png ... EM10
│   ├── Captura_EHM4.png           # Evento compartido (ambos generos)
│   ├── Final1.png                 # Imagen final Romantico
│   ├── Final2.png                 # Imagen final Por Lastima
│   ├── Final3.png                 # Imagen final Toxico / Psicopata
│   ├── musica.ogg                 # Musica de fondo (piano suave)
│   └── PlaywriteGBJ-VariableFont_wght.ttf  # Fuente del juego
├── bin/                  # Ejecutable .exe y DLLs
├── gallery/              # cover.png para CETUS
├── screenshots/          # Capturas para CETUS
├── video/                # demo.mp4 para CETUS
├── CMakeLists.txt
└── README.md
```

---

## 📜 Creditos

* **Musica:** Pixabay — Royalty Free Music
* **Motor:** SFML 3.0 — [sfml-dev.org](https://www.sfml-dev.org)
* **Imagenes**: CHAT GPT
* **Creadores**: Ximena Atienzo y Sofia Rodriguez 
* Proyecto desarrollado con fines academicos

---

*Hecho con 💕 en C++*
