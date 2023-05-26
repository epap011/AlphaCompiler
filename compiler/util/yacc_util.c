#include <stdio.h>
#include <stdlib.h>
#include "yacc_util.h"

extern int error_flag;

int yyerror(char* yaccProvideMessage) {
    fprintf(stderr, RED"%s:" RESET" at line " GRN "%d" RESET", before token:" YEL"%s" RESET"\n",  yaccProvideMessage, yylineno, yytext);
    fprintf(stderr , RED"INPUT NOT VALID"RESET"\n");
    error_flag = 1;
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