#ifndef _ABANDON_AST_H_
#define _ABANDON_AST_H_

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
};


Tree* createNodeTree(treeType type, Token tk);
Tree* createNodeTree();
Tree* createNodeTree(treeType type);
Tree* createNodeTree(Token tk);

class AST {
    public:
    Lexer* lx;
    Tree* tr;

    AST(Lexer* lx);
    ~AST();

    Tree* addToNodeTree(Tree* tr, Tree* child);

    #ifdef DEBUG
    void print(Tree* tr, int indent = 0);
    void print();
    #endif
};


#endif