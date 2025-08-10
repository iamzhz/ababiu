#include "CodeGen.h"
#include <string>
#include <vector>
#include "../SayError/SayError.h"

std::vector<std::string> common_regs = {
    "rax", "rcx", "rdx", "r10", "r11"
};
std::vector<std::string> call_regs = {
    "rdi", "rsi", "rdx", "rcx", "r8", "r9"
};  

CodeGen::CodeGen(IRs * irs, Symbol * symbol) {
    this->irs = irs;
    this->symbol = symbol;
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
            this->append("L" + std::to_string(this->getMark()));
        }
        switch (ir.op) {
            case Op_mov_iv_iv: {
                this->append("mov " + this->symbol->get_variable_mem(ir.iv0.content) + ", " + this->symbol->get_variable_mem(ir.iv1.content));
                break;
            }
            case Op_mov_iv_imm: {
                this->append("mov " + this->symbol->get_variable_mem(ir.iv0.content) + ", " + ir.imm0.content);
                break;
            }
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
                break;
            }
            case Op_load_imm_reg: {
                this->append("mov " + common_regs[ir.reg0.getReg()] + ", " + ir.imm0.content);
                break;
            }
            case Op_store_iv_reg: {
                this->append("mov " + this->symbol->get_variable_mem(ir.iv0.content) + ", " + common_regs[ir.reg0.getReg()]);
                break;
            }
            default: break;
        }
    }
}