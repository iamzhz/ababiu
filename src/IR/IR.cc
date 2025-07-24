#include "../include.h"

int IRs::getPosition() {
    this->pos ++;
    return (this->pos - 1);
}

int IRs::add(IR ir) {
    ir.pos = this->getPosition();
    content.push_back(std::move(ir));
    return ir.pos;
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
        case Op_push_qn: return "push_qn";
        case Op_push_iv: return "push_iv";
        case Op_mov_iv_iv: return "mov_iv_iv";
        case Op_mov_iv_qn: return "mov_iv_qn";
        case Op_add: return "add";
        case Op_sub: return "sub";
        case Op_mul: return "mul";
        case Op_div: return "div";
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
    }
    return "Error: IR.cc::IRs::display();\n";
}
void outIdVaiable(IdVariable iv) {
    std::print("  {}", iv.content);
}
void outQuicknumber(Quicknumber qn) {
    std::visit([](auto&& arg) {
        using T = std::decay_t<decltype(arg)>;
        if constexpr (std::is_same_v<T, std::monostate>) {
            std::print("\n");
        } else if constexpr (std::is_same_v<T, double>) {
            std::print("  {:.2f}\n", arg);
        } else {
            std::print("  {}\n", arg);
        }
    }, qn);
}
void IRs::display() {
    for (auto ir : this->content) {
        std::print("{}:{}\n", ir.pos, IROpToText(ir.op));
        outIdVaiable(ir.iv0);
        outIdVaiable(ir.iv1);
        outQuicknumber(ir.qn0);
    }
    return ;
}

#endif