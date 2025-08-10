#include "Symbol.h"
#include "../SayError/SayError.h"
#include <string>

void Symbol::insert_variable(std::string name, TypeType var_type) {
    SymbolValue sv;
    int size;
    sv.isVariable = true;
    sv.type = var_type;
    switch (var_type) {
        case TYPE_CHAR: size = 1; break;
        case TYPE_INT: size = 8; break;
        default: break; 
        // TODO
    }
    sv.frame_offset = this->i;
    this->i += size;
    this->table.insert({name, sv});
}

SymbolValue Symbol::get_variable(std::string name) {
    SymbolValue sv;
    auto f = this->table.find(name);
    if (f == this->table.end()) {
        sv.isExist = false;
        return sv;
    }
    sv = f->second;
    return sv;
}

std::string Symbol::get_variable_mem(std::string name) {
    SymbolValue sv = this->get_variable(name);
    if (!sv.isExist) {
        sayError("`" + name + "` does not exist.\n");
    }
    if (!sv.isVariable) {
        sayError("`" + name + "` is a function.\n");
    }
    return "[rbp-" + std::to_string(sv.frame_offset) + "]";
}