@echo off
g++ main.cc FileManager/FileManager.cc Token/Token.cc Lexer/Lexer.cc Lexer/signToken.cc SayError/SayError.cc -o abandon -std=c++11 -DDEBUG