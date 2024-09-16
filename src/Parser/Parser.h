#ifndef _ABANDON_PARSER_H_
#define _ABANDON_PARSER_H_
#include "../include.h"

extern Tree* epsilonTreeClass;

class Parser {
    public:
    Token current;

    Lexer* lx;
    Parser(Lexer* lx);
    Tree* parse_Unit(); // a unit is a function or a variable definition

    Tree* parse_Expr();
    Tree* parse_Assign();
    Tree* parse_Assign_();
    Tree* parse_Compare();
    Tree* parse_Compare_();
    Tree* parse_Add();
    Tree* parse_Add_();
    Tree* parse_Times();
    Tree* parse_Times_();
    Tree* parse_Power();
    Tree* parse_Power_();
    Tree* parse_Factor();
    Tree* parse_Sentence();
    Tree* parse_Sentences();
    Tree* parse_Statements();
    Tree* parse_ExprList();
    Tree* parse_ExprList_();
    Tree* parse_FunctionCall();
    Tree* parse_DefineFunction();
    Tree* parse_DefineVariable();

    Tree* parse_If();
    Tree* parse_Else();
    Tree* parse_While();
    Tree* parse_DoWhile();
    Tree* parse_For();

    Tree* parse_Break();
    Tree* parse_Continue();
    Tree* parse_Return();
    
    void getNextToken(); // to replace lx->getNextToken()
    void parserError(Token tk, std::string info);
    void parserError(std::string info);
};

#define EXPECTED_ERROR(STH) { this->parserError(STH " expected"); \
return nullptr; } 

#define ERROR_nullptr(TER) if (tr_##TER == nullptr) EXPECTED_ERROR(#TER); 
#endif