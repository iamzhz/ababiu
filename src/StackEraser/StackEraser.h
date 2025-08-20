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
#include "../Symbol/Symbol.h"
#include "../env_config/config.h"

class StackEraser {
    private:
    std::unordered_map<int, int> lineCast; // (line number) old IR -> new IR
    IRs * irs; // the new
    IRs * old;
    Symbol * symbol;
    std::vector<Value> stack;
    int tempCount = 0;
    int n;
    bool is_used[COMMON_REGS_NUMBER];
    std::unordered_set<int> stack_used; // stand for the real memory stack
    void markUsed(int n);
    Value getReg();
    Value getCallerReg(int number);
    void releaseReg(Value reg);
    Value loadToReg(Value t);
    Value loadToReg(Value t, Value reg);
    inline bool isStackUsed(int n); // n is a negative
    int getStack();
    void releaseStack(int n);
    
    void Handle_pop_iv(const IR & ir);
    void Handle_push_imm(const IR & ir);
    void Handle_push_iv(const IR & ir);
    void Handle_xxx(const IR & ir);
    void Handle_div(const IR & ir);
    void Handle_conditionJump_addr(const IR & ir);
    void Handle_callParaBegin(const IR & ir);
    void Handle_call_if(const IR & ir);
    void Handle_return(const IR & ir);
    void Handle_sign_sentence_end(const IR & ir);
    

    public:
    Value pop();
    void push(const Value & v);
    void append(const IR & ir);
    StackEraser(IRs * irs, Symbol * symbol);
    ~StackEraser();
    void convert();
    void replaceLineNumber();
    // ~StackEraser();
};


#endif