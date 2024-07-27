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
    Tree* m = createNodeTree(), *t2;
    Token ta, tb, tc;
    ta.content = "1"; ta.type = tokenTypeInt;
    tb.content = "\"hello\""; tb.type = tokenTypeString;
    tc.content = "3"; tc.type = tokenTypeInt;
    t2 = createNodeTree(treeTypeNode);
    t2->label = treeTypeNodeAdd;
    t2->add(createNodeTree(tb));
    t2->add(createNodeTree(tc));
    m->add(createNodeTree(treeTypeToken, ta));
    m->add(t2);
    m->label = treeTypeNodeSub;
    ast.tr = m;
    ast.print();
    /* e */

    f.closeFile();
    return 0;
}