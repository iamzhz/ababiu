#include "Symbol.h"

void Symbol::insert_variable(std::string name, TypeType var_type) {
    SymbolValue sv;
    int size;
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
