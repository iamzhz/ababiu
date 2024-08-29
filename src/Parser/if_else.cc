#include "../include.h"

Tree* Parser::parse_If() {
    Tree* tr = createTree(treeTypeNode_If);
    Tree* tr_Expr;
    Tree* tr_Statements;

    if (!this->current.matchKeyword("if")) EXPECTED_ERROR("If");
    this->getNextToken();

    tr_Expr = this->parse_Expr();
    ERROR_noneTreeClass(Expr);
    tr->add(tr_Expr);

    tr_Statements = this->parse_Statements();
    ERROR_noneTreeClass(Statements);
    tr->add(tr_Statements);

    return tr;
}

Tree* Parser::parse_Else() {
    Tree* tr = createTree(treeTypeNode_Else);
    Tree* tr_Statements;

    if (!this->current.matchKeyword("else")) EXPECTED_ERROR("Else");
    this->getNextToken();

    tr_Statements = this->parse_Statements();
    ERROR_noneTreeClass(Statements);
    tr->add(tr_Statements);

    return tr;
}