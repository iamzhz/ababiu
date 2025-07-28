#ifndef _IR_H_
#define _IR_H_

#include <string>
#include <vector>
#include <variant>

enum IROp {
    /*
    TIP ~n(n is a digit):
        ~n means the n-th of the stack (isn't a var).
        ~n's value poped when it is used.
    TIP $n(n is a digit):
        $n can be considered as a temp var.
        when n is from {1, 2, 3, 4}:
            $n will be the n-th register on CPU.
        when n is bigger than 4:
            $n will be a piece of memory in stack.
    
    Other Tip:
    qn -> quicknumber
    iv -> id.variable
    if -> id.function (but use `iv`)
    t  -> temp (but use `iv`)
    */
    Op_pop_iv,
    Op_push_qn,
    Op_push_iv,
    Op_mov_iv_iv, // iv0 = iv1
    Op_mov_iv_qn,
    Op_add, // push (~1 + ~0)
    Op_sub, // push (~1 - ~0)
    Op_mul,
    Op_div,
    Op_call_if,
    Op_equal, // push (~1 == ~0)
    Op_bigger, // push (~1 > ~0)
    Op_biggerEqual, // push (~1 >= ~0)
    Op_smaller, // push (~1 < ~0)
    Op_smallerEqual, // push (~1 <= ~0)
    Op_notEqual, // push (~1 != ~0)

    Op_power, // push (~1 ** ~0)

    Op_jump_qn, // jump to qn0 
    Op_jumpIfNot_qn, // jump to qn0 if not ~0
    Op_jumpIf_qn, // jump to qn0 if not ~0

    Sign_callParaBegin, // as a sign to mark the beginning
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

    int pos;
};

Quicknumber makeQuicknumber(int i);
Quicknumber makeQuicknumber(char c);
Quicknumber makeQuicknumber(double f);
Quicknumber makeQuicknumber(std::string s);
IdVariable makeIdVariable(std::string content);

class IRs {
    public:
    int pos = 0; // the position which will be on the next IR
    int getPosition();
    std::vector<IR> content;
    
    int add(IR ir); // return the position of IR
    void replace(IRs & old);
    //void 
    #ifdef DEBUG
    void display();
    #endif
};
#endif