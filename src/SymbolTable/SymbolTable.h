#ifndef _SYMBOLTABLE_H_
#define _SYMBOLTABLE_H_

#include "../include.h"

enum SymbolValueType {
    SymbolValueType_Func,
    SymbolValueType_Variable,
};

struct SymbolValue {
    SymbolValueType type;
    int index; // the index is used to get the position of it
};

class SymbolTable {
    private:
    std::unordered_map<std::string, SymbolValue> table;
    public:
    bool exsit(std::string name);
    void add(std::string name, SymbolValue value);
    void add(std::string name, SymbolValueType type, int index);
    int getIndex(std::string name);
    int getType(std::string name);
};

#endif