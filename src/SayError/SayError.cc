#include "SayError.h"
#include <iostream>
void sayError(int line, int column, std::string info) {
    std::cerr << "[Error]" << line << ',' << column << " " << info << std::endl;
    std::exit(1);
}
void sayError(std::string info) {
    std::cerr << "[Error] " << info << std::endl;
    std::exit(1);
}