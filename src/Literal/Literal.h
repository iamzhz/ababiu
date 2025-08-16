#ifndef _LITERAL_H_
#define _LITERAL_H_
#include <string>
#include <sstream>
#include "../Value/Value.h"

class Literal {
    private:
    std::stringstream _rodata;
    int count = 0;
    public:
    std::string get(Value val);
    std::string storeFloat(std::string fl);
    std::string get_rodata();
};

#endif