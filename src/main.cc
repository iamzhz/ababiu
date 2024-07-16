#include "include.h"
int main(int argc, char** argv) {
    FileManager f;
    Lexer lx;
    CmdLineParser clp(argc, argv);
    Parser parser;
    parser.lx = &lx;
    AST tree(&lx);
    clp.run();
    clp.print();
    if (!f.setInputFile(clp.inputFiles[0])) sayError("Cannot open input file");
    
    f.next();
    lx.setFile(f);

    ASSERT(parser.parser(&tree));
    tree.print();

    f.closeFile();
    return 0;
}