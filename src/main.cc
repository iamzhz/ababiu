#define DEBUG
#include "include.h"
int main(int argc, char** argv) {
    FileManager f;
    Lexer tkzer;
    Token tk;
    CmdLineParser clp(argc, argv);
    clp.run();
    clp.print();
    if (!f.setInputFile(clp.inputFiles[0])) sayError("Cannot open input file");
    
    f.next();
    tkzer.setFile(f);
    tk = tkzer.getNextToken();
    while (!tk.isEof()) {
        std::cout << tk.typeToText() << ' ' << tk.line << ' ' << tk.column << '['<< tk.content << ']' << std::endl;
        tk = tkzer.getNextToken();
    }
    f.closeFile();
    return 0;
}