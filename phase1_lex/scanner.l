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
intVal    [0-9]+
RealVal   {intVal}+"."{intVal}+
id        [a-zA-Z][a-zA-Z_0-9]* 
string    \"[^\n"]*\"
comment1  "//".*
comment2    "/\*".*"\*/"
undefined .

/*Rules*/
%%
"="          {fprintf(stderr, "%d:  #%d \"%s\" OPERATOR ASSIGN <-enumerated\n",yylineno, ++tkn_counter, yytext);}
"+"          {fprintf(stderr, "%d:  #%d \"%s\" OPERATOR PLUS <-enumerated\n",yylineno, ++tkn_counter, yytext);}
"-"          {fprintf(stderr, "%d:  #%d \"%s\" OPERATOR MINUS <-enumerated\n",yylineno, ++tkn_counter, yytext);}
"*"          {fprintf(stderr, "%d:  #%d \"%s\" OPERATOR MUL <-enumerated\n",yylineno, ++tkn_counter, yytext);}
"/"          {fprintf(stderr, "%d:  #%d \"%s\" OPERATOR SLASH <-enumerated\n",yylineno, ++tkn_counter, yytext);}
"%"          {fprintf(stderr, "%d:  #%d \"%s\" OPERATOR MOD <-enumerated\n",yylineno, ++tkn_counter, yytext);}
"=="         {fprintf(stderr, "%d:  #%d \"%s\" OPERATOR EQ <-enumerated\n",yylineno, ++tkn_counter, yytext);}
"!="         {fprintf(stderr, "%d:  #%d \"%s\" OPERATOR NEQ <-enumerated\n",yylineno, ++tkn_counter, yytext);}
"++"         {fprintf(stderr, "%d:  #%d \"%s\" OPERATOR INC <-enumerated\n",yylineno, ++tkn_counter, yytext);}
"--"         {fprintf(stderr, "%d:  #%d \"%s\" OPERATOR DEC <-enumerated\n",yylineno, ++tkn_counter, yytext);}
">"          {fprintf(stderr, "%d:  #%d \"%s\" OPERATOR GT <-enumerated\n",yylineno, ++tkn_counter, yytext);}
"<"          {fprintf(stderr, "%d:  #%d \"%s\" OPERATOR LT <-enumerated\n",yylineno, ++tkn_counter, yytext);}
">="         {fprintf(stderr, "%d:  #%d \"%s\" OPERATOR GTE <-enumerated\n",yylineno, ++tkn_counter, yytext);}
"<="         {fprintf(stderr, "%d:  #%d \"%s\" OPERATOR LTE <-enumerated\n",yylineno, ++tkn_counter, yytext);}   

"if"         {fprintf(stderr, "%d:  #%d \"%s\" KEYWORD IF <-enumerated \n",yylineno, ++tkn_counter, yytext);}
"else"       {fprintf(stderr, "%d:  #%d \"%s\" KEYWORD ELSE <-enumerated\n",yylineno, ++tkn_counter, yytext);}
"while"      {fprintf(stderr, "%d:  #%d \"%s\" KEYWORD WHILE <-enumerated\n",yylineno, ++tkn_counter, yytext);}
"for"        {fprintf(stderr, "%d:  #%d \"%s\" KEYWORD FOR <-enumerated\n",yylineno, ++tkn_counter, yytext);}
"function"   {fprintf(stderr, "%d:  #%d \"%s\" KEYWORD FUNCTION <-enumerated\n",yylineno, ++tkn_counter, yytext);}
"return"     {fprintf(stderr, "%d:  #%d \"%s\" KEYWORD RETURN <-enumerated\n",yylineno, ++tkn_counter, yytext);}
"break"      {fprintf(stderr, "%d:  #%d \"%s\" KEYWORD BREAK <-enumerated\n",yylineno, ++tkn_counter, yytext);}
"continue"   {fprintf(stderr, "%d:  #%d \"%s\" KEYWORD CONTINUE <-enumerated\n",yylineno, ++tkn_counter, yytext);}
"and"        {fprintf(stderr, "%d:  #%d \"%s\" KEYWORD AND <-enumerated\n",yylineno, ++tkn_counter, yytext);}
"not"        {fprintf(stderr, "%d:  #%d \"%s\" KEYWORD NOT <-enumerated\n",yylineno, ++tkn_counter, yytext);}
"or"         {fprintf(stderr, "%d:  #%d \"%s\" KEYWORD OR <-enumerated\n",yylineno, ++tkn_counter, yytext);}
"local"      {fprintf(stderr, "%d:  #%d \"%s\" KEYWORD LOCAL <-enumerated\n",yylineno, ++tkn_counter, yytext);}
"true"       {fprintf(stderr, "%d:  #%d \"%s\" KEYWORD TRUE <-enumerated\n",yylineno, ++tkn_counter, yytext);}
"false"      {fprintf(stderr, "%d:  #%d \"%s\" KEYWORD FALSE <-enumerated\n",yylineno, ++tkn_counter, yytext);}
"nil"        {fprintf(stderr, "%d:  #%d \"%s\" KEYWORD NIL <-enumerated\n",yylineno, ++tkn_counter, yytext);}  

"{"          {fprintf(stderr, "%d:  #%d \"%s\" PUNCTUATION LCBRACE <-enumerated\n",yylineno, ++tkn_counter, yytext);}
"}"          {fprintf(stderr, "%d:  #%d \"%s\" PUNCTUATION RCBRACE <-enumerated\n",yylineno, ++tkn_counter, yytext);}
"["          {fprintf(stderr, "%d:  #%d \"%s\" PUNCTUATION LBRACE <-enumerated\n",yylineno, ++tkn_counter, yytext);}
"]"          {fprintf(stderr, "%d:  #%d \"%s\" PUNCTUATION RBRACE <-enumerated\n",yylineno, ++tkn_counter, yytext);}
"("          {fprintf(stderr, "%d:  #%d \"%s\" PUNCTUATION LPAR <-enumerated\n",yylineno, ++tkn_counter, yytext);}
")"          {fprintf(stderr, "%d:  #%d \"%s\" PUNCTUATION RPAR <-enumerated\n",yylineno, ++tkn_counter, yytext);}
";"          {fprintf(stderr, "%d:  #%d \"%s\" PUNCTUATION SEMI <-enumerated\n",yylineno, ++tkn_counter, yytext);}
","          {fprintf(stderr, "%d:  #%d \"%s\" PUNCTUATION COMMA <-enumerated\n",yylineno, ++tkn_counter, yytext);}
":"          {fprintf(stderr, "%d:  #%d \"%s\" PUNCTUATION COLON <-enumerated\n",yylineno, ++tkn_counter, yytext);}
"::"         {fprintf(stderr, "%d:  #%d \"%s\" PUNCTUATION DCOLON <-enumerated\n",yylineno, ++tkn_counter, yytext);}
"."          {fprintf(stderr, "%d:  #%d \"%s\" PUNCTUATION DOT <-enumerated\n",yylineno, ++tkn_counter, yytext);}
".."         {fprintf(stderr, "%d:  #%d \"%s\" PUNCTUATION DDOT <-enumerated\n",yylineno, ++tkn_counter, yytext);}

{id}         {fprintf(stderr, "%d:  #%d \"%s\" ID <-char*\n",yylineno, ++tkn_counter, yytext);}
{string}     {fprintf(stderr, "%d:  #%d %s STRING <-char*\n",yylineno, ++tkn_counter, yytext);}
{intVal}     {fprintf(stderr, "%d:  #%d \"%s\" CONST_INT <-int\n",yylineno, ++tkn_counter, yytext);}
{RealVal}    {fprintf(stderr, "%d:  #%d \"%s\" CONST_REAL <-real\n",yylineno, ++tkn_counter, yytext);}
{comment1}   {fprintf(stderr, "%d:  #%d \"%s\" LINE_COMMENT <-enumerated\n",yylineno, ++tkn_counter, yytext);}
{comment2}   {fprintf(stderr, "%d:  #%d \"%s\" BLOCK_COMMENT \n",yylineno, ++tkn_counter, yytext);}
{undefined}  {fprintf(stderr, "Unrecoginzed character %s \n", yytext);}
\n           {yylineno++;} 
%%


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

    yylex();
    return 0;
}