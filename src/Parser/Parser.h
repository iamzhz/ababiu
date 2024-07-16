#ifndef _ABANDON_PARSER_H_
#define _ABANDON_PARSER_H_

#include "../include.h"
class Parser {
    public:
    Lexer* lx;
    bool parser(AST* ast);
    bool parser_term(AST* ast);
    bool parser_factor(AST* ast);
    bool parser_add_op_tail(AST* ast);
    bool parser_mul_op_tail(AST* ast);

};

#endif