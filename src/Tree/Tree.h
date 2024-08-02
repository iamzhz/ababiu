#ifndef _ABANDON_TREE_H_
#define _ABANDON_TREE_H_

#include "../include.h"

extern Token noneTokenClass;
enum treeType {
    treeTypeEnd,
    treeTypeToken,
    treeTypeNode
};

enum treeTypeNodeLabel {
    treeTypeNodeMain,
    treeTypeNodeNone,
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
    void add(Tree* tr);

    #ifdef DEBUG
    void display(int indent = 0);
    #endif
};

std::string treeTypeNodeLabelToText(treeTypeNodeLabel label);

Tree* createTree(treeType type, Token tk, treeTypeNodeLabel label);
Tree* createTree();
Tree* createTree(treeType type);
Tree* createTree(Token tk);
Tree* createTree(treeTypeNodeLabel label);
#endif