#include "../include.h"
bool Lexer::isSpace(char ch) {
    return 
        ch == ' ' ||
        ch == '\r' ||
        ch == '\n' ||
        ch == '\t';
}
bool Lexer::isDigit(char ch) {
    return ch >= '0' && ch <= '9';
}
bool Lexer::isLetter(char ch) {
    return (ch >= 'a' && ch <= 'z') ||
            (ch >= 'A' && ch <= 'Z');
}


void Lexer::setFile(FileManager& file) {
    this->file = &file; // copy pointer
}


Token Lexer::getNextToken() {
    Token tk;
    char cur;
    int tokenLine, tokenColumn;

    do {
        if (!isSpace(this->file->current())) break;
    }while(this->file->next()); // skip space
    if (this->file->isEof) {
        tk.type = tokenTypeEof;
        this->content = tk;
        return tk;
    }
    
    tokenLine = this->file->curLine;
    tokenColumn = this->file->curColumn;
    cur = this->file->current();
    if (this->isDigit(cur)) tk = this->intToken();
    else if (this->isLetter(cur) || cur == '_') tk = this->idToken();
    else if (cur == '\'') tk = this->charToken(); 
    else if (cur == '\"') tk = this->stringToken();
    else if (this->isSign(cur)) tk = this->signToken();
    else {
        tk.type = tokenTypeEof;
        this->file->next();
    }

    tk.line = tokenLine;
    tk.column = tokenColumn;
    this->content = tk;
    return tk;
}


Token Lexer::intToken() {
    Token tk, tmp;
    char cur;
    tk.type = tokenTypeInt;
    if (!this->isDigit(this->file->current())) 
            sayError(this->file->curLine, this->file->curColumn, "Should be a digit here");
    do {
        cur = this->file->current();
        if (this->isDigit(cur)) {
            tk.addToContent(cur);
        }else if ('.' == cur) { // if is float
        tk.type = tokenTypeFloat;
            tk.addToContent(cur);
            this->file->next();
            tmp = this->intToken();
            if (tmp.type != tokenTypeInt) sayError("Syntax wrong");
            tk.addToContent(tmp.content);
            break;
        }else break;
    } while (this->file->next());
    return tk;
}


Token Lexer::idToken() {
    Token tk;
    char cur;
    tk.type = tokenTypeId;
    do {
        cur = this->file->current();
        if (this->isLetter(cur) || this->isDigit(cur) || cur == '_') {
            tk.addToContent(cur);
        }else break;
    } while (this->file->next());

    tk.idToKeyword();
    return tk;
}


char Lexer::readChar(char cannotBe, bool& tell) {
    char ch = this->file->current();
    if (ch != '\\') {
        if (ch == cannotBe) tell = true;
        this->file->next();
        return ch;
    }

    if (this->file->next()) {
        switch (this->file->current()) {
            case 'n': ch = '\n'; break;
            case 'r': ch = '\r';break;
            case 'b': ch = '\b';break;
            case '0': ch = '\0';break;
            case '\\': ch = '\\';break;
            case '\'': ch = '\'';break;
            case '\"': ch = '\"';break;
            default: return '\\'; // IMPORTANT: no `next()` here
        }
        this->file->next();
        return ch;
    }
    sayError(this->file->curLine, this->file->curColumn, "Eof but not complete");
    return '\0'; // 随便返回个值意思意思编译器
}


Token Lexer::charToken() {
    Token tk;
    bool tell = false;
    this->file->next();
    tk.addToContent(this->readChar('\'', tell));
    if (tell) sayError(this->file->curLine, this->file->curColumn, "\'\'?");

    if (this->file->current() == '\'') {
        this->file->next(); // to make next token success
        tk.type = tokenTypeChar;
        return tk;
    }
    sayError(this->file->curLine, this->file->curColumn, 
                std::string("Ah?")+this->file->current()+'?');
    return tk;
}


Token Lexer::stringToken() {
    bool tell = false;
    Token tk;
    char ch;
    if (!this->file->next()) 
        sayError(this->file->curLine, this->file->curColumn, "only one \"?");
    
    while (true) {
        ch = this->readChar('\"', tell);
        if (tell) {
            tk.type = tokenTypeString;
            return tk;
        }
        tk.addToContent(ch);
    }
    sayError(this->file->curLine, this->file->curColumn, "another \"?");
    return tk;
}