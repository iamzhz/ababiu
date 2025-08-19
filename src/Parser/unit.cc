#include "Parser.h"
#ifdef DEBUG
#include <iostream>
#endif

Tree* Parser::parse_Unit() {
    Tree* tr = createTree(treeTypeNode_Unit);
    while (current.type != tokenTypeEof) {
        tr->add(this->parse_DefineFunction());
    }
    #ifdef DEBUG
    std::cout << "---------------" << std::endl;
    tr->display(0); // print tree
    #endif
    return tr;
}