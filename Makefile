APP=mandelbrot

LIB=$(addprefix -l, SDL2)

RELEASE=-O2
DEBUG=-ggdb -Wall -Wextra

CC=g++ -std=c++20

all: $(APP)

$(APP): main.cpp
	$(CC) $(RELEASE) $^ -o $(APP) $(LIB)

vintage: vintage.cpp
	$(CC) $(RELEASE) $^ -o $(APP)

debug: main.cpp
	$(CC) $(DEBUG) $^ -o $(APP) $(LIB)

debug_vintage: vintage.cpp
	$(CC) $(DEBUG) $^ -o $(APP)

clean:
	rm $(APP)