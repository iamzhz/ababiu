/*#ifndef TEST

#define private public
#include "include.h"
#define log(x) {std::cerr << __LINE__ << ": " << x << std::endl; ret = 1;}
int test_main() {
    int ret = 0;
    // SymbolTable
    SymbolValue _SymbolValue = {SymbolValueType_Var, nullptr};
    SymbolTable _SymbolTable;
    _SymbolTable.insert("test", _SymbolValue);
    if (_SymbolTable.exsit("test") == false) log("insert or exsit error");
    if (_SymbolTable.exsit("test2") == true) log("exsit error");
    if (_SymbolTable.table["test"].ptr != nullptr) log("insert error");


    // IRs
    IRs _irs()



    if (ret == 0) std::cout << "All test passed." << std::endl;
    return ret;
}
#endif*/