#include "CmdLineParser.h"

bool CmdLineParser::isOption(char *para) {
    return (para[0] == '-') && (para[1] != '\0');
}

std::string CmdLineParser::deleteDash(char * para) {
    while (*para) {
        if (*para != '-') break;
        para ++;
    }
    return std::string(para);
}

CmdLineParser::CmdLineParser(int argc, char** argv) {
    this->argc = argc;
    this->argv = argv;
}

void CmdLineParser::run() {
    int argc = this->argc;
    char ** argv = this->argv;
    for (int i = 1;  i < argc; ++ i) {
        if (this->isOption(argv[i]) && i != argc-1) {
            this->table.insert({
                this->deleteDash(argv[i]),
                std::string(argv[i+1])
            });
            ++ i;
        }
        this->table.insert({"", std::string(argv[i])});
    }
}