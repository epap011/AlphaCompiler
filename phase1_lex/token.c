#include <stdio.h>
#include <stdlib.h>    
#include <string.h>
#include "tokens.h"

/*List insertion function*/
void insert_token(TokenList *tokenList, int numline, int numToken, char *content, enum type tType, enum subtype sType){

    if(tokenList->head){
        tokenList->tail->next=malloc(sizeof(alpha_token_t));
        tokenList->tail->next->numline=numline;
        tokenList->tail->next->numToken=numToken;
        tokenList->tail->next->tType=tType;
        tokenList->tail->next->sType=sType;
        tokenList->tail->next->content=malloc(sizeof(char)*strlen(content) + 1);
        memcpy(tokenList->tail->next->content, content, strlen(content) + 1);
        tokenList->tail=tokenList->tail->next;
        tokenList->tail->next=NULL;
    }
    else{
        tokenList->head=malloc(sizeof(alpha_token_t));
        tokenList->head->numline=numline;
        tokenList->head->numToken=numToken;
        tokenList->head->tType=tType;
        tokenList->head->sType=sType;
        tokenList->head->content=malloc(sizeof(char)*strlen(content) + 1);
        memcpy(tokenList->head->content, content, strlen(content) + 1);
        tokenList->head->next=NULL;
        tokenList->tail=tokenList->head;
    }
}

/*Token type to string*/
const char* get_type(enum type s) {
    switch (s) {
        case STRING: return "STRING";
        case NUMBER: return "NUMBER";
        case IDENT: return "IDENT";
        case OPERATOR: return "OPERATOR";
        case KEYWORD: return "KEYWORD";
        case PUNCTUATION: return "PUNCTUATION";
        case COMMENT: return "COMMENT";
        case UNDEFCHR: return "UNDEFCHR";
        default: return "INVALID";
    }
}
const char* get_subtype(enum subtype s) {
    switch (s) {
        case ASSIGN: return "ASSIGN";
        case PLUS: return "PLUS";
        case MINUS: return "MINUS";
        case MUL: return "MUL";
        case SLASH: return "SLASH";
        case MOD: return "MOD";
        case EQ: return "EQ";
        case NEQ: return "NEQ";
        case INC: return "INC";
        case DEC: return "DEC";
        case GT: return "GT";
        case LT: return "LT";
        case GTE: return "GTE";
        case LTE: return "LTE";
        case IF: return "IF";
        case ELSE: return "ELSE";
        case WHILE: return "WHILE";
        case FOR: return "FOR";
        case FUNCTION: return "FUNCTION";
        case RETURN: return "RETURN";
        case BREAK: return "BREAK";
        case CONTINUE: return "CONTINUE";
        case AND: return "AND";
        case NOT: return "NOT";
        case OR: return "OR";
        case LOCAL: return "LOCAL";
        case TRUE: return "TRUE";
        case FALSE: return "FALSE";
        case NIL: return "NIL";
        case LBRACE: return "LBRACE";
        case RBRACE: return "RBRACE";
        case LCBRACE: return "LCBRACE";
        case RCBRACE: return "RCBRACE";
        case LPAR: return "LPAR";
        case RPAR: return "RPAR";
        case SEMI: return "SEMI";
        case COMMA: return "COMMA";
        case COLON: return "COLON";
        case DCOLON: return "DCOLON";
        case DOT: return "DOT";
        case DDOT: return "DDOT";
        case INTCONST: return "INTCONST";
        case REALCONST: return "REALCONST";
        case LINECOMM: return "LINECOMM";
        case BLOCKCOMM: return "BLOCKCOMM";
        case NOSTYPE: return "NOSTYPE";
        default: return "INVALID";
    }
}   