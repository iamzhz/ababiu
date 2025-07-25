#include "../include.h"
void AutoAssign::create() {
    this->data.push_back({});
}
void AutoAssign::add(IR* i) {
    std::vector<IR*>& lastVec = this->data.back();
    lastVec.push_back(i);
}
void AutoAssign::assign(int pos) {
    std::vector<IR*>& lastVec = this->data.back();
    for (IR* i : lastVec) {
        i->qn0 = makeQuicknumber(pos);
    }
}