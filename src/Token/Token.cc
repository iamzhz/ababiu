#include "../include.h"
bool Token::idToKeyword() {
    // fn, int, float, string
    switch (this->content.length()) {
        case 2:
            if ("fn" == this->content) break;
            if ("do" == this->content) break;
            return false;
        case 3:
            if ("int" == this->content) break;
            if ("for" == this->content) break;
            return false;
        case 4:
            if ("void" == this->content) break;
            if ("char" == this->content) break;
            return false;
        case 5:
            if ("float" == this->content) break;
            if ("while" == this->content) break;
            return false;
        case 6:
            if ("string" == this->content) break;
            if ("return" == this->content) break;
            return false;
        default:
            return false;
    }
    this->type = tokenTypeKeyword;
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

std::string Token::typeToText(tokenType type) {
    switch (type) {
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
        case tokenTypeSign:
            return "Sign";
        case tokenTypeString:
            return "String";
        case tokenTypeUnknown:
            return "Unknown";
    }
    return "What?";
}
std::string Token::typeToText() {
    return typeToText(this->type);
}