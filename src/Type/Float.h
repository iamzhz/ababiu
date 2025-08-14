#ifndef _FLOAT_H_
#define _FLOAT_H_
#include <vector>
#include <string>
class Float {
    public:
    bool div2(std::vector<int> & s, int & remainder);
    bool mul2(std::vector<int> & s, int & integer);
    void integerToBinary(std::vector<int> & integer);
    void fractionToBinary(std::vector<int> & fraction, int limit);
    std::string floatDecToBin(std::string f);
};

#endif