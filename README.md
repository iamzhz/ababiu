# Ababiu
It is a program for a programming language named `Ababiu`.

This project is WIP.
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
It will generate two files named `ababiu` and `ababiu_ir`.  

## Run this project
``` bash
./ababiu your_code.abb
```
Though `ababiu_ir` you can get the IR of your code.  
There is an AI-made interpreter named `run_ir.py`(Python).  
So now, you can do this:
``` bash
./ababiu_ir you_code.abb | python run_ir.py
```  
to run your Ababiu code!  
There is a test file `./hello.abb`. You can try it.  

(Compiler is continuing writing!)

## File
`src/` is the source code.  
`doc/` is the document.
