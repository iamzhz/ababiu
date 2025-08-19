#include "Syntax.h"
#include "../SayError/SayError.h"
#include "../Token/Token.h"
#ifdef DEBUG
#include <iostream>
#endif

Syntax::Syntax(Tree * tr, IRs * irs, Symbol * symbol) {
    this->tr = tr;
    this->irs = irs;
    this->symbol = symbol;
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

int Syntax::append(const IR & ir) {
    #ifdef DEBUG
    ir.display(this->count);
    ++ this->count;
    #endif
    return this->irs->add(ir);
}

void Syntax::analyze_unit() {
    #ifdef DEBUG
    std::cout << "---------------" << std::endl;
    this->count = 0;
    #endif
    for (auto tr_ : this->tr->children) {
        this->analyze_DefineFunction(tr_);
    }
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
    for (Tree * child : tr->children) {
        this->analyze_Sentence(child);
        this->append({Sign_SentenceEnd});
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
        case treeTypeNode_DefineVariable:
            this->analyze_DefineVariable(head);
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
    if (tr->label != treeTypeNode_FunctionCall) {
        return ;
    }
    this->append({Sign_callParaBegin});   // add mark
    function_name = tr->children[0]->tk.content;
    this->analyze_ExprList(tr->children[1]);
    this->append({Op_call_if, function_name});
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
    this->append({Op_pop_iv, tk.content});
}
void Syntax::analyze_Compare(Tree * tr) {
    IROp op;
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
    if (signToken->matchSign("==")) op = Op_equal;
    else if (signToken->matchSign(">")) op = Op_bigger;
    else if (signToken->matchSign(">=")) op = Op_biggerEqual;
    else if (signToken->matchSign("<")) op = Op_smaller;
    else if (signToken->matchSign("<=")) op = Op_smallerEqual;
    else if (signToken->matchSign("!=")) op = Op_notEqual;
    this->append({op});
}
void Syntax::analyze_Add(Tree * tr) {
    Tree * s;
    IROp op;
    this->analyze_Times(tr->children[0]);
    s = tr->children[1];
    while (s->label != treeTypeNode_Epsilon) {
        // OP
        if (s->children[0]->tk.matchSign("+")) op = Op_add;
        else op = Op_sub; // when s->children[0]->tk.matchSign("-")
        // another Times
        this->analyze_Times(s->children[1]);
        // add
        this->append({op});
        // prepare
        s = s->children[2];
    }
}
void Syntax::analyze_Times(Tree * tr) {
    Tree * s;
    IROp op;
    this->analyze_Power(tr->children[0]);
    s = tr->children[1];
    while (s->label != treeTypeNode_Epsilon) {
        // OP
        if (s->children[0]->tk.matchSign("*")) op = Op_mul;
        else op = Op_div; // when s->children[0]->tk.matchSign("/")
        // another Power
        this->analyze_Power(s->children[1]);
        // add
        this->append({op});
        // prepare
        s = s->children[2];
    }
}

void Syntax::analyze_Power(Tree * tr) {
    this->analyze_Factor(tr->children[0]);
    // if Power' is ε
    if (tr->children[1]->label == treeTypeNode_Epsilon) {
        return ;
    }
    // Compare'
    this->analyze_Factor(tr->children[1]->children[1]);
    this->append({Op_power});
}

void Syntax::analyze_Factor(Tree * tr) {
    Tree * head;
    if (tr->children.size() == 0) return ;
    head = tr->children[0];
    if (head->type == treeType_Token) {
        if (head->tk.type == tokenTypeId) {
            this->append({Op_push_iv, head->tk.content});
        } else {
            Immediate imm;
            switch (head->tk.type) {
                case tokenTypeChar: imm = makeImmediate(TYPE_CHAR, head->tk.content); break;
                case tokenTypeInt: imm = makeImmediate(TYPE_INT, head->tk.content); break;
                case tokenTypeFloat: imm = makeImmediate(TYPE_FLOAT, head->tk.content); break;
                case tokenTypeString: imm = makeImmediate(TYPE_STRING, head->tk.content); break;
                default: break;
            }
            this->append({Op_push_imm, imm});
        }
    } else if (head->label == treeTypeNode_Expr) {
        this->analyze_Expr(head);
    } else if (head->label == treeTypeNode_FunctionCall) {
        this->analyze_FunctionCall(head);
    }// else if ()
}
/*

 */
