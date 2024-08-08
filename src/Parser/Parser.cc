#include "../include.h"

Tree* noneTreeClass = createTree(treeType_None);
Tree* epsilonTreeClass = createTree(treeTypeNode_Epsilon);

Parser::Parser(Lexer* lx) {
    this->lx = lx;
}

void Parser::addToBack(Token tk) {
    this->backtracking.push_back(tk);
}
Token Parser::getToken() {
    Token tk;
    if (this->fromBeginIndex != -1) {
        return this->backtracking[this->fromBeginIndex];
        this->fromBeginIndex ++;
    }
    tk = this->lx->getNextToken();
    this->addToBack(tk);
    return tk;
}
Token Parser::clearBack() {
    Token lastToken;
    lastToken = this->backtracking.back();
    this->backtracking.clear(); // only save the last one
    this->backtracking.push_back(lastToken);
    this->fromBeginIndex = -1;
    return lastToken;
}
Token Parser::fromBegin() {
    this->fromBeginIndex = 0;
}

Tree* Parser::cst2ast(Tree* tr) {
    if (tr->type == treeType_Token) return tr;
    
    std::vector<Tree*> & c = tr->children;
    for (auto it = c.begin();  it != c.end();  ) {
        if ((*it)->type == treeType_Node && (*it)->label == treeTypeNode_Epsilon) {
            it = c.erase(it);
        } else {
            Tree* result = cst2ast(*it);
            if (result == nullptr) it = c.erase(it);
            else {
                *it = result;
                it ++;
            }
        }
    }
    if (c.empty()) return nullptr;
    if (c.size() == 1) return c[0];
    return tr;
}


Tree* Parser::parse_Expr() {
    Tree* tr = createTree(treeTypeNode_Expr);
    Tree* tr_Term = this->parse_Term();
    Tree* tr_Expr_;

    if (tr_Term == noneTreeClass) return noneTreeClass;
    tr->add(tr_Term);

    tr_Expr_ = this->parse_Expr_();// here
    if (tr_Expr_ == noneTreeClass) return noneTreeClass;
    tr->add(tr_Expr_);
    return tr;
}

Tree* Parser::parse_Expr_() {
    Token tk = this->lx->current;
    
    Tree* tr = createTree(treeTypeNode_Expr_);
    Tree* tr_Term;
    Tree* tr_Expr_;
    if (tk.matchSign("+") || tk.matchSign("-")) {
        tr->add(createTree(tk));
        this->lx->getNextToken();
    } else {
        return epsilonTreeClass; 
    }

    tr_Term = this->parse_Term();
    if (tr_Term == noneTreeClass) return noneTreeClass;
    tr->add(tr_Term);

    tr_Expr_ = this->parse_Expr_();
    if (tr_Expr_ == noneTreeClass) return noneTreeClass;
    tr->add(tr_Expr_);
    return tr;
}

Tree* Parser::parse_Term() {
    Tree* tr = createTree(treeTypeNode_Term);
    Tree* tr_Factor = this->parse_Factor();
    Tree* tr_Term_;

    if (tr_Factor == noneTreeClass) return noneTreeClass;
    tr->add(tr_Factor);

    tr_Term_ = this->parse_Term_();
    if (tr_Term_ == noneTreeClass) return noneTreeClass;
    // TODO: ' no add
    tr->add(tr_Term_);
    return tr;
}

Tree* Parser::parse_Term_() {
    Token tk = this->lx->current;
    
    Tree* tr = createTree(treeTypeNode_Term_);
    Tree* tr_Factor;
    Tree* tr_Term_;
    if (tk.matchSign("*") || tk.matchSign("/")) {
        tr->add(createTree(tk));
        this->lx->getNextToken();
    } else {
        return epsilonTreeClass; 
    }

    tr_Factor = this->parse_Factor();
    if (tr_Factor == noneTreeClass) return noneTreeClass;
    tr->add(tr_Factor);

    tr_Term_ = this->parse_Term_();
    if (tr_Term_ == noneTreeClass) return noneTreeClass;
    tr->add(tr_Term_);
    return tr;
}

Tree* Parser::parse_Factor() {
    Tree* tr = createTree(treeTypeNode_Factor);
    Tree* tr_Expr;
    Token tk = this->lx->current;
    if (tk.match(tokenTypeInt)) {
        tr->add(createTree(tk));
        this->lx->getNextToken();
        return tr;
    }
    if (tk.matchSign("(")) {
        this->lx->getNextToken();
        tr_Expr = this->parse_Expr();
        tr->add(tr_Expr);
        if (this->lx->current.matchSign(")")) {
            this->lx->getNextToken();
        } else {
            sayError("`)` expected");
        }
        return tr;
    }
    sayError("int or ( expected");
    return noneTreeClass;
}
Tree* Parser::parse_Sentence() {
    Tree* tr = createTree(treeTypeNode_Sentence);
    Tree* tr_Expr;
    Token tk;
    tr_Expr = this->parse_Expr();
    if (tr_Expr == noneTreeClass) return noneTreeClass;
    tr->add(tr_Expr);

    tk = this->lx->current;
    this->lx->getNextToken();
    if (tk.matchSign(";")) return tr;
    return noneTreeClass;
}