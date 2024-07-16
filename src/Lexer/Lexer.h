#ifndef _ABANDON_LEXER_H_
#define _ABANDON_LEXER_H_

#include "../include.h"

enum signState {
    signStateRight,
    signStateWrong,
    signStateCommit
};

class Lexer {
    private:
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
    std::vector<Token> stream; // has gotten
    int pointer = -1; // -1 conutine get, or stream[pointer]
    
    public:
    FileManager* file;
    void setFile(FileManager& file);
    Token getNextToken();
    void backToken();
    enum signState isSignTwoChars(char a, char b);
};
#endif