CC := g++
STD := -std=c++17
DEBUG := -g -DDEBUG # -DDEEPDEBUG
WARNINGS := -Wall -Wextra -Wpedantic

SRC_FILES := $(wildcard src/*.cc src/*/*.cc)
OBJ_FILES := $(filter-out src/main.o src/main_ir.o, $(SRC_FILES:.cc=.o))

EXECUTABLES := ababiu ababiu_ir

all: $(EXECUTABLES)

ababiu: src/main.o $(OBJ_FILES)
	$(CC) $^ -o $@ $(DEBUG)
ababiu_ir: src/main_ir.o $(OBJ_FILES)
	$(CC) $^ -o $@ $(DEBUG)

%.o: %.cc
	$(CC) -c $< -o $@ $(STD) $(DEBUG) $(WARNINGS)

clean:
	rm -f $(OBJ_FILES) src/main.o src/main_ir.o $(EXECUTABLES)

.PHONY: all clean