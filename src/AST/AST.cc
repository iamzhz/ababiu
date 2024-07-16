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
    ASSERT(content << '|' << tk.content);
    if (tk.type == tokenTypeEof) return false;
    if (tk.content == content) {
        ASSERT(content);
        this->addTokenChild(tk, this->lx);
        return true;
    }
    sayError(tk.line, tk.column, std::string("Should be `")+content+"` here");
    return true;
}

bool AST::match(tokenType want) {
    Token tk;
    tk = this->lx->getNextToken();
    ASSERT(tk.typeToText(want) << '|' << tk.typeToText());
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
    ASSERT(content << '|' << tk.content);
    if (tk.type == tokenTypeEof) return false;
    if (tk.content == content) {
        this->addTokenChild(tk, this->lx);
        tell = true;
        return true;
    }
    this->lx->backToken();
    tell = false;
    return true;
}
bool AST::isMatch(tokenType want, bool& tell) {
    Token tk;
    tk = this->lx->getNextToken();
    ASSERT(tk.typeToText(want) << '|' << tk.typeToText());
    if (tk.type == tokenTypeEof) return false;
    if (tk.type == want) {
        this->addTokenChild(tk, this->lx);
        tell = true;
        return true;
    }
    this->lx->backToken();
    tell = false;
    return true;
}
#ifdef DEBUG

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
