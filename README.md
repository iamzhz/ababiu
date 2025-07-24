# Abandon
It is a program for a programming language named `Abandon`.
> I believe all China's English learners can spell it. So I named it `Abandon`, but that doesn’t mean I intend to abandon the project.

This project is WIP.
You can see more about it [here](https://iamzhz.github.io/t/).  It was written by Chinese.
## Compile this project
``` bash
make
```
It will generate two files named `abandon` and `abandon_ir`.  

## Run this project
``` bash
./abandon your_code.abn
```
Though `abandon_ir` you can get the IR of your code.  
There is an AI-made interpreter named `run_ir.py`(Python).  
So now, you can do this:
``` bash
./abandon_ir you_code.abn | python run_ir.py
```  
to run your Abandon code!  
There is a test file `./hello.abn`. You can try it.  

(Compiler is continuing writing!)

## File
`src/` is the source code.  
`doc/` is the document.
