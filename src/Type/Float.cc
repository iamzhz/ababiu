#include <vector>
#include <algorithm>
#include <string>
//#include <iostream>

// float -> std::vector<int>

// <xyz / 2 = abc ... m>
// "xyz" is s
// "abc" is the result (s)
// m is remainder
// return: abc == 0
bool div2(std::vector<int> & s, int & remainder) {
    int carry = 0;
    bool isAppearNonZero = false;
    std::vector<int> new_;
    for (auto it = s.begin(); it != s.end(); ++it) {
        int current = carry * 10 + (*it);
        int q = current / 2;
        carry = current % 2;
        if (q != 0 || isAppearNonZero) {
            new_.push_back(q);
            isAppearNonZero = true;
        }
    }
    s = new_;
    remainder = carry;
    return s.empty();
}
// <0.xyz * 2 = m.abc>
// "zyx" is n
// "m" is integer
// "cba" is result (s) 
// return: abc == 0
bool mul2(std::vector<int> & s, int & integer) {
    int extra = 0;
    int digit;
    bool isAppearNonZero = false;
    std::vector<int> new_;
    for (auto it = s.begin();  it != s.end();  ++ it) {
        extra = (*it) * 2 + extra;
        digit = extra % 10;
        if (digit != 0) isAppearNonZero = true; 
        if (isAppearNonZero) {
            new_.push_back(digit);
        }
        extra /= 10;
    }
    integer = extra;
    s = new_;
    return s.empty();
}

void integerToBinary(std::vector<int> & integer) {
    int remainder;
    bool isEmpty;
    std::vector<int> new_;
    if (integer.size() == 0 || (integer.size() == 1 && integer[0] == '0')) {
        return ;
    }
    do {
         isEmpty = div2(integer, remainder);
        new_.push_back(remainder);
    } while (!isEmpty);

    std::reverse(new_.begin(), new_.end());
    if (new_.size() == 0) {
        new_.push_back(0);
    }
    integer = new_;
}

void fractionToBinary(std::vector<int> & fraction, int limit, bool isAppearOne) {
    std::vector<int> new_;
    int integer;
    int count = 0;
    int rest;
    while (count < limit) {
        int isEmpty = mul2(fraction, integer);
        new_.push_back(integer);
        if (integer == 1) isAppearOne = true;
        if (isAppearOne) ++ count;
        if (isEmpty) break;
    }
    rest = limit - count;
    while (rest > 0) {
        new_.push_back(0);
        -- rest;
    }
    fraction = new_;
}


std::string floatDecToBin(std::string f) {
    std::vector<int> integer;
    std::vector<int> fraction; // fractional part
    int rest = 53;
    for (auto c : f) {
        if (c == '.') {
            break;
        }
        integer.push_back((int)(c - '0'));
    }
    for (auto it = f.rbegin();  it != f.rend();  ++ it) {
        if (*it == '.') {
            break;
        }
        fraction.push_back((int)(*it - '0'));
    }
    integerToBinary(integer);
    rest -= integer.size();
    fractionToBinary(fraction, rest, integer.size()!=0);
    // test
    std::string s;
    for (auto c : integer) {
        s += (c+'0');
    }
    s += ".";
    for (auto c : fraction) {
        s += (c+'0');
    }
    return s;
}
/*
// test
int main() {
    std::string f;
    while (1) {
        std::cin >> f;
        std::cout << floatDecToBin(f) << std::endl;
    }
}
*/