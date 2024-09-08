#include "../include.h"

Tree* Parser::parse_Unit() {
    if (current.type == tokenTypeEof) return createTree(treeType_End);
    return this->parse_DefineFunction();
}