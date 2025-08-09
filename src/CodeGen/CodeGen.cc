#include "CodeGen.h"
#include <vector>

std::vector<std::string> common_regs = {
    "rax", "rcx", "rdx", "r10", "r11"
};
std::vector<std::string> call_regs = {
    "rdi", "rsi", "rdx", "rcx", "r8", "r9"
};  

CodeGen::CodeGen(IRs * irs) {
    this->irs = irs;
}

int CodeGen::getMark() {
    this->mark ++;
    return this->mark;
}

void CodeGen::append(std::string ins) {
    this->_output << ins << '\n';
}

std::string CodeGen::get_output() {
    return this->_output.str();
}

void CodeGen::generate() {
    for (IR ir : this->irs->content) {
        if (ir.isMarked) {
            this->append("L" + this->getMark());
        }
        switch (ir.op) {
            case Op_mov_reg_reg: // fall through
            case Op_add_reg_reg:
            case Op_sub_reg_reg:
            case Op_mul_reg_reg:
            case Op_div_reg_reg: {
                std::string opcode;
                switch (ir.op) {
                    case Op_mov_reg_reg: opcode = "mov"; break;
                    case Op_add_reg_reg: opcode = "add"; break;
                    case Op_sub_reg_reg: opcode = "sub"; break;
                    case Op_mul_reg_reg: opcode = "mul"; break;
                    case Op_div_reg_reg: opcode = "div"; break;
                    default: break;
                }
                this->append(opcode + ' ' + common_regs[ir.reg0.getReg()] + ", " + common_regs[ir.reg1.getReg()]);
            }
            default: break;
        }
    }
}