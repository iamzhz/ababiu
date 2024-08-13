#ifndef _ABANDON_PARSER_H_
#define _ABANDON_PARSER_H_
#include "../include.h"

extern Tree* noneTreeClass;
extern Tree* epsilonTreeClass;
class Parser {
    public:
    std::list<Token> backtracks;
    std::list<Token>::iterator it;
    bool restartMode = false;
    bool recordMode = false;
    Token current;

    Lexer* lx;
    Parser(Lexer* lx);
    Tree* cst2ast(Tree* tr);
    Tree* parse_Expr();
    Tree* parse_Expr_();
    Tree* parse_Term();
    Tree* parse_Term_();
    Tree* parse_Factor();
    Tree* parse_Sentence();
    Tree* parse_Sentences();
    Tree* parse_Statements();
    
    void getNextToken(); // to replace lx->getNextToken()
    void restart();
    void record();
    void unrecord();
    void parserError(Token tk, std::string info);
    void parserError(std::string info);
};

#endif