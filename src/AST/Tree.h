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
class Tree {
    public:
    treeType type;
    Token tk;
    treeTypeNodeLabel label;
    std::vector<Tree*> children;

    Tree();
    Tree(treeType type);
    Tree(treeTypeNodeLabel label);
    Tree(Token tk);
    void add(Tree* tr);
    void print(int indent = 0);
};

std::string treeTypeNodeLabelToText(treeTypeNodeLabel label);

Tree* createNodeTree(treeType type, Token tk);
Tree* createNodeTree();
Tree* createNodeTree(treeType type);
Tree* createNodeTree(Token tk);
#endif