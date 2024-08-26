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
    tokenTypeType,
    tokenTypeSign,
    tokenTypeEof
};

class Token {
    public:
    std::string content;
    tokenType type;
    int line;
    int column;
    Token();
    Token(std::string content, enum tokenType type, int line, int column);
    Token(const Token& other);
    bool idToKeyword(); // return true says `content` is a keyword, or not
    bool idToType(); // return true says `content` is a type, or not
    bool matchSign(std::string content);
    bool matchKeyword(std::string content);
    bool match(tokenType type);
    void addToContent(char newChar);
    void addToContent(int newChar);
    void addToContent(std::string newString);
    bool isEof();
    std::string typeToText();
};

extern Token noneTokenClass; // to cheat compiler

#endif