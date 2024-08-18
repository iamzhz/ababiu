#include "../include.h"

Tree* Parser::parse_ExprList() {
    Tree* tr = createTree(treeTypeNode_ExprList);
    Tree* tr_Expr;
    Tree* tr_ExprList_;
    Token tk = this->current;

    tr_Expr = this->parse_Expr();
    ERROR_noneTreeClass(Expr);
    tr->add(tr_Expr);

    tr_ExprList_ = this->parse_ExprList_();
    tr->add(tr_ExprList_);

    return tr;
}
Tree* Parser::parse_ExprList_() {
    Tree* tr = createTree(treeTypeNode_ExprList_);
    Tree* tr_Expr;
    Tree* tr_ExprList_;
    if (!this->current.matchSign(",")) {
        return tr; // esplion
    }
    this->getNextToken();

    tr_Expr = this->parse_Expr();
    ERROR_noneTreeClass(Expr);
    tr->add(tr_Expr);

    tr_ExprList_ = this->parse_ExprList_();
    tr->add(tr_ExprList_);

    return tr;
}

Tree* Parser::parse_FunctionCall() {
    Tree* tr = createTree(treeTypeNode_FunctionCall);
    Tree* tr_ExprList;
    if (!this->current.match(tokenTypeId)) {
        EXPECTED_ERROR("Id");
    }
    tr->add(createTree(this->current));
    this->getNextToken();

    if (!this->current.matchSign("(")) EXPECTED_ERROR("(");
    this->getNextToken();

    tr_ExprList = this->parse_ExprList();
    if (tr_ExprList == noneTreeClass) EXPECTED_ERROR("ExprList");
    tr->add(tr_ExprList);

    if (!this->current.matchSign(")")) EXPECTED_ERROR(")");
    this->getNextToken();

    return tr;
}