#include "../include.h"

bool SymbolTable::exsit(std::string name) {
    if (table.find(name) == table.end()) {
        return false;
    }
    return true;
}

void SymbolTable::insert(std::string name, SymbolValue value) {
    table[name] = value;
}