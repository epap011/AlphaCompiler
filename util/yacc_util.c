#include <stdio.h>
#include <stdlib.h>
#include "yacc_util.h"

int yyerror(char* yaccProvideMessage) {
    fprintf(stderr, "%s: at line %d, before token:%s\n",  yaccProvideMessage, yylineno, yytext);
    fprintf(stderr , "INPUT NOT VALID\n");
    return 0;
}

char* str_int_merge(const char* str, int num) {
    char* result = malloc(strlen(str) + 12); // allocate memory for merged string
    if(result == NULL) { // check if memory allocation failed
        return NULL;
    }
    snprintf(result, strlen(str) + 12, "%s%d", str, num); // format merged string
    return result;
}