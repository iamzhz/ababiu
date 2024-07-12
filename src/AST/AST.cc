#include "../include.h"

AST::AST(Lexer* lx) {
    this->lx = lx;
}


AST* AST::addChild(ast_type label, Lexer* lx) {
    AST* ret = new AST(lx);
    ret->label = label;
    this->children.push_back(ret);
    return ret;
}

AST* AST::addTokenChild(Token tk, Lexer* lx) {
    AST* ret = this->addChild(ast_token, lx);
    ret->setToken(tk);
    return ret;
}


void AST::setToken(Token tk) {
    this->tk = tk;
}

bool AST::match(std::string content) {
    Token tk;
    tk = this->lx->getNextToken();
    if (tk.type == tokenTypeEof) return false;
    if (tk.content == content) {
        this->addTokenChild(tk, this->lx);
        return true;
    }
    sayError(tk.line, tk.column, std::string("Should be `")+content+"` here");
    return true;
}

bool AST::match(tokenType want) {
    Token tk;
    tk = this->lx->getNextToken();
    if (tk.type == tokenTypeEof) return false;
    if (tk.type == want) {
        this->addTokenChild(tk, this->lx);
        return true;
    }
    sayError(tk.line, tk.column, std::string("Should be `")+tk.typeToText(want)+"` here");
    return true;
}

bool AST::isMatch(std::string content, bool& tell) {
    Token tk;
    tk = this->lx->getNextToken();
    if (tk.type == tokenTypeEof) return false;
    if (tk.content == content) {
        tell = true;
        return true;
    }
    tell = false;
    return true;
}
bool AST::isMatch(tokenType want, bool& tell) {
    Token tk;
    tk = this->lx->getNextToken();
    if (tk.type == tokenTypeEof) return false;
    if (tk.type == want) {
        tell = true;
        return true;
    }
    tell = false;
    return true;
}
#ifdef DEBUG

/*void AST::print() {
    if (this->label == ast_token) {
        std::cout << this->tk.content << std::endl;
        ASSERT("token");
        return;
    }
    std::cout << this->label << '\t' << this->tk.content << std::endl;
    for (auto a : this->children) {
        a->print();
    }
}*/

void AST::print(int indent) {
    for (int i = 0; i < indent; ++i) {
        std::cout << "  ";
    }
    switch (label) {
        case ast_token:
            std::cout << this->tk.content << std::endl;
            break;
        default:
            std::cout << "Node Label: " << label << std::endl;
            for (AST* child : this->children) {
                child->print(indent + 1);
            }
            break;
    }
}

#endif
