#ifndef _CODEGEN_H_
#define _CODEGEN_H_
#include <sstream>
#include <string>
#include "../IR/IR.h"
#include "../Symbol/Symbol.h"
#include "../env_config/config.h"

class CodeGen {
    private:
    std::stringstream _output;
    void append(std::string ins);
    IRs * irs;
    Symbol * symbol;

    std::string getReg(bool isLow8, int n);
    inline std::string getReg(int n);
    std::string getReg(const Value & reg);

    void Handle_mov_iv_iv(const IR & ir);
    void Handle_mov_iv_imm(const IR & ir);
    void Handle_xxx_reg_reg(const IR & ir);
    void Handle_load_imm_reg(const IR & ir);
    void Handle_load_iv_reg(const IR & ir);
    void Handle_store_iv_reg(const IR & ir);
    void Handle_jump_imm(const IR & ir);
    void Handle_jumpIf_imm_reg(const IR & ir);
    void Handle_jumpIfNot_imm_reg(const IR & ir);
    void Handle_compare_reg_reg(const IR & ir);
    void Handle_push_imm(const IR & ir);
    void Handle_push_iv(const IR & ir);
    void Handle_push_reg(const IR & ir);
    void Handle_call_if(const IR & ir);
    
    public:
    CodeGen(IRs * irs, Symbol * symbol);
    void generate();
    std::string get_output();
};

#endif