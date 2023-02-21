/*Options*/
%option noyywrap
%option outfile = "scanner.c"

%{
    #include <stdio.h>
    #include <stdlib.h>    
    #include <string.h>
    #include "tokens.h"

    /*To be modified, to add token to list*/
    #define TOKEN(str,lc,tkn,text) (fprintf(yyout, "%d:  #%d \"%s\"%s",lc,tkn,text,str))
    
    int  tkn_counter  = 0;

    /*Block comment handlers*/
    int   comm_counter = 0;
    int   comm_line;
    char* comment;

    char* replace_escape_chars(char *str, int yyleng);
    char* commcat(char* comm, char *cat);

    /*List of tokens to be written by the analyzer*/
    struct alpha_token_t *tokenList;

   // #define YY_DECL int alpha_yylex(alpha_token_t* ylval) //to prototype pou zitaei i askisi (ewrwtiseis 7)
%}

/*Macros (Regex)*/
intVal    [0-9]+
RealVal   {intVal}+"."{intVal}+
id        [a-zA-Z][a-zA-Z_0-9]*
string    \"(\\.|[^"\\])*\"
comment1  "//"[^*].*
comment2o "/\*"
comment2c "\*/"
blanks    [\t \v]
undefined [^ \n\t\r]

/*Rules*/
%%
"="          {if(!comm_counter) {TOKEN(" OPERATOR ASSIGN <-enumerated\n",yylineno, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
"+"          {if(!comm_counter) {TOKEN(" OPERATOR PLUS <-enumerated\n",yylineno, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
"-"          {if(!comm_counter) {TOKEN(" OPERATOR MINUS <-enumerated\n",yylineno, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
"*"          {if(!comm_counter) {TOKEN(" OPERATOR MUL <-enumerated\n",yylineno, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
"/"          {if(!comm_counter) {TOKEN(" OPERATOR SLASH <-enumerated\n",yylineno, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
"%"          {if(!comm_counter) {TOKEN(" OPERATOR MOD <-enumerated\n",yylineno, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
"=="         {if(!comm_counter) {TOKEN(" OPERATOR EQ <-enumerated\n",yylineno, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
"!="         {if(!comm_counter) {TOKEN(" OPERATOR NEQ <-enumerated\n",yylineno, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
"++"         {if(!comm_counter) {TOKEN(" OPERATOR INC <-enumerated\n",yylineno, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
"--"         {if(!comm_counter) {TOKEN(" OPERATOR DEC <-enumerated\n",yylineno, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
">"          {if(!comm_counter) {TOKEN(" OPERATOR GT <-enumerated\n",yylineno, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
"<"          {if(!comm_counter) {TOKEN(" OPERATOR LT <-enumerated\n",yylineno, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
">="         {if(!comm_counter) {TOKEN(" OPERATOR GTE <-enumerated\n",yylineno, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
"<="         {if(!comm_counter) {TOKEN(" OPERATOR LTE <-enumerated\n",yylineno, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }   

"if"         {if(!comm_counter) {TOKEN(" KEYWORD IF <-enumerated \n",yylineno, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
"else"       {if(!comm_counter) {TOKEN(" KEYWORD ELSE <-enumerated\n",yylineno, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
"while"      {if(!comm_counter) {TOKEN(" KEYWORD WHILE <-enumerated\n",yylineno, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
"for"        {if(!comm_counter) {TOKEN(" KEYWORD FOR <-enumerated\n",yylineno, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
"function"   {if(!comm_counter) {TOKEN(" KEYWORD FUNCTION <-enumerated\n",yylineno, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
"return"     {if(!comm_counter) {TOKEN(" KEYWORD RETURN <-enumerated\n",yylineno, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
"break"      {if(!comm_counter) {TOKEN(" KEYWORD BREAK <-enumerated\n",yylineno, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
"continue"   {if(!comm_counter) {TOKEN(" KEYWORD CONTINUE <-enumerated\n",yylineno, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
"and"        {if(!comm_counter) {TOKEN(" KEYWORD AND <-enumerated\n",yylineno, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
"not"        {if(!comm_counter) {TOKEN(" KEYWORD NOT <-enumerated\n",yylineno, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
"or"         {if(!comm_counter) {TOKEN(" KEYWORD OR <-enumerated\n",yylineno, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
"local"      {if(!comm_counter) {TOKEN(" KEYWORD LOCAL <-enumerated\n",yylineno, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
"true"       {if(!comm_counter) {TOKEN(" KEYWORD TRUE <-enumerated\n",yylineno, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
"false"      {if(!comm_counter) {TOKEN(" KEYWORD FALSE <-enumerated\n",yylineno, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
"nil"        {if(!comm_counter) {TOKEN(" KEYWORD NIL <-enumerated\n",yylineno, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }  

"{"          {if(!comm_counter) {TOKEN(" PUNCTUATION LCBRACE <-enumerated\n",yylineno, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
"}"          {if(!comm_counter) {TOKEN(" PUNCTUATION RCBRACE <-enumerated\n",yylineno, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
"["          {if(!comm_counter) {TOKEN(" PUNCTUATION LBRACE <-enumerated\n",yylineno, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
"]"          {if(!comm_counter) {TOKEN(" PUNCTUATION RBRACE <-enumerated\n",yylineno, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
"("          {if(!comm_counter) {TOKEN(" PUNCTUATION LPAR <-enumerated\n",yylineno, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
")"          {if(!comm_counter) {TOKEN(" PUNCTUATION RPAR <-enumerated\n",yylineno, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
";"          {if(!comm_counter) {TOKEN(" PUNCTUATION SEMI <-enumerated\n",yylineno, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
","          {if(!comm_counter) {TOKEN(" PUNCTUATION COMMA <-enumerated\n",yylineno, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
":"          {if(!comm_counter) {TOKEN(" PUNCTUATION COLON <-enumerated\n",yylineno, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
"::"         {if(!comm_counter) {TOKEN(" PUNCTUATION DCOLON <-enumerated\n",yylineno, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
"."          {if(!comm_counter) {TOKEN(" PUNCTUATION DOT <-enumerated\n",yylineno, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
".."         {if(!comm_counter) {TOKEN(" PUNCTUATION DDOT <-enumerated\n",yylineno, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }

{id}         {if(!comm_counter) {fprintf(yyout, "%d:  #%d \"%s\" ID \"%s\" <-char*\n",yylineno, ++tkn_counter, yytext, yytext);} else {comment=commcat(comment,yytext);} }
{intVal}     {if(!comm_counter) {fprintf(yyout, "%d:  #%d \"%s\" CONST_INT %s <-int\n",yylineno, ++tkn_counter, yytext, yytext);} else {comment=commcat(comment,yytext);} }
{RealVal}    {if(!comm_counter) {fprintf(yyout, "%d:  #%d \"%s\" CONST_REAL %s <-real\n",yylineno, ++tkn_counter, yytext, yytext);} else {comment=commcat(comment,yytext);} }

{string}     {
                if(!comm_counter) {
                    yytext = replace_escape_chars(yytext + 1, yyleng - 1);     // +1 to skip the first quote
                    fprintf(yyout, "%d:  #%d \"%s\" STRING \"%s\" <-char*\n",yylineno, ++tkn_counter, yytext, yytext);
                } 
                    else 
                        comment=commcat(comment,yytext);
            }

{comment1}   {
                if(comm_counter > 0) { //single line comment is inside a block comment
                    REJECT;
                }

                if(!comm_counter) {
                    TOKEN(" LINE_COMMENT <-enumerated\n",yylineno, ++tkn_counter, yytext);
                } 
                else {
                    comment=commcat(comment,yytext);
                } 
            }

{comment2o} {
                comm_counter++;
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
                    TOKEN(" BLOCK_COMMENT <-enumerated\n", comm_line, ++tkn_counter, comment);
                    free(comment);
                }
                else{
                    comment=commcat(comment,yytext);
                }
            }

{blanks}    {if (comm_counter){comment=commcat(comment,yytext);}}

{undefined}  {if(!comm_counter) {fprintf(stderr, "%d:  Undefined character \"%s\"\n",yylineno, yytext);} else {comment=commcat(comment,yytext);} }
\n           {yylineno++; if(comm_counter){comment=commcat(comment,"\\n");}} 

<<EOF>>      {
                if(comm_counter){
                    comment=commcat(comment,yytext);
                    TOKEN(" BLOCK_COMMENT <-enumerated\n", comm_line, ++tkn_counter, comment);
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
                default:            /*Invalid escape character, we leave it as it is*/
                    new_str[j] = str[i-1];
                    new_str[++j] = str[i];
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