#ifndef _ABANDON_PARSER_H_
#define _ABANDON_PARSER_H_

#include "../include.h"
class Parser {
    public:
    Lexer* lx;
    bool parser(AST* ast);
    bool parser_value_tail(AST* ast);
};

#endif