CC = gcc
CFLAGS = -Wall -std=c99 -g
INCLUDE = src

SOURCE := $(wildcard src/*.c)
OBJ := $(addprefix build/obj/, $(notdir $(SOURCE:.c=.o)))
EXE := build/cellcount

INPUT := data/input.bmp
OUTPUT := data/output.bmp

TEST_SOURCE := $(wildcard test_src/*.c)
TEST_OBJ := $(addprefix build/test_obj/, $(notdir $(TEST_SOURCE:.c=.o)))
TEST_EXE := $(filter-out build/cellcount, $(addprefix build/, $(notdir $(TEST_SOURCE:.c=))))
TEST_NEEDED_OBJ := $(filter-out build/obj/main.o, $(OBJ))

HEADERS = $(wildcard src/*.h)

all: $(EXE)

run: $(EXE)
	./$(EXE) $(INPUT) $(OUTPUT)

run_test: test
	$(foreach var, $(TEST_EXE), ./$(var);)

$(EXE): build $(OBJ) 
	$(CC) $(CFLAGS) -o $(EXE) $(OBJ)

test: build $(OBJ) $(TEST_OBJ) $(TEST_EXE)

build/obj/%.o: src/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

build/%: build/test_obj/%.o
	$(CC) $(CFLAGS) -o $@ $< $(TEST_NEEDED_OBJ)

build/test_obj/%.o: test_src/%.c $(HEADERS)
	$(CC) $(CFLAGS) -I$(INCLUDE) -c -o $@ $<

.PHONY: clean
clean:
	@if [ -d "build" ]; then rm -rf build; fi

.PHONY: build
build:
	@if [ ! -d "build" ]; then mkdir build && mkdir build/obj && mkdir build/test_obj; fi
