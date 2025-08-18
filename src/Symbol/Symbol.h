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
    TypeType type; // var -> type,  func -> return type
    // var
    int frame_offset;
    int size;
    // func
    std::vector<TypeType> args;
};

class Symbol {
    private:
    std::unordered_map<std::string, SymbolValue> table;
    std::vector<std::pair<int, int>> memory_unused; // first->addr; second->unused_bytes_number
    int assign_memory(int addr, int rest, int size, int & used);
    public:
    int i = (-8);
    Symbol() = default;
    void insert_variable(std::string name, TypeType var_type);
    SymbolValue get_variable(std::string name);
    std::string get_variable_mem(Value val); // val is a iv
    std::string get_variable_mem(std::string name);
    void insert_function(std::string name, SymbolValue sv);

    void clear_variable();
};

#endif
