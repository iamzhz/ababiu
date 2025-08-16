#include "Syntax.h"

void Syntax::analyze_DefineVariable(Tree * tr) {
    TypeType type0;
    std::string t = tr->children[0]->tk.content;
    std::string var_name = tr->children[1]->tk.content;

    if (t == "int") type0 = TYPE_INT;
    else if (t == "float") type0 = TYPE_FLOAT;
    else if (t == "char") type0 = TYPE_CHAR;
    else if (t == "string") type0 = TYPE_STRING;

    this->symbol->insert_variable(var_name, type0);

    this->irs->add({Sign_defineVariable_type_iv, Value(type0), Value(var_name)});
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