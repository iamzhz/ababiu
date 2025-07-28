#include "Syntax.h"
#include "../SayError/SayError.h"
#include "../Token/Token.h"

Syntax::Syntax(Tree * tr, IRs * irs) {
    this->tr = tr;
    this->irs = irs;
    this->start = nullptr;
    this->end = nullptr;
}
Syntax::~Syntax() {
    if (this->start != nullptr)
        delete this->start;
    if (this->end != nullptr)
        delete this->end;
}

void Syntax::init() {
    this->start = new AutoAssign(this->irs);
    this->end = new AutoAssign(this->irs);
}

void Syntax::analyze_unit() {
    this->analyze_Statements(this->tr);
}
Token Syntax::getInner(Tree * tr) {
    Tree * P = tr;
    for (;;) {
        if (P->type == treeType_Token) {
            return std::move(P->tk);
        }
        P = P->children[0];
    }
}
void Syntax::analyze_Statements(Tree * tr) {
    Tree * head = tr->children[0];
    if (head->label == treeTypeNode_Sentences) {
        this->analyze_Sentences(head);
    } else {
        this->analyze_Sentence(head);
    }
}
void Syntax::analyze_Sentences(Tree * tr) {
    Tree * s = tr;
    while (s->children.size() == 2) {
        this->analyze_Sentence(s->children[0]);
        s = s->children[1];
    }
}
void Syntax::analyze_Sentence(Tree * tr) {
    Tree * head = tr->children[0];
    switch (head->label) {
        case treeTypeNode_If:
            this->analyze_If(head);
            return ;
        case treeTypeNode_While:
            this->analyze_While(head);
            return ;
        case treeTypeNode_DoWhile:
            this->analyze_DoWhile(head);
            return ;
        case treeTypeNode_For:
            this->analyze_For(head);
            return ;
        case treeTypeNode_Break:
            this->analyze_Break();
            return ;
        case treeTypeNode_Continue:
            this->analyze_Continue();
            return ;
        case treeTypeNode_Return:
            this->analyze_Return(head);
            return ;
        case treeTypeNode_Expr:
            this->analyze_Expr(head);
            return ;
        default:
            return ; // if my code works well, it'll never run this
    }
    sayError(head->children[0]->tk.line, 
        head->children[0]->tk.column, 
        "Wrong keyword.");
}
void Syntax::analyze_FunctionCall(Tree * tr) {
    std::string function_name;
    IR ir;
    if (tr->label != treeTypeNode_FunctionCall) {
        return ;
    }
    function_name = tr->children[0]->tk.content;
    this->analyze_ExprList(tr->children[1]);
    ir.op = Sign_callParaBegin;
    this->irs->add(ir);   // add mark
    ir.op = Op_call_if;
    ir.iv0 = makeIdVariable(function_name);
    this->irs->add(ir);
}
void Syntax::analyze_ExprList(Tree * tr) {
    Tree * s = tr;
    while (s->children.size() == 2) {
        this->analyze_Expr(s->children[0]);
        s = s->children[1];
    }
}
void Syntax::analyze_Expr(Tree * tr) {
    this->analyze_Assign(tr->children[0]);
}
void Syntax::analyze_Assign(Tree * tr) {
    IR i;
    Token tk; // to store variable name for assign (left value)
    //tr = tr->children[0];// TEMP MEASURE
    Tree * compare = tr->children[0];
    Tree * assign_ = tr->children[1];
    // if it is not an assign
    if (assign_->label == treeTypeNode_Epsilon) {
        this->analyze_Compare(compare);
        return ;
    }
    // or tr->children[0] inner should be a `token id`
    tk = this->getInner(compare);
    if (tk.type != tokenTypeId) {
        sayError(tk.line, tk.column, "Should be an Id");
    }
    // assign_ -> children[0] is token `=`
    this->analyze_Compare(assign_->children[1]);
    i.op = Op_pop_iv;
    i.iv0 = makeIdVariable(tk.content);
    this->irs->add(i);
}
void Syntax::analyze_Compare(Tree * tr) {
    IR i;
    Tree * compare_; // Compare'
    Token * signToken;
    // if Compare' is ε
    if (tr->children[1]->label == treeTypeNode_Epsilon) {
        this->analyze_Add(tr->children[0]);
        return ;
    }
    // Compare'
    compare_ = tr->children[1];
    signToken = &(compare_->children[0]->tk);
    this->analyze_Add(tr->children[0]);
    this->analyze_Add(compare_->children[1]);
    if (signToken->matchSign("==")) i.op = Op_equal;
    else if (signToken->matchSign(">")) i.op = Op_bigger;
    else if (signToken->matchSign(">=")) i.op = Op_biggerEqual;
    else if (signToken->matchSign("<")) i.op = Op_smaller;
    else if (signToken->matchSign("<=")) i.op = Op_smallerEqual;
    else if (signToken->matchSign("!=")) i.op = Op_notEqual;
    this->irs->add(i);
}
void Syntax::analyze_Add(Tree * tr) {
    Tree * s;
    IR i;
    this->analyze_Times(tr->children[0]);
    s = tr->children[1];
    while (s->label != treeTypeNode_Epsilon) {
        // OP
        if (s->children[0]->tk.matchSign("+")) i.op = Op_add;
        else i.op = Op_sub; // when s->children[0]->tk.matchSign("-")
        // another Times
        this->analyze_Times(s->children[1]);
        // add
        this->irs->add(i);
        // prepare
        s = s->children[2];
    }
}
void Syntax::analyze_Times(Tree * tr) {
    Tree * s;
    IR i;
    this->analyze_Power(tr->children[0]);
    s = tr->children[1];
    while (s->label != treeTypeNode_Epsilon) {
        // OP
        if (s->children[0]->tk.matchSign("*")) i.op = Op_mul;
        else i.op = Op_div; // when s->children[0]->tk.matchSign("/")
        // another Power
        this->analyze_Power(s->children[1]);
        // add
        this->irs->add(i);
        // prepare
        s = s->children[2];
    }
}

void Syntax::analyze_Power(Tree * tr) {
    IR i;
    this->analyze_Factor(tr->children[0]);
    // if Power' is ε
    if (tr->children[1]->label == treeTypeNode_Epsilon) {
        return ;
    }
    // Compare'
    this->analyze_Factor(tr->children[1]->children[1]);
    i.op = Op_power;
    this->irs->add(i);
}

void Syntax::analyze_Factor(Tree * tr) {
    IR i;
    Tree * head;
    if (tr->children.size() == 0) return ;
    head = tr->children[0];
    if (head->type == treeType_Token) {
        if (head->tk.type == tokenTypeId) {
            i.op = Op_push_iv;
            i.iv0 = makeIdVariable(head->tk.content);
        } else {
            i.op = Op_push_qn;
            i.qn0 = makeQuicknumber(head->tk.content);
        }
        this->irs->add(i);
    } else if (head->label == treeTypeNode_Expr) {
        this->analyze_Expr(head);
    } else if (head->label == treeTypeNode_FunctionCall) {
        this->analyze_FunctionCall(head);
    }// else if ()
}
/*

 */
