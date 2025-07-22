#include "../include.h"
void sayError(int line, int column, std::string info) {
    std::print(stderr, "[Error] {},{} {}\n", line, column, info);
    std::exit(1);
}
void sayError(std::string info) {
    std::print(stderr, "[Error] {}\n", info);
    std::exit(1);
}