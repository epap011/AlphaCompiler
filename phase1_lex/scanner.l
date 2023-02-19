/*Options*/
%option noyywrap
%option outfile = "scanner.c"

%{
    #include <stdio.h>
    #include <stdlib.h>    
    
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

   // #define YY_DECL int alpha_yylex(alpha_token_t* ylval) //to prototype pou zitaei i askisi (ewrwtiseis 7)
%}

/*Macros (Regex)*/
intVal    [0-9]+
RealVal   {intVal}+"."{intVal}+
id        [a-zA-Z][a-zA-Z_0-9]* 
string    \"[^\n"]*\"
comment1  "//".*
comment2o  "/\*"
comment2c  "\*/"
blanks    [ \t \v]
undefined [^ \n \t]


/*Rules*/
%%
"="          {if(!comm_counter) {fprintf(stderr, "%d:  #%d \"%s\" OPERATOR ASSIGN <-enumerated\n",line_counter, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
"+"          {if(!comm_counter) {fprintf(stderr, "%d:  #%d \"%s\" OPERATOR PLUS <-enumerated\n",line_counter, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
"-"          {if(!comm_counter) {fprintf(stderr, "%d:  #%d \"%s\" OPERATOR MINUS <-enumerated\n",line_counter, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
"*"          {if(!comm_counter) {fprintf(stderr, "%d:  #%d \"%s\" OPERATOR MUL <-enumerated\n",line_counter, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
"/"          {if(!comm_counter) {fprintf(stderr, "%d:  #%d \"%s\" OPERATOR SLASH <-enumerated\n",line_counter, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
"%"          {if(!comm_counter) {fprintf(stderr, "%d:  #%d \"%s\" OPERATOR MOD <-enumerated\n",line_counter, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
"=="         {if(!comm_counter) {fprintf(stderr, "%d:  #%d \"%s\" OPERATOR EQ <-enumerated\n",line_counter, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
"!="         {if(!comm_counter) {fprintf(stderr, "%d:  #%d \"%s\" OPERATOR NEQ <-enumerated\n",line_counter, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
"++"         {if(!comm_counter) {fprintf(stderr, "%d:  #%d \"%s\" OPERATOR INC <-enumerated\n",line_counter, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
"--"         {if(!comm_counter) {fprintf(stderr, "%d:  #%d \"%s\" OPERATOR DEC <-enumerated\n",line_counter, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
">"          {if(!comm_counter) {fprintf(stderr, "%d:  #%d \"%s\" OPERATOR GT <-enumerated\n",line_counter, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
"<"          {if(!comm_counter) {fprintf(stderr, "%d:  #%d \"%s\" OPERATOR LT <-enumerated\n",line_counter, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
">="         {if(!comm_counter) {fprintf(stderr, "%d:  #%d \"%s\" OPERATOR GTE <-enumerated\n",line_counter, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
"<="         {if(!comm_counter) {fprintf(stderr, "%d:  #%d \"%s\" OPERATOR LTE <-enumerated\n",line_counter, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }   

"if"         {if(!comm_counter) {fprintf(stderr, "%d:  #%d \"%s\" KEYWORD IF <-enumerated \n",line_counter, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
"else"       {if(!comm_counter) {fprintf(stderr, "%d:  #%d \"%s\" KEYWORD ELSE <-enumerated\n",line_counter, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
"while"      {if(!comm_counter) {fprintf(stderr, "%d:  #%d \"%s\" KEYWORD WHILE <-enumerated\n",line_counter, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
"for"        {if(!comm_counter) {fprintf(stderr, "%d:  #%d \"%s\" KEYWORD FOR <-enumerated\n",line_counter, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
"function"   {if(!comm_counter) {fprintf(stderr, "%d:  #%d \"%s\" KEYWORD FUNCTION <-enumerated\n",line_counter, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
"return"     {if(!comm_counter) {fprintf(stderr, "%d:  #%d \"%s\" KEYWORD RETURN <-enumerated\n",line_counter, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
"break"      {if(!comm_counter) {fprintf(stderr, "%d:  #%d \"%s\" KEYWORD BREAK <-enumerated\n",line_counter, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
"continue"   {if(!comm_counter) {fprintf(stderr, "%d:  #%d \"%s\" KEYWORD CONTINUE <-enumerated\n",line_counter, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
"and"        {if(!comm_counter) {fprintf(stderr, "%d:  #%d \"%s\" KEYWORD AND <-enumerated\n",line_counter, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
"not"        {if(!comm_counter) {fprintf(stderr, "%d:  #%d \"%s\" KEYWORD NOT <-enumerated\n",line_counter, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
"or"         {if(!comm_counter) {fprintf(stderr, "%d:  #%d \"%s\" KEYWORD OR <-enumerated\n",line_counter, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
"local"      {if(!comm_counter) {fprintf(stderr, "%d:  #%d \"%s\" KEYWORD LOCAL <-enumerated\n",line_counter, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
"true"       {if(!comm_counter) {fprintf(stderr, "%d:  #%d \"%s\" KEYWORD TRUE <-enumerated\n",line_counter, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
"false"      {if(!comm_counter) {fprintf(stderr, "%d:  #%d \"%s\" KEYWORD FALSE <-enumerated\n",line_counter, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
"nil"        {if(!comm_counter) {fprintf(stderr, "%d:  #%d \"%s\" KEYWORD NIL <-enumerated\n",line_counter, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }  

"{"          {if(!comm_counter) {fprintf(stderr, "%d:  #%d \"%s\" PUNCTUATION LCBRACE <-enumerated\n",line_counter, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
"}"          {if(!comm_counter) {fprintf(stderr, "%d:  #%d \"%s\" PUNCTUATION RCBRACE <-enumerated\n",line_counter, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
"["          {if(!comm_counter) {fprintf(stderr, "%d:  #%d \"%s\" PUNCTUATION LBRACE <-enumerated\n",line_counter, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
"]"          {if(!comm_counter) {fprintf(stderr, "%d:  #%d \"%s\" PUNCTUATION RBRACE <-enumerated\n",line_counter, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
"("          {if(!comm_counter) {fprintf(stderr, "%d:  #%d \"%s\" PUNCTUATION LPAR <-enumerated\n",line_counter, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
")"          {if(!comm_counter) {fprintf(stderr, "%d:  #%d \"%s\" PUNCTUATION RPAR <-enumerated\n",line_counter, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
";"          {if(!comm_counter) {fprintf(stderr, "%d:  #%d \"%s\" PUNCTUATION SEMI <-enumerated\n",line_counter, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
","          {if(!comm_counter) {fprintf(stderr, "%d:  #%d \"%s\" PUNCTUATION COMMA <-enumerated\n",line_counter, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
":"          {if(!comm_counter) {fprintf(stderr, "%d:  #%d \"%s\" PUNCTUATION COLON <-enumerated\n",line_counter, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
"::"         {if(!comm_counter) {fprintf(stderr, "%d:  #%d \"%s\" PUNCTUATION DCOLON <-enumerated\n",line_counter, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
"."          {if(!comm_counter) {fprintf(stderr, "%d:  #%d \"%s\" PUNCTUATION DOT <-enumerated\n",line_counter, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }
".."         {if(!comm_counter) {fprintf(stderr, "%d:  #%d \"%s\" PUNCTUATION DDOT <-enumerated\n",line_counter, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }

{id}         {if(!comm_counter) {fprintf(stderr, "%d:  #%d \"%s\" ID \"%s\" <-char*\n",line_counter, ++tkn_counter, yytext, yytext);} else {comment=commcat(comment,yytext);} }
{string}     {if(!comm_counter) {fprintf(stderr, "%d:  #%d %s STRING %s <-char*\n",line_counter, ++tkn_counter, yytext, yytext);} else {comment=commcat(comment,yytext);} }
{intVal}     {if(!comm_counter) {fprintf(stderr, "%d:  #%d \"%s\" CONST_INT %s <-int\n",line_counter, ++tkn_counter, yytext, yytext);} else {comment=commcat(comment,yytext);} }
{RealVal}    {if(!comm_counter) {fprintf(stderr, "%d:  #%d \"%s\" CONST_REAL %s <-real\n",line_counter, ++tkn_counter, yytext, yytext);} else {comment=commcat(comment,yytext);} }
{comment1}   {if(!comm_counter) {fprintf(stderr, "%d:  #%d \"%s\" LINE_COMMENT <-enumerated\n",line_counter, ++tkn_counter, yytext);} else {comment=commcat(comment,yytext);} }

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
                    fprintf(stderr, "%d:  #%d \"%s\" BLOCK_COMMENT <-enumerated\n", comm_line, ++tkn_counter, comment);
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