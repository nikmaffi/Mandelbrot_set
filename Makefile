APP=mandelbrot

LIB_SDL2=$(addprefix -l, SDL2)

LIB_SFML=$(addprefix -l, sfml-graphics sfml-window sfml-system)

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
	$(CC) $(RELEASE) $^ -o $(APP) $(LIB_SFML)

debug_sfml: sfml/main.cpp
	$(CC) $(DEBUG) $^ -o $(APP) $(LIB_SFML)


clean:
	rm $(APP) 
