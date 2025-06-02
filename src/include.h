#ifndef _INCLUDE_H_
#define _INCLUDE_H_

#define DEBUG
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <utility>
#include <unordered_map>
#include <functional>
#include "./SayError/SayError.h"
#include "./FileManager/FileManager.h"
#include "./debug/debug.h"
#include "./Token/Token.h"
#include "./Lexer/Lexer.h"
#include "./CmdLineParser/CmdLineParser.h"
#include "./PointerManager/PointerManager.h"
#include "./Tree/Tree.h"
#include "./Parser/Parser.h"
#include "./SymbolTable/VariableMap.h"
#include "./SymbolTable/FunctionMap.h"
#include "./SymbolTable/SymbolTable.h"
#include "./IR/IR.h"

// pay attention to the order!! (to myself)

#ifdef TEST
#define test_main main
#else
#define program_main main
#endif

#endif