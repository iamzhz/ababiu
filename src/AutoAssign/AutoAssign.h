#ifndef _AUTOASSIGN_H_
#define _AUTOASSIGN_H_
#include "../IR/IR.h"
#include <vector>
#include <utility>

class AutoAssign {
    private:
    std::vector<
      std::pair<
        std::vector<int>, Immediate>> data;
    IRs * irs;
    public:
    AutoAssign(IRs * irs);
    void create();
    void add(int pos);
    void set(const Immediate& imm);
    void assign();
};

#endif