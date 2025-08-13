#ifndef _SYMBOL_H_
#define _SYMBOL_H_

#include <unordered_map>
#include <string>
#include <vector>
#include <utility>
#include "../Value/Value.h"
#include "../env_config/config.h"

struct SymbolValue{
    bool isExist = true;
    bool isVariable; // true -> Variable;  false -> Function
    TypeType type;
    int frame_offset;
    int size;
};

class Symbol {
    private:
    int i = (-8);
    std::unordered_map<std::string, SymbolValue> table;
    std::vector<std::pair<int, int>> memory_unused; // first->addr; second->unused_bytes_number
    int assign_memory(int addr, int rest, int size, int & used);
    public:
    Symbol() = default;
    void insert_variable(std::string name, TypeType var_type);
    SymbolValue get_variable(std::string name);
    std::string get_variable_mem(std::string name);
};

#endif
