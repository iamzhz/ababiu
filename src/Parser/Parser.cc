#include "../include.h"

Tree* noneTreeClass = createTree(treeTypeNode_None);
Tree* epsilonTreeClass = createTree(treeTypeNode_Epsilon);

Parser::Parser(Lexer* lx) {
    this->lx = lx;
    this->getNextToken();
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
    Token tk = this->current;
    
    Tree* tr = createTree(treeTypeNode_Expr_);
    Tree* tr_Term;
    Tree* tr_Expr_;
    if (tk.matchSign("+") || tk.matchSign("-")) {
        tr->add(createTree(tk));
        this->getNextToken();
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
    Token tk = this->current;
    
    Tree* tr = createTree(treeTypeNode_Term_);
    Tree* tr_Factor;
    Tree* tr_Term_;
    if (tk.matchSign("*") || tk.matchSign("/")) {
        tr->add(createTree(tk));
        this->getNextToken();
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
    Token tk = this->current;
    if (tk.match(tokenTypeInt) || tk.match(tokenTypeFloat) || tk.match(tokenTypeChar) || 
        tk.match(tokenTypeId) || tk.match(tokenTypeString)) {
        tr->add(createTree(tk));
        this->getNextToken();
        return tr;
    }
    if (tk.matchSign("(")) {
        this->getNextToken();
        tr_Expr = this->parse_Expr();
        tr->add(tr_Expr);
        if (this->current.matchSign(")")) {
            this->getNextToken();
        } else {
            this->parserError("`)` expected");
            return noneTreeClass;
        }
        return tr;
    }
    this->parserError("Something or ( expected");
    return noneTreeClass;
}


Tree* Parser::parse_Sentence() {
    Tree* tr = createTree(treeTypeNode_Sentence);
    Tree* tr_Expr;
    tr_Expr = this->parse_Expr();
    if (tr_Expr == noneTreeClass) return noneTreeClass;
    tr->add(tr_Expr);

    if (!this->current.matchSign(";")) return noneTreeClass;
    tr->add(createTree(this->current));
    this->getNextToken();

    return tr;
}

Tree* Parser::parse_Sentences() {
    Tree* tr = createTree(treeTypeNode_Sentences);
    Tree* tr_Sentence;
    Tree* tr_Sentences;
    
    tr_Sentence = this->parse_Sentence();
    if (tr_Sentence == noneTreeClass) return noneTreeClass;
    tr->add(tr_Sentence);

    this->record();
    tr_Sentences = this->parse_Sentences();
    this->unrecord();
    if (tr_Sentences == noneTreeClass) {
        this->restart();
    } else {
        tr->add(tr_Sentences);
    }
    return tr;
}

Tree* Parser::parse_Statements() {
    Tree* tr = createTree(treeTypeNode_Statements);
    Tree* tr_Sentences;
    Tree* tr_Sentence;
    if (!this->current.matchSign("{")) { // try { Sentences }
        tr_Sentence = this->parse_Sentence();
        if (tr_Sentence == noneTreeClass) { // try Sentence
            this->parserError("Statements expected");
        }
        tr->add(tr_Sentence);
        return tr;
    }
    this->getNextToken();

    tr_Sentences = this->parse_Sentences();
    if (tr_Sentences == noneTreeClass) return noneTreeClass;
    tr->add(tr_Sentences);

    if (!this->current.matchSign("}")) {
        this->parserError("`}` expected");
        return noneTreeClass;
    }
    this->getNextToken();

    return tr;
}