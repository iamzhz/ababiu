cc := g++
std := -std=c++11
debug := -DDEBUG
abandon: src/*.cc src/*/*.cc
	$(cc) $^ -o $@ $(std) $(debug)