#include "../include.h"
void sayError(int line, int column, std::string info) {
    std::cerr << "[ERROR] " << line << ',' << column << ' ' << info << std::endl;
    std::exit(1);
}