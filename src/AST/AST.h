#ifndef _ABANDON_AST_H_
#define _ABANDON_AST_H_

#include "../include.h"

enum ast_type { // _
    ast_token,
    ast_value,
    ast_term,
    ast_factor,
    ast_add_op_tail,
    ast_mul_op_tail
};

class AST {
    public:
    Lexer* lx;
    ast_type label;
    std::vector<AST*> children;
    Token tk; 


    AST(Lexer* lx);
    AST* addChild(ast_type label, Lexer* lx);
    AST* addTokenChild(Token tk, Lexer* lx);
    void setToken(Token tk);


    bool match(std::string content); // return false is eof
    bool match(tokenType want); // return false is eof
    bool isMatch(std::string content, bool& tell); // return false is eof
    bool isMatch(tokenType want, bool& tell); // return false is eof
    #ifdef DEBUG

    void print(int indent = 0);

    #endif

};
#endif