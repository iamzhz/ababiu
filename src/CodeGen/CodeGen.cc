#include "CodeGen.h"
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <format>
#include "../SayError/SayError.h"

std::vector<std::string> regs_string = {
    "rax", "r10", "r9", "r8", 
    "rcx", "rdx", "rsi", "rdi",
    
    "r11",

    "xmm0", "xmm1", "xmm2", "xmm3", 
    "xmm4", "xmm5", "xmm6", "xmm7", 
    "xmm8", "xmm9", "xmm10", "xmm11", 
    "xmm12", "xmm13", "xmm14", "xmm15"
};
std::vector<std::string> low8_regs_string = {
    "al", "r10b", "r11b", "r9b", "r8b",
    "cl", "dl", "rsi", "dil",
};
std::string CodeGen::getReg(bool isLow8, int n) {
    if (n >= 0 && n < COMMON_REGS_NUMBER) {
        return isLow8?low8_regs_string[n]:regs_string[n];
    }
    return regs_string[n];
}
inline std::string CodeGen::getReg(bool isLow8, Value reg) {
    return this->getReg(isLow8, reg.getReg());
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
    this->_output.back().code << ins << '\n';
}
std::string CodeGen::get_output() {
    std::string ret;
    ret += "section .rodata\n" +
            this->literal.get_rodata() +
            "section .text\n"
            "extern print\n"
            "extern input\n"
            "extern pow\n";
    for (FuncData & _o : this->_output) {
        ret += std::format(
            "\n"
            "global {}\n"
            "{}:\n"
            "push rbp\n"
            "mov rbp, rsp\n"
            "sub rsp, {}\n"
            "{}"
        , _o.name, _o.name, _o.allocate, _o.code.str());
    }
    return ret;
}

void CodeGen::Handle_newFunction_iv(const IR & ir) {
    std::string func_name = ir.val0.getIdVariable().content;
    this->symbol->new_scope();
    this->_output.push_back(FuncData{
        .allocate=0, // not important
        .name=func_name,
        .code=std::stringstream()
    });
    SymbolValue func = this->symbol->get(func_name);
    // rdi, rsi, rdx, rcx, r8, r9
    int int_regs[] = {
        RDI_NUMBER, RSI_NUMBER, RDX_NUMBER, 
        RCX_NUMBER, R8_NUMBER, R9_NUMBER,
    };
    int float_regs[] = {
        XMM0_NUMBER, XMM1_NUMBER, XMM2_NUMBER, XMM3_NUMBER,
        XMM4_NUMBER, XMM5_NUMBER, XMM6_NUMBER, XMM7_NUMBER,
    };
    int int_count = 0;
    int float_count = 0;
    for (const FunctionArg & arg : func.args) {
        if (arg.type == TYPE_INT) {
            this->symbol->insert_variable(arg.name, TYPE_INT);
            this->append(std::format(
                "mov {}, {}",
                this->symbol->get_variable_mem(arg.name),
                this->getReg(int_regs[int_count])
            ));
            ++ int_count;
        } else if (arg.type == TYPE_FLOAT) {
            this->symbol->insert_variable(arg.name, TYPE_FLOAT);
            this->append(std::format(
                "movsd {}, {}",
                this->symbol->get_variable_mem(arg.name),
                this->getReg(float_regs[float_count])
            ));
            ++ float_count;
        }
    }
}

void CodeGen::Handle_endFunction(const IR & ir) {
    (void)ir;
    int allocate = -this->symbol->exit_scope();
    allocate = (allocate + 15) & ~15;
    this->_output.back().allocate = allocate;
}
void CodeGen::Handle_sign_defineVariable_type_iv(const IR & ir) {
    TypeType var_type = ir.val0.getType();
    std::string var_name = ir.val1.getIdVariable().content;
    this->symbol->insert_variable(var_name, var_type);
}
void CodeGen::Handle_mov_iv_imm(const IR & ir) {
    std::string opcode;
    if (this->symbol->get_variable(ir.val0).type == TYPE_FLOAT) {
        opcode = "movsd";
    } else {
        opcode = "mov";
    }
    this->append(std::format("{} {}, {}",
        opcode,
        this->symbol->get_variable_mem(ir.val0),
        this->literal.get(ir.val1)
    ));
}
void CodeGen::Handle_xxx_reg_reg(const IR & ir) {
    std::string opcode;
    switch (ir.op) {
        case Op_mov_reg_reg: {
            int reg_int = ir.val0.getReg();
            if (reg_int >= XMM0_NUMBER && reg_int < XMM0_NUMBER + XMM_NUMBER) {
                opcode = "movsd";
            } else {
                opcode = "mov";
            }
            break;
        }
        case Op_add_reg_reg: opcode = "add"; break;
        case Op_sub_reg_reg: opcode = "sub"; break;
        case Op_mul_reg_reg: opcode = "imul"; break;
        default: break;
    }
    this->append(opcode + ' ' + this->getReg(ir.val0) + ", " + this->getReg(ir.val1));
}
void CodeGen::Handle_xxxsd_reg_reg(const IR & ir) {
    std::string opcode;
    switch (ir.op) {
        case Op_addsd_reg_reg: opcode = "add"; break;
        case Op_subsd_reg_reg: opcode = "sub"; break;
        case Op_mulsd_reg_reg: opcode = "mul"; break;
        case Op_divsd_reg_reg: opcode = "div"; break;
        default:
            sayError("CodeGen::Handle_xxxsd_reg_reg()");
    }
    this->append(std::format("{}sd {}, {}",
        opcode,
        this->getReg(ir.val0),
        this->getReg(ir.val1)
    ));
}
void CodeGen::Handle_idiv_val(const IR & ir) {
    if (ir.val0.isReg()) {
        this->append("idiv " + this->getReg(ir.val0));
    } else if (ir.val0.isImmediate()) {
        this->append("idiv " + ir.val0.getImmediate().content);
    } else if (ir.val0.isVariable()) {
        this->append("idiv " + this->symbol->get_variable_mem(ir.val0));
    }else {
        sayError("Unkown type");
    }
}
void CodeGen::Handle_cqo(const IR & ir) {
    (void)ir;
    this->append("cqo");
}
void CodeGen::Handle_load_imm_reg(const IR & ir) {
    std::string opcode;
    if (ir.val0.getImmediate().type == TYPE_FLOAT) {
        opcode = "movsd";
    } else {
        opcode = "mov";
    }
    this->append(std::format("{} {}, {}",
        opcode,
        this->getReg(ir.val1),
        this->literal.get(ir.val0)
    ));
}
void CodeGen::Handle_load_iv_reg(const IR & ir) {
    std::string opcode;
    if (this->symbol->get_variable(ir.val0).type == TYPE_FLOAT) {
        opcode = "movsd";
    } else {
        opcode = "mov";
    }
    this->append(std::format("{} {}, {}",
        opcode,
        this->getReg(ir.val1),
        this->symbol->get_variable_mem(ir.val0))
    );
}
void CodeGen::Handle_store_iv_reg(const IR & ir) {
    std::string opcode;
    if (this->symbol->get_variable(ir.val0).type == TYPE_FLOAT) {
        opcode = "movsd";
    } else {
        opcode = "mov";
    }
    this->append(std::format("{} {},{}",
        opcode,
        this->symbol->get_variable_mem(ir.val0),
        this->getReg(ir.val1)
    ));
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
    std::string low8_reg0 = this->getReg(true, ir.val0);
    switch (ir.op) {
        case Op_equal_reg_reg: opcode = "sete"; break;
        case Op_bigger_reg_reg: opcode = "setg"; break;
        case Op_biggerEqual_reg_reg: opcode = "setge"; break;
        case Op_smaller_reg_reg: opcode = "setl"; break;
        case Op_smallerEqual_reg_reg: opcode = "setle"; break;
        case Op_notEqual_reg_reg: opcode = "setne"; break;
        default: break;
    }
    this->append("cmp " + reg0 + ", " + reg1);
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
        {Sign_newFunction_iv, &CodeGen::Handle_newFunction_iv},
        {Sign_endFunction, &CodeGen::Handle_endFunction},
        {Sign_defineVariable_type_iv, &CodeGen::Handle_sign_defineVariable_type_iv},
        {Op_mov_iv_imm, &CodeGen::Handle_mov_iv_imm},
        {Op_mov_reg_reg, &CodeGen::Handle_xxx_reg_reg},
        {Op_add_reg_reg, &CodeGen::Handle_xxx_reg_reg},
        {Op_sub_reg_reg, &CodeGen::Handle_xxx_reg_reg},
        {Op_mul_reg_reg, &CodeGen::Handle_xxx_reg_reg},
        {Op_idiv_val, &CodeGen::Handle_idiv_val},
        {Op_cqo, &CodeGen::Handle_cqo},
        {Op_addsd_reg_reg, &CodeGen::Handle_xxxsd_reg_reg},
        {Op_subsd_reg_reg, &CodeGen::Handle_xxxsd_reg_reg},
        {Op_mulsd_reg_reg, &CodeGen::Handle_xxxsd_reg_reg},
        {Op_divsd_reg_reg, &CodeGen::Handle_xxxsd_reg_reg},
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