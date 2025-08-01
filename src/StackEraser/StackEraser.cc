#include "StackEraser.h"
#include <stdexcept>
Value StackEraser::getReg() {
    for (int i = 0;  i < REG_NUMBER;  i ++) {
        if (!this->is_used[i]) {
            this->is_used[i] = true;
            return i;
        }
    }
    return (-1); // TODO
}

StackEraser::StackEraser(IRs * irs) {
    this->old = irs;
    this->irs = new IRs();
    for (int i = 0;  i < REG_NUMBER;  i ++) {
        this->is_used[i] = false;
    }
}
void StackEraser::releaseReg(Value reg) {
    int r = reg.getReg();
    if (r < REG_NUMBER && r >= 0) {
        this->is_used[r] = false;
    } else {
        // TODO
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
            case Op_pop_iv: {
                v = this->pop();
                if (v.isVariable()) {
                    ir.op = Op_mov_iv_iv;
                    ir.iv0 = i.iv0;
                    ir.iv1 = v.getIdVariable();
                } else if (v.isQuicknumber()) {
                    ir.op = Op_mov_iv_qn;
                    ir.iv0 = i.iv0;
                    ir.qn0 = v.getQuicknumber();
                } else if (v.isReg()) {
                    ir.op = Op_store_iv_reg;
                    ir.iv0 = i.iv0;
                    ir.reg0 = v;
                }
                this->append(ir);
                break;
            }
            case Op_push_qn: {
                this->push(Value(i.qn0));
                break;
            }
            case Op_push_iv: {
                this->push(Value(i.iv0));
                break;
            }
            case Op_add: {
                Value b = this->pop();
                Value a = this->pop();
                Value a_b_regs[2];
                int regs_index = 0;
                for (Value t : {a, b}) {
                    if (t.isVariable()) {
                        ir.op = Op_load_iv_reg;
                        ir.reg0 = a_b_regs[regs_index] = this->getReg();
                        ir.iv0  = t.getIdVariable();
                        this->append(ir);
                    } else if (t.isQuicknumber()) {
                        ir.op = Op_load_qn_reg;
                        ir.reg0 = a_b_regs[regs_index] = this->getReg();
                        ir.qn0 = t.getQuicknumber();
                        this->append(ir);
                    } else if (t.isReg()) {
                        a_b_regs[regs_index] = t;
                    }
                    regs_index ++;
                }
                ir.clean();
                ir.op = Op_add_reg_reg;
                ir.reg0 = a_b_regs[0];
                ir.reg1 = a_b_regs[1];
                this->append(ir);
                this->releaseReg(a_b_regs[1]);
                this->push(a_b_regs[0]);
                break;
            }
            case Op_mov_iv_iv: // fall through
            case Op_mov_iv_qn: {
                this->append(i);
                break;
            }
            default:
                break;
        }
        n ++;
    }
    this->old->replace(*this->irs);
}