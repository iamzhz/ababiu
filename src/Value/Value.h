#ifndef _VALUE_H_
#define _VALUE_H_
#include <string>
#include <variant>
#include "../IR/IR.h"
class Value {
    private:
    std::variant<Quicknumber, IdVariable> data_;
    public:
    Value();
    Value(const Value & o) = default;
    Value(const Quicknumber & qn);
    Value(const IdVariable & iv);
    ~Value() = default;
    Value& operator=(const Value & o) = default;
    Value& operator=(const Quicknumber & o);
    Value& operator=(const IdVariable & o);
    Value& operator=(const std::string & o);
    bool isVariable();
    const Quicknumber& getQuicknumber() const;
    const IdVariable& getIdVariable() const;

};


#endif