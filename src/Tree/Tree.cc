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
        case treeTypeNodeMain: return "Main";
        case treeTypeNodeNone: return "None";
        case treeTypeNodeAdd: return "Add";
        case treeTypeNodeSub: return "Sub";
    }
    return "Unkown";
}

#ifdef DEBUG
void Tree::display(int indent) {
    int i;
    for (i = 0;  i < indent;  i ++) { // for beauty
        std::cout << ' ';
    }
    if (this->type == treeTypeToken) {
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
    if (type == treeTypeToken) {
        tr->tk = tk;
    }
    return tr;
}
Tree* createTree() {
    return createTree(treeTypeNode, noneTokenClass, treeTypeNodeNone);
}
Tree* createTree(treeType type) {
    return createTree(type, noneTokenClass, treeTypeNodeNone);
}
Tree* createTree(Token tk) {
    return createTree(treeTypeToken, tk, treeTypeNodeNone);
}
Tree* createTree(treeTypeNodeLabel label) {
    return createTree(treeTypeNode, noneTokenClass, label);
}
/* createTree() end */