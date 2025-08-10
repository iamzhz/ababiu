#include "IR.h"
#include <iostream>

void IR::clean() {
    #ifdef DEBUG
    this->iv0 = {};
    this->iv1 = {};
    this->imm0 = {};
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

void IRs::replace(IRs & new_) {
    this->content = new_.content;
    this->pos = this->content.size();
}

#ifdef DEBUG
std::string IROpToText(IROp n) {
    switch (n) {
        case Op_none: return "none";
        case Op_pop_iv: return "pop_iv";
        case Op_push_imm: return "push_imm";
        case Op_push_iv: return "push_iv";
        case Op_push_reg: return "push_reg";
        case Op_mov_iv_iv: return "mov_iv_iv";
        case Op_mov_iv_imm: return "mov_iv_imm";
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
        case Op_jump_imm: return "jump_imm";
        case Op_jumpIfNot_imm: return "jumpIfNot_imm";
        case Op_jumpIf_imm: return "jumpIf_imm";
        case Sign_callParaBegin: return "callParaBegin";
        case Op_load_iv_reg: return "load_iv_reg";
        case Op_load_imm_reg: return "load_imm_reg";
        case Op_store_iv_reg: return "store_iv_reg";
        case Op_equal_reg_reg:  return "equal_reg_reg";
        case Op_bigger_reg_reg:  return "bigger_reg_reg";
        case Op_biggerEqual_reg_reg:  return "biggerEqual_reg_reg";
        case Op_smaller_reg_reg:  return "smaller_reg_reg";
        case Op_smallerEqual_reg_reg:  return "smallerEqual_reg_reg";
        case Op_notEqual_reg_reg:  return "notEqual_reg_reg";
        case Op_power_reg_reg:  return "power_reg_reg";
        case Op_jumpIf_imm_reg: return "jump_imm_reg";
        case Op_jumpIfNot_imm_reg: return "jumpIfNot_imm_reg";
        case Sign_defineVariable_type_iv: return "defineVariable_type_iv";
    }
    return "Error: IR.cc::IRs::display();\n";
}
void outIdVaiable(IdVariable iv) {
    std::cout << iv.content << "  ";
}
void outImmediate(Immediate imm) {
    std::cout << imm.content << "  ";
}
void IRs::display() {
    int count = 0;
    for (auto ir : this->content) {
        std::cout << count << ':' << IROpToText(ir.op) << std::endl;
        outIdVaiable(ir.iv0);
        outIdVaiable(ir.iv1);
        outImmediate(ir.imm0);
        if (ir.reg0.isReg())
            std::cout << ir.reg0.getReg() << "   ";
        if (ir.reg1.isReg())
            std::cout << ir.reg1.getReg() << "   " << std::endl;
        else std::cout << std::endl;
        count ++;
    }
    return ;
}

#endif