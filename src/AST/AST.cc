#include "../include.h"

/* createNodeTree() begin */
Tree* createNodeTree(treeType type, Token tk) {
    Tree *tr = new Tree;
    pmTree.add(tr);
    tr->type = type;
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



AST::AST(Lexer* lx) {
    this->lx = lx;
    this->tr = new Tree;
    pmTree.add(this->tr);
}
AST::~AST() {
    // nothing now
}

Tree* AST::addToNodeTree(Tree* tr, Tree* child) {
    #ifdef DEBUG
        if (tr->type != treeTypeNode) ASSERT("Not a Node Tree");
    #endif

    tr->children.push_back(child);

    return tr;
}

#ifdef DEBUG
void AST::print(Tree* tr, int indent) {
    int i;
    for (i = 0;  i < indent;  i ++) { // for beauty
        std::cout << ' ';
    }
    if (tr->type == treeTypeToken) {
        std::cout << "Token " << tr->tk.typeToText() << 
                " [" << tr->tk.content << ']' << std::endl;
        return ;
    }
    // is Node
    for (auto child : tr->children) {
        std::cout << "Node " << treeTypeNodeLabelToText(child->label) << std::endl;
        this->print(child, indent + 1);
    }
}
void AST::print() {
    this->print(this->tr);
}
#endif

Token noneTokenClass;