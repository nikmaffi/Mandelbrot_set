APP=mandelbrot

LIB_SDL2=$(addprefix -l, SDL2)

LIB_RAYLIB=$(addprefix -l, raylib GL m pthread dl rt X11)

RELEASE=-O2 -s
DEBUG=-ggdb -Wall -Wextra -fsanitize=address

CC=g++ -std=c++20


all: $(APP)

$(APP): main.cpp
	$(CC) $(RELEASE) $^ -o $(APP)

debug: main.cpp
	$(CC) $(DEBUG) $^ -o $(APP)


sdl: sdl2/main.cpp
	$(CC) $(RELEASE) $^ -o $(APP) $(LIB_SDL2)

debug_sdl: sdl2/main.cpp
	$(CC) $(DEBUG) $^ -o $(APP) $(LIB_SDL2)


raylib: raylib/main.cpp
	$(CC) $(RELEASE) $^ -o $(APP) $(LIB_RAYLIB)

debug_raylib: raylib/main.cpp
	$(CC) $(DEBUG) $^ -o $(APP) $(LIB_RAYLIB)


clean:
	rm $(APP)