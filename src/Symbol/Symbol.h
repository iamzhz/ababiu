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
struct ScopeValue {
    std::unordered_map<std::string, SymbolValue> map;
    int i;
    // first->addr; second->unused_bytes_number
    std::vector<std::pair<int, int>> memory_unused;
};

class Symbol {
    private:
    int assign_memory(int addr, int rest, int size, int & used);
    public:
    std::vector<ScopeValue> table;
    //int i = (-8);
    Symbol();
    void insert_variable(std::string name, TypeType var_type);
    SymbolValue get_variable(std::string name);
    SymbolValue get_variable(Value val);
    std::string get_variable_mem(Value val); // val is a iv
    std::string get_variable_mem(std::string name);
    void insert_function(std::string name, SymbolValue sv);
    SymbolValue get(std::string name);

    void new_scope();
    int exit_scope();
};

#endif
