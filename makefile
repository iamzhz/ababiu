CC := g++
STD := -std=c++20
DEBUG := -g # -DDEBUG
WARNINGS := -Wall -Wextra -Wpedantic

SRC_FILES := $(wildcard src/*.cc src/*/*.cc)
OBJ_FILES := $(SRC_FILES:.cc=.o)

EXECUTABLES := ababiu

all: $(EXECUTABLES)

ababiu: src/main.o $(OBJ_FILES)
	$(CC) $^ -o $@ $(DEBUG)
%.o: %.cc
	$(CC) -c $< -o $@ $(STD) $(DEBUG) $(WARNINGS)

clean:
	rm -f $(OBJ_FILES) $(EXECUTABLES)

.PHONY: all clean
