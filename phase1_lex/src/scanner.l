/*Options*/
%option noyywrap
%option yylineno

%{
    #include <stdio.h>
    #include <stdlib.h>    
    #include <string.h>
    #include "tokens.h"

    #define RED     "\033[31m"  //for colorful output
    #define DEFAULT "\x1b[0m"

    #define TOKEN(type,subtype,lc,tkn, text) insert_token(yylval,lc,tkn,text,type,subtype)

    int  tkn_counter  = 0;

    /*Block comment handlers*/
    int   comm_counter = 0;
    int   comm_line;
    int   nest_line;
    char* comment;

    char* replace_escape_chars(char *str, int yyleng);
    char* commcat(char* comm, char *cat);

    #define YY_DECL int alpha_yylex(void* yylval)
%}

/*Macros (Regex)*/
intVal    [0-9]+
RealVal   {intVal}+"."{intVal}+
id        [a-zA-Z][a-zA-Z_0-9]*
string    \"(\\.|[^"\\])*\"
comment1  "//"[^*].*
comment2o "/\*"
comment2c "\*/"
blanks    [ \t\v]
undefined [^\r\n]

/*Rules*/
%%
"="        {if(!comm_counter) {TOKEN(OPERATOR, ASSIGN,     yylineno, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
"+"        {if(!comm_counter) {TOKEN(OPERATOR, PLUS,       yylineno, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
"-"        {if(!comm_counter) {TOKEN(OPERATOR, MINUS,      yylineno, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
"*"        {if(!comm_counter) {TOKEN(OPERATOR, MUL,        yylineno, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
"/"        {if(!comm_counter) {TOKEN(OPERATOR, SLASH,      yylineno, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
"%"        {if(!comm_counter) {TOKEN(OPERATOR, MOD,        yylineno, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
"=="       {if(!comm_counter) {TOKEN(OPERATOR, EQ,         yylineno, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
"!="       {if(!comm_counter) {TOKEN(OPERATOR, NEQ,        yylineno, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
"++"       {if(!comm_counter) {TOKEN(OPERATOR, INC,        yylineno, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
"--"       {if(!comm_counter) {TOKEN(OPERATOR, DEC,        yylineno, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
">"        {if(!comm_counter) {TOKEN(OPERATOR, GT,         yylineno, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
"<"        {if(!comm_counter) {TOKEN(OPERATOR, LT,         yylineno, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
">="       {if(!comm_counter) {TOKEN(OPERATOR, GTE,        yylineno, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
"<="       {if(!comm_counter) {TOKEN(OPERATOR, LTE,        yylineno, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }   
   
"if"       {if(!comm_counter) {TOKEN(KEYWORD, IF,          yylineno, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
"else"     {if(!comm_counter) {TOKEN(KEYWORD, ELSE,        yylineno, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
"while"    {if(!comm_counter) {TOKEN(KEYWORD, WHILE,       yylineno, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
"for"      {if(!comm_counter) {TOKEN(KEYWORD, FOR,         yylineno, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
"function" {if(!comm_counter) {TOKEN(KEYWORD, FUNCTION,    yylineno, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
"return"   {if(!comm_counter) {TOKEN(KEYWORD, RETURN,      yylineno, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
"break"    {if(!comm_counter) {TOKEN(KEYWORD, BREAK,       yylineno, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
"continue" {if(!comm_counter) {TOKEN(KEYWORD, CONTINUE,    yylineno, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
"and"      {if(!comm_counter) {TOKEN(KEYWORD, AND,         yylineno, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
"not"      {if(!comm_counter) {TOKEN(KEYWORD, NOT,         yylineno, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
"or"       {if(!comm_counter) {TOKEN(KEYWORD, OR,          yylineno, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
"local"    {if(!comm_counter) {TOKEN(KEYWORD, LOCAL,       yylineno, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
"true"     {if(!comm_counter) {TOKEN(KEYWORD, TRUE,        yylineno, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
"false"    {if(!comm_counter) {TOKEN(KEYWORD, FALSE,       yylineno, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
"nil"      {if(!comm_counter) {TOKEN(KEYWORD, NIL,         yylineno, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }  
   
"{"        {if(!comm_counter) {TOKEN(PUNCTUATION, LCBRACE, yylineno, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
"}"        {if(!comm_counter) {TOKEN(PUNCTUATION, RCBRACE, yylineno, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
"["        {if(!comm_counter) {TOKEN(PUNCTUATION, LBRACE,  yylineno, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
"]"        {if(!comm_counter) {TOKEN(PUNCTUATION, RBRACE,  yylineno, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
"("        {if(!comm_counter) {TOKEN(PUNCTUATION, LPAR,    yylineno, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
")"        {if(!comm_counter) {TOKEN(PUNCTUATION, RPAR,    yylineno, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
";"        {if(!comm_counter) {TOKEN(PUNCTUATION, SEMI,    yylineno, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
","        {if(!comm_counter) {TOKEN(PUNCTUATION, COMMA,   yylineno, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
":"        {if(!comm_counter) {TOKEN(PUNCTUATION, COLON,   yylineno, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
"::"       {if(!comm_counter) {TOKEN(PUNCTUATION, DCOLON,  yylineno, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
"."        {if(!comm_counter) {TOKEN(PUNCTUATION, DOT,     yylineno, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
".."       {if(!comm_counter) {TOKEN(PUNCTUATION, DDOT,    yylineno, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }

{id}       {if(!comm_counter) {TOKEN(IDENT, NOSTYPE,       yylineno, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
{intVal}   {if(!comm_counter) {TOKEN(NUMBER, INTCONST,     yylineno, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
{RealVal}  {if(!comm_counter) {TOKEN(NUMBER, REALCONST,    yylineno, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }

{string}     {
                if(!comm_counter) {
                    yytext = replace_escape_chars(yytext + 1, yyleng - 1);     // +1 to skip the first quote
                    TOKEN(STRING, NOSTYPE, yylineno, ++tkn_counter, yytext);
                } 
                else {
                    comment=commcat(comment,yytext);
                }
            }

{comment1}   {
                if(comm_counter > 0) { //single line comment is inside a block comment
                    REJECT;
                }
                if(!comm_counter) {
                    TOKEN(COMMENT, LINECOMM, yylineno, ++tkn_counter, yytext);
                } 
                else {
                    comment=commcat(comment,yytext);
                } 
            }

{comment2o} {
                comm_counter++;
                push(top,yylineno);
                comment=commcat(comment,yytext);
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
                    comment=commcat(comment,yytext);
                    TOKEN(COMMENT, BLOCKCOMM, comm_line, ++tkn_counter, comment);
                    free(comment);
                }
                else{
                    TOKEN(COMMENT, NESTCOMM, pop(top), ++tkn_counter, comment);
                    comment=commcat(comment,yytext);
                }
            }

{blanks}     {if (comm_counter){comment=commcat(comment,yytext);}}

{undefined}  {
                if(!comm_counter) {
                    TOKEN(UNDEFCHR, NOSTYPE, yylineno, -1, yytext); 
                    fprintf(stderr, RED"Warning: "DEFAULT"Detected Undefined character: \"%s\" at line %d\n",yytext,yylineno);
                }   
                else 
                    comment=commcat(comment,yytext); 
            }
\n           {if(comm_counter){comment=commcat(comment,yytext);}}

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