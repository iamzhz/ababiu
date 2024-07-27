#include "../include.h"

PointerManager<Tree*> pmTree;

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