#include "../include.h"

bool Lexer::isSign(char ch) {
    char signs[] = {'+', '-', '*', '/', '=', '{', '}', '[', ']'};
    for (int i = 0;  i < sizeof(signs);  i ++) {
        if (ch == signs[i]) return true;
    }
    return false;
}

Token Lexer::signToken() {
    Token tk;
    char cur;
    char pre = this->file->current();
    tk.type = tokenTypeSign;
    tk.addToContent(pre);

    if (!this->file->next()) return tk;
    cur = this->file->current();
    if (!this->isSign(cur)) return tk;

    if (pre == '+' && cur == '=') tk.addToContent(cur);
    else if (pre == '+' && cur == '+') tk.addToContent(cur);
    else if (pre == '-' && cur == '=') tk.addToContent(cur);
    else if (pre == '-' && cur == '-') tk.addToContent(cur);
    else if (pre == '*' && cur == '=') tk.addToContent(cur);
    else if (pre == '/' && cur == '=') tk.addToContent(cur);
    else return tk;
    this->file->next();
    return tk;
}