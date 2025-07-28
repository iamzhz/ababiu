#include "Value.h"

Value::Value() {}
Value::Value(const Quicknumber & qn) {
    this->data_ = qn;
}
Value::Value(const IdVariable & iv) {
    this->data_ = iv;
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
const Quicknumber& Value::getQuicknumber() const {
    return std::get<Quicknumber>(data_);
}
const IdVariable& Value::getIdVariable() const {
    return std::get<IdVariable>(data_);
}