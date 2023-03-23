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
"="        {TOKEN(OPERATOR, ASSIGN,     yylineno, ++tkn_counter, yytext);}
"+"        {TOKEN(OPERATOR, PLUS,       yylineno, ++tkn_counter, yytext);}
"-"        {TOKEN(OPERATOR, MINUS,      yylineno, ++tkn_counter, yytext);}
"*"        {TOKEN(OPERATOR, MUL,        yylineno, ++tkn_counter, yytext);}
"/"        {TOKEN(OPERATOR, SLASH,      yylineno, ++tkn_counter, yytext);}
"%"        {TOKEN(OPERATOR, MOD,        yylineno, ++tkn_counter, yytext);}
"=="       {TOKEN(OPERATOR, EQ,         yylineno, ++tkn_counter, yytext);}
"!="       {TOKEN(OPERATOR, NEQ,        yylineno, ++tkn_counter, yytext);}
"++"       {TOKEN(OPERATOR, INC,        yylineno, ++tkn_counter, yytext);}
"--"       {TOKEN(OPERATOR, DEC,        yylineno, ++tkn_counter, yytext);}
">"        {TOKEN(OPERATOR, GT,         yylineno, ++tkn_counter, yytext);}
"<"        {TOKEN(OPERATOR, LT,         yylineno, ++tkn_counter, yytext);}
">="       {TOKEN(OPERATOR, GTE,        yylineno, ++tkn_counter, yytext);}
"<="       {TOKEN(OPERATOR, LTE,        yylineno, ++tkn_counter, yytext);}   
   
"if"       {TOKEN(KEYWORD, IF,          yylineno, ++tkn_counter, yytext);}
"else"     {TOKEN(KEYWORD, ELSE,        yylineno, ++tkn_counter, yytext);}
"while"    {TOKEN(KEYWORD, WHILE,       yylineno, ++tkn_counter, yytext);}
"for"      {TOKEN(KEYWORD, FOR,         yylineno, ++tkn_counter, yytext);}
"function" {TOKEN(KEYWORD, FUNCTION,    yylineno, ++tkn_counter, yytext);}
"return"   {TOKEN(KEYWORD, RETURN,      yylineno, ++tkn_counter, yytext);}
"break"    {TOKEN(KEYWORD, BREAK,       yylineno, ++tkn_counter, yytext);}
"continue" {TOKEN(KEYWORD, CONTINUE,    yylineno, ++tkn_counter, yytext);}
"and"      {TOKEN(KEYWORD, AND,         yylineno, ++tkn_counter, yytext);}
"not"      {TOKEN(KEYWORD, NOT,         yylineno, ++tkn_counter, yytext);}
"or"       {TOKEN(KEYWORD, OR,          yylineno, ++tkn_counter, yytext);}
"local"    {TOKEN(KEYWORD, LOCAL,       yylineno, ++tkn_counter, yytext);}
"true"     {TOKEN(KEYWORD, TRUE,        yylineno, ++tkn_counter, yytext);}
"false"    {TOKEN(KEYWORD, FALSE,       yylineno, ++tkn_counter, yytext);}
"nil"      {TOKEN(KEYWORD, NIL,         yylineno, ++tkn_counter, yytext);}  
   
"{"        {TOKEN(PUNCTUATION, LCBRACE, yylineno, ++tkn_counter, yytext);}
"}"        {TOKEN(PUNCTUATION, RCBRACE, yylineno, ++tkn_counter, yytext);}
"["        {TOKEN(PUNCTUATION, LBRACE,  yylineno, ++tkn_counter, yytext);}
"]"        {TOKEN(PUNCTUATION, RBRACE,  yylineno, ++tkn_counter, yytext);}
"("        {TOKEN(PUNCTUATION, LPAR,    yylineno, ++tkn_counter, yytext);}
")"        {TOKEN(PUNCTUATION, RPAR,    yylineno, ++tkn_counter, yytext);}
";"        {TOKEN(PUNCTUATION, SEMI,    yylineno, ++tkn_counter, yytext);}
","        {TOKEN(PUNCTUATION, COMMA,   yylineno, ++tkn_counter, yytext);}
":"        {TOKEN(PUNCTUATION, COLON,   yylineno, ++tkn_counter, yytext);}
"::"       {TOKEN(PUNCTUATION, DCOLON,  yylineno, ++tkn_counter, yytext);}
"."        {TOKEN(PUNCTUATION, DOT,     yylineno, ++tkn_counter, yytext);}
".."       {TOKEN(PUNCTUATION, DDOT,    yylineno, ++tkn_counter, yytext);}

{id}       {TOKEN(IDENT, NOSTYPE,       yylineno, ++tkn_counter, yytext); yylval.stringVal = strdup(yytext); return IDENT}
{intVal}   {TOKEN(NUMBER, INTCONST,     yylineno, ++tkn_counter, yytext); yylval.intVal = atoi(yytext); return INTCONST;}
{RealVal}  {TOKEN(NUMBER, REALCONST,    yylineno, ++tkn_counter, yytext); yylval.realVal = atof(yytext); return REALCONST;}

{string}     {
                    yytext = replace_escape_chars(yytext + 1, yyleng - 1);     // +1 to skip the first quote
                    TOKEN(STRING, NOSTYPE, yylineno - str_nl_counter, ++tkn_counter, yytext);
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
                    TOKEN(COMMENT, LINECOMM, yylineno, ++tkn_counter, NULL);
                }
            }

{comment2o} {
                comm_counter++;
                int* line_no = (int*)malloc(sizeof(int));
                *line_no = yylineno;
                push(stack, line_no);
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
                    TOKEN(COMMENT, BLOCKCOMM, comm_line, ++tkn_counter, NULL);
                    free(comment);
                }
                else{
                    TOKEN(COMMENT, NESTCOMM, *(int*)pop(stack), ++tkn_counter, NULL);
                }
            }

{blanks}     {}

{undefined}  {
                    TOKEN(UNDEFCHR, NOSTYPE, yylineno, -1, yytext); 
                    fprintf(stderr, RED"Warning: "DEFAULT"Detected Undefined character: \"%s\" at line %d\n",yytext,yylineno);
            }
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
/*
char* commcat(char* comm, char *cat) {
    size_t comm_len = comm ? strlen(comm) : 0;
    size_t cat_len = strlen(cat);
    char* result = malloc(comm_len + cat_len + 1);
    if (!result) {
        fprintf(stderr, "Failed to allocate memory for concatenated string\n");
        exit(1);
    }
    if (comm_len > 0) {
        memcpy(result, comm, comm_len);
    }
    memcpy(result + comm_len, cat, cat_len + 1);
    return result;
}
*/