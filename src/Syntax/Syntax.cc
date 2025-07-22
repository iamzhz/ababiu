#include "../include.h"

Syntax::Syntax(Tree * tr, IRs * irs) {
    this->tr = tr;
    this->irs = irs;
}

int Syntax::analyze_quicknumber(Token * tk) {
    return 1;
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
    std::string keyword;
    if (head->children[0]->type != treeType_Token
        || head->children[0]->tk.type != tokenTypeKeyword) {
        
        this->analyze_Expr(head);
        return ;
    }
    keyword = head->children[0]->tk.content;
    switch (keyword.length()) {
        case 2:
            if ("if" == keyword) {
                this->analyze_If(head);
                return ;
            }
            if ("do" == keyword) {
                this->analyze_DoWhile(head);
                return ;
            }
            break;
        case 3:
            if ("for" == keyword) {
                this->analyze_For(head);
                return ;
            }
            break;
        case 4:
            if ("else" == keyword) {
                this->analyze_Else(head);
                return ;
            }
            break;
        case 5:
            if ("while" == keyword) {
                this->analyze_While(head);
                return ;
            }
            if ("break" == keyword) {
                this->analyze_Break(head);
                return ;
            }
            break;
        case 6:
            if ("return" == keyword) {
                this->analyze_Return(head);
                return ;
            }
            break;
        case 8:
            if ("continue" == keyword) {
                this->analyze_Continue(head);
                return ;
            }
            break;
    }
    sayError(head->children[0]->tk.line, 
        head->children[0]->tk.column, 
        "Wrong keyword.");
}
void Syntax::analyze_FuntionCall(Tree * tr) {
    std::string function_name;
    IR ir;
    if (tr->label != treeTypeNode_FunctionCall) {
        return ;
    }
    function_name = tr->children[0]->tk.content;
    this->analyze_ExprList(tr->children[1]);
    ir.op = Op_call_if;
    ir.iv0 = makeIdVariable(function_name);
    this->irs->add(ir);
}
void Syntax::analyze_ExprList(Tree * tr) {
    // TODO: only deal the first now!
    this->analyze_Expr(tr->children[0]);
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
    IR i;
    i.op = Op_add;
    i.qn0 = makeQuicknumber("hello");
    this->irs->add(i);
}
void analyze_Times(Tree * tr);
void analyze_Factor(Tree * tr);