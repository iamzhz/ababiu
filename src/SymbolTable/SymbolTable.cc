#include "../include.h"

bool SymbolTable::exsit(std::string name) {
    if (table.find(name) == table.end()) {
        return false;
    }
    return true;
}

void SymbolTable::add(std::string name, SymbolValue value) {
    table[name] = value;
}

void SymbolTable::add(std::string name, SymbolValueType type, int index) {
    SymbolValue sv = {type, index};
    this->add(name, sv);
}

int SymbolTable::getIndex(std::string name) {
    return table[name].index;
}

int getType(std::string name) {
    return table[name].type;
}