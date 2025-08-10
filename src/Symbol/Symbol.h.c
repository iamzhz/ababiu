// src/Semantic/Symbol.h
#ifndef _SYMBOL_H_
#define _SYMBOL_H_
#include "../PointerManager/PointerManager.h"
#include "../Token/Token.h"
#include <string>
#include <cstdlib>
#include <unordered_map>

enum SymbolType { SYMBOL_VAR, SYMBOL_FUNC };

enum VarType {VAR_UNKNOWN, VAR_INT, VAR_CHAR, VAR_FLOAT, VAR_STRING};

struct VarSymbol {
    std::string name;
    VarType type;
    // Todo: more info for finding it
};
struct FuncSymbol {
    std::string name;
    VarType return_type;
    std::vector<std::string> param_types; // ToDo: parse for param for func
    // ToDo: more info for calling
};

VarType tokenTypeToVarType(tokenType tt);

// Symbol Table
class Symbol {
    private:
    std::unordered_map<std::string, struct VarSymbol*> vars;
    std::unordered_map<std::string, struct FuncSymbol*> funcs;
    public:
    void insert_var(std::string name, VarType vt/*, ...*/);
    void insert_func(std::string name, VarType return_type/*, ...*/);
};

extern PointerManager<VarSymbol*> pmVar;
extern PointerManager<FuncSymbol*> pmFunc;
extern Symbol sym;

#endif
