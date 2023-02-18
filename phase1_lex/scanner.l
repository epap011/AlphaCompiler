/*Options*/
%option yylineno 
%option outfile = "scanner.c"
%option noyywrap

%{
    #include <stdio.h>
    #include <stdlib.h>    
    
    
%}
/*Macros (Regex)*/
intVal      [0-9]+
RealVal     {intVal}+"."{intVal}+
id          [a-zA-Z][a-zA-Z_0-9]* 
string      \"[^\n"]*\"
comment1    "//".*
undefined .

/*Rules*/
%%
{id}         {fprintf(stderr, "Recognized ID with value: %s\n", yytext);}
{string}     {fprintf(stderr, "Recognized string with value: %s\n", yytext);}
{intVal}     {fprintf(stderr, "Recognized integer with value: %s\n", yytext);}
{RealVal}    {fprintf(stderr, "Recognized real number with value: %s\n", yytext);}
{comment1}   {fprintf(stderr, "Recognized comment with value: %s\n", yytext);}
{undefined}  {fprintf(stderr, "Recognized undefined with value: %s\n", yytext);}
%%

struct alpha_token_t {          //to struct pou dinei stin erwtisi 8
  unsigned int     numline;
  unsigned int     numToken;
  char          *content;
  char          *type;
  struct alpha_token_t *alpha_yylex;

};

int main(int argc, char** argv){

    yyin = stdin;
    yyout = stdout;

    yylex();
    return 0;
}