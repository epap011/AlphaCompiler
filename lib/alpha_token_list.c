#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "alpha_token_list.h"
#include "alpha_types.h"
#include "utilities.h"
#include "alpha_types.h"

TokenList* create_alpha_token_list(){
    TokenList *tokenList=malloc(sizeof(TokenList));
    tokenList->head=NULL;
    tokenList->tail=NULL;
    return tokenList;
}

void insert_alpha_token(TokenList *tokenList, int numline, int numToken, char *content, enum type tType, enum subtype sType){

    if(tokenList->head){
        tokenList->tail->next=malloc(sizeof(alpha_token_t));
        tokenList->tail->next->numline=numline;
        tokenList->tail->next->numToken=numToken;
        tokenList->tail->next->tType=tType;
        tokenList->tail->next->sType=sType;
        if(content){
            tokenList->tail->next->content=malloc(sizeof(char)*strlen(content) + 1);
            memcpy(tokenList->tail->next->content, content, strlen(content) + 1);
        }
        else
            tokenList->tail->next->content=NULL;
        tokenList->tail=tokenList->tail->next;
        tokenList->tail->next=NULL;
    }
    else{
        tokenList->head=malloc(sizeof(alpha_token_t));
        tokenList->head->numline=numline;
        tokenList->head->numToken=numToken;
        tokenList->head->tType=tType;
        tokenList->head->sType=sType;
        if(content)
        {
            tokenList->head->content=malloc(sizeof(char)*strlen(content) + 1);
            memcpy(tokenList->head->content, content, strlen(content) + 1);
        }
        else
            tokenList->head->content=NULL;
        tokenList->head->next=NULL;
        tokenList->tail=tokenList->head;
    }
}

void print_alpha_token_list(TokenList *tokenList, FILE *yyout){

    alpha_token_t *iterator=tokenList->head;
    while(iterator){

        if(iterator->tType == UNDEFCHR)
            fprintf(yyout, "%d:\tUndefined character\t\"%s\"\n",iterator->numline, FORMAT_NEWLINES(iterator->content));
        else if(iterator->tType == COMMENT)
            fprintf(yyout, "%d:\t#%d\t\"%s\"\t%s\t%s\t\"%s\"\t<-%s\n",iterator->numline, iterator->numToken, "", str_type(iterator->tType), str_subtype(iterator->sType), "", "enumerated");   
        else if(iterator->sType == NOSTYPE){
            fprintf(yyout, "%d:\t#%d\t\"%s\"\t%s\t\"%s\"\t<-%s\n",iterator->numline, iterator->numToken, FORMAT_NEWLINES(iterator->content), str_type(iterator->tType), FORMAT_NEWLINES(iterator->content), "char*");    
        }
        else{
            if(iterator->sType == INTCONST)
                fprintf(yyout, "%d:\t#%d\t\"%s\"\t%s\t%s\t\"%s\"\t<-%s\n",iterator->numline, iterator->numToken, FORMAT_NEWLINES(iterator->content), str_type(iterator->tType), str_subtype(iterator->sType), FORMAT_NEWLINES(iterator->content), "int");
            else if(iterator->sType == REALCONST)
                fprintf(yyout, "%d:\t#%d\t\"%s\"\t%s\t%s\t\"%s\"\t<-%s\n",iterator->numline, iterator->numToken, FORMAT_NEWLINES(iterator->content), str_type(iterator->tType), str_subtype(iterator->sType), FORMAT_NEWLINES(iterator->content), "float");
            else
                fprintf(yyout, "%d:\t#%d\t\"%s\"\t%s\t%s\t\"%s\"\t<-%s\n",iterator->numline, iterator->numToken, FORMAT_NEWLINES(iterator->content), str_type(iterator->tType), str_subtype(iterator->sType), FORMAT_NEWLINES(iterator->content), "enumerated");   
        }
        iterator=iterator->next;
    }
}
    