#include "../include.h"
void IRs::add(IR ir) {
    content.push_back(ir);
}

QuicknumberType getQuicknumberType(const Quicknumber& qn) {
    switch (qn.index()) {
        case 0: return QN_UNKNOWN;
        case 1: return QN_INT;
        case 2: return QN_CHAR;
        case 3: return QN_FLOAT;
        case 4: return QN_STRING;
        default: return QN_UNKNOWN;
    }
}

Quicknumber makeQuicknumber(int i) { return i;}
Quicknumber makeQuicknumber(char c) { return c;}
Quicknumber makeQuicknumber(double f)  { return f;}
Quicknumber makeQuicknumber(std::string s) { return s;}

IdVariable makeIdVariable(std::string content) {
    IdVariable iv;
    iv.content = content;
    return iv;
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