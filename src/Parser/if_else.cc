#include "Parser.h"

Tree* Parser::parse_If() {
    Tree* tr = createTree(treeTypeNode_If);
    Tree* tr_Expr;
    Tree* tr_Statements;
    Tree* tr_Else;

    if (!this->current.matchKeyword("if")) EXPECTED_ERROR("If");
    this->getNextToken();

    tr_Expr = this->parse_Expr();
    CHECK_nullptr(Expr);
    tr->add(tr_Expr);

    tr_Statements = this->parse_Statements();
    CHECK_nullptr(Statements);
    tr->add(tr_Statements);

    tr_Else = this->parse_Else();
    CHECK_nullptr(Else);
    tr->add(tr_Else);

    return tr;
}

Tree* Parser::parse_Else() {
    Tree* tr = createTree(treeTypeNode_Else);
    Tree* tr_Statements;

    if (!this->current.matchKeyword("else")) return epsilonTreeClass;
    this->getNextToken();

    tr_Statements = this->parse_Statements();
    CHECK_nullptr(Statements);
    tr->add(tr_Statements);

    return tr;
}