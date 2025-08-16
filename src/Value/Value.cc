#include "Value.h"
#include <string>

TypeType getImmediateType(const Immediate& imm) {
    return imm.type;
}

Immediate makeImmediate(TypeType type, std::string s) {
    Immediate imm;
    imm.type = type;
    imm.content = s;
    return imm;
}

Immediate makeImmediate(int i) {
    return makeImmediate(TYPE_INT,  std::to_string(i));
}

IdVariable makeIdVariable(std::string content) {
    IdVariable iv;
    iv.content = content;
    return iv;
}

Value::Value() {}
Value::Value(const Immediate & imm) {
    this->data_ = imm;
}
Value::Value(const std::string & iv_name) {
    this->data_ = makeIdVariable(iv_name);
}
Value::Value(const IdVariable & iv) {
    this->data_ = iv;
}
Value::Value(const int & reg) {
    this->data_ = reg;
}
Value::Value(const TypeType & type) {
    this->data_ = type;
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