#include "Symbol/Symbol.h"
#ifndef TEST

#include <iostream>
#include "CmdLineParser/CmdLineParser.h"
#include "FileManager/FileManager.h"
#include "Lexer/Lexer.h"
#include "Tree/Tree.h"
#include "Parser/Parser.h"
#include "Syntax/Syntax.h"
#include "StackEraser/StackEraser.h"
#include "CodeGen/CodeGen.h"


int main(int argc, char ** argv) {
    CmdLineParser clp(argc, argv);
    FileManager file;
    Lexer lexer;
    Tree * root;
    IRs irs;
    Symbol symbol;
    clp.run();
    auto inputFile = clp.table.find("");
    auto outputFile = clp.table.find("o");
    bool isOutputToFile = false;
    if (inputFile != clp.table.end()) {
        bool r = file.setInputFile(inputFile->second);
        if (!r) {
            std::cerr << "Could not open file " << inputFile->second << std::endl;
            return 1;
        }
    }
    if (outputFile != clp.table.end()) {
        isOutputToFile = file.setOutputFile(outputFile->second);
    }
    file.next();
    lexer.setFile(file);
    Parser parser(&lexer);
    root = parser.parse_Unit();
    Syntax syntax(root, &irs, &symbol);
    syntax.init();
    syntax.analyze_unit();
    StackEraser stackeraser(&irs);
    stackeraser.convert();
    CodeGen codegen(&irs, &symbol);
    codegen.generate();
    if (isOutputToFile) {
        file.outputToFile(codegen.get_output());
    } else {
        std::cout << codegen.get_output();
    }
    return 0;
}

#endif