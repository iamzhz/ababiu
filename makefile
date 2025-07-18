cc := g++
std := -std=c++17
debug := -g

SRC_FILES := $(wildcard src/*.cc src/*/*.cc)
OBJ_FILES := $(SRC_FILES:.cc=.o)

all: abandon

# link
abandon: $(OBJ_FILES)
	$(cc) $^ -o $@ $(debug)
# compile
%.o: %.cc
	$(cc) -c $< -o $@ $(std) $(debug) -Wall -Wextra -Wpedantic


# clean
clean:
	rm -f $(OBJ_FILES) abandon

.PHONY: all clean