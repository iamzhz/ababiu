
#include "include.h"
int main() {
    FileManager f;
    Lexer tkzer;
    Token tk;
    f.setInputFile("hello.txt");
    //std::cout << f.isEof;
    f.next();
    tkzer.setFile(f);
    tk = tkzer.getNextToken();
    while (!tk.isEof()) {
        std::cout << tk.typeToText() << '['<< tk.content << ']' << std::endl;
        tk = tkzer.getNextToken();
    }
    f.closeFile();
    return 0;
}