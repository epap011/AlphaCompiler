#include <stdio.h>
#include <stdlib.h>
#include "yacc_util.h"

int yyerror(char* yaccProvideMessage) {
    fprintf(stderr, "%s: at line %d, before token:%s\n",  yaccProvideMessage, yylineno, yytext);
    fprintf(stderr , "INPUT NOT VALID\n");
    return 0;
}