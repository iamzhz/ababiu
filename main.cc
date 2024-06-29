#include "include.h"
int main() {
    FileManager f;
    f.setInputFile("hello.txt");
    std::cout << f.isEof;
    f.nextChar();
    while (!f.isEof) {
        std::cout << f.current();
        f.nextChar();
    }
    f.backChar();
    ASSERT(f.current());
    f.closeFile();
    return 0;
}