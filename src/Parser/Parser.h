#ifndef _ABANDON_PARSER_H_
#define _ABANDON_PARSER_H_
#include "../include.h"

extern Tree* noneTreeClass;
extern Tree* epsilonTreeClass;
class Parser {
    public:
    Lexer* lx;
    Parser(Lexer* lx);
    Tree* parse_Expr();
    Tree* parse_Expr_();
    Tree* parse_Term();
    Tree* parse_Term_();
    Tree* parse_Factor();
    bool parseSub();
};

#endif