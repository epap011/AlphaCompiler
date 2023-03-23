#ifndef UTILITIES_H
#define UTILITIES_H

#include <stdio.h>

extern int   yylineno;
extern char* yytext;

int yylex(void);
int yyerror(char* yaccProvideMessage);

extern int yylineno;
extern char * yytext;
extern FILE * yyin;    

#endif /*UTILITIES_H*/