#include "../include.h"

void Parser::getNextToken() {
    this->current = this->lx->getNextToken();
}
void Parser::parserError(Token tk, std::string info) {
    sayError(tk.line, tk.column, info);
}
void Parser::parserError(std::string info) {
    this->parserError(this->current, info);
}