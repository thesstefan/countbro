CC = gcc
CFLAGS = -Wall -std=c99
INCLUDE = src

SOURCE := $(wildcard src/*.c)
OBJ := $(addprefix build/obj/, $(notdir $(SOURCE:.c=.o)))

TEST_SOURCE := $(wildcard test_src/*.c)
TEST_OBJ := $(addprefix build/test_artifacts/, $(notdir $(TEST_SOURCE:.c=.o)))
TEST_EXE := $(addprefix build/, $(notdir $(TEST_SOURCE:.c=.x)))
TEST_NEEDED_OBJ := $(filter-out build/obj/main.o, $(OBJ))

HEADERS = $(wildcard src/*.h)

all: cellcount

run: cellcount
	./cellcount

run_test: test
	$(foreach var, $(TEST_EXE), ./$(var) &)

cellcount: build $(OBJ) 
	$(CC) $(C_FLAGS) -o cellcount $(OBJ)

test: build $(OBJ) $(TEST_OBJ) $(TEST_EXE)

build/obj/%.o: src/%.c
	$(CC) $(C_FLAGS) -c -o $@ $<

build/%.x: build/test_artifacts/%.o
	$(CC) $(C_FLAGS) -o $@ $< $(TEST_NEEDED_OBJ)

build/test_artifacts/%.o: test_src/%.c $(HEADERS)
	$(CC) $(C_FLAGS) -I$(INCLUDE) -c -o $@ $<

.PHONY: clean
clean:
	@if [ -d "build" ]; then rm -rf build; fi

.PHONY: build
build:
	@if [ ! -d "build" ]; then mkdir build && mkdir build/obj && mkdir build/test_artifacts; fi
