#include "Symbol.h"

PointerManager<VarSymbol*> pmVar;
PointerManager<FuncSymbol*> pmFunc;
Symbol sym;

VarType tokenTypeToVarType(tokenType tt) {
    switch (tt) {
        case tokenTypeInt: return VAR_INT;
        case tokenTypeChar: return VAR_CHAR;
        case tokenTypeFloat: return VAR_FLOAT;
        case tokenTypeString: return VAR_STRING;
        case tokenTypeId:
        case tokenTypeKeyword:
        case tokenTypeSign:
        case tokenTypeEof:
        case tokenTypeType:
            return VAR_UNKNOWN;
    }
    return VAR_UNKNOWN; // will not run, just cheat compiler
}

void Symbol::insert_var(std::string name, VarType vt/*, ...*/) {
    struct VarSymbol * vs = (struct VarSymbol*)std::malloc(sizeof(struct VarSymbol));
    pmVar.add(vs);

    vs->name = name;
    vs->type = vt;

    this->vars.insert({name, vs});
}


void Symbol::insert_func(std::string name, VarType return_type/*, ...*/) {
    struct FuncSymbol * fs = (struct FuncSymbol*)std::malloc(sizeof(struct FuncSymbol));
    pmFunc.add(fs);

    fs->name = name;
    fs->return_type = return_type;

    this->funcs.insert({name, fs});
}