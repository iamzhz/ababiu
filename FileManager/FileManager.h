#include "../include.h"

#ifndef _ABANDON_FILEMANAGER_H_
#define _ABANDON_FILEMANAGER_H_

#define READFILE_BUFFER_SIZE 51
class FileManager {
    private:
    std::ifstream inputFile;
    std::ifstream outputFile;
    char bufferA[READFILE_BUFFER_SIZE];
    char bufferB[READFILE_BUFFER_SIZE];
    bool isBufferA = true; // true means bufferA, or bufferB
    int readPoint = READFILE_BUFFER_SIZE;
    int bufferLengths[2] = {0}; // [0] for bufferB, [1] for bufferA
    bool notToReread = false;
    public:
    
    bool isEof = false;

    bool setInputFile(std::string fileName); // return true is a success
    bool setOutputFile(std::string fileName); // return true is a success
    void closeFile();
    char* getBuffer();
    void readToBuffer();
    char current();
    void nextChar();
    bool backChar(); // return true is a success
};

#endif