#ifndef _IR_H_
#define _IR_H_
#include "../include.h"

enum IROp {
    /*
    qn -> quicknumber
    iv -> id.variable
    if -> id.function
    */
    Op_pop_qn,
    Op_pop_iv,
    Op_push_iv,
    Op_mov_iv_iv,
    Op_mov_iv_qn,
    Op_add,
    Op_sub,
    Op_mul,
    OP_div,
    Op_call_if,
};

struct Quicknumber {
    // TODO: somrthing to store
};
struct IdVariable {
    int index;
};
struct IR {
    IROp op;
    IdVariable iv0;
    IdVariable iv1;
    Quicknumber qn0;
};

class IRs {
    public:
    SymbolTable st;
    std::vector<IR> content;

    IRs();
    void add(IR ir);
    //void 
    #ifdef DEBUG
    void display();
    #endif
};
#endif