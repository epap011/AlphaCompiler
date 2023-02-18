/*Options*/
%option noyywrap
%option outfile = "scanner.c"

%{
    #include <stdio.h>
    #include <stdlib.h>    
    
    int  tkn_counter  = 0;
    int  line_counter = 1;

   // #define YY_DECL int alpha_yylex(alpha_token_t* ylval) //to prototype pou zitaei i askisi (ewrwtiseis 7)
%}

/*Macros (Regex)*/
intVal    [0-9]+
RealVal   {intVal}+"."{intVal}+
id        [a-zA-Z][a-zA-Z_0-9]* 
string    \"[^\n"]*\"
comment1  "//".*
undefined [^ \n \t]


/*Rules*/
%%
"="          {fprintf(stderr, "%d:  #%d \"%s\" OPERATOR ASSIGN <-enumerated\n",line_counter, ++tkn_counter, yytext);}
"+"          {fprintf(stderr, "%d:  #%d \"%s\" OPERATOR PLUS <-enumerated\n",line_counter, ++tkn_counter, yytext);}
"-"          {fprintf(stderr, "%d:  #%d \"%s\" OPERATOR MINUS <-enumerated\n",line_counter, ++tkn_counter, yytext);}
"*"          {fprintf(stderr, "%d:  #%d \"%s\" OPERATOR MUL <-enumerated\n",line_counter, ++tkn_counter, yytext);}
"/"          {fprintf(stderr, "%d:  #%d \"%s\" OPERATOR SLASH <-enumerated\n",line_counter, ++tkn_counter, yytext);}
"%"          {fprintf(stderr, "%d:  #%d \"%s\" OPERATOR MOD <-enumerated\n",line_counter, ++tkn_counter, yytext);}
"=="         {fprintf(stderr, "%d:  #%d \"%s\" OPERATOR EQ <-enumerated\n",line_counter, ++tkn_counter, yytext);}
"!="         {fprintf(stderr, "%d:  #%d \"%s\" OPERATOR NEQ <-enumerated\n",line_counter, ++tkn_counter, yytext);}
"++"         {fprintf(stderr, "%d:  #%d \"%s\" OPERATOR INC <-enumerated\n",line_counter, ++tkn_counter, yytext);}
"--"         {fprintf(stderr, "%d:  #%d \"%s\" OPERATOR DEC <-enumerated\n",line_counter, ++tkn_counter, yytext);}
">"          {fprintf(stderr, "%d:  #%d \"%s\" OPERATOR GT <-enumerated\n",line_counter, ++tkn_counter, yytext);}
"<"          {fprintf(stderr, "%d:  #%d \"%s\" OPERATOR LT <-enumerated\n",line_counter, ++tkn_counter, yytext);}
">="         {fprintf(stderr, "%d:  #%d \"%s\" OPERATOR GTE <-enumerated\n",line_counter, ++tkn_counter, yytext);}
"<="         {fprintf(stderr, "%d:  #%d \"%s\" OPERATOR LTE <-enumerated\n",line_counter, ++tkn_counter, yytext);}   

"if"         {fprintf(stderr, "%d:  #%d \"%s\" KEYWORD IF <-enumerated \n",line_counter, ++tkn_counter, yytext);}
"else"       {fprintf(stderr, "%d:  #%d \"%s\" KEYWORD ELSE <-enumerated\n",line_counter, ++tkn_counter, yytext);}
"while"      {fprintf(stderr, "%d:  #%d \"%s\" KEYWORD WHILE <-enumerated\n",line_counter, ++tkn_counter, yytext);}
"for"        {fprintf(stderr, "%d:  #%d \"%s\" KEYWORD FOR <-enumerated\n",line_counter, ++tkn_counter, yytext);}
"function"   {fprintf(stderr, "%d:  #%d \"%s\" KEYWORD FUNCTION <-enumerated\n",line_counter, ++tkn_counter, yytext);}
"return"     {fprintf(stderr, "%d:  #%d \"%s\" KEYWORD RETURN <-enumerated\n",line_counter, ++tkn_counter, yytext);}
"break"      {fprintf(stderr, "%d:  #%d \"%s\" KEYWORD BREAK <-enumerated\n",line_counter, ++tkn_counter, yytext);}
"continue"   {fprintf(stderr, "%d:  #%d \"%s\" KEYWORD CONTINUE <-enumerated\n",line_counter, ++tkn_counter, yytext);}
"and"        {fprintf(stderr, "%d:  #%d \"%s\" KEYWORD AND <-enumerated\n",line_counter, ++tkn_counter, yytext);}
"not"        {fprintf(stderr, "%d:  #%d \"%s\" KEYWORD NOT <-enumerated\n",line_counter, ++tkn_counter, yytext);}
"or"         {fprintf(stderr, "%d:  #%d \"%s\" KEYWORD OR <-enumerated\n",line_counter, ++tkn_counter, yytext);}
"local"      {fprintf(stderr, "%d:  #%d \"%s\" KEYWORD LOCAL <-enumerated\n",line_counter, ++tkn_counter, yytext);}
"true"       {fprintf(stderr, "%d:  #%d \"%s\" KEYWORD TRUE <-enumerated\n",line_counter, ++tkn_counter, yytext);}
"false"      {fprintf(stderr, "%d:  #%d \"%s\" KEYWORD FALSE <-enumerated\n",line_counter, ++tkn_counter, yytext);}
"nil"        {fprintf(stderr, "%d:  #%d \"%s\" KEYWORD NIL <-enumerated\n",line_counter, ++tkn_counter, yytext);}  

"{"          {fprintf(stderr, "%d:  #%d \"%s\" PUNCTUATION LCBRACE <-enumerated\n",line_counter, ++tkn_counter, yytext);}
"}"          {fprintf(stderr, "%d:  #%d \"%s\" PUNCTUATION RCBRACE <-enumerated\n",line_counter, ++tkn_counter, yytext);}
"["          {fprintf(stderr, "%d:  #%d \"%s\" PUNCTUATION LBRACE <-enumerated\n",line_counter, ++tkn_counter, yytext);}
"]"          {fprintf(stderr, "%d:  #%d \"%s\" PUNCTUATION RBRACE <-enumerated\n",line_counter, ++tkn_counter, yytext);}
"("          {fprintf(stderr, "%d:  #%d \"%s\" PUNCTUATION LPAR <-enumerated\n",line_counter, ++tkn_counter, yytext);}
")"          {fprintf(stderr, "%d:  #%d \"%s\" PUNCTUATION RPAR <-enumerated\n",line_counter, ++tkn_counter, yytext);}
";"          {fprintf(stderr, "%d:  #%d \"%s\" PUNCTUATION SEMI <-enumerated\n",line_counter, ++tkn_counter, yytext);}
","          {fprintf(stderr, "%d:  #%d \"%s\" PUNCTUATION COMMA <-enumerated\n",line_counter, ++tkn_counter, yytext);}
":"          {fprintf(stderr, "%d:  #%d \"%s\" PUNCTUATION COLON <-enumerated\n",line_counter, ++tkn_counter, yytext);}
"::"         {fprintf(stderr, "%d:  #%d \"%s\" PUNCTUATION DCOLON <-enumerated\n",line_counter, ++tkn_counter, yytext);}
"."          {fprintf(stderr, "%d:  #%d \"%s\" PUNCTUATION DOT <-enumerated\n",line_counter, ++tkn_counter, yytext);}
".."         {fprintf(stderr, "%d:  #%d \"%s\" PUNCTUATION DDOT <-enumerated\n",line_counter, ++tkn_counter, yytext);}

{id}         {fprintf(stderr, "%d:  #%d \"%s\" ID \"%s\" <-char*\n",line_counter, ++tkn_counter, yytext, yytext);}
{string}     {fprintf(stderr, "%d:  #%d %s STRING %s <-char*\n",line_counter, ++tkn_counter, yytext, yytext);}
{intVal}     {fprintf(stderr, "%d:  #%d \"%s\" CONST_INT %s <-int\n",line_counter, ++tkn_counter, yytext, yytext);}
{RealVal}    {fprintf(stderr, "%d:  #%d \"%s\" CONST_REAL %s <-real\n",line_counter, ++tkn_counter, yytext, yytext);}
{comment1}   {fprintf(stderr, "%d:  #%d \"%s\" LINE_COMMENT <-enumerated\n",line_counter, ++tkn_counter, yytext);}
{undefined}  {fprintf(stderr, "%d:  Undefined character \"%s\"\n",line_counter, yytext);}
\n           {line_counter++;} 
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