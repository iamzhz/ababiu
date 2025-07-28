#ifndef _STACKERASER_H_
#define _STACKERASER_H_
/*
Stack Eraser is used to convert a stack-IR to non-stack-IR
*/
#include <unordered_map>
#include <vector>
#include "../IR/IR.h"
#include "../Value/Value.h"

class StackEraser {
    private:
    std::unordered_map<int, int> lineCast; // (line number) old IR -> new IR
    IRs * irs; // the new
    IRs * old;
    std::vector<Value> stack;
    bool canBeUsed[4] = {true, true, true, true};

    Value getTempVar();

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