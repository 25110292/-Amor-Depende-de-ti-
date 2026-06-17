# 💕 Amor? Depende de ti

> *Un juego de novela visual donde cada decision define el rumbo de una historia de amor adolescente.*

---

## 📖 Descripcion

**Amor? Depende de ti** es una novela visual desarrollada en C++ con SFML 3, donde el jugador vive una historia romantica a traves de 10 eventos clave. Cada decision tomada acumula puntos que determinan uno de los **4 finales posibles**, reflejando el tipo de relacion que construiste a lo largo del juego.

---

<<<<<<< HEAD
### 🏆 Características
* **4 Finales Completamente Diferentes:**
  1. Final Romántico: Logran superar las adversidades con madurez y terminan siendo felices juntos.
  2. Final de Costumbre:El amor se apaga; se quedan juntos únicamente por rutina, miedo a la soledad y comodidad.
  3. Final Trágico: El desenlace más oscuro, donde la obsesión y la locura consumen a uno de los personajes, terminando con la vida del otro.
=======
## 🎮 Como jugar
>>>>>>> 880b7a3a406e2c7c9a8960e24bfb795d39f8e17e

1. Ingresa tu nombre y el de tu interes romantico
2. Elige tu genero (Hombre / Mujer)
3. Lee cada situacion y elige una de las 3 opciones disponibles
4. Tus decisiones acumulan puntos en secreto
5. Al terminar los 10 eventos, descubre que tipo de relacion construiste

<<<<<<< HEAD
### 👥 Equipo
* **Integrante 1:** Ximena Carolina Gonzalez Atienzo
<<<<<<< HEAD
* **Integrante 2:** Ana Sofia Rodriguez Sanchez 
=======
* **Integrante 2:** Ana Sofia 
>>>>>>> 83ba12739fc2e5146c1ca851bf86900b466b94c3


=======
### Controles
| Accion | Control |
|--------|---------|
| Seleccionar opcion | Clic izquierdo |
| Pausar juego | Boton "Pausa" o ESC |
| Regresar al evento anterior | Boton "< Volver" |
| Continuar / Cerrar | Clic o Enter |

---

## 💘 Finales posibles

| Final | Condicion |
|-------|-----------|
| 💖 **Romantico** | 22 o mas puntos |
| 😶 **Por Lastima** | 13 a 21 puntos |
| 🔥 **Toxico** | 5 a 12 puntos |
| 🚨 **Psicopata** | 3 o mas opciones psicopata elegidas |

---

## 🛠️ Tecnologias

- **Lenguaje:** C++17
- **Motor grafico:** SFML 3.0 (Simple and Fast Multimedia Library)
- **Compilador:** MinGW-w64 (GCC 15.2)
- **Build system:** CMake 3.10+
- **Plataforma:** Windows (MSYS2 / MinGW64)

---

## 📁 Estructura del proyecto

```
AmorDependeDeTi/
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
├── CMakeLists.txt
└── README.md
```

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

## 👩‍💻 Creditos

| Rol | Nombre |
|-----|--------|
| Desarrollo y Programacion | Ana Sofia Rodriguez |
| Narrativa y Diseno | Ximena Gonzalez |

**Musica:** Pixabay — Royalty Free Music  
**Motor:** SFML 3.0 — [sfml-dev.org](https://www.sfml-dev.org)

---

## 📄 Licencia

Este proyecto fue desarrollado con fines academicos.  
Las imagenes y musica utilizadas son de uso libre (royalty free).

---

*Hecho con 💕 en C++*
>>>>>>> 880b7a3a406e2c7c9a8960e24bfb795d39f8e17e
