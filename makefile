cc := g++
std := -std=c++11
abandon: src/*.cc src/*/*.cc
	$(cc) $^ -o $@ $(std) -g
test: src/*.cc src/*/*.cc
	$(cc) $^ -o $@ $(std) -g -DTEST
	./$@