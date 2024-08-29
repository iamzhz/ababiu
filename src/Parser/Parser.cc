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
    Tree* tr_Assign = this->parse_Assign();
    ERROR_noneTreeClass(Assign);
    tr->add(tr_Assign);
    return tr;
}
Tree* Parser::parse_Assign() {
    Tree* tr = createTree(treeTypeNode_Assign);
    Tree* tr_Add;
    Tree* tr_Assign_;

    tr_Add = this->parse_Add();
    ERROR_noneTreeClass(Add);
    tr->add(tr_Add);

    tr_Assign_ = this->parse_Assign_();
    tr->add(tr_Assign_);
    return tr;
}
Tree* Parser::parse_Assign_() {
    Token tk = this->current;
    
    Tree* tr = createTree(treeTypeNode_Assign_);
    Tree* tr_Add;
    Tree* tr_Assign_;
    if (tk.matchSign("=")) {
        tr->add(createTree(tk));
        this->getNextToken();
    } else {
        return epsilonTreeClass; 
    }

    tr_Add = this->parse_Add();
    ERROR_noneTreeClass(Add);
    tr->add(tr_Add);

    tr_Assign_ = this->parse_Assign_();
    // if (tr_Expr_ == noneTreeClass) return noneTreeClass; (I believe it'll never run)
    tr->add(tr_Assign_);
    return tr;
}

Tree* Parser::parse_Add() {
    Tree* tr = createTree(treeTypeNode_Add);
    Tree* tr_Term = this->parse_Term();
    Tree* tr_Add_;

    ERROR_noneTreeClass(Term);
    tr->add(tr_Term);

    tr_Add_ = this->parse_Add_();// here
    //if (tr_Expr_ == noneTreeClass) return noneTreeClass;
    tr->add(tr_Add_);
    return tr;
}

Tree* Parser::parse_Add_() {
    Token tk = this->current;
    
    Tree* tr = createTree(treeTypeNode_Add_);
    Tree* tr_Term;
    Tree* tr_Add_;
    if (tk.matchSign("+") || tk.matchSign("-")) {
        tr->add(createTree(tk));
        this->getNextToken();
    } else {
        return epsilonTreeClass; 
    }

    tr_Term = this->parse_Term();
    ERROR_noneTreeClass(Term);
    tr->add(tr_Term);

    tr_Add_ = this->parse_Add_();
    // if (tr_Expr_ == noneTreeClass) return noneTreeClass; (I believe it'll never run)
    tr->add(tr_Add_);
    return tr;
}

Tree* Parser::parse_Term() {
    Tree* tr = createTree(treeTypeNode_Term);
    Tree* tr_Power = this->parse_Power();
    Tree* tr_Term_;

    ERROR_noneTreeClass(Power);
    tr->add(tr_Power);

    tr_Term_ = this->parse_Term_();
    // if (tr_Term_ == noneTreeClass) return noneTreeClass;
    tr->add(tr_Term_);
    return tr;
}

Tree* Parser::parse_Term_() {
    Token tk = this->current;
    
    Tree* tr = createTree(treeTypeNode_Term_);
    Tree* tr_Power;
    Tree* tr_Term_;
    if (tk.matchSign("*") || tk.matchSign("/")) {
        tr->add(createTree(tk));
        this->getNextToken();
    } else {
        return epsilonTreeClass; 
    }

    tr_Power = this->parse_Power();
    ERROR_noneTreeClass(Power);
    tr->add(tr_Power);

    tr_Term_ = this->parse_Term_();
    // if (tr_Term_ == noneTreeClass) return noneTreeClass;
    tr->add(tr_Term_);
    return tr;
}

Tree* Parser::parse_Power() {
    Tree* tr = createTree(treeTypeNode_Term);
    Tree* tr_Factor = this->parse_Factor();
    Tree* tr_Power_;

    ERROR_noneTreeClass(Factor);
    tr->add(tr_Factor);

    tr_Power_ = this->parse_Power_();
    //if (tr_Power_ == noneTreeClass) return noneTreeClass;
    tr->add(tr_Power_);
    return tr;
}

Tree* Parser::parse_Power_() {
    Token tk = this->current;
    
    Tree* tr = createTree(treeTypeNode_Term_);
    Tree* tr_Factor;
    Tree* tr_Power_;
    if (tk.matchSign("**")) {
        tr->add(createTree(tk));
        this->getNextToken();
    } else {
        return epsilonTreeClass; 
    }

    tr_Factor = this->parse_Factor();
    ERROR_noneTreeClass(Factor);
    tr->add(tr_Factor);

    tr_Power_ = this->parse_Power_();
    //if (tr_Power_ == noneTreeClass) return noneTreeClass;
    tr->add(tr_Power_);
    return tr;
}

Tree* Parser::parse_Factor() {
    Tree* tr = createTree(treeTypeNode_Factor);
    Tree* tr_Expr;
    Tree* tr_FunctionCall;
    Token tk = this->current;

    if (this->current.matchSign("@")) {
        this->getNextToken();
        tr_FunctionCall = this->parse_FunctionCall();
        if (tr_FunctionCall != noneTreeClass) {
            tr->add(tr_FunctionCall);
            return tr;
        }
    }

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
            EXPECTED_ERROR(")");
        }
        return tr;
    }
    EXPECTED_ERROR("( or something other");
}


Tree* Parser::parse_Sentence() {
    Tree* tr = createTree(treeTypeNode_Sentence);
    Tree* tr_Expr;

    if (this->current.matchKeyword("if")) {
        Tree* tr_If = this->parse_If();
        ERROR_noneTreeClass(If);
        tr->add(tr_If);
        return tr;
    } else if (this->current.matchKeyword("else")) {
        Tree* tr_Else = this->parse_Else();
        ERROR_noneTreeClass(Else);
        tr->add(tr_Else);
        return tr;
    }
        
    tr_Expr = this->parse_Expr();
    ERROR_noneTreeClass(Expr);
    tr->add(tr_Expr);

    if (!this->current.matchSign(";")) {
        EXPECTED_ERROR(";");
    }
    tr->add(createTree(this->current));
    this->getNextToken();

    return tr;
}

Tree* Parser::parse_Sentences() {
    Tree* tr = createTree(treeTypeNode_Sentences);
    Tree* tr_Sentence;
    Tree* tr_Sentences;
    
    if (this->current.matchSign("}")) {
        return tr;
    }

    tr_Sentence = this->parse_Sentence();
    ERROR_noneTreeClass(Sentence);
    tr->add(tr_Sentence);

    
    tr_Sentences = this->parse_Sentences();
    ERROR_noneTreeClass(Sentences);
    tr->add(tr_Sentences);

    return tr;
}

Tree* Parser::parse_Statements() {
    Tree* tr = createTree(treeTypeNode_Statements);
    Tree* tr_Sentences;
    Tree* tr_Sentence;
    if (!this->current.matchSign("{")) { // try not { Sentences }
        tr_Sentence = this->parse_Sentence();
        if (tr_Sentence == noneTreeClass) { // try is Sentence
            this->parserError("Statements expected");
        }
        tr->add(tr_Sentence);
        return tr;
    }
    this->getNextToken();

    tr_Sentences = this->parse_Sentences();
    ERROR_noneTreeClass(Sentences);
    tr->add(tr_Sentences);

    this->getNextToken();

    return tr;
}