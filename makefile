CC = gcc
CFLAGS = -Wall -std=c99
SOURCE := $(wildcard src/*.c)
OBJ := $(addprefix build/, $(notdir $(SOURCE:.c=.o)))

TEST_SOURCE := $(wildcard testing/*.c)
TEST_OBJ := $(addprefix test/, $(notdir $(TEST_SOURCE:.c=.o)))

HEADERS = $(wildcard src/*.h)

all: $(OBJ) build
	$(CC) $(C_FLAGS) -o cellcount $(OBJ)

build/%.o: src/%.c
	$(CC) $(C_FLAGS) -c -o $@ $<

test: $(TEST_OBJ) test_build
	$(CC) $(C_FLAGS) -o tested $(TEST_OBJ)

test/%.o: testing/%.c
	$(CC) $(C_FLAGS) -c -o $@ $<

test_build:
	mkdir test_build

test_clean:
	rm -rf test_build

clean:
	rm -rf build

build:
	mkdir build
