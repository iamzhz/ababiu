# Ababiu
It is a program for a programming language named `Ababiu`.  
**(This project is WIP.)**  
  
To compile this project, you should have `make` or `cmake`.  
To compile your Ababiu code, you should have `nasm` and `gcc`.  
## Build this project
If you use `makefile`:
``` bash
make
```
If you use `cmake`:
```bash
mkdir build
cd build
cmake ..
cmake --build .
```
It will generate a executable file named `ababiu`.

## Prepare before use
You should run
```bash
gcc -c libababiu/libababiu.c -o libababiu.o
```
to prepare the library of Abandon.

## Compile your code
(There is a test file `test.abb`, you can try it)  
``` bash
./ababiu your_code.abb -o assembly.asm  # compile to assembly code
nasm -f elf64 assembly.asm -o a.o
gcc a.o libababiu.o -o output

```
Then you can run it by
```bash
./output
```
## File
`src/` is the source code.  
`libababiu/` is the library of Ababiu.
