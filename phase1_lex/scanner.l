
/*Options*/
%option yylineno 
%option outfile = "scanner.c"

%{
    #include <stdio.h>
    #include <stdlib.h>    
    
    #define YY_DECL int alpha_yylex(alpha_token_t* ylval) //to prototype pou zitaei i askisi (ewrwtiseis 7)
%}

/*Macros (Regex)*/
if          "if"        /*1os tropos*/
else        "else"
while       "while"
for         "for"
function    "function"
return      "return"
break       "break"
continue    "continue"
and         "and"
or          "or"
not         "not"
local       "local"
true        "true"
false       "false"
nil         "nil"
keyWord     {if}|{else}|{while}|{for}|{function}|{return}|{break}|{continue}|{and}|{or}|{not}|{local}|{true}|{false}|{nil}

operator    "="| "+" | "-" | "*" | "/" | "%" | "==" | "!=" | "++" | "--" | ">" | "<" | ">=" | "<="  /*2os tropos*/

intVal      [0-9]+
RealVal     {intVal}+"."{intVal}+
id          [a-zA-Z][a-zA-Z_0-9]* 
string      \"[^\n"]*\"
comment1    "//".*
whiteSpace  [ \t\v\r]
newline     \n 

undefined .

/*Rules*/
%%
{keyWord}    {fprintf(stderr, "Recognized key word with value: %s\n",    yytext);}
{operator}   {fprintf(stderr, "Recognized operator word with value: %s\n", yytext);}
{id}         {fprintf(stderr, "Recognized ID with value: %s\n", yytext);}
{string}     {fprintf(stderr, "Recognized string with value: %s\n", yytext);}
{intVal}     {fprintf(stderr, "Recognized integer with value: %s\n", yytext);}
{RealVal}    {fprintf(stderr, "Recognized real number with value: %s\n", yytext);}

/*User Code*/
%%

struct alpha_token_t {          //to struct pou dinei stin erwtisi 8
  unsigned int     numline;
  unsigned int     numToken;
  char          *content;
  char          *type;
  struct alpha_token_t *alpha_yylex;

}

int main(int argc, char** argv){
    alpha_yylex();
    return 0;
}