#include "FileManager.h"
#include "../debug/debug.h"

bool FileManager::setInputFile(std::string fileName) {
    this->inputFile.open(fileName);
    if (this->inputFile.is_open()) {
        this->isEof = false;
        return true;
    }
    return false;
}


bool FileManager::setOutputFile(std::string fileName) {
    this->outputFile.open(fileName);
    return this->outputFile.is_open();
}

void FileManager::outputToFile(std::string text) {
    this->outputFile << text;
}


void FileManager::closeFile() {
    this->inputFile.close();
    this->outputFile.close();
}


char* FileManager::getBuffer() {
    if (this->isBufferA) return this->bufferA;
    return this->bufferB;
}


void FileManager::readToBuffer() {
    char* buffer = this->getBuffer();
    int& bufferLength = this->bufferLengths[this->isBufferA]; // choose right var for length

    if (this->inputFile.eof()) {
        this->isEof = true;
        return ;
    }

    this->inputFile.read(buffer, READFILE_BUFFER_SIZE - 1);
    bufferLength = this->inputFile.gcount();
    buffer[bufferLength] = '\0';
}


char FileManager::current() {
    char* buffer = this->getBuffer();
    return buffer[this->readPoint];
}


bool FileManager::next() {
    int& bufferLength = this->bufferLengths[this->isBufferA];
    this->readPoint ++;
    if (this->readPoint >= bufferLength) { // ready to change buffer
        this->isBufferA = !this->isBufferA; // true to false, false to true
        if (this->notToReread) this->notToReread = false;
        else this->readToBuffer();
        this->readPoint = 0;
        if (this->isEof) return false;
    }
    if (this->current() == '\n') {
        this->curLine ++;
        this->curColumn = 0;
    } else {
        this->curColumn ++;
    }
    return true;
}


bool FileManager::back() {
    this->readPoint --;
    if (this->readPoint < 0) {
        this->isBufferA = this->isBufferA == false;
        if (this->bufferLengths[this->isBufferA] == 0) return false;
        this->readPoint = this->bufferLengths[this->isBufferA] - 1;
        this->notToReread = true;
    }
    this->curColumn --; // backChar always not jump to previous line
    return true;
}


bool FileManager::skipToNextLine() {
    while (this->next()) {
        if (this->current() == '\n') {
            return this->next();
        }
    }
    return false;
}

FileManager::~FileManager() {
    this->inputFile.close();
    INFO("[file] Input file closed");
}