#include "../include.h"

Tree* Parser::parse_While() {
    Tree* tr = createTree(treeTypeNode_While);
    Tree* tr_Expr;
    Tree* tr_Statements;
    
    if (!this->current.matchKeyword("while")) EXPECTED_ERROR("while");
    this->getNextToken();
    
    tr_Expr = this->parse_Expr();
    ERROR_nullptr(Expr);
    tr->add(tr_Expr);

    tr_Statements = this->parse_Statements();
    ERROR_nullptr(Statements);
    tr->add(tr_Statements);

    return tr;
}

Tree* Parser::parse_DoWhile() {
    Tree* tr = createTree(treeTypeNode_DoWhile);
    Tree* tr_Expr;
    Tree* tr_Statements;
    
    if (!this->current.matchKeyword("do")) EXPECTED_ERROR("do");
    this->getNextToken();
    
    tr_Statements = this->parse_Statements();
    ERROR_nullptr(Statements);
    tr->add(tr_Statements);

    if (!this->current.matchKeyword("while")) EXPECTED_ERROR("while");
    this->getNextToken();

    tr_Expr = this->parse_Expr();
    ERROR_nullptr(Expr);
    tr->add(tr_Expr);

    if (!this->current.matchSign(";")) EXPECTED_ERROR(";");
    this->getNextToken();

    return tr;
}

Tree* Parser::parse_For() {
    Tree* tr = createTree(treeTypeNode_For);
    Tree* tr_Expr0, *tr_Expr1, *tr_Expr2;
    Tree* tr_Statements;

    if (!this->current.matchKeyword("for")) EXPECTED_ERROR("for");
    this->getNextToken();

    if (!this->current.matchSign("(")) EXPECTED_ERROR("(");
    this->getNextToken();

    tr_Expr0 = this->parse_Expr(); // 0
    ERROR_nullptr(Expr0);
    tr->add(tr_Expr0);
    if (!this->current.matchSign(";")) EXPECTED_ERROR(";");
    this->getNextToken();

    tr_Expr1 = this->parse_Expr(); // 1
    ERROR_nullptr(Expr1);
    tr->add(tr_Expr1);
    if (!this->current.matchSign(";")) EXPECTED_ERROR(";");
    this->getNextToken();

    tr_Expr2 = this->parse_Expr(); // 2
    ERROR_nullptr(Expr2);
    tr->add(tr_Expr2);

    if (!this->current.matchSign(")")) EXPECTED_ERROR(")");
    this->getNextToken();

    tr_Statements = this->parse_Statements();
    ERROR_nullptr(Statements);
    tr->add(tr_Statements);

    return tr;
}

Tree* Parser::parse_Break() {
    Tree* tr = createTree(treeTypeNode_Break);
    if (!this->current.matchKeyword("break")) EXPECTED_ERROR("break");
    this->getNextToken();

    if (!this->current.matchSign(";")) EXPECTED_ERROR(";");
    this->getNextToken();

    return tr;
}

Tree* Parser::parse_Continue() {
    Tree* tr = createTree(treeTypeNode_Continue);
    if (!this->current.matchKeyword("continue")) EXPECTED_ERROR("continue");
    this->getNextToken();

    if (!this->current.matchSign(";")) EXPECTED_ERROR(";");
    this->getNextToken();

    return tr;
}