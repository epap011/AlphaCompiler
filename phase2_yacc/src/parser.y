%{
    #include <stdio.h>
    #include <stdlib.h>

    int yyerror(char * error_msg);
    int yylex(void);

    extern int yylineno;
    extern char * yytext;
    extern FILE * yyin;    
%}

%defines

%start program

%token ASSIGN PLUS MINUS MUL DIV MOD EQ NEQ INC DEC GT LT GTE LTE UMINUS
%token AND OR NOT IF ELSE WHILE FOR FUNCTION RETURN BREAK CONTINUE LOCAL TRUE FALSE NIL
%token LBRACE RBRACE LCBRACE RCBRACE LPAR RPAR SEMI COMMA COLON DCOLON DOT DDOT
%token IDENT STRING INTCONST REALCONST 

%union{

}

%right ASSIGN
%left OR
%left AND 
%nonassoc EQ NEQ
%nonassoc LT GT LTE GTE
%left PLUS MINUS
%left MUL DIV MOD
%right NOT INC DEC UMINUS
%left DOT DDOT  
%left LBRACE RBRACE 
%left LPAR RPAR 
 
%%  

program     : stmtList                  {}
            ;   

stmt        : expr SEMI                 {}
            | ifstmt                    {}
            | whilestmt                 {}
            | forstmt                   {}
            | returnstmt                {}
            | BREAK SEMI                {}
            | CONTINUE SEMI             {}
            | block                     {}
            | funcdef                   {}
            | SEMI                      {}
            ;           

expr        : assignexpr                {}
            | expr op expr              {}
            | term                      {}
            ;           

op          : PLUS                      {}
            | MINUS                     {}
            | MUL                       {}
            | DIV                       {}
            | MOD                       {}
            | EQ                        {}
            | NEQ                       {}
            | GT                        {}
            | LT                        {}
            | GTE                       {}
            | LTE                       {}
            | AND                       {}
            | OR                        {}
            | NOT                       {}
            ;           

term        : LPAR expr RPAR            {}
            | UMINUS expr               {}
            | NOT expr                  {}
            | INC lvalue                {}
            | lvalue INC                {}
            | DEC lvalue                {}
            | lvalue DEC                {}
            | primary                   {}
            ;   

assignexpr  : lvalue ASSIGN expr        {}
            ;   

primary     : lvalue                    {}
            | call                      {}
            | objectdef                 {}
            | LPAR funcdef RPAR         {}
            | const                     {}
            ;   

lvalue      : IDENT                     {}
            | LOCAL IDENT               {}
            | DCOLON IDENT              {}
            | member                    {}
            ;   

member      : lvalue DOT IDENT          {}
            | lvalue LBRACE expr RBRACE {}
            | call DOT IDENT            {}
            | call LBRACE expr RBRACE   {}
            ;

call        : call LPAR elist RPAR
            | lvalue callsuffix
            | LPAR funcdef RPAR LPAR elist RPAR     
            ;

callsuffix  : normcall
            | methodcall
            ;

normcall    : LPAR elist RPAR
            ;

methodcall  : DDOT IDENT LPAR elist RPAR
            ;

elist       : %empty
            | expr com_expr_opt
            ;

objectdef   : LCBRACE elist RCBRACE
            | LCBRACE indexed RCBRACE
            ;

indexed     : indexedelem com_indexedelem_opt
            ;


indexedelem     : LCBRACE expr COLON expr RCBRACE
                ;

block           : LCBRACE stmtList RCBRACE
                ;

funcdef         : FUNCTION IDENT LPAR idlist RPAR block
                ;

const           : INTCONST
                | REALCONST
                | STRING
                | TRUE
                | FALSE
                | NIL
                ;

idlist          : %empty
                | IDENT COMMA idlist
                | IDENT
                ;

ifstmt          : IF LPAR expr RPAR stmt

whilestmt       : WHILE LPAR expr RPAR stmt

forstmt         : FOR LPAR expr SEMI expr SEMI expr RPAR stmt

stmtList        : %empty
                | stmt stmtList
                ;

returnstmt      : RETURN expr semi_opt
                ;

com_indexedelem_opt : %empty
                    | COMMA indexedelem
                    ;

com_expr_opt : %empty
             | COMMA expr com_expr_opt
             ;

semi_opt        : SEMI
                | %empty
                ;

%%