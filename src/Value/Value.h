#ifndef _VALUE_H_
#define _VALUE_H_
#include <string>
#include "../IR/IR.h"
class Value {
    private:
    bool isVariable; // true -> variable;  false->quicknumber
    union {
        Quicknumber qn;
        IdVariable iv;
    };
    Value operator=(const Value & o);
    Value operator=(const Quicknumber & o);
    Value operator=(const IdVariable & o);
    Value operator=(const std::string & o);
};


#endif