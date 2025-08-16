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
    int allocate = -this->symbol->i;
    allocate = (allocate + 15) & ~15;
    return  "section .rodata\n" +
            this->literal.get_rodata() +
            "section .text\n"
            "extern print\n"
            "extern input\n"
            "global main\n"
            "main:\n"
            "push rbp\n"
            "mov rbp, rsp\n"
            "sub rsp, " + std::to_string(allocate) + "\n"
            + this->_output.str() +
            "xor rax, rax\n"
            "leave\n"
            "ret\n"
            "\n";
}

void CodeGen::Handle_mov_iv_iv(const IR & ir) {
    this->append("mov " + this->symbol->get_variable_mem(ir.val0) + ", " + this->symbol->get_variable_mem(ir.val1));
}
void CodeGen::Handle_mov_iv_imm(const IR & ir) {
    this->append("mov " + this->symbol->get_variable_mem(ir.val0) + ", " + this->literal.get(ir.val1));
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
    this->append(opcode + ' ' + this->getReg(ir.val0) + ", " + this->getReg(ir.val1));
}
void CodeGen::Handle_load_imm_reg(const IR & ir) {
    this->append("mov " + this->getReg(ir.val1) + ", " + this->literal.get(ir.val0));
}
void CodeGen::Handle_load_iv_reg(const IR & ir) {
    this->append("mov " + this->getReg(ir.val1) + ", " + this->symbol->get_variable_mem(ir.val0));
}
void CodeGen::Handle_store_iv_reg(const IR & ir) {
    this->append("mov " + this->symbol->get_variable_mem(ir.val0) + ", " + this->getReg(ir.val1));
}
void CodeGen::Handle_jump_addr(const IR & ir) {
    this->append("jmp L" + std::to_string(this->irs->marks[ir.get_addr().line]));
}
void CodeGen::Handle_jumpIf_addr_reg(const IR & ir) {
    this->append("test " + this->getReg(ir.val0) + ", " + this->getReg(ir.val0));
    this->append("jne L" + std::to_string(this->irs->marks[ir.get_addr().line]));
}
void CodeGen::Handle_jumpIfNot_addr_reg(const IR & ir) {
    this->append("test " + this->getReg(ir.val0) + ", " + this->getReg(ir.val0));
    this->append("je L" + std::to_string(this->irs->marks[ir.get_addr().line]));
}
void CodeGen::Handle_compare_reg_reg(const IR & ir) {
    std::string opcode;
    std::string reg0 = this->getReg(ir.val0);
    std::string reg1 = this->getReg(ir.val1);
    std::string low8_reg0 = common_low8_regs[ir.val0.getReg()];
    switch (ir.op) {
        case Op_equal_reg_reg: opcode = "sete"; break;
        case Op_bigger_reg_reg: opcode = "setg"; break;
        case Op_biggerEqual_reg_reg: opcode = "setge"; break;
        case Op_smaller_reg_reg: opcode = "setl"; break;
        case Op_smallerEqual_reg_reg: opcode = "setle"; break;
        case Op_notEqual_reg_reg: opcode = "setne"; break;
        default: break;
    }
    this->append("cmp " + reg1 + ", " + reg0);
    this->append(opcode + " " + low8_reg0);
    this->append("movzx " + reg0 + ", " + low8_reg0);
}
void CodeGen::Handle_push_imm(const IR & ir) {
    this->append("push " + ir.val0.getImmediate().content);
}
void CodeGen::Handle_push_iv(const IR & ir) {
    this->append("push " + this->symbol->get_variable_mem(ir.val0));
}
void CodeGen::Handle_push_reg(const IR & ir) {
    this->append("push " + this->getReg(ir.val0));
}
void CodeGen::Handle_pop_reg(const IR & ir) {
    this->append("pop " + this->getReg(ir.val0));
}
void CodeGen::Handle_pop_iv(const IR & ir) {
    this->append("pop " + this->symbol->get_variable_mem(ir.val0));
}
void CodeGen::Handle_call_if(const IR & ir) {
    this->append("call " + ir.val0.getIdVariable().content);
}
void CodeGen::Handle_return_imm(const IR & ir) {
    if (ir.val0.getImmediate().content == "0") {
        this->append("xor rax, rax");
    } else {
        this->append("mov rax, " + ir.val0.getImmediate().content);
    }
    this->append("leave");
    this->append("ret");
}
void CodeGen::Handle_return_reg(const IR & ir) {
    if (ir.val0.getReg() != RAX_NUMBER) {
        this->append("mov rax, " + this->getReg(ir.val0));
    }
    this->append("leave");
    this->append("ret");
}

void CodeGen::generate() {
    int count = 0;
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
        {Op_jump_addr, &CodeGen::Handle_jump_addr},
        {Op_jumpIf_addr_reg, &CodeGen::Handle_jumpIf_addr_reg},
        {Op_jumpIfNot_addr_reg, &CodeGen::Handle_jumpIfNot_addr_reg},
        {Op_equal_reg_reg, &CodeGen::Handle_compare_reg_reg},
        {Op_bigger_reg_reg, &CodeGen::Handle_compare_reg_reg},
        {Op_biggerEqual_reg_reg, &CodeGen::Handle_compare_reg_reg},
        {Op_smaller_reg_reg, &CodeGen::Handle_compare_reg_reg},
        {Op_smallerEqual_reg_reg, &CodeGen::Handle_compare_reg_reg},
        {Op_notEqual_reg_reg, &CodeGen::Handle_compare_reg_reg},
        {Op_push_imm, &CodeGen::Handle_push_imm},
        {Op_push_iv, &CodeGen::Handle_push_iv},
        {Op_push_reg, &CodeGen::Handle_push_reg},
        {Op_pop_reg, &CodeGen::Handle_pop_reg},
        {Op_pop_iv, &CodeGen::Handle_pop_iv},
        {Op_call_if, &CodeGen::Handle_call_if},
        {Op_return_imm, &CodeGen::Handle_return_imm},
        {Op_return_reg, &CodeGen::Handle_return_reg},
    };
    for (IR ir : this->irs->content) {
        auto mark = this->irs->marks.find(count);
        if (mark != this->irs->marks.end()) {
            this->append("L" + std::to_string(mark->second) + ":");
        }
        auto it = handlers.find(ir.op);
        if (it != handlers.end()) {
            (this->*(it->second))(ir);
        }
        count ++;
    }
}