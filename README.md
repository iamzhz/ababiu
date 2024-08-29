# Abandon
It is a program for a programming language named `Abandon`.
> I believe all Chinese English learners can spell it. So I named it `Abandon`, but that doesn’t mean I intend to abandon the project.  

This project is WIP.
You can see more about it [here](https://iamzhz.github.io/t/).  It was written by Chinese.
## Compile this project
If you have `makefile` in your computer, you can run:
``` bash
make
```
or, you can run:
``` bash
g++ src/main.cc src/CmdLineParser/CmdLineParser.cc src/FileManager/FileManager.cc src/Lexer/Lexer.cc src/Lexer/signToken.cc src/Parser/Parser.cc src/Parser/function.cc src/Parser/if_else.cc src/Parser/loop.cc src/Parser/utils.cc src/PointerManager/PointerManager.cc src/SayError/SayError.cc src/Token/Token.cc src/Tree/Tree.cc src/debug/debug.cc -o abandon -std=c++11 -g -finput-charset=UTF-8 -fexec-charset=GBK
```

## Run this project
``` bash
./abandon your_code.abn
```
There is a test file `./hello.abn`. You can try it.  

## File
`src/` is the source code.  
`doc/` is the document.
