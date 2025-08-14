#include "Syntax.h"

#define POS_NOW_INT (this->irs->pos)
#define POS_NOW (makeImmediate(POS_NOW_INT))

void Syntax::analyze_If(Tree * tr) {
    IR i;
    int jump_pos;
    i.op = Op_jumpIfNot_imm;
    this->analyze_Expr(tr->children[0]);
    jump_pos = this->irs->add(i);
    this->analyze_Statements(tr->children[1]);

    if (tr->children[2]->label == treeTypeNode_Else) {
        this->analyze_Else(tr->children[2], jump_pos);
    } else {
        this->irs->content[jump_pos].imm0 = POS_NOW;
    }
}
void Syntax::analyze_Else(Tree * tr, int if_jump_pos) {
    IR i;
    int jump_pos;
    i.op = Op_jump_imm; // for if-statements jump out
    jump_pos = this->irs->add(i);
    this->analyze_Statements(tr->children[0]);
    this->irs->content[jump_pos].imm0 = POS_NOW;
    this->irs->content[if_jump_pos].imm0 = makeImmediate(jump_pos + 1);
}
void Syntax::analyze_DoWhile(Tree * tr) {
    this->start->create();
    this->end->create();
    IR i;
    this->start->set(POS_NOW);
    this->analyze_Statements(tr->children[0]);
    this->analyze_Expr(tr->children[1]);
    i.op = Op_jumpIf_imm;
    this->start->add(this->irs->add(i));
    this->end->set(POS_NOW);
    this->start->assign();
    this->end->assign();
}
void Syntax::analyze_For(Tree * tr) {
    this->start->create();
    this->end->create();
    IR i;
    int if_jump_pos;
    this->analyze_Expr(tr->children[0]);
    if_jump_pos = POS_NOW_INT;
    this->analyze_Expr(tr->children[1]);
    i.op = Op_jumpIfNot_imm;
    this->end->add(this->irs->add(i));
    this->analyze_Statements(tr->children[3]);
    this->start->set(POS_NOW);
    this->analyze_Expr(tr->children[2]);
    i.op = Op_jump_imm;
    i.imm0 = makeImmediate(if_jump_pos);
    this->irs->add(i);
    this->end->set(POS_NOW);
    this->start->assign();
    this->end->assign();
}
void Syntax::analyze_While(Tree * tr) {
    this->start->create();
    this->end->create();
    IR i;
    this->start->set(POS_NOW_INT);
    this->analyze_Expr(tr->children[0]);
    i.op = Op_jumpIfNot_imm;
    this->end->add(this->irs->add(i));
    this->analyze_Statements(tr->children[1]);
    i.op = Op_jump_imm;
    this->start->add(this->irs->add(i));
    this->end->set(POS_NOW);
    this->start->assign();
    this->end->assign();
}
void Syntax::analyze_Break() {
    IR i;
    i.op = Op_jump_imm;
    this->end->add(this->irs->add(i));
}
void Syntax::analyze_Return(Tree * tr) {
    IR i;
    this->analyze_Expr(tr->children[0]);
    i.op = Op_return;
    this->irs->add(i);
}
void Syntax::analyze_Continue() {
    IR i;
    i.op = Op_jump_imm;
    this->start->add(this->irs->add(i));
}