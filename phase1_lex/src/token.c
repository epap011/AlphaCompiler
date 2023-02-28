#include <stdio.h>
#include <stdlib.h>    
#include <string.h>
#include "tokens.h"

/*List of tokens to be written*/
TokenList *tokenList;

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
const char* str_type(enum type s) {
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
const char* str_subtype(enum subtype s) {
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
//Get subtyoe from type & content.
enum subtype get_subtype(enum type s, char* str) {
        if(s == OPERATOR){
            if (strcmp(str,"==") == 0) return ASSIGN;
            if (strcmp(str,"+") == 0) return PLUS;
            if (strcmp(str,"-") == 0) return MINUS;
            if (strcmp(str,"*") == 0) return MUL;
            if (strcmp(str,"/") == 0) return SLASH;
            if (strcmp(str,"%") == 0) return MOD;
            if (strcmp(str,"=") == 0) return EQ;
            if (strcmp(str,"!=") == 0) return NEQ;
            if (strcmp(str,"++") == 0) return INC;
            if (strcmp(str,"--") == 0) return DEC;
            if (strcmp(str,">") == 0) return GT;
            if (strcmp(str,"<") == 0) return LT;
            if (strcmp(str,">=") == 0) return GTE;
            if (strcmp(str,"<=") == 0) return LTE;
        }
        else if(s == KEYWORD){
            if (strcmp(str,"if") == 0) return IF;
            if (strcmp(str,"else") == 0) return ELSE;
            if (strcmp(str,"while") == 0) return WHILE;
            if (strcmp(str,"for") == 0) return FOR;
            if (strcmp(str,"function") == 0) return FUNCTION;
            if (strcmp(str,"return") == 0) return RETURN;
            if (strcmp(str,"break") == 0) return BREAK;
            if (strcmp(str,"continue") == 0) return CONTINUE;
            if (strcmp(str,"and") == 0) return AND;
            if (strcmp(str,"not") == 0) return NOT;
            if (strcmp(str,"or") == 0) return OR;
            if (strcmp(str,"local") == 0) return LOCAL;
            if (strcmp(str,"true") == 0) return TRUE;
            if (strcmp(str,"false") == 0) return FALSE;
            if (strcmp(str,"nil") == 0) return NIL;
       }
        else if (s == PUNCTUATION){
            if (strcmp(str,"[") == 0) return LBRACE;
            if (strcmp(str,"]") == 0) return RBRACE;
            if (strcmp(str,"{") == 0) return LCBRACE;
            if (strcmp(str,"}") == 0) return RCBRACE;
            if (strcmp(str,"(") == 0) return LPAR;
            if (strcmp(str,")") == 0) return RPAR;
            if (strcmp(str,";") == 0) return SEMI;
            if (strcmp(str,",") == 0) return COMMA;
            if (strcmp(str,"") == 0) return COLON;
            if (strcmp(str,"") == 0) return DCOLON;
            if (strcmp(str,".") == 0) return DOT;
            if (strcmp(str,"..") == 0) return DDOT;
        }
        //return INTCONST;
        //return REALCONST;
        //return LINECOMM;
        //return BLOCKCOMM;

        //No subtype found.
        //Further chekcs required for int, real or comment.
	    return NOSTYPE;
}

void print_list(TokenList *tokenList, FILE *yyout){

    alpha_token_t *iterator=tokenList->head;
    while(iterator){

        if(iterator->tType == UNDEFCHR)
            fprintf(stderr, "%d:  Undefined character \"%s\"\n",iterator->numline, iterator->content);
        
        else
        if(iterator->sType == NOSTYPE){
            fprintf(yyout, "%d  #%d \"%s\" %s \"%s\" <-%s\n",iterator->numline, iterator->numToken, iterator->content, str_type(iterator->tType), iterator->content, "char*");    
        }
        else{
            if(iterator->sType == INTCONST)
                fprintf(yyout, "%d  #%d \"%s\" %s %s \"%s\" <-%s\n",iterator->numline, iterator->numToken, iterator->content, str_type(iterator->tType), str_subtype(iterator->sType), iterator->content, "int");
            else if(iterator->sType == REALCONST)
                fprintf(yyout, "%d  #%d \"%s\" %s %s \"%s\" <-%s\n",iterator->numline, iterator->numToken, iterator->content, str_type(iterator->tType), str_subtype(iterator->sType), iterator->content, "float");
            else
                fprintf(yyout, "%d  #%d \"%s\" %s %s \"%s\" <-%s\n",iterator->numline, iterator->numToken, iterator->content, str_type(iterator->tType), str_subtype(iterator->sType), iterator->content, "enumerated");   
        }
        iterator=iterator->next;
    }
}

int main(int argc, char** argv){

    if (argc == 2 || argc == 3) {
        if(!(yyin = fopen(argv[1], "r"))) {
          fprintf(stderr, "Could not open input file: %s\n", argv[1]);
          return 1;
        }
    }
    else if(argc < 2)
        yyin = stdin;
    else {
        fprintf(stderr, "Invalid arguments.\n");
        return 1;
    }

    if(argc == 3) {
        if(!(yyout = fopen(argv[2], "w"))) {
          fprintf(stderr, "Could not open output file: %s\n", argv[2]);
          return 1;
        }
    }
    else
        yyout = stdout;

    tokenList = malloc(sizeof(TokenList));
    
    alpha_yylex(tokenList);   //tokenList is a list of alpha_token_t tokens

    print_list(tokenList, yyout);

    return 0;
}