# Abandon
It is a program for a programming language named `Abandon`.
> I believe all Chinese English learners can spell it. So I named it `Abandon`, but that doesn’t mean I intend to abandon the project.

## Compile this project
If you have `makefile` in your computer, you can run:
``` bash
make
```
or, you can run:
``` bash
g++ main.cc FileManager/FileManager.cc Token/Token.cc Lexer/Lexer.cc Lexer/signToken.cc SayError/SayError.cc -o abandon -std=c++11 -DDEBUG
```
`-DDEBUG` means compile in debug mode (just in this project).  
Since the project is under development, it is recommended to keep the -DDEBUG flag for ease of debugging.