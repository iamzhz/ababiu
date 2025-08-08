#include "Value.h"

TypeType getImmediateType(const Immediate& imm) {
    switch (imm.index()) {
        case 0: return TYPE_UNKNOWN;
        case 1: return TYPE_INT;
        case 2: return TYPE_CHAR;
        case 3: return TYPE_FLOAT;
        case 4: return TYPE_STRING;
        default: return TYPE_UNKNOWN;
    }
}

Immediate makeImmediate(int i) { return i;}
Immediate makeImmediate(char c) { return c;}
Immediate makeImmediate(double f)  { return f;}
Immediate makeImmediate(std::string s) { return s;}

int getImmediateInt(Immediate imm) {
    return std::get<int>(imm);
}

IdVariable makeIdVariable(std::string content) {
    IdVariable iv;
    iv.content = content;
    return iv;
}

Value::Value() {}
#include <iostream>
Value::Value(const Immediate & imm) {
    this->data_ = imm;
}
Value::Value(const IdVariable & iv) {
    this->data_ = iv;
}
Value::Value(const int & reg) {
    this->data_ = reg;
}
Value::Value(const SpecialMark & spm) {
    this->data_ = spm;
}
Value& Value::operator=(const Immediate & o) {
    this->data_ = o;
    return *this;
}

Value& Value::operator=(const IdVariable & o) {
    this->data_ = o;
    return *this;
}

Value& Value::operator=(const std::string & o) {
    this->data_ = makeIdVariable(o);
    return *this;
}
bool Value::isVariable() {
    return std::holds_alternative<IdVariable>(data_);
}
bool Value::isImmediate() {
    return std::holds_alternative<Immediate>(data_);
}
bool Value::isReg() {
    return std::holds_alternative<int>(data_);
}
bool Value::isParaHead() {
    if (!std::holds_alternative<SpecialMark>(data_)) {
        return false;
    }
    return (FUNCTION_CALL_PARA_HEAD == std::get<SpecialMark>(data_));
}
const Immediate& Value::getImmediate() const {
    return std::get<Immediate>(data_);
}
const IdVariable& Value::getIdVariable() const {
    return std::get<IdVariable>(data_);
}
const int& Value::getReg() const {
    return std::get<int>(data_);
}