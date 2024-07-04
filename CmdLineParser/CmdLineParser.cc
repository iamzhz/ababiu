#include "../include.h"
#define v (argv[i])
#define v2 (argv[i+1])

bool CmdLineParser::isOption(char *para) {
    return (para[0] == '-');
}


std::string CmdLineParser::deleteDash(char *para) {
    std::string ret(para);
    std::string::iterator it;
    for (it = ret.begin(); it != ret.end();  it ++) {
        if (*it != '-') break;
        ret.erase(it);
    }
    return ret;
}


bool CmdLineParser::option(std::string first, std::string second) {
    std::string para;
    char opt = first[0];
    switch (opt) {
        case 'o': // output file
            if (first[1] == '\0') {
                this->outputFile = second;
                return true;
            }else {
                sayError(std::string("`-o` does not be allowed to do like this "));
            }
            break;
        default:
            sayError(std::string("Undefined option "));
    }
    return false;
}

CmdLineParser::CmdLineParser(int argc, char** argv) {
    this->setArgs(argc, argv);
}


void CmdLineParser::setArgs(int argc, char** argv) {
    this->argc = argc;
    this->argv = argv;
}


void CmdLineParser::run() {
    for (int i = 1;  i < argc;  i ++) {
        if (this->isOption(v)) {
            if (this->option(this->deleteDash(v), std::string(v2))) i ++;
        }
        this->inputFiles.push_back(v);
    }
}


#ifdef DEBUG
void CmdLineParser::print() {
    std::cout << "Input File: ";
    for (int i = 0;  i < this->inputFiles.size();  i ++) {
        std::cout << this->inputFiles[i] << " ";
    }
    std::cout << std::endl << "Output File: " << this->outputFile << std::endl;
}
#endif

#undef v
#undef v2