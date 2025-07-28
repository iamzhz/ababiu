#include "StackEraser.h"

StackEraser::StackEraser(IRs * irs) {
    this->old = irs;
    this->irs = new IRs();
}

StackEraser::~StackEraser() {
    delete this->irs;
}

Value StackEraser::getTempVar() {
    int i;
    Value v;
    for (i = 0;  i < 4;  i ++) {
        if (this->canBeUsed[i]) {
            v = "$" + std::to_string(i);
            this->canBeUsed[i] = false;
            return v;
        }
    }
    // TODO
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
void StackEraser::append(IR & ir) {
    this->irs->add(ir);
}

void StackEraser::convert() {
    int n = 0;
    Value v;
    for (IR i : this->old->content) {
        IR ir;
        this->lineCast.insert({n, this->irs->pos});
        switch (i.op) {
            case Op_pop_iv:
                v = this->pop();
                if (v.isVariable()) {
                    ir.op = Op_mov_iv_iv;
                    ir.iv1 = v.getIdVariable();
                } else {
                    ir.op = Op_mov_iv_qn;
                    ir.qn0 = v.getQuicknumber();
                }
                ir.iv0 = i.iv0;
                this->append(ir);
                break;
            case Op_push_qn:
                this->push(Value(i.qn0));
                break;
            case Op_push_iv:
                this->push(Value(i.iv0));
                break;
            default:
                break;
        }
        n ++;
    }
    this->old->replace(*this->irs);
}