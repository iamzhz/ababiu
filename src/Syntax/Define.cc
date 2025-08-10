#include "Syntax.h"

void Syntax::analyze_DefineVariable(Tree * tr) {
    IR ir;
    ir.op = Sign_defineVariable_type_iv;
    std::string t = tr->children[0]->tk.content;
    std::string var_name = tr->children[1]->tk.content;

    if (t == "int") ir.type0 = TYPE_INT;
    else if (t == "float") ir.type0 = TYPE_FLOAT;
    else if (t == "char") ir.type0 = TYPE_CHAR;
    else if (t == "string") ir.type0 = TYPE_STRING;

    ir.iv0 = makeIdVariable(var_name);

    this->symbol->insert_variable(var_name, ir.type0);

    this->irs->add(ir);
}

void Syntax::analyze_DefineVariableList(Tree * tr) {
    for (Tree * DefineVariable : tr->children) {
        this->analyze_DefineVariable(DefineVariable);
    }
}

void Syntax::analyze_DefineFunction(Tree * tr) {
    // TODO: it's a test version now
    this->analyze_DefineVariableList(tr->children[2]);
    this->analyze_Statements(tr->children[3]);
}