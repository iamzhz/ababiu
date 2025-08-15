#include "Literal.h"
#include <cstdint>
#include <bit>
#include <string>
#include <format>

void Literal::storeFloat(std::string fl) {
    double f64_val = std::stod(fl);
    int64_t i64_val = std::bit_cast<int64_t>(f64_val);
    int32_t low32 = static_cast<int32_t>(i64_val & 0xFFFFFFFF);
    int32_t high32 = static_cast<int32_t>(i64_val >> 32);
    this->_rodata << std::format("LC{}: dd {}, {}\n", this->count, low32, high32);
    ++ count;
}

std::string Literal::get_rodata() {
    return this->_rodata.str();
}