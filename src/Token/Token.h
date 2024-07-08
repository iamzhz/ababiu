#ifndef _ABANDON_TOKEN_H_
#define _ABANDON_TOKEN_H_

#include "../include.h"

enum tokenType {
    tokenTypeString, 
    tokenTypeChar,
    tokenTypeInt, 
    tokenTypeFloat, 
    tokenTypeId, 
    tokenTypeKeyword, 
    tokenTypeSign,
    tokenTypeEof,
    tokenTypeUnknown
};

class Token {
    public:
    std::string content;
    enum tokenType type;
    int line;
    int column;
    bool idToKeyword(); // return true says `content` is a keyword, or not
    bool matchSign(std::string content);
    bool matchKeyword(std::string content);
    void addToContent(char newChar);
    void addToContent(int newChar);
    void addToContent(std::string newString);
    bool isEof();

    #ifdef DEBUG
    std::string typeToText();
    #endif
};
#endif