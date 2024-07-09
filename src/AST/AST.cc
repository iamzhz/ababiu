#include "../include.h"

AST::AST(Lexer* lx) {
    this->lx = lx;
}
void AST::addChild(AST child) {
    this->children.push_back(child);
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
#ifdef DEBUG

void AST::print() {
    if (this->type == ast_token) {
        std::cout << this->tk.content;
        return;
    }
    std::cout << this->type << '\t' << this->tk.content;
    for (auto a : this->children) {
        a.print();
    }
}

#endif
