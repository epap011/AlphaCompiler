%{
    #include "yacc_util.h"
%}

%start program

%union{
    int intVal;
    double realVal;
    char *stringVal;
}

%token <intVal>    INTCONST
%token <realVal>   REALCONST
%token <stringVal> STRING
%token <stringVal> IDENT

%token ASSIGN  "="
%token PLUS    "+"
%token MINUS   "-"
%token MUL     "*" 
%token DIV     "/"
%token MOD     "%"
%token EQ      "=="
%token NEQ     "!="
%token INC     "++"
%token DEC     "--"
%token GT      ">"
%token LT      "<"
%token GTE     ">="
%token LTE     "<=" 
%token LBRACE  "["  
%token RBRACE  "]"
%token LCBRACE "{"
%token RCBRACE "}"
%token LPAR    "("
%token RPAR    ")"
%token SEMI    ";"
%token COMMA   ","
%token COLON   ":"
%token DCOLON  "::"
%token DOT     "."
%token DDOT    ".."

%token UMINUS /* recheck */

%token AND OR NOT IF ELSE WHILE FOR FUNCTION RETURN BREAK CONTINUE LOCAL TRUE FALSE NIL

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

stmt        : expr ";"                  {}
            | ifstmt                    {}
            | whilestmt                 {}
            | forstmt                   {}
            | returnstmt                {}
            | BREAK ";"                 {}
            | CONTINUE ";"              {}
            | block                     {}
            | funcdef                   {}
            | ";"                       {}
            ;           

expr        : assignexpr                {}
            | expr op expr              {}
            | term                      {}
            ;           

op          : "+"                       {}
            | "-"                       {}
            | "*"                       {}
            | "/"                       {}
            | "%"                       {}
            | "=="                      {}
            | "!="                      {}
            | ">"                       {}
            | "<"                       {}
            | ">="                      {}
            | "<="                      {}
            | AND                       {}
            | OR                        {}
            | NOT                       {}
            ;           

term        : "(" expr ")"              {}
            | UMINUS expr               {}
            | NOT expr                  {}
            | "++" lvalue               {}
            | lvalue "++"               {}
            | "--" lvalue               {}
            | lvalue "--"               {}
            | primary                   {}
            ;   

assignexpr  : lvalue "=" expr           {}
            ;   

primary     : lvalue                    {}
            | call                      {}
            | objectdef                 {}
            | "(" funcdef ")"           {}
            | const                     {}
            ;   

lvalue      : IDENT                     {}
            | LOCAL IDENT               {}
            | "::" IDENT                {}
            | member                    {}
            ;   

member      : lvalue "." IDENT          {}
            | lvalue "(" expr ")"       {}
            | call "." IDENT            {}
            | call "(" expr ")"         {}
            ;

call        : call "(" elist ")"            {}
            | lvalue callsuffix             {}
            | "(" funcdef ")" "(" elist ")" {}     
            ;

callsuffix  : normcall   {}
            | methodcall {}
            ;

normcall    : "(" elist ")" {}
            ;

methodcall  : ".." IDENT "(" elist ")" {}
            ;

com_expr_opt : /* empty */
             | COMMA expr com_expr_opt
             ;

objectdef   : "[" indexed "]" {}
            | "[" elist   "]" {}
            ;

elist       : /* empty */
            | expr com_expr_opt
            ;
            
indexed     : /* empty */
            | indexedelem com_indexedelem_opt {}
            ;

indexedelem     : "{" expr ":" expr "}" {}
                ;

com_indexedelem_opt : /* empty */
                    | "," indexedelem com_indexedelem_opt {}
                    ;

block           : "{" stmtList "}" {}
                ;

stmtList        : /* empty */
                | stmt stmtList {}
                ;

funcdef         : FUNCTION id_opt "(" idlist ")" block {}
                ;

id_opt  : /* empty */
        | IDENT {}
        ;

const           : INTCONST  {}
                | REALCONST {}
                | STRING    {}
                | TRUE      {}
                | FALSE     {}
                | NIL       {}
                ;

idlist          : /* empty */
                | IDENT com_id_opt {}
                ;

com_id_opt      : /* empty */
                | "," IDENT com_id_opt {}
                ;

ifstmt          : IF "(" expr ")" stmt else_stml_opt {}
                ;

else_stml_opt   : /* empty */
                | ELSE stmt {}
                ;

whilestmt       : WHILE "(" expr ")" stmt {}

forstmt         : FOR "(" expr ";" expr ";" expr ")" stmt {}

returnstmt      : RETURN expr_opt ";" {}
                ;

expr_opt        : /* empty */
                | expr {}
                ;

%%