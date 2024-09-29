#include "../include.h"
IRs::IRs(IRsType type) {
    this->type = type;
}
IRs::IRs() {
    this->type = IRsType_Main;
}
void IRs::add(IR ir) {
    content.push_back(ir);
}