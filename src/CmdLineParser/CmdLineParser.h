#ifndef _ABANDON_CMDLINEPARSER_H_
#define _ABANDON_CMDLINEPARSER_H_

#include "../include.h"

class CmdLineParser {
    int argc;
    char** argv;

    bool isOption(char *para);
    bool option(std::string first, std::string second); // return true means used `second`
    std::string deleteDash(char *para);
    public:

    std::vector<std::string> inputFiles;
    std::string outputFile;
    CmdLineParser(int argc, char** argv);
    void setArgs(int argc, char** argv);
    void run();

    #ifdef DEBUG
    void display();
    #endif
};

#endif