#include "../include.h"
enum tokenType {
    tokenTypeString, 
    tokenTypeChar,
    tokenTypeInt, 
    tokenTypeFloat, 
    tokenTypeId, 
    tokenTypeKeyword, 
    tokenTypeSign,
    tokenTypeEof,
    tokenTypeUnknown
};

class Token {
    public:
    std::string content;
    enum tokenType type;
    int line;
    int column;
    enum tokenType curType; // may be not final type
    bool idToKeyword(); // return true says `content` is a keyword, or not
    bool matchSign(std::string content);
    bool matchKeyword(std::string content);
    void addToContent(char newChar);
    void addToContent(int newChar);
    bool isEof();

    #ifdef DEBUG
    std::string typeToText();
    #endif
};