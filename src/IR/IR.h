#ifndef _IR_H_
#define _IR_H_
#include "../include.h"

enum IROp {
    /*
    qn -> quicknumber
    iv -> id.variable
    if -> id.function (but use `iv`)
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

enum QuicknumberType {
    QN_UNKNOWN, 
    QN_INT, 
    QN_CHAR, 
    QN_FLOAT, 
    QN_STRING
};

using Quicknumber = std::variant<
    std::monostate, 
    int,
    char,
    double,
    std::string
>;

QuicknumberType getQuicknumberType(const Quicknumber& qn) ;

struct IdVariable {
    std::string content;
};
struct IR {
    IROp op;
    IdVariable iv0;
    IdVariable iv1;
    Quicknumber qn0;
};

Quicknumber makeQuicknumber(int i);
Quicknumber makeQuicknumber(char c);
Quicknumber makeQuicknumber(double f);
Quicknumber makeQuicknumber(std::string s);
IdVariable makeIdVariable(std::string content);

class IRs {
    public:
    std::vector<IR> content;

    IRs();
    void add(IR ir);
    //void 
    #ifdef DEBUG
    void display();
    #endif
};
#endif