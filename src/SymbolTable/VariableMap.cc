#include "../include.h"

VariableMap::VariableMap() {
    this->indexCount = 0;
}

int VariableMap::add() {
    int index = this->indexCount;
    VariableInfo info;
    this->indexCount ++;
    // TODO: set some info to `info`
    this->map.push_back(info);
    return index;
}