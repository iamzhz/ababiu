#include "Value.h"

Value Value::operator=(const Value & o) {
    if (o.isVariable) {
        this->iv = o.iv;
    } else {
        this->qn = o.qn;
    }
}

Value Value::operator=(const Quicknumber & o) {
    this->isVariable = false;
    this->qn = o;
}

Value Value::operator=(const IdVariable & o) {
    this->isVariable = true;
    this->iv = o;
}

Value Value::operator=(const std::string & o) {
    this->isVariable = true;
    this->iv = makeIdVariable(o);
}