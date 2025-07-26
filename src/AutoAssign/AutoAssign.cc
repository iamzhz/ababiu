#include "../include.h"
AutoAssign::AutoAssign(IRs * irs) {
    this->irs = irs;
}
void AutoAssign::create() {
    this->data.push_back({});
}
void AutoAssign::add(int pos) {
    std::vector<int>& lastVec = this->data.back().first;
    lastVec.push_back(pos);
}
void AutoAssign::set(const Quicknumber& qn) {
    this->data.back().second = qn;
}
void AutoAssign::assign() {
    std::vector<int>& lastVec = this->data.back().first;
    const Quicknumber& qn = this->data.back().second;
    for (int i : lastVec) {
        this->irs->content[i].qn0 = qn;
    }
    this->data.pop_back();
}