#include "../include.h"

void Parser::getNextToken() {
    Token tk; 
    if (this->restartMode) {
        this->current = *this->it;
        this->it ++;
        if (this->it == this->backtracks.end()) { // reset restart mode
            this->restartMode = false;
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
    this->it = this->backtracks.begin();
    this->backtracks.push_back(this->current);
} 

void Parser::record() {
    this->backtracks.push_back(this->current);
    this->recordMode = true;
}

void Parser::unrecord() {
    this->recordMode = false;
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