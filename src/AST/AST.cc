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


void AST::setToken(Token tk) {
    this->tk = tk;
}

bool AST::match(std::string content) {
    Token tk;
    tk = this->lx->getNextToken();
    if (tk.type == tokenTypeEof) return false;
    if (tk.content == content) return true;
    sayError(tk.line, tk.column, std::string("Should be `")+content+"` here");
    return true;
}

bool AST::match(tokenType want) {
    Token tk;
    tk = this->lx->getNextToken();
    if (tk.type == tokenTypeEof) return false;
    if (tk.type == want) return true;
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

void AST::print() {
    if (this->label == ast_token) {
        std::cout << this->tk.content;
        return;
    }
    std::cout << this->label << '\t' << this->tk.content;
    for (auto a : this->children) {
        a->print();
    }
}

#endif
