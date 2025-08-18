#ifndef TEST

#include <iostream>
#include <string>
#include <cstdlib>
#include "Symbol/Symbol.h"
#include "CmdLineParser/CmdLineParser.h"
#include "FileManager/FileManager.h"
#include "Lexer/Lexer.h"
#include "Tree/Tree.h"
#include "Parser/Parser.h"
#include "Syntax/Syntax.h"
#include "StackEraser/StackEraser.h"
#include "CodeGen/CodeGen.h"

std::string compile_file(std::string filename, Symbol * symbol);

int main(int argc, char ** argv) {
    CmdLineParser clp(argc, argv);
    FileManager file;
    Symbol symbol;
    clp.run();
    auto inputFile = clp.table.find("");
    auto outputFile = clp.table.find("o");
    bool isOutputToFile = false;
    if (inputFile == clp.table.end()) {
        std::cerr << "Please provide input file" << std::endl;
        return 1;
    }
    if (outputFile != clp.table.end()) {
        isOutputToFile = file.setOutputFile(outputFile->second);
    }
    // analyze built-in library
    compile_file("libababiu/libababiu.abb", &symbol);
    // compile input file
    std::string output = compile_file(inputFile->second, &symbol);
    if (isOutputToFile) {
        file.outputToFile(output);
    } else {
        std::cout << output;
    }
    return 0;
}

std::string compile_file(std::string filename, Symbol * symbol) {
    FileManager file;
    Lexer lexer;
    Tree * root;
    IRs irs;
    bool isOutputToFile = false;
    bool r = file.setInputFile(filename);
    if (!r) {
        std::cerr << "Could not open file " << filename << std::endl;
        std::exit(1);
    }
    file.next();
    lexer.setFile(file);
    Parser parser(&lexer);
    root = parser.parse_Unit();
    Syntax syntax(root, &irs, symbol);
    syntax.init();
    syntax.analyze_unit();
    StackEraser stackeraser(&irs);
    stackeraser.convert();
    CodeGen codegen(&irs, symbol);
    codegen.generate();
    return codegen.get_output();
}

#endif