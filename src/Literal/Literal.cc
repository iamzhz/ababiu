#include "Literal.h"
#include <cstdint>
#include <bit>
#include <stdexcept>
#include <string>
#include <format>

std::string Literal::get(Value val) {
    if (!val.isImmediate()) {
        std::runtime_error("Literal::get(Value val)");
    }
    Immediate li = val.getImmediate();
    switch (li.type) {
        case TYPE_UNKNOWN: std::runtime_error("Literal::get TYPE_UNKNOWN"); break;
        case TYPE_CHAR: return std::format("'{}'", li.content);
        case TYPE_INT: return li.content;
        case TYPE_FLOAT: return this->storeFloat(li.content);
        default: break;
    }
    return "";
}

std::string Literal::storeFloat(std::string fl) {
    double f64_val = std::stod(fl);
    int64_t i64_val = std::bit_cast<int64_t>(f64_val);
    int32_t low32 = static_cast<int32_t>(i64_val & 0xFFFFFFFF);
    int32_t high32 = static_cast<int32_t>(i64_val >> 32);
    this->_rodata << std::format("LC{}: dd {}, {}\n", this->count, low32, high32);
    std::string ret = std::format("[rel LC{}]", this->count);
    ++ count;
    return ret;
}

std::string Literal::get_rodata() {
    return this->_rodata.str();
}