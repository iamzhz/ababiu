#include "AutoAssign.h"
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
void AutoAssign::set(const Immediate& imm) {
    this->data.back().second = imm;
}
void AutoAssign::set(int i) {
    this->set(makeImmediate(i));
}
void AutoAssign::assign() {
    std::vector<int>& lastVec = this->data.back().first;
    const Immediate& imm = this->data.back().second;
    for (int i : lastVec) {
        this->irs->content[i].imm0 = imm;
    }
    this->data.pop_back();
}