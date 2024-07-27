#ifndef _ABANDON_AST_H_
#define _ABANDON_AST_H_

#include "../include.h"

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