#include "Parser.h"
#include "../SayError/SayError.h"
#ifdef DEBUG
#include <iostream>
#endif
void Parser::getNextToken() {
    this->current = this->lx->getNextToken();
    #ifdef DEBUG
    std::cout << this->current.content << std::endl;
    #endif
}
void Parser::parserError(Token tk, std::string info) {
    sayError(tk.line, tk.column, info);
}
void Parser::parserError(std::string info) {
    this->parserError(this->current, info);
}