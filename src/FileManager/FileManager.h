#ifndef _FILEMANAGER_H_
#define _FILEMANAGER_H_

#include <fstream>
#include <string>

#define READFILE_BUFFER_SIZE 51
class FileManager {
    private:
    std::ifstream inputFile;
    std::ofstream outputFile;
    char bufferA[READFILE_BUFFER_SIZE];
    char bufferB[READFILE_BUFFER_SIZE];
    bool isBufferA = true; // true means bufferA, or bufferB
    int readPoint = READFILE_BUFFER_SIZE;
    int bufferLengths[2] = {0}; // [0] for bufferB, [1] for bufferA
    bool notToReread = false;

    char* getBuffer();
    void readToBuffer();

    
    public:
    
    bool isEof = false;
    int curLine = 1;
    int curColumn = 0;

    bool setInputFile(std::string fileName); // return true is a success
    bool setOutputFile(std::string fileName); // return true is a success
    void outputToFile(std::string text);
    void closeFile();
    char current();
    bool next(); // return false means eof
    bool back(); // return true is a success
    bool skipToNextLine(); // return false is EOF

    ~FileManager();
};

#endif