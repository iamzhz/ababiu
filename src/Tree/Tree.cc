#include "../include.h"

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
        case treeTypeNode_None: return "None";
        case treeTypeNode_Add: return "Add";
        case treeTypeNode_Sub: return "Sub";
    }
    return "Unkown";
}

#ifdef DEBUG
void Tree::display(int indent) {
    int i;
    for (i = 0;  i < indent;  i ++) { // for beauty
        std::cout << ' ';
    }
    if (this->type == treeType_Token) {
        std::cout << "Token " << this->tk.typeToText() << 
                " [" << this->tk.content << ']' << std::endl;
        return ;
    }
    // is Node
    std::cout << "Node " << treeTypeNodeLabelToText(this->label) << std::endl;
    for (auto child : this->children) {
        child->display(indent + 1);
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