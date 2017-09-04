CC = gcc
CFLAGS = -Wall -std=c99
INCLUDE = src

SOURCE := $(wildcard src/*.c)
OBJ := $(addprefix build/, $(notdir $(SOURCE:.c=.o)))

TEST_SOURCE := $(wildcard test_src/*.c)
TEST_OBJ := $(addprefix test_build/, $(notdir $(TEST_SOURCE:.c=.o)))
TEST_EXE := $(addprefix test_build/, $(notdir $(TEST_SOURCE:.c=.x)))
TEST_NEEDED_OBJ := $(filter-out build/main.o, $(OBJ))

HEADERS = $(wildcard src/*.h)

all: run

run: cellcount
	./cellcount

run_test:
	$(foreach var, $(TEST_EXE), ./$(var) &)

cellcount: build $(OBJ) 
	$(CC) $(C_FLAGS) -o cellcount $(OBJ)

test: build $(OBJ) test_build $(TEST_OBJ) $(TEST_EXE) run_test

build/%.o: src/%.c
	$(CC) $(C_FLAGS) -c -o $@ $<

test_build/%.x: test_build/%.o
	$(CC) $(C_FLAGS) -o $@ $< $(TEST_NEEDED_OBJ)

test_build/%.o: test_src/%.c $(HEADERS)
	$(CC) $(C_FLAGS) -I$(INCLUDE) -c -o $@ $<

.PHONY: clean
clean:
	@if [ -d "build" ]; then rm -rf build; fi

.PHONY: build
build:
	@if [ ! -d "build" ]; then mkdir build; fi

.PHONY: test_clean
test_clean:
	@if [ -d "test_build" ]; then rm -rf test_build; fi

.PHONY: test_build
test_build:
	@if [ ! -d "test_build" ]; then mkdir test_build; fi
