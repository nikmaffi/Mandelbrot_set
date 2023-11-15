APP=mandelbrot

LIB_SDL2=$(addprefix -l, SDL2)

DEFINE_SFML=-DSFML_STATIC
LIB_SFML=$(addprefix -l, sfml-graphics-s sfml-window-s sfml-system-s opengl32 winmm gdi32 freetype)

RELEASE=-O2
DEBUG=-ggdb -Wall -Wextra

CC=g++ -std=c++20


all: $(APP)

$(APP): main.cpp
	$(CC) $(RELEASE) $^ -o $(APP)

debug: main.cpp
	$(CC) $(DEBUG) $^ -o $(APP)


sdl2: sdl2/main.cpp
	$(CC) $(RELEASE) $^ -o $(APP) $(LIB_SDL2)

debug_sdl2: sdl2/main.cpp
	$(CC) $(DEBUG) $^ -o $(APP) $(LIB_SDL2)


sfml: sfml/main.cpp
	$(CC) $(RELEASE) $(DEFINE_SFML) $^ -o $(APP) $(LIB_SFML)

debug_sfml: sfml/main.cpp
	$(CC) $(DEBUG) $(DEFINE_SFML) $^ -o $(APP) $(LIB_SFML)


clean:
	rm $(APP) 