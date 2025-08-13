#ifndef _CMDLINEPARSER_H_
#define _CMDLINEPARSER_H_

#include <string>
#include <vector>
#include <unordered_map>
#include "../SayError/SayError.h"

class CmdLineParser {
    int argc;
    char** argv;

    bool isOption(char *para);
    bool option(std::string first, std::string second); // return true means used `second`
    std::string deleteDash(char *para);
    public:
    // "" -> input file
    // "o" -> output file
    std::unordered_map<std::string, std::string> table;
    CmdLineParser(int argc, char** argv);
    void run();
};

#endif