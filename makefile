cc := g++
std := -std=c++11
debug := -DDEBUG
abandon: *.cc */*.cc
	$(cc) $^ -o $@ $(std) $(debug)