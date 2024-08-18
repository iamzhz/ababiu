#include "../include.h"

void Parser::getNextToken() {
    Token tk; 
    if (this->restartMode) {
        this->current = *this->it;
        this->it ++;
        if (this->it == this->backtracks.end()) { // reset restart mode
            if (this->itStack.empty())  {
                this->restartMode = false;
            } else {
                this->over();
            }
        }
        return ;
    }
    tk = this->lx->getNextToken();
    this->current = tk;
    if (this->recordMode) {
        this->backtracks.push_back(tk);
    }
}

void Parser::restart() {
    this->restartMode = true;
    this->it = this->itStack.top();
    this->backtracks.push_back(this->current);
} 

void Parser::record() {
    this->backtracks.push_back(this->current);
    this->recordMode = true;
    this->itStack.push(-- this->backtracks.end());
}

void Parser::unrecord() {
    if (this->itStack.empty()) 
        this->recordMode = false;
}

void Parser::over() {
    this->itStack.pop(); 
    if (this->itStack.empty()) {
        this->restartMode = false;
    } else {
        this->it = itStack.top();
    }
}

void Parser::parserError(Token tk, std::string info) {
    if (!this->recordMode) {
        sayError(tk.line, tk.column, info);
    }
}
void Parser::parserError(std::string info) {
    this->parserError(this->current, info);
}
/*
Token Parser::getNextToken() {
    if (this->backtrackMode) {
        if (!this->tokenStack.empty()) {
            this->current = this->tokenStack.top();
            this->tokenStack.pop();
            return this->current;
        }
        this->disableBacktrack();
    }

    this->current = this->lx->getNextToken();
    this->tokenStack.push(this->current);
    return this->current;
}

Token Parser::getCurrentToken() {
    return this->current;
}

void Parser::enableBacktrack() {
    this->backtrackMode = true;
}

void Parser::disableBacktrack() {
    this->backtrackMode = false;
    this->clearBacktrack();
}

void Parser::clearBacktrack() {
    while (!this->tokenStack.empty()) {
        this->tokenStack.pop();
    }
}*/