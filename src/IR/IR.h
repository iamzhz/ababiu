#ifndef _IR_H_
#define _IR_H_

#include <string>
#include <vector>
#include <variant>
#include <unordered_map>
#include "../Value/Value.h"

enum IROp {
    /*
    TIP ~n(n is a digit):
        ~n means the n-th of the stack (isn't a var).
        ~n's value poped when it is used.
    TIP $n(n is a digit):
        $n can be considered as a temp var.
        $n will be a register or a piece of memory in stack.
    
    Other Tip:
    imm -> Immediate
    iv -> id.variable
    if -> id.function (but use `iv`)
    t  -> temp (but use `iv`)
    */
    Op_none,
    Op_pop_iv,
    Op_pop_reg,
    Op_push_imm,
    Op_push_iv,
    Op_push_reg,
    Op_mov_iv_iv, // iv0 = iv1
    Op_mov_iv_imm,
    Op_mov_reg_reg,
    Op_add, // push (~1 + ~0)
    Op_add_reg_reg,
    Op_sub, // push (~1 - ~0)
    Op_sub_reg_reg,
    Op_mul, // push (~1 * ~0)
    Op_mul_reg_reg,
    Op_div, // push (~1 / ~0)
    Op_div_reg_reg,
    Op_call_if,
    Op_equal, // push (~1 == ~0)
    Op_equal_reg_reg,
    Op_bigger, // push (~1 > ~0)
    Op_bigger_reg_reg,
    Op_biggerEqual, // push (~1 >= ~0)
    Op_biggerEqual_reg_reg,
    Op_smaller, // push (~1 < ~0)
    Op_smaller_reg_reg,
    Op_smallerEqual, // push (~1 <= ~0)
    Op_smallerEqual_reg_reg,
    Op_notEqual, // push (~1 != ~0)
    Op_notEqual_reg_reg,

    Op_power, // push (~1 ** ~0)
    Op_power_reg_reg,

    Op_jump_imm, // jump to imm0 
    Op_jumpIfNot_imm, // jump to imm0 if not ~0
    Op_jumpIf_imm, // jump to imm0 if not ~0

    Op_jumpIfNot_imm_reg,
    Op_jumpIf_imm_reg,

    Sign_callParaBegin, // as a sign to mark the beginning
    
    Op_load_iv_reg,
    Op_load_imm_reg,
    Op_store_iv_reg,

    Sign_defineVariable_type_iv,
};


struct IR {
    IROp op;
    IdVariable iv0;
    IdVariable iv1;
    Immediate imm0;
    Value reg0;
    Value reg1;
    TypeType type0;
    void clean();
};

class IRs {
    public:
    int pos = 0; // the position which will be on the next IR
    int getPosition();
    std::vector<IR> content;
    std::unordered_map<std::string, int> marks;
    
    int add(IR ir); // return the position of IR
    void replace(IRs & new_);
    //void
    #ifdef DEBUG
    void display();
    #endif
};
#endif