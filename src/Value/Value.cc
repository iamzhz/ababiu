#include "Value.h"

QuicknumberType getQuicknumberType(const Quicknumber& qn) {
    switch (qn.index()) {
        case 0: return QN_UNKNOWN;
        case 1: return QN_INT;
        case 2: return QN_CHAR;
        case 3: return QN_FLOAT;
        case 4: return QN_STRING;
        default: return QN_UNKNOWN;
    }
}

Quicknumber makeQuicknumber(int i) { return i;}
Quicknumber makeQuicknumber(char c) { return c;}
Quicknumber makeQuicknumber(double f)  { return f;}
Quicknumber makeQuicknumber(std::string s) { return s;}

IdVariable makeIdVariable(std::string content) {
    IdVariable iv;
    iv.content = content;
    return iv;
}

Value::Value() {}
Value::Value(const Quicknumber & qn) {
    this->data_ = qn;
}
Value::Value(const IdVariable & iv) {
    this->data_ = iv;
}
Value::Value(const int & reg) {
    this->data_ = reg;
}
Value& Value::operator=(const Quicknumber & o) {
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
bool Value::isQuicknumber() {
    return std::holds_alternative<Quicknumber>(data_);
}
bool Value::isReg() {
    return std::holds_alternative<int>(data_);
}
const Quicknumber& Value::getQuicknumber() const {
    return std::get<Quicknumber>(data_);
}
const IdVariable& Value::getIdVariable() const {
    return std::get<IdVariable>(data_);
}
const int& Value::getReg() const {
    return std::get<int>(data_);
}