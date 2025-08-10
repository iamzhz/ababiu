#ifndef _VALUE_H_
#define _VALUE_H_
#include <string>
#include <variant>
enum TypeType {
    TYPE_UNKNOWN, 
    TYPE_INT, 
    TYPE_CHAR, 
    TYPE_FLOAT, 
    TYPE_STRING
};

struct Immediate {
    TypeType type;
    std::string content;
};

TypeType getImmediateType(const Immediate& imm) ;

struct IdVariable {
    std::string content;
};

int getImmediateInt(Immediate imm);
Immediate makeImmediate(TypeType type, std::string s);
Immediate makeImmediate(int i);
IdVariable makeIdVariable(std::string content);

enum SpecialMark {
    FUNCTION_CALL_PARA_HEAD,
};

class Value {
    private:
    std::variant<std::monostate, Immediate, IdVariable, int, SpecialMark> data_;
    public:
    Value();
    Value(const Value & o) = default;
    Value(const Immediate & imm);
    Value(const IdVariable & iv);
    Value(const int & reg);
    Value(const SpecialMark & spm);
    ~Value() = default;
    Value& operator=(const Value & o) = default;
    Value& operator=(const Immediate & o);
    Value& operator=(const IdVariable & o);
    Value& operator=(const std::string & o);
    bool isVariable();
    bool isImmediate();
    bool isReg();
    bool isParaHead();
    const Immediate& getImmediate() const;
    const IdVariable& getIdVariable() const;
    const int& getReg() const;
};

#endif