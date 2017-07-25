CC=gcc
CFLAGS=-Wall -std=c99
DEPS = colors.h image.h morphology.h transform.h
OBJ = build/image.o build/morphology.o build/transform.o

%.o: src/%.c
	$(CC) -c -o build/$@ $< $(CFLAGS)

all: $(OBJ) build
	gcc -o cellcount $(OBJ) src/main.c $(CFLAGS)

build:
	mkdir build

clean:
	rm -rf build
