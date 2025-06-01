#ifndef _VARIABLEMAP_H_
#define _VARIABLEMAP_H_

struct VariableInfo {
    // TODO: some data to store
};
class VariableMap {
    // it doesn't record the name of variable, but SymbolTable does
    private:
    int indexCount;
    std::vector<VariableInfo> map;
    public:
    VariableMap();
    int add();  // return the index
};

#endif