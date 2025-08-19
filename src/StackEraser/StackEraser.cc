#include "StackEraser.h"
#include <format>
#include <string>
#include "../SayError/SayError.h"
#ifdef DEBUG
#include <iostream>
#endif

void StackEraser::markUsed(int n) {
    if (n >= 0 && n < COMMON_REGS_NUMBER) {
        this->is_used[n] = true;
    }
}

Value StackEraser::getReg() {
    for (int i = 0;  i < COMMON_REGS_NUMBER;  i ++) {
        if (!this->is_used[i]) {
            this->is_used[i] = true;
            return i;
        }
    }
    return (-1); // TODO
}
Value StackEraser::getCallerReg(int number) {
    // reverse of RDI, RSI, RDX, RCX, R8, R9
    return (COMMON_REGS_NUMBER + number);
}

StackEraser::StackEraser(IRs * irs, Symbol * symbol) {
    this->old = irs;
    this->irs = new IRs();
    this->Handle_sign_sentence_end({});
    this->symbol = symbol;
}
void StackEraser::releaseReg(Value reg) {
    int r = reg.getReg();
    if (r < COMMON_REGS_NUMBER && r >= 0) {
        this->is_used[r] = false;
    } else {
        // TODO
    }
}

Value StackEraser::loadToReg(Value t) {
    return this->loadToReg(t, this->getReg());
}

Value StackEraser::loadToReg(Value t, Value reg) {
    IR ir;
    if (t.isVariable()) {
        this->append({Op_load_iv_reg, t, reg});
    } else if (t.isImmediate()) {
        this->append({Op_load_imm_reg, t, reg});
    } else if (t.isReg()) {
        if (reg.getReg() < COMMON_REGS_NUMBER) {
            this->releaseReg(reg);
            return t;
        }
        this->append({Op_mov_reg_reg, reg, t});
    }
    return reg;
}

inline bool StackEraser::isStackUsed(int n) {
    return this->stack_used.find(n) != this->stack_used.end();
}

int StackEraser::getStack() {
    int i = (-1);
    while (this->isStackUsed(i)) {
        i --;
    }
    this->stack_used.insert(i);
    return i;
}

void StackEraser::releaseStack(int n){
    if (this->isStackUsed(n)) {
        this->stack_used.erase(n);
    }
}

StackEraser::~StackEraser() {
    delete this->irs;
}

Value StackEraser::pop() {
    Value v;
    v = this->stack.back();
    this->stack.pop_back();
    return v;
}
void StackEraser::push(const Value & v) {
    this->stack.push_back(v);
}
void StackEraser::append(const IR & ir) {
    #ifdef DEBUG
    ir.display(this->n);
    #endif
    this->irs->add(ir);
}
void StackEraser::Handle_pop_iv(const IR & i) {
    Value v = this->pop();
    if (v.isVariable()) {
        Value reg = this->getReg();
        this->append({Op_load_iv_reg, v, reg});
        this->append({Op_store_iv_reg, i.val0, reg});
        this->releaseReg(reg);
    } else if (v.isImmediate()) {
        this->append({Op_mov_iv_imm, i.val0, v});
    } else if (v.isReg()) {
        this->append({Op_store_iv_reg, i.val0, v});
        this->releaseReg(v);
    }
    
}
void StackEraser::Handle_push_imm(const IR & i) {
    this->push(Value(i.val0));
}
void StackEraser::Handle_push_iv(const IR & i) {
    this->push(Value(i.val0));
}
void StackEraser::Handle_xxx(const IR & i) {
    IROp op;
    switch (i.op) {
        case Op_add: op = Op_add_reg_reg;  break;
        case Op_sub: op = Op_sub_reg_reg;  break;
        case Op_mul: op = Op_mul_reg_reg;  break;
        case Op_div: op = Op_div_reg_reg;  break;
        case Op_equal: op = Op_equal_reg_reg;  break;
        case Op_bigger: op = Op_bigger_reg_reg;  break;
        case Op_biggerEqual: op = Op_biggerEqual_reg_reg;  break;
        case Op_smaller: op = Op_smaller_reg_reg;  break;
        case Op_smallerEqual: op = Op_smallerEqual_reg_reg;  break;
        case Op_notEqual: op = Op_notEqual_reg_reg;  break;
        case Op_power: op = Op_power_reg_reg;  break;
        default: break;
    }
    Value a_reg = this->loadToReg(this->pop());
    Value b_reg = this->loadToReg(this->pop());
    this->append({op, b_reg, a_reg});
    this->releaseReg(a_reg);
    this->push(b_reg);
}
void StackEraser::Handle_conditionJump_addr(const IR & i) {
    IROp op;
    switch (i.op) {
        case Op_jumpIf_addr: op = Op_jumpIf_addr_reg; break;
        case Op_jumpIfNot_addr: op = Op_jumpIfNot_addr_reg; break;
        default: break;
    }
    Value a_reg = this->loadToReg(this->pop());
    this->append({op, i.get_addr(), a_reg});
    this->releaseReg(a_reg);
}
void StackEraser::Handle_callParaBegin(const IR & i) {
    (void)i;
    this->push(Value(static_cast<SpecialMark>(FUNCTION_CALL_PARA_HEAD)));
}
void StackEraser::Handle_call_if(const IR & i) {
    std::string func_name = i.val0.getIdVariable().content;
    SymbolValue func = this->symbol->get(func_name);
    if (func.isExist == false) {
        sayError(std::format("`{}` is not exist as a function.", func_name));
    }
    if (func.isVariable == true) {
        sayError(std::format("`{}` is a variable name.", func_name));
    }
    bool isRaxProtect = this->is_used[RAX_NUMBER];
    if (!this->stack.empty()) {
        isRaxProtect = isRaxProtect && this->stack.back() != Value(RAX_NUMBER);
    }
    if (isRaxProtect) {
        this->append({Op_push_reg, Value(RAX_NUMBER)});
    }
    std::vector<Value> parameters; // reverse of real parameters
    // reverse of RDI, RSI, RDX, RCX, R8, R9
    std::vector<Value> last6; // for register (reverse)
    int paras_size = 0;
    int last6_size;
    Value para;
    while (!(para = this->pop()).isParaHead()) {
        parameters.push_back(para);
        paras_size ++;
    }
    if (paras_size >= 6) last6_size = 6;
    else last6_size = paras_size;

    last6.assign(parameters.end() - last6_size, parameters.end());
    parameters.erase(parameters.end() - last6_size, parameters.end());

    // deal with register paras
    int reg_para_count = 0;
    for (auto it = last6.rbegin(); it != last6.rend(); ++it) {
        this->loadToReg(*it, this->getCallerReg(reg_para_count));
        reg_para_count ++;
    }
    // deal with stack paras
    for (Value stack_para : parameters) {
        Value reg = this->loadToReg(stack_para);
        this->append({Op_push_reg, reg});
        this->releaseReg(reg);
    }
    this->append(i); // call func
    if (isRaxProtect) {
        this->append({Op_mov_reg_reg, this->getReg(), RAX_NUMBER});
        this->append({Op_pop_reg, Value(RAX_NUMBER)});
    } else {
        if (func.type == TYPE_VOID) {
            return ;
        }
        this->push(Value(RAX_NUMBER));
        this->markUsed(RAX_NUMBER);
    }
}
void StackEraser::Handle_return(const IR & i) {
    (void)i;
    Value v = this->pop();
    if (v.isImmediate()) {
        this->append({Op_return_imm, v});
        return ;
    }
    Value v_reg = this->loadToReg(v);
    this->append({Op_return_reg, v_reg});
}
void StackEraser::Handle_sign_sentence_end(const IR & ir) {
    (void)ir;
    this->stack = {};
    for (int i = 0;  i < COMMON_REGS_NUMBER;  i ++) {
        this->is_used[i] = false;
    }
}
void StackEraser::convert() {
    n = 0; // this->n
    #ifdef DEBUG
    std::cout << "---------------" << std::endl;
    #endif
    Value v;
    using OpHandler = void (StackEraser::*)(const IR&);
    std::unordered_map<IROp, OpHandler> handlers = {
        {Op_pop_iv, &StackEraser::Handle_pop_iv},
        {Op_push_imm, &StackEraser::Handle_push_imm},
        {Op_push_iv, &StackEraser::Handle_push_iv},
        {Op_add, &StackEraser::Handle_xxx},
        {Op_sub, &StackEraser::Handle_xxx},
        {Op_mul, &StackEraser::Handle_xxx},
        {Op_div, &StackEraser::Handle_xxx},
        {Op_equal, &StackEraser::Handle_xxx},
        {Op_bigger, &StackEraser::Handle_xxx},
        {Op_biggerEqual, &StackEraser::Handle_xxx},
        {Op_smaller, &StackEraser::Handle_xxx},
        {Op_smallerEqual, &StackEraser::Handle_xxx},
        {Op_notEqual, &StackEraser::Handle_xxx},
        {Op_power, &StackEraser::Handle_xxx},
        {Op_jumpIf_addr, &StackEraser::Handle_conditionJump_addr},
        {Op_jumpIfNot_addr, &StackEraser::Handle_conditionJump_addr},
        {Sign_callParaBegin, &StackEraser::Handle_callParaBegin},
        {Op_call_if, &StackEraser::Handle_call_if},
        {Op_return, &StackEraser::Handle_return},
        {Sign_SentenceEnd, &StackEraser::Handle_sign_sentence_end},
    };
    for (IR i : this->old->content) {
        this->lineCast.insert({n, this->irs->pos});
        auto it = handlers.find(i.op);
        if (it != handlers.end()) {
            (this->*(it->second))(i);
        } else {
            this->append(i);
        }
        n ++;
    }
    this->lineCast.insert({n, this->irs->pos});
    this->replaceLineNumber();
    this->old->replace(*this->irs);
}
void StackEraser::replaceLineNumber() {
    int size = this->irs->content.size();
    int count = 0;
    for (IR & i : this->irs->content) {
        switch (i.op) {
            case Op_jump_addr: // fall through
            case Op_jumpIf_addr_reg:
            case Op_jumpIfNot_addr_reg: {
                int line = this->lineCast.find(i.get_addr().line)->second;
                if (line >= size) {
                    this->irs->content.push_back({Op_none});
                    size ++;
                }
                // when meet line, show L{count}:
                this->irs->marks.insert({line, count});
                count ++;
                i.set_addr(Address(line));
                break;
            }
            default: break;
        }
    }
}