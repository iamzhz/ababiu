#include "IR.h"
#include <iostream>

void IR::clean() {
    #ifdef DEBUG
    this->iv0 = {};
    this->iv1 = {};
    this->qn0 = {};
    this->reg0 = Value();
    this->reg1 = Value();
    #endif
    // if I do not want to see the IR by my eyes, this method is useless.
}

int IRs::getPosition() {
    this->pos ++;
    return (this->pos - 1);
}

int IRs::add(IR ir) {
    int pos = this->getPosition();
    content.push_back(std::move(ir));
    return pos;
}

void IRs::replace(IRs & theNew) {
    this->content = theNew.content;
    this->pos = this->content.size();
}

#ifdef DEBUG
std::string IROpToText(IROp n) {
    switch (n) {
        case Op_pop_iv: return "pop_iv";
        case Op_push_qn: return "push_qn";
        case Op_push_iv: return "push_iv";
        case Op_mov_iv_iv: return "mov_iv_iv";
        case Op_mov_iv_qn: return "mov_iv_qn";
        case Op_mov_reg_reg: return "mov_reg_reg";
        case Op_add: return "add";
        case Op_add_reg_reg: return "add_reg_reg";
        case Op_sub: return "sub";
        case Op_sub_reg_reg: return "sub_reg_reg";
        case Op_mul: return "mul";
        case Op_mul_reg_reg: return "mul_reg_reg";
        case Op_div: return "div";
        case Op_div_reg_reg: return "div_reg_reg";
        case Op_call_if: return "call_if";
        case Op_equal: return "equal";
        case Op_bigger: return "bigger";
        case Op_biggerEqual: return "biggerEqual";
        case Op_smaller: return "smaller";
        case Op_smallerEqual: return "smallerEqual";
        case Op_notEqual: return "notEqual";
        case Op_power: return "power";
        case Op_jump_qn: return "jump_qn";
        case Op_jumpIfNot_qn: return "jumpIfNot_qn";
        case Op_jumpIf_qn: return "jumpIf_qn";
        case Sign_callParaBegin: return "callParaBegin";
        case Op_load_iv_reg: return "load_iv_reg";
        case Op_load_qn_reg: return "load_qn_reg";
        case Op_store_iv_reg: return "store_iv_reg";
    }
    return "Error: IR.cc::IRs::display();\n";
}
void outIdVaiable(IdVariable iv) {
    std::cout << "  " << iv.content;
}
void outQuicknumber(Quicknumber qn) {
    std::visit([](auto&& arg) {
        using T = std::decay_t<decltype(arg)>;
        if constexpr (std::is_same_v<T, std::monostate>) {
            //std::cout << std::endl;
        } else if constexpr (std::is_same_v<T, double>) {
            std::cout << "  " << arg;
        } else {
            std::cout << "  " << arg;
        }
    }, qn);
}
void IRs::display() {
    int count = 0;
    for (auto ir : this->content) {
        std::cout << count << ':' << IROpToText(ir.op) << std::endl;
        outIdVaiable(ir.iv0);
        outIdVaiable(ir.iv1);
        outQuicknumber(ir.qn0);
        if (ir.reg0.isReg())
            std::cout << "   " << ir.reg0.getReg();
        if (ir.reg1.isReg())
            std::cout << "   " << ir.reg1.getReg() << std::endl;
        else std::cout << std::endl;
        count ++;
    }
    return ;
}

#endif