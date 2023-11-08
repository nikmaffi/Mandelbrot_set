APP=mandelbrot

LIB=$(addprefix -l, SDL2)

RELEASE=-O2
DEBUG=-ggdb -Wall -Wextra -DDEBUG_MANDELBROT_FRACTAL

CC=g++ -std=c++20

all: $(APP)

$(APP): main.cpp
	$(CC) $(RELEASE) $^ -o $(APP) $(LIB)

debug: main.cpp
	$(CC) $(DEBUG) $^ -o $(APP) $(LIB)

clean:
	rm $(APP)