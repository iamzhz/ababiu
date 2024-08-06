#ifndef _ABANDON_TREE_H_
#define _ABANDON_TREE_H_

#include "../include.h"

extern Token noneTokenClass;
enum treeType {
    treeType_End,
    treeType_Token,
    treeType_Node
};

enum treeTypeNodeLabel {
    treeTypeNode_Main,
    treeTypeNode_None,
    treeTypeNode_Epsilon,
    treeTypeNode_Expr,
    treeTypeNode_Expr_,
    treeTypeNode_Term,
    treeTypeNode_Term_,
    treeTypeNode_Factor,
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
    void display(int indent, bool last);
    #endif
};

std::string treeTypeNodeLabelToText(treeTypeNodeLabel label);

Tree* createTree(treeType type, Token tk, treeTypeNodeLabel label);
Tree* createTree();
Tree* createTree(treeType type);
Tree* createTree(Token tk);
Tree* createTree(treeTypeNodeLabel label);
#endif