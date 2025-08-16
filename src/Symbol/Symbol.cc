#include "Symbol.h"
#include "../SayError/SayError.h"
#include <stdexcept>
#include <string>

int Symbol::assign_memory(int addr, int rest, int size, int & used) {
    int frame_offset;
    used = size;
    frame_offset = addr + (rest - size);
    if (size == 2 || size == 4 || size == 8) {
        int extra = frame_offset % size;
        if (extra != 0) {
            frame_offset -= extra;
            used += extra;
        }
    }
    return frame_offset;
}

void Symbol::insert_variable(std::string name, TypeType var_type) {
    SymbolValue sv;
    int size;
    sv.isVariable = true;
    sv.type = var_type;
    switch (var_type) {
        case TYPE_CHAR: size = CHAR_SIZE; break;
        case TYPE_INT: size = INT_SIZE; break;
        default: break; 
        // TODO
    }
    /* find suitable memory address */
    auto it = this->memory_unused.begin();
    for (; it != this->memory_unused.end();  ++ it) {
        if (it->second >= size) {
            int used;
            sv.frame_offset = this->assign_memory(it->first, it->second, size, used);
            it->second -= used;
            if (it->second == 0) {
                this->memory_unused.erase(it);
            }
            break;
        }
    }
    // if cannot find suitable memory to stay
    if (it == this->memory_unused.end()) {
        if (size == 8) {
            sv.frame_offset = this->i;
        } else {
            int used;
            sv.frame_offset = this->assign_memory(this->i, 8, size, used);
            this->memory_unused.push_back({this->i, (8-used)});
        }
        this->i -= 8;
    }
    //
    sv.size = size;
    this->table.insert({name, sv});
}

SymbolValue Symbol::get_variable(std::string name) {
    SymbolValue sv;
    auto f = this->table.find(name);
    if (f == this->table.end()) {
        sv.isExist = false;
        return sv;
    }
    sv = f->second;
    return sv;
}
std::string Symbol::get_variable_mem(Value val) {
    if (!val.isVariable()) {
        std::runtime_error("Symbol::get_variable_mem(Value val)");
    }
    return this->get_variable_mem(val.getIdVariable().content);
}

std::string Symbol::get_variable_mem(std::string name) {
    SymbolValue sv = this->get_variable(name);
    std::string ret;
    if (!sv.isExist) {
        sayError("`" + name + "` does not exist.\n");
    }
    if (!sv.isVariable) {
        sayError("`" + name + "` is a function.\n");
    }
    switch (sv.size) {
        case 1: ret = "BYTE "; break;
        case 2: ret = "WORD "; break;
        case 4: ret = "DWORD "; break;
        case 8: ret = "QWORD "; break;
    }
    if (sv.frame_offset > 0) {
        ret += "[rbp+" + std::to_string(sv.frame_offset) + "]";
    } else if (sv.frame_offset < 0) {
        ret += "[rbp" + std::to_string(sv.frame_offset) + "]";
    } else if (sv.frame_offset == 0) {
        ret += "[rbp]";
    }
    return ret;
}