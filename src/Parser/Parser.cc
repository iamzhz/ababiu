#include "Parser.h"

Tree* epsilonTreeClass = createTree(treeTypeNode_Epsilon);

Parser::Parser(Lexer* lx) {
    this->lx = lx;
    this->getNextToken();
}

Tree* Parser::parse_Expr() {
    Tree* tr = createTree(treeTypeNode_Expr);
    Tree* tr_Assign = this->parse_Assign();
    CHECK_nullptr(Assign);
    tr->add(tr_Assign);
    return tr;
}
Tree* Parser::parse_Assign() {
    Tree* tr = createTree(treeTypeNode_Assign);
    Tree* tr_Compare;
    Tree* tr_Assign_;

    tr_Compare = this->parse_Compare();
    CHECK_nullptr(Compare);
    tr->add(tr_Compare);

    tr_Assign_ = this->parse_Assign_();
    tr->add(tr_Assign_);
    return tr;
}
Tree* Parser::parse_Assign_() {
    Token tk = this->current;
    
    Tree* tr = createTree(treeTypeNode_Assign_);
    Tree* tr_Compare;
    if (tk.matchSign("=")) {
        tr->add(createTree(tk));
        this->getNextToken();
    } else {
        return epsilonTreeClass; 
    }

    tr_Compare = this->parse_Compare();
    CHECK_nullptr(Compare);
    tr->add(tr_Compare);

    // if (tr_Expr_ == nullptr) return nullptr; (I believe it'll never run)
    return tr;
}

Tree* Parser::parse_Compare() {
    Tree* tr = createTree(treeTypeNode_Compare);
    Tree* tr_Add;
    Tree* tr_Compare_;

    tr_Add = this->parse_Add();
    CHECK_nullptr(Add);
    tr->add(tr_Add);

    tr_Compare_ = this->parse_Compare_();
    tr->add(tr_Compare_);
    return tr;
}
Tree* Parser::parse_Compare_() {
    Token tk = this->current;
    
    Tree* tr = createTree(treeTypeNode_Compare_);
    Tree* tr_Add;
    if (tk.matchSign("==") || tk.matchSign("<") || tk.matchSign(">") || tk.matchSign(">=") || tk.matchSign("<=") || tk.matchSign("!=")) {
        tr->add(createTree(tk));
        this->getNextToken();
    } else {
        return epsilonTreeClass; 
    }

    tr_Add = this->parse_Add();
    CHECK_nullptr(Add);
    tr->add(tr_Add);

    // if (tr_Expr_ == nullptr) return nullptr; (I believe it'll never run)
    return tr;
}

Tree* Parser::parse_Add() {
    Tree* tr = createTree(treeTypeNode_Add);
    Tree* tr_Times = this->parse_Times();
    Tree* tr_Add_;

    CHECK_nullptr(Times);
    tr->add(tr_Times);

    tr_Add_ = this->parse_Add_();// here
    //if (tr_Expr_ == nullptr) return nullptr;
    tr->add(tr_Add_);
    return tr;
}

Tree* Parser::parse_Add_() {
    Token tk = this->current;
    
    Tree* tr = createTree(treeTypeNode_Add_);
    Tree* tr_Times;
    Tree* tr_Add_;
    if (tk.matchSign("+") || tk.matchSign("-")) {
        tr->add(createTree(tk));
        this->getNextToken();
    } else {
        return epsilonTreeClass; 
    }

    tr_Times = this->parse_Times();
    CHECK_nullptr(Times);
    tr->add(tr_Times);

    tr_Add_ = this->parse_Add_();
    // if (tr_Expr_ == nullptr) return nullptr; (I believe it'll never run)
    tr->add(tr_Add_);
    return tr;
}

Tree* Parser::parse_Times() {
    Tree* tr = createTree(treeTypeNode_Times);
    Tree* tr_Power = this->parse_Power();
    Tree* tr_Times_;

    CHECK_nullptr(Power);
    tr->add(tr_Power);

    tr_Times_ = this->parse_Times_();
    // if (tr_Times_ == nullptr) return nullptr;
    tr->add(tr_Times_);
    return tr;
}

Tree* Parser::parse_Times_() {
    Token tk = this->current;
    
    Tree* tr = createTree(treeTypeNode_Times_);
    Tree* tr_Power;
    Tree* tr_Times_;
    if (tk.matchSign("*") || tk.matchSign("/") || tk.matchSign("%")) {
        tr->add(createTree(tk));
        this->getNextToken();
    } else {
        return epsilonTreeClass; 
    }

    tr_Power = this->parse_Power();
    CHECK_nullptr(Power);
    tr->add(tr_Power);

    tr_Times_ = this->parse_Times_();
    // if (tr_Times_ == nullptr) return nullptr;
    tr->add(tr_Times_);
    return tr;
}

Tree* Parser::parse_Power() {
    Tree* tr = createTree(treeTypeNode_Power);
    Tree* tr_Factor = this->parse_Factor();
    Tree* tr_Power_;

    CHECK_nullptr(Factor);
    tr->add(tr_Factor);

    tr_Power_ = this->parse_Power_();
    //if (tr_Power_ == nullptr) return nullptr;
    tr->add(tr_Power_);
    return tr;
}

Tree* Parser::parse_Power_() {
    Token tk = this->current;
    
    Tree* tr = createTree(treeTypeNode_Power_);
    Tree* tr_Factor;
    if (tk.matchSign("**")) {
        tr->add(createTree(tk));
        this->getNextToken();
    } else {
        return epsilonTreeClass; 
    }

    tr_Factor = this->parse_Factor();
    CHECK_nullptr(Factor);
    tr->add(tr_Factor);

    return tr;
}

Tree* Parser::parse_Factor() {
    Tree* tr = createTree(treeTypeNode_Factor);
    Tree* tr_Expr;
    Tree* tr_FunctionCall;
    Token tk = this->current;

    if (this->current.type == tokenTypeId && this->lx->peek().matchSign("(")) {
        tr_FunctionCall = this->parse_FunctionCall();
        if (tr_FunctionCall != nullptr) {
            tr->add(tr_FunctionCall);
            return tr;
        }
    }
    if (this->current.type == tokenTypeType) {
        Tree* tr_DefineVariable = this->parse_DefineVariable();
        CHECK_nullptr(DefineVariable);
        tr->add(tr_DefineVariable);
        return tr;
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
    // EXPECTED_ERROR("( or something other");
    return tr;
}


Tree* Parser::parse_Sentence() {
    Tree* tr = createTree(treeTypeNode_Sentence);
    Tree* tr_Expr;
    if (this->current.type == tokenTypeKeyword) { // control
        if (this->current.matchKeyword("if")) {
            Tree* tr_If = this->parse_If();
            CHECK_nullptr(If);
            tr->add(tr_If);
            return tr;
        } else if (this->current.matchKeyword("while")) {
            Tree* tr_While = this->parse_While();
            CHECK_nullptr(While);
            tr->add(tr_While);
            return tr;
        } else if (this->current.matchKeyword("do")) {
            Tree* tr_DoWhile = this->parse_DoWhile();
            CHECK_nullptr(DoWhile);
            tr->add(tr_DoWhile);
            return tr;
        } else if (this->current.matchKeyword("for")) {
            Tree* tr_For = this->parse_For();
            CHECK_nullptr(For);
            tr->add(tr_For);
            return tr;
        } else if (this->current.matchKeyword("continue")) {
            Tree* tr_Continue = this->parse_Continue();
            CHECK_nullptr(Continue);
            tr->add(tr_Continue);
            return tr;
        } else if (this->current.matchKeyword("break")) {
            Tree* tr_Break = this->parse_Break();
            CHECK_nullptr(Break);
            tr->add(tr_Break);
            return tr;
        } else if (this->current.matchKeyword("return")) {
            Tree* tr_Return = this->parse_Return();
            CHECK_nullptr(Return);
            tr->add(tr_Return);
            return tr;
        }
    } else if (this->current.type == tokenTypeType) { // int x; char y; float z;
        Tree* tr_DefineVariable = this->parse_DefineVariable();
        CHECK_nullptr(DefineVariable);
        tr->add(tr_DefineVariable);
        if (!this->current.matchSign(";")) EXPECTED_ERROR(";");
        this->getNextToken();
        return tr;
    } else if (this->current.type == tokenTypeSign) {
        if (this->current.matchSign("++") || this->current.matchSign("--") || this->current.matchSign("**")) {
            Tree* tr_Increment = this->parse_Increment();
            CHECK_nullptr(Increment);
            tr->add(tr_Increment);
            return tr;
        }
    }
        
    tr_Expr = this->parse_Expr();
    CHECK_nullptr(Expr);
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
    
    while (!this->current.matchSign("}")) {
        tr_Sentence = this->parse_Sentence();
        CHECK_nullptr(Sentence);
        tr->add(tr_Sentence);
    }

    return tr;
}

Tree* Parser::parse_Statements() {
    Tree* tr = createTree(treeTypeNode_Statements);
    Tree* tr_Sentences;
    Tree* tr_Sentence;
    if (!this->current.matchSign("{")) { // try not { Sentences }
        tr_Sentence = this->parse_Sentence();
        if (tr_Sentence == nullptr) { // try is Sentence
            this->parserError("Statements expected");
        }
        tr->add(tr_Sentence);
        return tr;
    }
    this->getNextToken();

    tr_Sentences = this->parse_Sentences();
    CHECK_nullptr(Sentences);
    tr->add(tr_Sentences);

    this->getNextToken();

    return tr;
}

// ++ var
// -- var
// ** var (var ** 2)
Tree* Parser::parse_Increment() {
    Tree* tr = createTree(treeTypeNode_Increment);
    tr->add(createTree(this->current));
    this->getNextToken();
    if (this->current.type == tokenTypeEof) {
        return nullptr;
    }
    if (this->current.type != tokenTypeId) {
        this->parserError("Should be an Id");
    }
    tr->add(createTree(this->current));
    this->getNextToken();
    return tr;
}
