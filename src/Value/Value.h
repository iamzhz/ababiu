#ifndef _VALUE_H_
#define _VALUE_H_
#include <string>
#include <variant>
enum QuicknumberType {
    QN_UNKNOWN, 
    QN_INT, 
    QN_CHAR, 
    QN_FLOAT, 
    QN_STRING
};

using Quicknumber = std::variant<
    std::monostate, 
    int,
    char,
    double,
    std::string
>;

QuicknumberType getQuicknumberType(const Quicknumber& qn) ;

struct IdVariable {
    std::string content;
};
Quicknumber makeQuicknumber(int i);
Quicknumber makeQuicknumber(char c);
Quicknumber makeQuicknumber(double f);
Quicknumber makeQuicknumber(std::string s);
IdVariable makeIdVariable(std::string content);
class Value {
    private:
    std::variant<std::monostate, Quicknumber, IdVariable, int> data_;
    public:
    Value();
    Value(const Value & o) = default;
    Value(const Quicknumber & qn);
    Value(const IdVariable & iv);
    Value(const int & reg);
    ~Value() = default;
    Value& operator=(const Value & o) = default;
    Value& operator=(const Quicknumber & o);
    Value& operator=(const IdVariable & o);
    Value& operator=(const std::string & o);
    bool isVariable();
    bool isQuicknumber();
    bool isReg();
    const Quicknumber& getQuicknumber() const;
    const IdVariable& getIdVariable() const;
    const int& getReg() const;
};

#endif