#ifndef _AUTOASSIGN_H_
#define _AUTOASSIGN_H_
#include "../include.h"

class AutoAssign {
    private:
    std::vector<std::vector<IR*>> data;
    public:
    void create();
    void add(IR*);
    void assign(int pos);
};

#endif