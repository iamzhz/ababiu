#ifndef _SYMBOL_H_
#define _SYMBOL_H_

#include <unordered_map>
#include <string>
#include "../Value/Value.h"

struct SymbolValue{
    bool isVariable; // true -> Variable;  false -> Function
    TypeType type;
    int frame_offset;
};

class Symbol {
    private:
    int i = 0;
    std::unordered_map<std::string, SymbolValue> table;
    public:
    Symbol() = default;
    void insert_variable(std::string name, TypeType var_type);
};

#endif
