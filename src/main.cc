#include "FileManager/FileManager.h"
#include "Lexer/Lexer.h"
#include "CmdLineParser/CmdLineParser.h"
#include "Token/Token.h"
#include "Parser/Parser.h"
#include "Syntax/Syntax.h"
#include "StackEraser/StackEraser.h"
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
    clp.display();

    //tk = tkzer.getNextToken();
    /*
    while (!tk.isEof()) {
        std::cout << tk.typeToText() << ' ' << tk.line << ' ' << tk.column << '['<< tk.content << ']' << std::endl;
        tk = tkzer.getNextToken();
    }*/


    /* s */
    Tree *root = psr.parse_Unit(); 
    if (root == nullptr) sayError("what??");
    root->display();
    std::cout << " ----------\n";
    IRs irs;
    Syntax syn(root, &irs);
    syn.init();
    syn.analyze_unit();
    StackEraser se(&irs);
    se.convert();
    irs.display();
    /* e */
    return 0;
}