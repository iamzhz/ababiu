#include "Parser.h"

Tree* Parser::parse_ExprList() {
    Tree* tr = createTree(treeTypeNode_ExprList);
    Tree* tr_Expr;
    Tree* tr_ExprList_;
    Token tk = this->current;

    tr_Expr = this->parse_Expr();
    ERROR_nullptr(Expr);
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
    ERROR_nullptr(Expr);
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
    if (tr_ExprList == nullptr) EXPECTED_ERROR("ExprList");
    tr->add(tr_ExprList);

    if (!this->current.matchSign(")")) EXPECTED_ERROR(")");
    this->getNextToken();

    return tr;
}

Tree* Parser::parse_DefineFunction() {
    Tree* tr = createTree(treeTypeNode_DefineFunction);
    Tree* tr_Id;
    Tree* tr_ExprList;
    Tree* tr_Statements;
    if (!this->current.matchKeyword("fn")) EXPECTED_ERROR("fn");
    this->getNextToken();

    if (!this->current.match(tokenTypeType)) EXPECTED_ERROR("Type");
    tr->add(createTree(this->current));
    this->getNextToken();

    if (!this->current.match(tokenTypeId)) EXPECTED_ERROR("Id");
    tr_Id = createTree(this->current);
    tr->add(tr_Id);
    this->getNextToken();

    if (!this->current.matchSign("(")) EXPECTED_ERROR("(");
    this->getNextToken();

    if (this->current.matchKeyword("void")) {
        tr->add(createTree(treeTypeNode_ExprList));
        this->getNextToken();
    } else {
        tr_ExprList = this->parse_ExprList();
        ERROR_nullptr(ExprList);
        tr->add(tr_ExprList);
    }

    if (!this->current.matchSign(")")) EXPECTED_ERROR(")");
    this->getNextToken();

    tr_Statements = this->parse_Statements();
    if (tr_Statements == nullptr) EXPECTED_ERROR("Statements");
    tr->add(tr_Statements);

    return tr;
}

Tree* Parser::parse_Return() {
    Tree* tr = createTree(treeTypeNode_Return);
    Tree* tr_Expr;

    if (!this->current.matchKeyword("return")) EXPECTED_ERROR("return");
    this->getNextToken();

    tr_Expr = this->parse_Expr();
    ERROR_nullptr(Expr);
    tr->add(tr_Expr);

    if (!this->current.matchSign(";")) EXPECTED_ERROR(";");
    this->getNextToken();

    return tr;
}

Tree* Parser::parse_DefineVariable() {
    Tree* tr = createTree(treeTypeNode_DefineVariable);
    if (!this->current.match(tokenTypeType)) EXPECTED_ERROR("Type");
    tr->add(createTree(this->current));
    this->getNextToken();

    if (!this->current.match(tokenTypeId)) EXPECTED_ERROR("Id");
    tr->add(createTree(this->current));
    this->getNextToken();
    
    return tr;
}