#include "../include.h"

PointerManager<Tree*> pmTree;

Tree::Tree() {
    // nothing here
}

Tree::Tree(treeType type) {
    this->type = type;
    pmTree.add(this);
}

Tree::Tree(treeTypeNodeLabel label) {
    this->type = treeTypeNode;
    this->label = label;
}

Tree::Tree(Token tk) {
    this->type = treeTypeToken;
    this->tk = tk;
}


void Tree::add(Tree* tr) {
    this->children.push_back(tr);
}

std::string treeTypeNodeLabelToText(treeTypeNodeLabel label) {
    switch (label) {
        case treeTypeNodeMain: return "Main";
        case treeTypeNodeAdd: return "Add";
        case treeTypeNodeSub: return "Sub";
    }
    return "Unkown";
}

/* createNodeTree() begin */
Tree* createNodeTree(treeType type, Token tk) {
    Tree *tr = new Tree(type);
    pmTree.add(tr);
    if (type == treeTypeToken) {
        tr->tk = tk;
    }
    return tr;
}
Tree* createNodeTree() {
    return createNodeTree(treeTypeNode, noneTokenClass);
}
Tree* createNodeTree(treeType type) {
    return createNodeTree(type, noneTokenClass);
}
Tree* createNodeTree(Token tk) {
    return createNodeTree(treeTypeToken, tk);
}
/* createNodeTree() end */

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