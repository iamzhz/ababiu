#include "../include.h"
void IRs::add(IR ir) {
    content.push_back(ir);
}

#ifdef DEBUG
std::string IROpToText(IROp n) {
    switch (n) {
        case Op_pop_qn: return "pop_qn";
        case Op_pop_iv: return "pop_iv";
        case Op_push_iv: return "push_iv";
        case Op_mov_iv_iv: return "mov_iv_iv";
        case Op_mov_iv_qn: return "mov_iv_qn";
        case Op_add: return "add";
        case Op_sub: return "sub";
        case Op_mul: return "mul";
        case OP_div: return "div";
        case Op_call_if: return "call_if";
    }
    return "Error: IR.cc::IRs::display();\n";
}
void IRs::display() {
    for (auto ir : this->content) {
        std::cout << IROpToText(ir.op) << " \n" ;
    }
    return ;
}

#endif