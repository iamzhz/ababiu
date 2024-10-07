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
void IRs::setFuncName(std::string name) {
    this->name = name;
}

#ifdef DEBUG
void IRs::display() {
    if (this->type == IRsType_Main) {
        for (auto func : this->funcs) {
            func.display();
        }
        return ;
    }
    // display content of one function
    std::cout << "[" << this->name << "]\n";
    for (auto ir : this->content) {
        std::cout << IROpToText(ir.op) << " " 
            << OpNumberToText(ir.n1) << " " 
            << OpNumberToText(ir.n2) << " " 
            << OpNumberToText(ir.n3) << "\n";
    }
    return ;
}

std::string IROpToText(IROp op) {
    switch (op) {
        case Op_Add: return "Add";
        case Op_Sub: return "Sub";
        case Op_Mul: return "Mul";
        case Op_Div: return "Div";
        case Op_Assign: return "Assign";
    }
    return "Unknown";
}

std::string OpNumberToText(OpNumber & n) {
    switch (n.type) {
        case OpNumberType_int:
            return std::to_string(*(int*)(n.ptr));
        case OpNumberType_float:
            return std::to_string(*(float*)(n.ptr));
        case OpNumberType_string:
            return *(std::string*)(n.ptr);
        case OpNumberType_isGetAdress:
            return (*(IRisGetAdress*)(n.ptr))   ? "&" : "";
        case OpNumberType_variable:
            return *(std::string*)(n.ptr);
        case OpNumberType_reg:
            return "Reg" + std::to_string(*(int*)(n.ptr));
    }
    return "Unknown";
}

#endif
