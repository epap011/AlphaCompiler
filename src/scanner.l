/*Options*/
%option noyywrap
%option yylineno

%{
    #include <stdio.h>
    #include <stdlib.h>    
    #include <string.h>
    #include "stack.h"
    #include "parser.h"

    #define RED     "\033[31m"
    #define BLU     "\x1b[34m"
    #define DEFAULT "\x1b[0m"

    #define TOKEN(type,subtype,lc,tkn,text) //insert_alpha_token(yylval,lc,tkn,text,type,subtype)

    int  tkn_counter  = 0;

    /*Block comment handlers*/
    int   comm_counter = 0;
    int   comm_line;
    int   nest_line;
    char* comment;
    int str_nl_counter = 0;

    char* replace_escape_chars(char *str, int yyleng);
    /*char* commcat(char* comm, char *cat);*/

    Stack* stack;

    
%}

/*Macros (Regex)*/
intVal    [0-9]+
RealVal   {intVal}+"."{intVal}+
id        [a-zA-Z][a-zA-Z_0-9]*
string    \"(\\.|[^"\\])*\"
unclosed_string \"(\\.|[^"\\])*
comment1  "//"[^*].*
comment2o "/\*"
comment2c "\*/"
blanks    [ \t\v]
undefined [^\r\n]

/*Rules*/
%%
"="        {if(!comm_counter) return ASSIGN;}
"+"        {if(!comm_counter) return PLUS;}
"-"        {if(!comm_counter) return MINUS;}
"*"        {if(!comm_counter) return MUL;}
"/"        {if(!comm_counter) return DIV;}
"%"        {if(!comm_counter) return MOD;}
"=="       {if(!comm_counter) return EQ;}
"!="       {if(!comm_counter) return NEQ;}
"++"       {if(!comm_counter) return INC;}
"--"       {if(!comm_counter) return DEC;}
">"        {if(!comm_counter) return GT;}
"<"        {if(!comm_counter) return LT;}
">="       {if(!comm_counter) return GTE;}
"<="       {if(!comm_counter) return LTE;}   

"if"       {if(!comm_counter) return IF;}
"else"     {if(!comm_counter) return ELSE;}
"while"    {if(!comm_counter) return WHILE;}
"for"      {if(!comm_counter) return FOR;}
"function" {if(!comm_counter) return FUNCTION;}
"return"   {if(!comm_counter) return RETURN;}
"break"    {if(!comm_counter) return BREAK;}
"continue" {if(!comm_counter) return CONTINUE;}
"and"      {if(!comm_counter) return AND;}
"not"      {if(!comm_counter) return NOT;}
"or"       {if(!comm_counter) return OR;}
"local"    {if(!comm_counter) return LOCAL;}
"true"     {if(!comm_counter) return TRUE;}
"false"    {if(!comm_counter) return FALSE;}
"nil"      {if(!comm_counter) return NIL;}  

"{"        {if(!comm_counter) return LCBRACE;}
"}"        {if(!comm_counter) return RCBRACE;}
"["        {if(!comm_counter) return LBRACE;}
"]"        {if(!comm_counter) return RBRACE;}
"("        {if(!comm_counter) return LPAR;}
")"        {if(!comm_counter) return RPAR;}
";"        {if(!comm_counter) return SEMI;}
","        {if(!comm_counter) return COMMA;}
":"        {if(!comm_counter) return COLON;}
"::"       {if(!comm_counter) return DCOLON;}
"."        {if(!comm_counter) return DOT;}
".."       {if(!comm_counter) return DDOT;}

{id}       {if(!comm_counter) {yylval.stringVal = strdup(yytext); return IDENT;}}
{intVal}   {if(!comm_counter) {yylval.intVal    = atoi(yytext);   return INTCONST;}}
{RealVal}  {if(!comm_counter) {yylval.realVal   = atof(yytext);   return REALCONST;}}

{string}     {if(!comm_counter) {
                    yytext = replace_escape_chars(yytext + 1, yyleng - 1);
                    str_nl_counter=0;
                    yylval.stringVal = strdup(yytext); 
                    return STRING;
                }
            }

{unclosed_string} {fprintf(stderr, RED"Error: "DEFAULT"Unclosed string: \"%s\" at line %d\n",yytext,yylineno); return 0;}

{comment1}   {
                if(comm_counter > 0) { //single line comment is inside a block comment
                    REJECT;
                }
                else if(!comm_counter) {
                    fprintf(yyout, BLU "Single line comment found!"DEFAULT"\n");
                }
            }

{comment2o} {
                comm_counter++;
                if(comm_counter==1){
                    comm_line=yylineno;
                }
            }

{comment2c} {
            comm_counter--;
                if(comm_counter==-1){
                    comm_counter=0;
                    /*revert chars*/
                    REJECT;
                }
                else if(!comm_counter){ 
                     fprintf(yyout, BLU "Block comment found!"DEFAULT"\n");
                }
                else {
                    fprintf(yyout, BLU "Nested comment found!"DEFAULT"\n");
                }
            }

{blanks}     {}

{undefined} { fprintf(stderr, RED"Warning: "DEFAULT"Detected Undefined character: \"%s\" at line %d\n",yytext,yylineno); }

\n           {}

<<EOF>>      {
                if(comm_counter){
                    fprintf(stderr, RED"ERROR: "DEFAULT"Unclosed comment at line %d\n",comm_line);
                    free(comment);
                    return 1;
                }
                return 0;
             }
%%

/*This function is used to process the string and replace any escape character with their actual value*/
char * replace_escape_chars(char* str, int length){

    str[length - 1] = '\0'; //remove the last quote as well

    char *new_str = malloc(length);

    int  i = 0, j = 0;

    while(str[i] != '\0'){

        if(str[i] == '\\'){ 
            switch(str[++i]){
                case 'n': 
                    new_str[j] = '\n';
                    str_nl_counter++;
                    break;
                case 't':
                    new_str[j] = '\t';
                    break;
                case 'r':
                    new_str[j] = '\r';

                    break;
                case '\\': 
                    new_str[j] = '\\';
                    break;
                case '"':
                    new_str[j] = '"';
                    break;
                case '\'':              //auto einai peritto? (afou stin glwsa mas den uparxei mono quote den exoume logo kaneis nato kanei escape??)
                    new_str[j] = '\'';
                    break;
                case '?':
                    new_str[j] = '\?';
                    break;
                case 'a':
                    new_str[j] = '\a';
                    break;
                case 'b':
                    new_str[j] = '\b';
                    break;
                case 'e':
                    new_str[j] = '\e';
                    break;
                case 'v':
                    new_str[j] = '\v';
                    break;
                default:            /*Invalid escape character, we leave it as it is, but we print a warning*/
                    new_str[j] = str[i-1];
                    new_str[++j] = str[i];
                    fprintf(stderr, RED"Warning: "DEFAULT"Invalid escape character \'%c\' in string : %s\" at line %d\n",str[i],yytext,yylineno);
                    break;
            }          
        }
        else
            new_str[j] = str[i];
        
        i++; j++;
    }
    return new_str;
}
