CC = gcc
CFLAGS = -Wall -std=c99

TEST_SOURCE = src/test.c
TEST_OBJ := $(addprefix build/test/, $(notdir $(TEST_SOURCE:.c=.o)))

SOURCE := $(filter-out $(TEST_SOURCE), $(wildcard src/*.c))
OBJ := $(addprefix build/, $(notdir $(SOURCE:.c=.o)))

HEADERS = $(wildcard src/*.h)

all: $(OBJ) build
	$(CC) $(C_FLAGS) -o cellcount $(OBJ)

build/%.o: src/%.c
	$(CC) $(C_FLAGS) -c -o $@ $<

test: $(TEST_OBJ) 
	$(CC) $(C_FLAGS) -o tested $(TEST_OBJ) $(OBJ)

build/test/%.o: $(TEST_SOURCE)
	$(CC) $(C_FLAGS) $(OBJ) -c $< -o $@ 

test_build: build
	mkdir build/test

test_clean:
	rm -rf build_test

clean:
	rm -rf build

build:
	mkdir build
