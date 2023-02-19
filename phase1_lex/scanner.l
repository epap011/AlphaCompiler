/*Options*/
%option noyywrap
%option outfile = "scanner.c"

%{
    #include <stdio.h>
    #include <stdlib.h>    
    #include "tokens.h"

    /*To be modified, to add token to list*/
    #define TOKEN(str,lc,tkn,text) (fprintf(yyout, "%d:  #%d \"%s\"%s",lc,tkn,text,str))
    
    int  tkn_counter  = 0;
    int  line_counter = 1;

    /*Block comment handlers*/
    int   comm_counter = 0;
    int   comm_line;
    char* comment;

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

    /*List of tokens to be written by the analyzer*/
    struct alpha_token_t *tokenList;

   // #define YY_DECL int alpha_yylex(alpha_token_t* ylval) //to prototype pou zitaei i askisi (ewrwtiseis 7)
%}

/*Macros (Regex)*/
intVal    [0-9]+
RealVal   {intVal}+"."{intVal}+
id        [a-zA-Z][a-zA-Z_0-9]* 
string    \"[^\n"]*\"
comment1  "//".*
comment2o "/\*"
comment2c "\*/"
blanks    [\t \v]
undefined [^ \n\t\r]

/*Rules*/
%%
"="          {if(!comm_counter) {TOKEN(" OPERATOR ASSIGN <-enumerated\n",line_counter, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
"+"          {if(!comm_counter) {TOKEN(" OPERATOR PLUS <-enumerated\n",line_counter, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
"-"          {if(!comm_counter) {TOKEN(" OPERATOR MINUS <-enumerated\n",line_counter, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
"*"          {if(!comm_counter) {TOKEN(" OPERATOR MUL <-enumerated\n",line_counter, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
"/"          {if(!comm_counter) {TOKEN(" OPERATOR SLASH <-enumerated\n",line_counter, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
"%"          {if(!comm_counter) {TOKEN(" OPERATOR MOD <-enumerated\n",line_counter, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
"=="         {if(!comm_counter) {TOKEN(" OPERATOR EQ <-enumerated\n",line_counter, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
"!="         {if(!comm_counter) {TOKEN(" OPERATOR NEQ <-enumerated\n",line_counter, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
"++"         {if(!comm_counter) {TOKEN(" OPERATOR INC <-enumerated\n",line_counter, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
"--"         {if(!comm_counter) {TOKEN(" OPERATOR DEC <-enumerated\n",line_counter, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
">"          {if(!comm_counter) {TOKEN(" OPERATOR GT <-enumerated\n",line_counter, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
"<"          {if(!comm_counter) {TOKEN(" OPERATOR LT <-enumerated\n",line_counter, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
">="         {if(!comm_counter) {TOKEN(" OPERATOR GTE <-enumerated\n",line_counter, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
"<="         {if(!comm_counter) {TOKEN(" OPERATOR LTE <-enumerated\n",line_counter, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }   

"if"         {if(!comm_counter) {TOKEN(" KEYWORD IF <-enumerated \n",line_counter, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
"else"       {if(!comm_counter) {TOKEN(" KEYWORD ELSE <-enumerated\n",line_counter, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
"while"      {if(!comm_counter) {TOKEN(" KEYWORD WHILE <-enumerated\n",line_counter, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
"for"        {if(!comm_counter) {TOKEN(" KEYWORD FOR <-enumerated\n",line_counter, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
"function"   {if(!comm_counter) {TOKEN(" KEYWORD FUNCTION <-enumerated\n",line_counter, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
"return"     {if(!comm_counter) {TOKEN(" KEYWORD RETURN <-enumerated\n",line_counter, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
"break"      {if(!comm_counter) {TOKEN(" KEYWORD BREAK <-enumerated\n",line_counter, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
"continue"   {if(!comm_counter) {TOKEN(" KEYWORD CONTINUE <-enumerated\n",line_counter, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
"and"        {if(!comm_counter) {TOKEN(" KEYWORD AND <-enumerated\n",line_counter, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
"not"        {if(!comm_counter) {TOKEN(" KEYWORD NOT <-enumerated\n",line_counter, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
"or"         {if(!comm_counter) {TOKEN(" KEYWORD OR <-enumerated\n",line_counter, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
"local"      {if(!comm_counter) {TOKEN(" KEYWORD LOCAL <-enumerated\n",line_counter, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
"true"       {if(!comm_counter) {TOKEN(" KEYWORD TRUE <-enumerated\n",line_counter, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
"false"      {if(!comm_counter) {TOKEN(" KEYWORD FALSE <-enumerated\n",line_counter, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
"nil"        {if(!comm_counter) {TOKEN(" KEYWORD NIL <-enumerated\n",line_counter, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }  

"{"          {if(!comm_counter) {TOKEN(" PUNCTUATION LCBRACE <-enumerated\n",line_counter, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
"}"          {if(!comm_counter) {TOKEN(" PUNCTUATION RCBRACE <-enumerated\n",line_counter, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
"["          {if(!comm_counter) {TOKEN(" PUNCTUATION LBRACE <-enumerated\n",line_counter, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
"]"          {if(!comm_counter) {TOKEN(" PUNCTUATION RBRACE <-enumerated\n",line_counter, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
"("          {if(!comm_counter) {TOKEN(" PUNCTUATION LPAR <-enumerated\n",line_counter, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
")"          {if(!comm_counter) {TOKEN(" PUNCTUATION RPAR <-enumerated\n",line_counter, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
";"          {if(!comm_counter) {TOKEN(" PUNCTUATION SEMI <-enumerated\n",line_counter, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
","          {if(!comm_counter) {TOKEN(" PUNCTUATION COMMA <-enumerated\n",line_counter, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
":"          {if(!comm_counter) {TOKEN(" PUNCTUATION COLON <-enumerated\n",line_counter, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
"::"         {if(!comm_counter) {TOKEN(" PUNCTUATION DCOLON <-enumerated\n",line_counter, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
"."          {if(!comm_counter) {TOKEN(" PUNCTUATION DOT <-enumerated\n",line_counter, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
".."         {if(!comm_counter) {TOKEN(" PUNCTUATION DDOT <-enumerated\n",line_counter, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }

{id}         {if(!comm_counter) {fprintf(yyout, "%d:  #%d \"%s\" ID \"%s\" <-char*\n",line_counter, ++tkn_counter, yytext, yytext);} else {comment=commcat(comment,yytext);} }
{string}     {if(!comm_counter) {fprintf(yyout, "%d:  #%d %s STRING %s <-char*\n",line_counter, ++tkn_counter, yytext, yytext);} else {comment=commcat(comment,yytext);} }
{intVal}     {if(!comm_counter) {fprintf(yyout, "%d:  #%d \"%s\" CONST_INT %s <-int\n",line_counter, ++tkn_counter, yytext, yytext);} else {comment=commcat(comment,yytext);} }
{RealVal}    {if(!comm_counter) {fprintf(yyout, "%d:  #%d \"%s\" CONST_REAL %s <-real\n",line_counter, ++tkn_counter, yytext, yytext);} else {comment=commcat(comment,yytext);} }
{comment1}   {if(!comm_counter) {TOKEN(" LINE_COMMENT <-enumerated\n",line_counter, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }

{comment2o} {
                comm_counter++;
                comment=commcat(comment,yytext);
                if(comm_counter==1){
                    comm_line=line_counter;
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

{undefined}  {if(!comm_counter) {fprintf(stderr, "%d:  Undefined character \"%s\"\n",line_counter, yytext);} else {comment=commcat(comment,yytext);} }
\n           {line_counter++; if(comm_counter){comment=commcat(comment,"\\n");}} 
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