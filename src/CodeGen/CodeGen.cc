#include "CodeGen.h"
#include <string>
#include <vector>

std::vector<std::string> common_regs = {
    "rax", "rcx", "rdx", "r10", "r11"
};
std::vector<std::string> common_low8_regs = {
    "al", "cl", "dl", "r10b", "r11b"
};
std::vector<std::string> call_regs = {
    "rdi", "rsi", "rdx", "rcx", "r8", "r9"
};  

CodeGen::CodeGen(IRs * irs, Symbol * symbol) {
    this->irs = irs;
    this->symbol = symbol;
}

void CodeGen::append(std::string ins) {
    this->_output << ins << '\n';
}

std::string CodeGen::get_output() {
    return this->_output.str();
}

void CodeGen::generate() {
    int count = 0;
    for (IR ir : this->irs->content) {
        auto mark = this->irs->marks.find(std::to_string(count));
        if (mark != this->irs->marks.end()) {
            this->append("L" + std::to_string(mark->second) + ":");
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
            case Op_load_iv_reg: {
                this->append("mov " + common_regs[ir.reg0.getReg()] + ", " + this->symbol->get_variable_mem(ir.iv0.content));
                break;
            }
            case Op_store_iv_reg: {
                this->append("mov " + this->symbol->get_variable_mem(ir.iv0.content) + ", " + common_regs[ir.reg0.getReg()]);
                break;
            }
            case Op_jump_imm: {
                this->append("jmp L" + std::to_string(this->irs->marks[ir.imm0.content]));
                break;
            }
            case Op_jumpIf_imm_reg: {
                this->append("test " + common_regs[ir.reg0.getReg()] + ", " + common_regs[ir.reg0.getReg()]);
                this->append("jne L" + std::to_string(this->irs->marks[ir.imm0.content]));
                break;
            }
            case Op_jumpIfNot_imm_reg: {
                this->append("test " + common_regs[ir.reg0.getReg()] + ", " + common_regs[ir.reg0.getReg()]);
                this->append("je L" + std::to_string(this->irs->marks[ir.imm0.content]));
                break;
            }
            case Op_equal_reg_reg:  // fall through
            case Op_bigger_reg_reg:
            case Op_biggerEqual_reg_reg:
            case Op_smaller_reg_reg:
            case Op_smallerEqual_reg_reg:
            case Op_notEqual_reg_reg: {
                std::string opcode;
                switch (ir.op) {
                    case Op_equal_reg_reg: opcode = "sete"; break;
                    case Op_bigger_reg_reg: opcode = "seta"; break;
                    case Op_biggerEqual_reg_reg: opcode = "setae"; break;
                    case Op_smaller_reg_reg: opcode = "setb"; break;
                    case Op_smallerEqual_reg_reg: opcode = "setbe"; break;
                    case Op_notEqual_reg_reg: opcode = "setne"; break;
                    default: break;
                }
                this->append("cmp " + common_regs[ir.reg0.getReg()] + ", " + common_regs[ir.reg1.getReg()]);
                this->append(opcode + " " + common_low8_regs[ir.reg0.getReg()]);
                this->append("movzx " + common_regs[ir.reg0.getReg()] + ", " + common_low8_regs[ir.reg0.getReg()]);
                break;
            }
            default: break;
        }
        count ++;
    }
}