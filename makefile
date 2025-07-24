CC := g++
STD := -std=c++23
DEBUG := -g -DDEBUG # -DDEEPDEBUG
WARNINGS := -Wall -Wextra -Wpedantic

SRC_FILES := $(wildcard src/*.cc src/*/*.cc)
OBJ_FILES := $(filter-out src/main.o src/main_ir.o, $(SRC_FILES:.cc=.o))

EXECUTABLES := abandon abandon_ir

all: $(EXECUTABLES)

abandon: src/main.o $(OBJ_FILES)
	$(CC) $^ -o $@ $(DEBUG)
abandon_ir: src/main_ir.o $(OBJ_FILES)
	$(CC) $^ -o $@ $(DEBUG)

%.o: %.cc
	$(CC) -c $< -o $@ $(STD) $(DEBUG) $(WARNINGS)

clean:
	rm -f $(OBJ_FILES) src/main.o src/main_ir.o $(EXECUTABLES)

.PHONY: all clean