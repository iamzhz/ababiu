#ifndef _TREE_H_
#define _TREE_H_

#include "../PointerManager/PointerManager.h"
#include "../Token/Token.h"

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
    treeTypeNode_Assign,
    treeTypeNode_Assign_,
    treeTypeNode_Compare,
    treeTypeNode_Compare_,
    treeTypeNode_Add,
    treeTypeNode_Add_,
    treeTypeNode_Times,
    treeTypeNode_Times_,
    treeTypeNode_Power,
    treeTypeNode_Power_,
    treeTypeNode_Factor,
    treeTypeNode_Sentence,
    treeTypeNode_Sentences,
    treeTypeNode_Statements,
    treeTypeNode_ExprList,
    treeTypeNode_ExprList_,
    treeTypeNode_FunctionCall,
    treeTypeNode_DefineFunction,
    treeTypeNode_DefineVariable,
    treeTypeNode_DefineVariableList,

    treeTypeNode_If,
    treeTypeNode_Else,
    treeTypeNode_While,
    treeTypeNode_DoWhile,
    treeTypeNode_For,

    treeTypeNode_Break,
    treeTypeNode_Continue,
    treeTypeNode_Return,
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