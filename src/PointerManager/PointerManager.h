#ifndef _POINTERMANAGER_H_
#define _POINTERMANAGER_H_
#include "../include.h"
class Tree;
template <class T>
class PointerManager {
    private:
        std::vector<T> ptrs;
    public:
        void add(T ptr);
        void free();
        ~PointerManager();
        #ifdef DEBUG
        void display();
        #endif
};

#endif