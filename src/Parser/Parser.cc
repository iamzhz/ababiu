#include "../include.h"
#define CHILD(label) ast->addChild((label), this->lx)


bool Parser::parser(AST* ast) {
    ASSERT("value");
    ast->label = ast_value;
    if (this->parser_term( CHILD(ast_term) ))
    if (this->parser_add_op_tail( CHILD(ast_add_op_tail) ))
        return true;
    return false;
}

bool Parser::parser_term(AST* ast) {
    ASSERT("term");
    ast->label = ast_term;
    if (this->parser_factor( CHILD(ast_factor) ))
        if (this->parser_mul_op_tail( CHILD(ast_mul_op_tail) ))
            return true;
    return false;
}
bool Parser::parser_factor(AST* ast) {
    bool tell;
    ASSERT("fatcor");
    ast->label = ast_factor;
    if (ast->isMatch(tokenTypeInt, tell)) {
        if (tell) return true;

        ast->match("(");
        if (this->parser( CHILD(ast_value) ))
        ast->match(")"); 
        return true;
    }
    return false;
}
bool Parser::parser_add_op_tail(AST* ast) {
    bool tell;
    ASSERT("add");
    ast->label = ast_add_op_tail;
    do {
        if (ast->isMatch("+", tell));
        if (ast->isMatch("-", tell));
        if (tell) break;
        if (ast->lx->file->isEof) ;
        return true;
    } while (0);
    if (this->parser_term( CHILD(ast_term) ))
    this->parser_add_op_tail( CHILD(ast_add_op_tail) );
    return true; // ε production
}


bool Parser::parser_mul_op_tail(AST* ast) {
    bool tell;
    ASSERT("mul");
    ast->label = ast_mul_op_tail;
    do {
        if (ast->isMatch("*", tell));
        if (ast->isMatch("/", tell));
        if (tell) break;
        if (ast->lx->file->isEof) ;
        return true;
    } while (0);
    if (this->parser_factor( CHILD(ast_factor) ))
    this->parser_mul_op_tail( CHILD(ast_mul_op_tail) );
    return true; // ε production
}
