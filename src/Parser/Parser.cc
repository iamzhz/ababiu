#include "../include.h"

bool Parser::parser(AST* ast) {
    bool tell = false;
    AST* child;
    if (ast->match(tokenTypeInt)) {
        ast->label = ast_value;
        child = ast->addChild(ast_value_tail, this->lx);
        if (parser_value_tail(child)) {
            return true;
        }
    }
    return false;
}

bool Parser::parser_value_tail(AST* ast) {
    if (ast->match(tokenTypeSign)) {
        return parser(ast);
    }
    return true;
}