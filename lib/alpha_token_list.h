#ifndef ALPHA_LIST_H
#define ALPHA_LIST_H

#include "alpha_types.h"

typedef struct alpha_token_t {
    unsigned int numline;
    unsigned int numToken;
    char         *content;
    enum type    tType;
    enum subtype sType;
    struct alpha_token_t *next;
}alpha_token_t;

typedef struct TokenList{
    alpha_token_t *head;
    alpha_token_t *tail;
} TokenList;

TokenList* create_alpha_token_list();
void insert_alpha_token(TokenList *tokenList, int numline, int numToken, char *content, enum type tType, enum subtype sType);
void print_alpha_token_list(TokenList *tokenList, FILE *yyout);

#endif /*ALPHA_LIST_H*/