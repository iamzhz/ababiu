#ifndef _ABANDON_PARSER_H_
#define _ABANDON_PARSER_H_
#include "../include.h"

extern Tree* noneTreeClass;
extern Tree* epsilonTreeClass;
class Parser {
    private:
    std::vector<Token> backtracking;
    int fromBeginIndex = -1;
    void addToBack(Token tk);
    Token getToken();
    Token clearBack();
    Token fromBegin();
    public:
    Lexer* lx;
    Parser(Lexer* lx);
    Tree* cst2ast(Tree* tr);
    Tree* parse_Expr();
    Tree* parse_Expr_();
    Tree* parse_Term();
    Tree* parse_Term_();
    Tree* parse_Factor();
    Tree* parse_Sentence();
};

#endif