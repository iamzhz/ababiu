#ifndef _ABANDON_TREE_H_
#define _ABANDON_TREE_H_
#include "../include.h"

enum treeType {
    treeTypeEnd,
    treeTypeToken,
    treeTypeNode
};

enum treeTypeNodeLabel {
    treeTypeNodeMain,
    treeTypeNodeAdd,
    treeTypeNodeSub
};

extern PointerManager<Tree*> pmTree;
struct Tree {
    treeType type;
    Token tk;
    treeTypeNodeLabel label;
    std::vector<Tree*> children;

    void add(Tree* tr);
};

std::string treeTypeNodeLabelToText(treeTypeNodeLabel label);

#endif