#ifndef _STACKERASER_H_
#define _STACKERASER_H_
/*
Stack Eraser is used to convert a stack-IR to non-stack-IR
*/
#include <unordered_map>
#include <vector>
#include "../IR/IR.h"
#include "../Value/Value.h"

#define REG_NUMBER_X86_64 12
#define REG_NUMBER REG_NUMBER_X86_64

class StackEraser {
    private:
    std::unordered_map<int, int> lineCast; // (line number) old IR -> new IR
    IRs * irs; // the new
    IRs * old;
    std::vector<Value> stack;
    int tempCount = 0;
    bool is_used[REG_NUMBER];
    Value getReg();
    void releaseReg(Value reg);
    public:
    Value pop();
    void push(const Value & v);
    void append(IR & ir);
    StackEraser(IRs * irs);
    ~StackEraser();
    void convert();
    // ~StackEraser();
};


#endif