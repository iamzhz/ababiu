#include "include.h"
int main(int argc, char** argv) {
    FileManager f;
    Lexer tkzer;
    Token tk;
    CmdLineParser clp(argc, argv);
    clp.run();
    if (!f.setInputFile(clp.inputFiles[0])) sayError("Cannot open input file");
    f.next();
    tkzer.setFile(f);
    Parser psr(&tkzer);
    Tree *root = psr.parse_Unit(); 
    if (root == nullptr) sayError("what??");
    IRs irs;
    Syntax syn(root, &irs);
    syn.analyze_unit();
    irs.display();
    return 0;
}