#ifndef _ABANDON_LEXER_H_
#define _ABANDON_LEXER_H_

#include "../include.h"

class Lexer {
    private:
    FileManager* file;
    Token intToken();
    Token idToken();
    char readChar(char cannotBe, bool& tell); // is char is CB, then tell'll be true
    Token charToken();
    Token stringToken();
    Token signToken();
    bool isSpace(char ch);
    bool isDigit(char ch);
    bool isLetter(char ch);
    bool isSign(char ch);
    
    public:
    void setFile(FileManager& file);
    Token getNextToken();
};
#endif