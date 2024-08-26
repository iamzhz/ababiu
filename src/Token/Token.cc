#include "../include.h"

Token::Token() {
    // nothing now
}
Token::Token(std::string content, enum tokenType type, int line, int column) {
    this->content = content;
    this->type = type;
    this->line = line;
    this->column = column;
}
Token::Token(const Token& other) {
    this->content = other.content;
    this->type = other.type;
    this->line = other.line;
    this->column = other.column;
}
bool Token::idToKeyword() {
    // fn, int, float, string
    switch (this->content.length()) {
        case 2:
            if ("fn" == this->content) break;
            if ("do" == this->content) break;
            return false;
        case 3:
            if ("for" == this->content) break;
            return false;
        case 4:
            if ("void" == this->content) break;
            return false;
        case 5:
            if ("while" == this->content) break;
            if ("break" == this->content) break;
            return false;
        case 6:
            if ("return" == this->content) break;
            return false;
        case 8:
            if ("continue" == this->content) break;
        default:
            return false;
    }
    this->type = tokenTypeKeyword;
    return true;
}

bool Token::idToType() {
    // int char float string
    switch (this->content.length()) {
        case 3:
            if ("int" == this->content) break;
            return false;
        case 4:
            if ("char" == this->content) break;
            return false;
        case 5:
            if ("float" == this->content) break;
            return false;
        case 6:
            if ("string" == this->content) break;
            return false;
        default:
            return false;
    }
    this->type = tokenTypeType;
    return true;
}

bool Token::matchSign(std::string content) {
    if (this->type == tokenTypeSign) {
        if (this->content == content) return true;
    }
    return false;
}

bool Token::matchKeyword(std::string content) {
    if (this->type == tokenTypeKeyword) {
        if (this->content == content) return true;
    }
    return true;
}

bool Token::match(tokenType type) {
    return this->type == type;
}

void Token::addToContent(char newChar) {
    char tmp[2] = {0};
    tmp[0] = newChar;
    this->content.append(tmp);
}

void Token::addToContent(int newChar) {
    this->addToContent((char)(newChar+'0'));
}

void Token::addToContent(std::string newString) {
    this->content += newString;
}

bool Token::isEof() {
    return this->type == tokenTypeEof;
}

std::string Token::typeToText() {
    switch (this->type) {
        case tokenTypeEof:
            return "Eof";
        case tokenTypeChar:
            return "Char";
        case tokenTypeFloat:
            return "Float";
        case tokenTypeId:
            return "Id";
        case tokenTypeInt:
            return "Int";
        case tokenTypeKeyword:
            return "Keyword";
        case tokenTypeType:
            return "Type";
        case tokenTypeSign:
            return "Sign";
        case tokenTypeString:
            return "String";
    }
    return "Unknown";
}