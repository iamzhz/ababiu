#ifndef _IR_H_
#define _IR_H_
#include "../include.h"

enum IROp {
    Op_Add,
    Op_Sub,
    Op_Mul,
    Op_Div,
    Op_Assign,
};
enum OpNumberType {
    OpNumberType_value,
    OpNumberType_variable,
    OpNumberType_reg,
};
struct OpNumber {
    OpNumberType type;
    int val;
};
struct IR {
    IROp op;
    OpNumber n1;
    OpNumber n2;
    OpNumber n3;
};

enum IRsType {IRsType_Main, IRsType_Func};
class IRs {
    public:
    IRsType type;
    SymbolTable st;
    std::vector<IRs> funcs;
    std::vector<IR> content;

    IRs(IRsType type);
    IRs();
    void add(IR ir);
};
#endif