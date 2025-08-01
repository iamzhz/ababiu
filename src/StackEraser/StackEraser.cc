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
    IROp temp_op;
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
                } else if (v.isImmediate()) {
                    ir.op = Op_mov_iv_imm;
                    ir.iv0 = i.iv0;
                    ir.imm0 = v.getImmediate();
                } else if (v.isReg()) {
                    ir.op = Op_store_iv_reg;
                    ir.iv0 = i.iv0;
                    ir.reg0 = v;
                }
                this->append(ir);
                break;
            }
            case Op_push_imm: {
                this->push(Value(i.imm0));
                break;
            }
            case Op_push_iv: {
                this->push(Value(i.iv0));
                break;
            }
            case Op_add: // fall through
            case Op_sub:
            case Op_mul:
            case Op_div:
            case Op_equal:
            case Op_bigger:
            case Op_biggerEqual:
            case Op_smaller:
            case Op_smallerEqual:
            case Op_notEqual:
            case Op_power: {
                switch (i.op) {
                    case Op_add: temp_op = Op_add_reg_reg;  break;
                    case Op_sub: temp_op = Op_sub_reg_reg;  break;
                    case Op_mul: temp_op = Op_mul_reg_reg;  break;
                    case Op_div: temp_op = Op_div_reg_reg;  break;
                    case Op_equal: temp_op = Op_equal_reg_reg;  break;
                    case Op_bigger: temp_op = Op_bigger_reg_reg;  break;
                    case Op_biggerEqual: temp_op = Op_biggerEqual_reg_reg;  break;
                    case Op_smaller: temp_op = Op_smaller_reg_reg;  break;
                    case Op_smallerEqual: temp_op = Op_smallerEqual_reg_reg;  break;
                    case Op_notEqual: temp_op = Op_notEqual_reg_reg;  break;
                    case Op_power: temp_op = Op_power_reg_reg;  break;
                    default: break;
                }
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
                    } else if (t.isImmediate()) {
                        ir.op = Op_load_imm_reg;
                        ir.reg0 = a_b_regs[regs_index] = this->getReg();
                        ir.imm0 = t.getImmediate();
                        this->append(ir);
                    } else if (t.isReg()) {
                        a_b_regs[regs_index] = t;
                    }
                    regs_index ++;
                }
                ir.clean();
                ir.op = temp_op;
                ir.reg0 = a_b_regs[0];
                ir.reg1 = a_b_regs[1];
                this->append(ir);
                this->releaseReg(a_b_regs[1]);
                this->push(a_b_regs[0]);
                break;
            }
            case Op_mov_iv_iv: // fall through
            case Op_mov_iv_imm: {
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