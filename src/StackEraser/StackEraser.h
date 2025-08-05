#ifndef _STACKERASER_H_
#define _STACKERASER_H_
/*
Stack Eraser is used to convert a stack-IR to non-stack-IR
*/
#include <unordered_map>
#include <unordered_set>
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
    std::unordered_set<int> stack_used; // stand for the real memory stack
    Value getReg();
    Value getCallerReg(int number);
    void releaseReg(Value reg);
    Value loadToReg(Value t);
    Value loadToReg(Value t, Value reg);
    inline bool isStackUsed(int n); // n is a negative
    int getStack();
    void releaseStack(int n);
    public:
    Value pop();
    void push(const Value & v);
    void append(IR & ir);
    StackEraser(IRs * irs);
    ~StackEraser();
    void convert();
    void replaceLineNumber();
    // ~StackEraser();
};


#endif