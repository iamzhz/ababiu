#ifndef _ABANDON_AST_H_
#define _ABANDON_AST_H_

#include "../include.h"

enum ast_type { // _
    ast_token,
    ast_value,
    ast_value_tail
};

class AST {
    public:
    Lexer* lx;
    ast_type label;
    std::vector<AST*> children;
    Token tk; 


    AST(Lexer* lx);
    AST* addChild(ast_type label, Lexer* lx);
    void setToken(Token tk);


    bool match(std::string content); // return false is eof
    bool match(tokenType want); // return false is eof
    bool isMatch(std::string content, bool& tell); // return false is eof
    bool isMatch(tokenType want, bool& tell); // return false is eof
    #ifdef DEBUG

    void print();

    #endif

};

#endif