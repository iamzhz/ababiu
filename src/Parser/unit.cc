#include "Parser.h"

Tree* Parser::parse_Unit() {
    Tree* tr = createTree(treeTypeNode_Unit);
    while (current.type != tokenTypeEof) {
        tr->add(this->parse_DefineFunction());
    }
    return tr;
}