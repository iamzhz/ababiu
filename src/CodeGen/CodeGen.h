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

    int mark = (-1);
    int getMark();
    public:
    CodeGen(IRs * irs, Symbol * symbol);
    void generate();
    std::string get_output();
};

#endif