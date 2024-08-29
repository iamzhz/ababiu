#ifndef _ABANDON_PARSER_H_
#define _ABANDON_PARSER_H_
#include "../include.h"

extern Tree* noneTreeClass;
extern Tree* epsilonTreeClass;

struct valsForBacktrack {
    std::list<Token>::iterator it;
    bool restartMode = false;
    bool recordModeChanged = false; // whether change `mainRecordMode` or not
};

class Parser {
    public:
    Token current;

    Lexer* lx;
    Parser(Lexer* lx);
    Tree* cst2ast(Tree* tr);
    Tree* parse_Expr();
    Tree* parse_Assign();
    Tree* parse_Assign_();
    Tree* parse_Add();
    Tree* parse_Add_();
    Tree* parse_Term();
    Tree* parse_Term_();
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

    Tree* parse_If();
    Tree* parse_Else();
    
    void getNextToken(); // to replace lx->getNextToken()
    void parserError(Token tk, std::string info);
    void parserError(std::string info);
};

#define EXPECTED_ERROR(STH) { this->parserError(STH " expected"); \
return noneTreeClass; } 

#define ERROR_noneTreeClass(TER) if (tr_##TER == noneTreeClass) EXPECTED_ERROR(#TER); 
#endif