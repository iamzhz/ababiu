#include "Tree.h"
#include "../PointerManager/PointerManager.h"
#include "../Token/Token.h"
#ifdef DEBUG
#include <iostream>
#endif

PointerManager<Tree*> pmTree;
Token noneTokenClass;

Tree::Tree() {}
Tree::Tree(treeType type) {
    this->type = type;
}


void Tree::add(Tree* tr) {
    this->children.push_back(tr);
}

std::string treeTypeNodeLabelToText(treeTypeNodeLabel label) {
    switch (label) {
        case treeTypeNode_Main: return "Main";
        case treeTypeNode_Epsilon: return "ε";
        case treeTypeNode_Expr: return "Expr";
        case treeTypeNode_Assign: return "Assign";
        case treeTypeNode_Assign_: return "Assign'";
        case treeTypeNode_Compare: return "Compare";
        case treeTypeNode_Compare_: return "Compare'";
        case treeTypeNode_Add: return "Add";
        case treeTypeNode_Add_: return "Add'";  
        case treeTypeNode_Times: return "Times";
        case treeTypeNode_Times_: return "Times'";
        case treeTypeNode_Power: return "Power";
        case treeTypeNode_Power_: return "Power'";
        case treeTypeNode_Factor: return "Factor";
        case treeTypeNode_Sentence: return "Sentence";
        case treeTypeNode_Sentences: return "Sentences";
        case treeTypeNode_Statements: return "Statements";
        case treeTypeNode_ExprList: return "ExprList";
        case treeTypeNode_ExprList_: return "ExprList'";
        case treeTypeNode_FunctionCall: return "FunctionCall";
        case treeTypeNode_DefineFunction: return "DefineFunction";
        case treeTypeNode_DefineVariable: return "DefineVariable";
        case treeTypeNode_DefineVariableList: return "DefineVariableList";
        case treeTypeNode_If: return "If";
        case treeTypeNode_Else: return "Else";
        case treeTypeNode_While: return "While";
        case treeTypeNode_DoWhile: return "DoWhile";
        case treeTypeNode_For: return "For";
        case treeTypeNode_Break: return "Break";
        case treeTypeNode_Continue: return "Continue";
        case treeTypeNode_Return: return "Return";
        case treeTypeNode_None: return "None";
        case treeTypeNode_Unit: return "Unit";
        case treeTypeNode_FunctionExtern: return "FunctionExtern";
        case treeTypeNode_Increment: return "Increment";
    }
    return "Unkown";
}

#ifdef DEBUG
void Tree::display(int indent) {
    this->display(indent, true);
}
void Tree::display(int indent, bool last) {
    for (int i = 0; i < indent - 1; ++i) {
        std::cout << (i < indent - 1 ? "│   " : "    ");
    }

    if (indent > 0) {
        std::cout << (last ? "└── " : "├── ");
    }

    if (this->type == treeType_Token) {
        std::cout << "Token "
            << this->tk.typeToText() << " [" << this->tk.content << "]\n";
    } else {
        std::cout << "Node " << treeTypeNodeLabelToText(this->label) << std::endl;

        for (size_t i = 0; i < this->children.size(); ++i) {
            this->children[i]->display(indent + 1, i == this->children.size() - 1);
        }
    }
}

#endif



/* createTree() begin */
Tree* createTree(treeType type, Token tk, treeTypeNodeLabel label) {
    Tree *tr = new Tree(type);
    tr->label = label;
    pmTree.add(tr);
    if (type == treeType_Token) {
        tr->tk = tk;
    }
    return tr;
}
Tree* createTree() {
    return createTree(treeType_Node, noneTokenClass, treeTypeNode_None);
}
Tree* createTree(treeType type) {
    return createTree(type, noneTokenClass, treeTypeNode_None);
}
Tree* createTree(Token tk) {
    return createTree(treeType_Token, tk, treeTypeNode_None);
}
Tree* createTree(treeTypeNodeLabel label) {
    return createTree(treeType_Node, noneTokenClass, label);
}
/* createTree() end */
