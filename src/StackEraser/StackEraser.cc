#include "StackEraser.h"
#include <stdexcept>
#include <iostream>
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
                    ir.clean();
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
            case Op_jumpIf_imm: // fall through
            case Op_jumpIfNot_imm: {
                switch (i.op) {
                    case Op_jumpIf_imm: temp_op = Op_jumpIf_imm_reg; break;
                    case Op_jumpIfNot_imm: temp_op = Op_jumpIfNot_imm_reg; break;
                    default: break;
                }
                Value a = this->pop();
                Value a_reg;
                if (a.isVariable()) {
                    ir.op = Op_load_iv_reg;
                    ir.iv0 = a.getIdVariable();
                    ir.reg0 = a_reg = this->getReg();
                    this->append(ir);
                } else if (a.isImmediate()) {
                    ir.op = Op_load_imm_reg;
                    ir.imm0 = a.getImmediate();
                    ir.reg0 = a_reg = this->getReg();
                    this->append(ir);
                } else if (a.isReg()) {
                    a_reg = a;
                }
                ir.clean();
                ir.op = temp_op;
                ir.imm0 = i.imm0;
                ir.reg0 = a_reg;
                this->append(ir);
                this->releaseReg(a_reg);
                break;
            }
            case Sign_callParaBegin: {
                this->push(Value(FUNCTION_CALL_PARA_HEAD));
                break;
            }
            case Op_call_if: {
                std::vector<Value> parameters; // reverse of real parameters
                // reverse of RDI, RSI, RDX, RCX, R8, R9
                std::vector<Value> last6; // for register (reverse)
                int paras_size = 0;
                int last6_size;
                Value para;
                while ((para = this->pop()).isParaHead()) {
                    parameters.push_back(para);
                    paras_size ++;
                }
                if (paras_size > 6) last6_size = 6;
                else last6_size = paras_size;

                last6.assign(parameters.end() - last6_size, parameters.end());
                parameters.erase(parameters.end() - last6_size, parameters.end());

                // TODO
                break;
            }
            default: {
                this->append(i);
                break;
            }
        }
        n ++;
    }
    this->lineCast.insert({n, this->irs->pos});
    this->replaceLineNumber();
    this->old->replace(*this->irs);
}

void StackEraser::replaceLineNumber() {
    for (IR & i : this->irs->content) {
        switch (i.op) {
            case Op_jumpIf_imm_reg: // fall through
            case Op_jumpIfNot_imm_reg: {
                i.imm0 = makeImmediate(this->lineCast.find(getImmediateInt(i.imm0))->second);
                break;
            }
            default: break;
        }
    }
}