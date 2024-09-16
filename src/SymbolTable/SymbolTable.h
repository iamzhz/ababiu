#include "../include.h"

enum SymbolValueType {
    SymbolValueType_Func,
    SymbolValueType_Var,
};

struct SymbolValue {
    SymbolValueType type;
    void * ptr; // TODO: will change
};

class SymbolTable {
    private:
    std::unordered_map<std::string, SymbolValue> table;
    public:
    bool exsit(std::string name);
    void insert(std::string name, SymbolValue value);
};