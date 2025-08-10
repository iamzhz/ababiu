#include "FileManager/FileManager.h"
#include "Lexer/Lexer.h"
#include "CmdLineParser/CmdLineParser.h"
#include "Token/Token.h"
#include "Parser/Parser.h"
#include "Symbol/Symbol.h"
#include "Syntax/Syntax.h"
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
    Symbol symbol;
    Syntax syn(root, &irs, &symbol);
    syn.init();
    syn.analyze_unit();
    irs.display();
    return 0;
}