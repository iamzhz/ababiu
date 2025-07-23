#include "../include.h"

void Syntax::analyze_If(Tree * tr) {
    IR i;
    int jump_pos;
    i.op = Op_jumpIfNot_qn;
    this->analyze_Expr(tr->children[0]);
    jump_pos = this->irs->add(i);
    this->analyze_Statements(tr->children[1]);
    this->irs->content[jump_pos].qn0 = makeQuicknumber(this->irs->pos);
    this->if_jump_pos = jump_pos;
}
void Syntax::analyze_Else(Tree * tr) {
    IR i;
    int jump_pos;
    i.op = Op_jump_qn;
    jump_pos = this->irs->add(i);
    this->analyze_Statements(tr->children[0]);
    this->irs->content[jump_pos].qn0 = makeQuicknumber(this->irs->pos);
    this->irs->content[this->if_jump_pos].qn0 = makeQuicknumber(jump_pos + 1);
    this->if_jump_pos = (-1);
}
void Syntax::analyze_DoWhile(Tree * tr) {

}
void Syntax::analyze_For(Tree * tr) {

}
void Syntax::analyze_While(Tree * tr) {

}
void Syntax::analyze_Break(Tree * tr) {

}
void Syntax::analyze_Return(Tree * tr) {

}
void Syntax::analyze_Continue(Tree * tr) {

}