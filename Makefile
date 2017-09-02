CC = gcc
CFLAGS = -Wall -std=c99

SOURCE := $(wildcard src/*.c)
OBJ := $(addprefix build/, $(notdir $(SOURCE:.c=.o)))

TEST_SOURCE := $(wildcard test_src/*.c)
TEST_OBJ := $(addprefix test_build/, $(notdir $(TEST_SOURCE:.c=.o)))
TEST_FINAL := $(addprefix test_exec/, $(notdir $(TEST_SOURCE:.c=)))
TEST_NEEDED_OBJ := $(filter-out build/main.o, $(OBJ))

HEADERS = $(wildcard src/*.h)

all: build $(OBJ)
	$(CC) $(C_FLAGS) -o cellcount $(OBJ)

build/%.o: src/%.c
	$(CC) $(C_FLAGS) -c -o $@ $<

test: test_build $(TEST_OBJ) $(TEST_FINAL)

test_exec/%: test_build/%.o
	$(CC) $(C_FLAGS) -o $@ $< $(TEST_NEEDED_OBJ)

test_build/%.o: test_src/%.c $(HEADERS)
	$(CC) $(C_FLAGS) -Isrc -c -o $@ $<

.PHONY: clean
clean: test_clean
	rm -rf build

.PHONY: build
build:
	mkdir build

.PHONY: test_clean
test_clean:
	rm -rf test_build

.PHONY: test_build
test_build:
	mkdir test_build
