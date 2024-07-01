@echo off
g++ main.cc FileManager/FileManager.cc Token/Token.cc Lexer/Lexer.cc SayError/SayError.cc -o main.exe -std=c++11 -DDEBUG