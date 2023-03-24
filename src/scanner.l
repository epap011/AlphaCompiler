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
"="        {return ASSIGN;}
"+"        {return PLUS;}
"-"        {return MINUS;}
"*"        {return MUL;}
"/"        {return DIV;}
"%"        {return MOD;}
"=="       {return EQ;}
"!="       {return NEQ;}
"++"       {return INC;}
"--"       {return DEC;}
">"        {return GT;}
"<"        {return LT;}
">="       {return GTE;}
"<="       {return LTE;}   
   
"if"       {return IF;}
"else"     {return ELSE;}
"while"    {return WHILE;}
"for"      {return FOR;}
"function" {return FUNCTION;}
"return"   {return RETURN;}
"break"    {return BREAK;}
"continue" {return CONTINUE;}
"and"      {return AND;}
"not"      {return NOT;}
"or"       {return OR;}
"local"    {return LOCAL;}
"true"     {return TRUE;}
"false"    {return FALSE;}
"nil"      {return NIL;}  
   
"{"        {return LCBRACE;}
"}"        {return RCBRACE;}
"["        {return LBRACE;}
"]"        {return RBRACE;}
"("        {return LPAR;}
")"        {return RPAR;}
";"        {return SEMI;}
","        {return COMMA;}
":"        {return COLON;}
"::"       {return DCOLON;}
"."        {return DOT;}
".."       {return DDOT;}


{id}       {yylval.stringVal = strdup(yytext); return IDENT;}
{intVal}   {yylval.intVal    = atoi(yytext);   return INTCONST;}
{RealVal}  {yylval.realVal   = atof(yytext);   return REALCONST;}

{string}     {
                    yytext = replace_escape_chars(yytext + 1, yyleng - 1);
                    str_nl_counter=0;
                    yylval.stringVal = strdup(yytext); 
                    return STRING;
            }

{unclosed_string} {fprintf(stderr, RED"Error: "DEFAULT"Unclosed string: \"%s\" at line %d\n",yytext,yylineno); return 0;}

{comment1}   {
                if(comm_counter > 0) { //single line comment is inside a block comment
                    REJECT;
                }
                else if(!comm_counter) {
                    printf("Single line comment found!\n");
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
                     printf("Block comment found!\n");
                }
                else {
                    printf("Nested comment found!\n");
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
