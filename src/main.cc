#define DEBUG
#include "include.h"
int main(int argc, char** argv) {
    FileManager f;
    Lexer tkzer;
    Token tk;
    CmdLineParser clp(argc, argv);
    Parser psr(&tkzer);
    clp.run();
    clp.display();
    if (!f.setInputFile(clp.inputFiles[0])) sayError("Cannot open input file");
    
    f.next();
    tkzer.setFile(f);
    tk = tkzer.getNextToken();
    /*
    while (!tk.isEof()) {
        std::cout << tk.typeToText() << ' ' << tk.line << ' ' << tk.column << '['<< tk.content << ']' << std::endl;
        tk = tkzer.getNextToken();
    }*/


    /* s */
    Tree *root = psr.parse_Expr();
    root = psr.cst2ast(root);
    root->display();
    /* e */
    return 0;
}