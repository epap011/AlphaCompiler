#ifndef UTILITIES_H
#define UTILITIES_H

#include <stdio.h>
#include "symbol_table.h"

#define RED   "\x1b[31m"
#define GRN   "\x1b[32m"
#define YEL   "\x1b[33m"
#define BLU   "\x1b[34m"
#define MAG   "\x1b[35m"
#define CYN   "\x1b[36m"
#define RESET "\x1b[0m"

extern int   yylineno;
extern char* yytext;
extern int formal_flag;

int yylex(void);
int yyerror(char* yaccProvideMessage);

extern int yylineno;
extern char * yytext;
extern void * yylvlval;
extern FILE * yyin;  
extern FILE * yyout;
extern SymbolTable* symTable;

#endif /*UTILITIES_H*/