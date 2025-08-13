#include "CodeGen.h"
#include <string>
#include <vector>
#include <unordered_map>

std::vector<std::string> common_regs = {
    "rax", "rcx", "rdx", "r10", "r11"
};
std::vector<std::string> common_low8_regs = {
    "al", "cl", "dl", "r10b", "r11b"
};
std::vector<std::string> call_regs = {
    "rdi", "rsi", "rdx", "rcx", "r8", "r9"
};

std::string CodeGen::getReg(bool isLow8, int n) {
    if (n >= 0 && n < COMMON_REGS_NUMBER) {
        return isLow8?common_low8_regs[n]:common_regs[n];
    }
    return call_regs[n-COMMON_REGS_NUMBER];
}
inline std::string CodeGen::getReg(int n) {
    return this->getReg(false, n);
}
std::string CodeGen::getReg(const Value & reg) {
    return this->getReg(reg.getReg());
}

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

void CodeGen::Handle_mov_iv_iv(const IR & ir) {
    this->append("mov " + this->symbol->get_variable_mem(ir.iv0.content) + ", " + this->symbol->get_variable_mem(ir.iv1.content));
}
void CodeGen::Handle_mov_iv_imm(const IR & ir) {
    this->append("mov " + this->symbol->get_variable_mem(ir.iv0.content) + ", " + ir.imm0.content);
}
void CodeGen::Handle_xxx_reg_reg(const IR & ir) {
    std::string opcode;
    switch (ir.op) {
        case Op_mov_reg_reg: opcode = "mov"; break;
        case Op_add_reg_reg: opcode = "add"; break;
        case Op_sub_reg_reg: opcode = "sub"; break;
        case Op_mul_reg_reg: opcode = "mul"; break;
        case Op_div_reg_reg: opcode = "div"; break;
        default: break;
    }
    this->append(opcode + ' ' + this->getReg(ir.reg0) + ", " + this->getReg(ir.reg1));
}
void CodeGen::Handle_load_imm_reg(const IR & ir) {
    this->append("mov " + this->getReg(ir.reg0) + ", " + ir.imm0.content);
}
void CodeGen::Handle_load_iv_reg(const IR & ir) {
    this->append("mov " + this->getReg(ir.reg0) + ", " + this->symbol->get_variable_mem(ir.iv0.content));
}
void CodeGen::Handle_store_iv_reg(const IR & ir) {
    this->append("mov " + this->symbol->get_variable_mem(ir.iv0.content) + ", " + this->getReg(ir.reg0));
}
void CodeGen::Handle_jump_imm(const IR & ir) {
    this->append("jmp L" + std::to_string(this->irs->marks[ir.imm0.content]));
}
void CodeGen::Handle_jumpIf_imm_reg(const IR & ir) {
    this->append("test " + this->getReg(ir.reg0) + ", " + this->getReg(ir.reg1));
                this->append("jne L" + std::to_string(this->irs->marks[ir.imm0.content]));
}
void CodeGen::Handle_jumpIfNot_imm_reg(const IR & ir) {
    this->append("test " + this->getReg(ir.reg0) + ", " + this->getReg(ir.reg0));
    this->append("je L" + std::to_string(this->irs->marks[ir.imm0.content]));
}
void CodeGen::Handle_compare_reg_reg(const IR & ir) {
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
    this->append("cmp " + this->getReg(ir.reg0) + ", " + this->getReg(ir.reg1));
    this->append(opcode + " " + common_low8_regs[ir.reg0.getReg()]);
    this->append("movzx " + this->getReg(ir.reg0) + ", " + common_low8_regs[ir.reg0.getReg()]);
}

void CodeGen::generate() {
    int count = 0;
    for (IR ir : this->irs->content) {
        auto mark = this->irs->marks.find(std::to_string(count));
        if (mark != this->irs->marks.end()) {
            this->append("L" + std::to_string(mark->second) + ":");
        }
        using OpHandler = void (CodeGen::*)(const IR&);
        std::unordered_map<IROp, OpHandler> handlers = {
            {Op_mov_iv_iv, &CodeGen::Handle_mov_iv_iv},
            {Op_mov_iv_imm, &CodeGen::Handle_mov_iv_imm},
            {Op_mov_reg_reg, &CodeGen::Handle_xxx_reg_reg},
            {Op_add_reg_reg, &CodeGen::Handle_xxx_reg_reg},
            {Op_sub_reg_reg, &CodeGen::Handle_xxx_reg_reg},
            {Op_mul_reg_reg, &CodeGen::Handle_xxx_reg_reg},
            {Op_div_reg_reg, &CodeGen::Handle_xxx_reg_reg},
            {Op_load_imm_reg, &CodeGen::Handle_load_imm_reg},
            {Op_load_iv_reg, &CodeGen::Handle_load_iv_reg},
            {Op_store_iv_reg, &CodeGen::Handle_store_iv_reg},
            {Op_jump_imm, &CodeGen::Handle_jump_imm},
            {Op_jumpIf_imm_reg, &CodeGen::Handle_jumpIf_imm_reg},
            {Op_jumpIfNot_imm_reg, &CodeGen::Handle_jumpIfNot_imm_reg},
            {Op_equal_reg_reg, &CodeGen::Handle_compare_reg_reg},
            {Op_bigger_reg_reg, &CodeGen::Handle_compare_reg_reg},
            {Op_biggerEqual_reg_reg, &CodeGen::Handle_compare_reg_reg},
            {Op_smaller_reg_reg, &CodeGen::Handle_compare_reg_reg},
            {Op_smallerEqual_reg_reg, &CodeGen::Handle_compare_reg_reg},
            {Op_notEqual_reg_reg, &CodeGen::Handle_compare_reg_reg},
        };
        auto it = handlers.find(ir.op);
        if (it != handlers.end()) {
            (this->*(it->second))(ir);
        }
        count ++;
    }
}