#include "Syntax.h"

#define POS_CURRENT_INT (this->irs->pos)
#define POS_CURRENT (Address(POS_CURRENT_INT))

void Syntax::analyze_If(Tree * tr) {
    int jump_pos;
    this->analyze_Expr(tr->children[0]);
    jump_pos = this->append({Op_jumpIfNot_addr});
    this->analyze_Statements(tr->children[1]);

    if (tr->children[2]->label == treeTypeNode_Else) {
        this->analyze_Else(tr->children[2], jump_pos);
    } else {
        this->irs->content[jump_pos].set_addr(POS_CURRENT);
    }
}
void Syntax::analyze_Else(Tree * tr, int if_jump_pos) {
    int jump_pos;
    // for if-statements jump out
    jump_pos = this->append({Op_jump_addr});
    this->analyze_Statements(tr->children[0]);
    this->irs->content[jump_pos].set_addr(POS_CURRENT);
    this->irs->content[if_jump_pos].set_addr(Address(jump_pos + 1));
}
void Syntax::analyze_DoWhile(Tree * tr) {
    this->start->create();
    this->end->create();
    this->start->set(POS_CURRENT);
    this->analyze_Statements(tr->children[0]);
    this->analyze_Expr(tr->children[1]);
    this->start->add(this->append({Op_jumpIf_addr}));
    this->end->set(POS_CURRENT);
    this->start->assign();
    this->end->assign();
}
void Syntax::analyze_For(Tree * tr) {
    this->start->create();
    this->end->create();
    int if_jump_pos;
    this->analyze_Expr(tr->children[0]);
    if_jump_pos = POS_CURRENT_INT;
    this->analyze_Expr(tr->children[1]);
    this->end->add(this->append({Op_jumpIfNot_addr}));
    this->analyze_Statements(tr->children[3]);
    this->start->set(POS_CURRENT);
    this->analyze_Expr(tr->children[2]);
    this->append({Op_jump_addr, Address(if_jump_pos)});
    this->end->set(POS_CURRENT);
    this->start->assign();
    this->end->assign();
}
void Syntax::analyze_While(Tree * tr) {
    this->start->create();
    this->end->create();
    this->start->set(POS_CURRENT);
    this->analyze_Expr(tr->children[0]);
    this->end->add(this->append({Op_jumpIfNot_addr}));
    this->analyze_Statements(tr->children[1]);
    this->start->add(this->append({Op_jump_addr}));
    this->end->set(POS_CURRENT);
    this->start->assign();
    this->end->assign();
}
void Syntax::analyze_Break() {
    this->end->add(this->append({Op_jump_addr}));
}
void Syntax::analyze_Return(Tree * tr) {
    this->analyze_Expr(tr->children[0]);
    this->append({Op_return});
}
void Syntax::analyze_Continue() {
    this->start->add(this->append({Op_jump_addr}));
}