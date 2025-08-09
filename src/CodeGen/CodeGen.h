#ifndef _CODEGEN_H_
#define _CODEGEN_H_
#include <sstream>
#include <string>
#include "../IR/IR.h"
#include "../env_config/config.h"

class CodeGen {
    private:
    std::stringstream _output;
    void append(std::string ins);
    IRs * irs;

    int mark = (-1);
    int getMark();
    public:
    CodeGen(IRs * irs);
    void generate();
    std::string get_output();
};

#endif