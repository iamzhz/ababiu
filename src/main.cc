#include "AST/Tree.h"
#define DEBUG
#include "include.h"
int main(int argc, char** argv) {
    FileManager f;
    Lexer tkzer;
    Token tk;
    CmdLineParser clp(argc, argv);
    AST ast(&tkzer);
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


    /* s */
    Tree root;
    Token token1("1", tokenTypeInt, 0, 0);
    Token token2("2", tokenTypeInt, 0, 0);
    Token token3("2", tokenTypeInt, 0, 0);
    Tree ttoken1(token1);
    Tree ttoken2(token2);
    Tree ttoken3(token3);
    Tree ttokenSub(treeTypeNodeSub);
    ttokenSub.add(&ttoken2); ttokenSub.add(&ttoken3);
    root.label = treeTypeNodeAdd;
    root.add(&ttoken1);
    root.add(&ttokenSub);
    root.print(0);
    /* e */

    f.closeFile();
    return 0;
}