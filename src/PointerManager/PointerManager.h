#ifndef _ABANDON_POINTERMANAGER_H_
#define _ABANDON_POINTERMANAGER_H_
#include "../include.h"
struct Tree;
template <class T>
class PointerManager {
    private:
        std::vector<T> ptrs;
    public:
        void add(T ptr) {
            this->ptrs.push_back(ptr);
        }
        void free() {
            for (auto ptr : this->ptrs) {
                if (ptr != nullptr) {
                delete ptr;
                INFO("[free] " << ptr);
                ptr = nullptr;
                }
            }
        }
        ~PointerManager() {
            this->free();
        }

        #ifdef DEBUG
        void print() {
            for (auto ptr : this->ptrs) {
                std::cout << ptr << std::endl;
            }
        }
        #endif
};

#endif