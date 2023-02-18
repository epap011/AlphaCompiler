/*Options*/
%option yylineno 
%option noyywrap
%option outfile = "scanner.c"

%{
    #include <stdio.h>
    #include <stdlib.h>    
    
    int  tkn_counter = 0;

   // #define YY_DECL int alpha_yylex(alpha_token_t* ylval) //to prototype pou zitaei i askisi (ewrwtiseis 7)
%}

/*Macros (Regex)*/
intVal      [0-9]+
RealVal     {intVal}+"."{intVal}+
id          [a-zA-Z][a-zA-Z_0-9]* 
string      \"[^\n"]*\"
comment1    "//".*
undefined   .

/*Rules*/
%%
"="  {fprintf(stderr, "%d:  #%d \"%s\" OPERATOR \n",yylineno, ++tkn_counter, yytext);}
"+"  {fprintf(stderr, "%d:  #%d \"%s\" OPERATOR \n",yylineno, ++tkn_counter, yytext);}
"-"  {fprintf(stderr, "%d:  #%d \"%s\" OPERATOR \n",yylineno, ++tkn_counter, yytext);}
"*"  {fprintf(stderr, "%d:  #%d \"%s\" OPERATOR \n",yylineno, ++tkn_counter, yytext);}
"/"  {fprintf(stderr, "%d:  #%d \"%s\" OPERATOR \n",yylineno, ++tkn_counter, yytext);}
"%"  {fprintf(stderr, "%d:  #%d \"%s\" OPERATOR \n",yylineno, ++tkn_counter, yytext);}
"==" {fprintf(stderr, "%d:  #%d \"%s\" OPERATOR \n",yylineno, ++tkn_counter, yytext);}
"!=" {fprintf(stderr, "%d:  #%d \"%s\" OPERATOR \n",yylineno, ++tkn_counter, yytext);}
"++" {fprintf(stderr, "%d:  #%d \"%s\" OPERATOR \n",yylineno, ++tkn_counter, yytext);}
"--" {fprintf(stderr, "%d:  #%d \"%s\" OPERATOR \n",yylineno, ++tkn_counter, yytext);}
">"  {fprintf(stderr, "%d:  #%d \"%s\" OPERATOR \n",yylineno, ++tkn_counter, yytext);}
"<"  {fprintf(stderr, "%d:  #%d \"%s\" OPERATOR \n",yylineno, ++tkn_counter, yytext);}
">=" {fprintf(stderr, "%d:  #%d \"%s\" OPERATOR \n",yylineno, ++tkn_counter, yytext);}
"<=" {fprintf(stderr, "%d:  #%d \"%s\" OPERATOR \n",yylineno, ++tkn_counter, yytext);}

"if"       {fprintf(stderr, "%d:  #%d \"%s\" KEYWORD \n",yylineno, ++tkn_counter, yytext);}
"else"     {fprintf(stderr, "%d:  #%d \"%s\" KEYWORD \n",yylineno, ++tkn_counter, yytext);}
"while"    {fprintf(stderr, "%d:  #%d \"%s\" KEYWORD \n",yylineno, ++tkn_counter, yytext);}
"for"      {fprintf(stderr, "%d:  #%d \"%s\" KEYWORD \n",yylineno, ++tkn_counter, yytext);}
"function" {fprintf(stderr, "%d:  #%d \"%s\" KEYWORD \n",yylineno, ++tkn_counter, yytext);}
"return"   {fprintf(stderr, "%d:  #%d \"%s\" KEYWORD \n",yylineno, ++tkn_counter, yytext);}
"break"    {fprintf(stderr, "%d:  #%d \"%s\" KEYWORD \n",yylineno, ++tkn_counter, yytext);}
"continue" {fprintf(stderr, "%d:  #%d \"%s\" KEYWORD \n",yylineno, ++tkn_counter, yytext);}
"and"      {fprintf(stderr, "%d:  #%d \"%s\" KEYWORD \n",yylineno, ++tkn_counter, yytext);}
"not"      {fprintf(stderr, "%d:  #%d \"%s\" KEYWORD \n",yylineno, ++tkn_counter, yytext);}
"or"       {fprintf(stderr, "%d:  #%d \"%s\" KEYWORD \n",yylineno, ++tkn_counter, yytext);}
"local"    {fprintf(stderr, "%d:  #%d \"%s\" KEYWORD \n",yylineno, ++tkn_counter, yytext);}
"true"     {fprintf(stderr, "%d:  #%d \"%s\" KEYWORD \n",yylineno, ++tkn_counter, yytext);}
"false"    {fprintf(stderr, "%d:  #%d \"%s\" KEYWORD \n",yylineno, ++tkn_counter, yytext);}
"nil"      {fprintf(stderr, "%d:  #%d \"%s\" KEYWORD \n",yylineno, ++tkn_counter, yytext);}

"{"  {fprintf(stderr, "%d:  #%d \"%s\" PUNCTUATION \n",yylineno, ++tkn_counter, yytext);}
"}"  {fprintf(stderr, "%d:  #%d \"%s\" PUNCTUATION \n",yylineno, ++tkn_counter, yytext);}
"["  {fprintf(stderr, "%d:  #%d \"%s\" PUNCTUATION \n",yylineno, ++tkn_counter, yytext);}
"]"  {fprintf(stderr, "%d:  #%d \"%s\" PUNCTUATION \n",yylineno, ++tkn_counter, yytext);}
"("  {fprintf(stderr, "%d:  #%d \"%s\" PUNCTUATION \n",yylineno, ++tkn_counter, yytext);}
")"  {fprintf(stderr, "%d:  #%d \"%s\" PUNCTUATION \n",yylineno, ++tkn_counter, yytext);}
";"  {fprintf(stderr, "%d:  #%d \"%s\" PUNCTUATION \n",yylineno, ++tkn_counter, yytext);}
","  {fprintf(stderr, "%d:  #%d \"%s\" PUNCTUATION \n",yylineno, ++tkn_counter, yytext);}
":"  {fprintf(stderr, "%d:  #%d \"%s\" PUNCTUATION \n",yylineno, ++tkn_counter, yytext);}
"::" {fprintf(stderr, "%d:  #%d \"%s\" PUNCTUATION \n",yylineno, ++tkn_counter, yytext);}
"."  {fprintf(stderr, "%d:  #%d \"%s\" PUNCTUATION \n",yylineno, ++tkn_counter, yytext);}
".." {fprintf(stderr, "%d:  #%d \"%s\" PUNCTUATION \n",yylineno, ++tkn_counter, yytext);}

{id}         {fprintf(stderr, "%d:  #%d \"%s\" ID \n",yylineno, ++tkn_counter, yytext);}
{string}     {fprintf(stderr, "%d:  #%d \"%s\" STRING \n",yylineno, ++tkn_counter, yytext);}
{intVal}     {fprintf(stderr, "%d:  #%d \"%s\" CONST_INT \n",yylineno, ++tkn_counter, yytext);}
{RealVal}    {fprintf(stderr, "%d:  #%d \"%s\" CONST_REAL \n",yylineno, ++tkn_counter, yytext);}
{comment1}   {fprintf(stderr, "%d:  #%d \"%s\" LINE_COMMENT \n",yylineno, ++tkn_counter, yytext);}
\n           {yylineno++;} 
%%

struct alpha_token_t {          //to struct pou dinei stin erwtisi 8
  unsigned int numline;
  unsigned int numToken;
  char         *content;
  char         *type;
  struct alpha_token_t *alpha_yylex;

};

int main(int argc, char** argv){

    if (argc == 2) {
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

    yyout = stdout;

    yylex();
    return 0;
}