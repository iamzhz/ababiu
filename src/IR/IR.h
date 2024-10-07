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
enum IRisGetAdress {IsGetAdress = 1, NotGetAdress = 0}; // `&` or not
enum OpNumberType {
    OpNumberType_int, // pointer to int
    OpNumberType_float, // pointer to float
    OpNumberType_string, // pointer to std::string
    OpNumberType_isGetAdress, // pointer to IRisGetAdress
    OpNumberType_variable, // pointer to std::string (variable name)
    OpNumberType_reg, // pointer to int (register number)
};
struct OpNumber {
    OpNumberType type;
    void * ptr;
};
struct IR {
    IROp op;
    OpNumber n1;
    OpNumber n2;
    OpNumber n3;
};

enum IRsType {IRsType_Main, IRsType_Func};

#ifdef DEBUG
std::string IROpToText(IROp op);
std::string OpNumberToText(OpNumber & n);
#endif
class IRs {
    public:
    IRsType type;
    SymbolTable st;
    std::vector<IRs> funcs; // when type is IRsType_Main
    std::vector<IR> content; // when type is IRsType_Func
    std::string name; // when type is IRsType_Func

    IRs(IRsType type);
    IRs();
    void setFuncName(std::string name);
    void add(IR ir);
    void 
    #ifdef DEBUG
    void display();
    #endif
};
#endif