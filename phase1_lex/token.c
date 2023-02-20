#include <stdlib.h>
#include "tokens.h"

void insert_token(alpha_token_t *tokenList, int numline, int numToken, char *content, enum type tType, enum subtype sType){
    alpha_token_t *tail = tokenList->tail;
    alpha_token_t *head = tokenList->head;
    
    if(tail){
        tail->next=malloc(sizeof(alpha_token_t));
        tail->next->numline=numline;
        tail->next->numToken=numToken;
        tail->next->tType=tType;
        tail->next->sType=sType;
        tail->next->content=malloc(sizeof(char)*strlen(content) + 1);
        memcpy(tail->next->content, content, strlen(content) + 1);
        tail=tail->next;
        tail->next=NULL;
    }
    else{
        head=malloc(sizeof(alpha_token_t));
        head->numline=numline;
        head->numToken=numToken;
        head->tType=tType;
        head->sType=sType;
        head->content=malloc(sizeof(char)*strlen(content) + 1);
        memcpy(head->content, content, strlen(content) + 1);
        tail->next=NULL;
        head=tail;
    }
}