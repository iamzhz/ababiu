#ifndef _LITERAL_H_
#define _LITERAL_H_
#include <string>
#include <sstream>

class Literal {
    private:
    std::stringstream _rodata;
    int count = 0;
    public:
    void storeFloat(std::string fl);
    std::string get_rodata();
};

#endif