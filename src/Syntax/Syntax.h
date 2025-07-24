#ifndef _SYNTAX_H_
#define _SYNTAX_H_
#include "../include.h"

class Syntax {
    private:
    Tree * tr; // the Tree need to deal with
    IRs * irs;   // the result
    public:
    Syntax(Tree * tr, IRs * irs);
    // analyze
    int analyze_quicknumber(Token * tk); // return the index
    void analyze_unit(); // run this to start working
    Token getInner(Tree * tr);
    void analyze_Statements(Tree * tr);
    void analyze_Sentences(Tree * tr);
    void analyze_Sentence(Tree * tr);
    void analyze_If(Tree * tr);
    void analyze_DoWhile(Tree * tr);
    void analyze_For(Tree * tr);
    void analyze_Else(Tree * tr, int if_jump_pos);
    void analyze_While(Tree * tr);
    void analyze_Break(Tree * tr);
    void analyze_Return(Tree * tr);
    void analyze_Continue(Tree * tr);
    void analyze_FunctionCall(Tree * tr);
    void analyze_ExprList(Tree * tr);
    void analyze_Expr(Tree * tr);
    void analyze_Assign(Tree * tr);
    void analyze_Compare(Tree * tr);
    void analyze_Add(Tree * tr);
    void analyze_Times(Tree * tr);
    void analyze_Power(Tree * tr);
    void analyze_Factor(Tree * tr);
    
};

#endif