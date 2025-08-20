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
void auto_continue_compile(std::string output_file);

int main(int argc, char ** argv) {
    CmdLineParser clp(argc, argv);
    FileManager file;
    Symbol symbol;
    clp.run();
    bool isAutoContinueCompile = clp.table.find("auto") != clp.table.end();
    auto inputFile = clp.table.find("");
    auto outputFile = clp.table.find("o");
    bool isOutputToFile = false;
    if (inputFile == clp.table.end()) {
        std::cerr << "Please provide input file" << std::endl;
        return 1;
    }
    if (outputFile != clp.table.end()) {
        if (isAutoContinueCompile) {
            isOutputToFile = file.setOutputFile("ababiu_temp.asm");
        } else {
            isOutputToFile = file.setOutputFile(outputFile->second);
        }
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
    file.closeFile();
    if (isAutoContinueCompile) {
        auto_continue_compile(outputFile->second);
    }
    return 0;
}

std::string compile_file(std::string filename, Symbol * symbol) {
    FileManager file;
    Lexer lexer;
    Tree * root;
    IRs irs;
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
    StackEraser stackeraser(&irs, symbol);
    stackeraser.convert();
    CodeGen codegen(&irs, symbol);
    codegen.generate();
    return codegen.get_output();
}

void auto_continue_compile(std::string output_file) {
    // check nasm & ld
    int nasm_return = std::system("nasm --version > /dev/null");
    int ld_return = std::system("ld --version > /dev/null");
    if (nasm_return != 0) {
        std::cerr << "nasm is not exist.\n";
        std::exit(1);
    }
    if (ld_return != 0) {
        std::cerr << "ld is not exist.\n";
        std::exit(1);
    }
    std::system("nasm -f elf64 ababiu_temp.asm -o ababiu_temp.o");
    std::system(("ld ababiu_temp.o -o " + output_file + " -L. -lc -lababiu -dynamic-linker /lib64/ld-linux-x86-64.so.2").c_str());
}