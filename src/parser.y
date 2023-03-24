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

program     : stmtList                  {fprintf(yyout, MAG "Detected :" RESET"program stmtList \n");}
            ;   

stmt        : expr ";"                  {fprintf(yyout, MAG "Detected :" RESET"expr ; \n");}
            | ifstmt                    {fprintf(yyout, MAG "Detected :" RESET"ifstmt \n");}
            | whilestmt                 {fprintf(yyout, MAG "Detected :" RESET"whilestmt \n");}
            | forstmt                   {fprintf(yyout, MAG "Detected :" RESET"forstmt \n");}
            | returnstmt                {fprintf(yyout, MAG "Detected :" RESET"returnstmt \n");}
            | BREAK ";"                 {fprintf(yyout, MAG "Detected :" RESET"BREAK ;"CYN""RESET"-> stmt\n");}
            | CONTINUE ";"              {fprintf(yyout, MAG "Detected :" RESET"CONTINUE"CYN""RESET"-> stmt ; \n");}
            | block                     {fprintf(yyout, MAG "Detected :" RESET"block \n");}
            | funcdef                   {fprintf(yyout, MAG "Detected :" RESET"funcdef \n");}
            | ";"                       {fprintf(yyout, MAG "Detected :" RESET"; "CYN""RESET"-> stmt\n");}
            ;           

expr        : assignexpr                {fprintf(yyout, MAG "Detected :" RESET"assignexpr \n");}
            | expr op expr              {fprintf(yyout, MAG "Detected :" RESET"expr op expr\n");}
            | term                      {fprintf(yyout, MAG "Detected :" RESET"term \n");}
            ;           

op          : "+"                       {fprintf(yyout, MAG "Detected :" RESET"+"CYN" ->"RESET" op \n");}
            | "-"                       {fprintf(yyout, MAG "Detected :" RESET"-"CYN" ->"RESET" op \n");}
            | "*"                       {fprintf(yyout, MAG "Detected :" RESET"*"CYN" ->"RESET" op \n");}
            | "/"                       {fprintf(yyout, MAG "Detected :" RESET"/"CYN" ->"RESET" op \n");}
            | "%"                       {fprintf(yyout, MAG "Detected :" RESET"%"CYN" ->"RESET" op \n");}
            | "=="                      {fprintf(yyout, MAG "Detected :" RESET"=="CYN" ->"RESET" op \n");}
            | "!="                      {fprintf(yyout, MAG "Detected :" RESET"!="CYN" ->"RESET" op \n");}
            | ">"                       {fprintf(yyout, MAG "Detected :" RESET">"CYN" ->"RESET" op \n");}
            | "<"                       {fprintf(yyout, MAG "Detected :" RESET"<"CYN" ->"RESET" op \n");}
            | ">="                      {fprintf(yyout, MAG "Detected :" RESET">="CYN" ->"RESET" op \n");}
            | "<="                      {fprintf(yyout, MAG "Detected :" RESET"<="CYN" ->"RESET" op \n");}
            | AND                       {fprintf(yyout, MAG "Detected :" RESET"AND"CYN" ->"RESET" op \n");}
            | OR                        {fprintf(yyout, MAG "Detected :" RESET"OR"CYN" ->"RESET" op \n");}
            | NOT                       {fprintf(yyout, MAG "Detected :" RESET"NOT"CYN" ->"RESET" op \n");}
            ;           

term        : "(" expr ")"              {fprintf(yyout, MAG "Detected :" RESET"( expr ) \n");}
            | UMINUS expr               {fprintf(yyout, MAG "Detected :" RESET"UMINUS expr \n");}
            | NOT expr                  {fprintf(yyout, MAG "Detected :" RESET"NOT expr \n");}
            | "++" lvalue               {fprintf(yyout, MAG "Detected :" RESET"++ lvalue \n");}
            | lvalue "++"               {fprintf(yyout, MAG "Detected :" RESET"lvalue ++ \n");}
            | "--" lvalue               {fprintf(yyout, MAG "Detected :" RESET"-- lvalue \n");}
            | lvalue "--"               {fprintf(yyout, MAG "Detected :" RESET"lvalue -- \n");}
            | primary                   {fprintf(yyout, MAG "Detected :" RESET"primary \n");}
            ;   

assignexpr  : lvalue "=" expr           {fprintf(yyout, MAG "Detected :" RESET"lvalue = expr \n");}
            ;   

primary     : lvalue                    {fprintf(yyout, MAG "Detected :" RESET"lvalue \n");}
            | call                      {fprintf(yyout, MAG "Detected :" RESET"call \n");}
            | objectdef                 {fprintf(yyout, MAG "Detected :" RESET"objectdef \n");}
            | "(" funcdef ")"           {fprintf(yyout, MAG "Detected :" RESET"( funcdef ) \n");}
            | const                     {fprintf(yyout, MAG "Detected :" RESET"const \n");}
            ;   

lvalue      : IDENT                     {fprintf(yyout, MAG "Detected :" RESET"%s"CYN" -> "RESET" IDENT \n",yylval.stringVal);}
            | LOCAL IDENT               {fprintf(yyout, MAG "Detected :" RESET"local %s"CYN" -> "RESET" LOCAL IDENT \n",yylval.stringVal);}
            | "::" IDENT                {fprintf(yyout, MAG "Detected :" RESET"::%s"CYN" -> "RESET" ::IDENT \n",yylval.stringVal);}
            | member                    {fprintf(yyout, MAG "Detected :" RESET"member \n");}
            ;   

member      : lvalue "." IDENT          {fprintf(yyout, MAG "Detected :" RESET"lvalue . IDENT \n");}
            | lvalue "(" expr ")"       {fprintf(yyout, MAG "Detected :" RESET"lvalue ( expr ) \n");}
            | call "." IDENT            {fprintf(yyout, MAG "Detected :" RESET"call . IDENT \n");}
            | call "(" expr ")"         {fprintf(yyout, MAG "Detected :" RESET"call ( expr ) \n");}
            ;

call        : call "(" elist ")"            {fprintf(yyout, MAG "Detected :" RESET"call ( elist ) \n");}
            | lvalue callsuffix             {fprintf(yyout, MAG "Detected :" RESET"lvalue callsuffix \n");}
            | "(" funcdef ")" "(" elist ")" {fprintf(yyout, MAG "Detected :" RESET"( funcdef ) ( elist ) \n");}   
            ;

callsuffix  : normcall   {fprintf(yyout, MAG "Detected :" RESET"normcall \n");}
            | methodcall {fprintf(yyout, MAG "Detected :" RESET"methodcall \n");}
            ;

normcall    : "(" elist ")" {fprintf(yyout, MAG "Detected :" RESET"( elist ) \n");}
            ;

methodcall  : ".." IDENT "(" elist ")" {fprintf(yyout, MAG "Detected :" RESET".. IDENT ( elist ) \n");}
            ;

com_expr_opt : /* empty */                  {fprintf(yyout, MAG "Detected :" RESET"com_expr_opt "YEL" (empty) "RESET"\n");}
             | COMMA expr com_expr_opt      {fprintf(yyout, MAG "Detected :" RESET"COMMA expr com_expr_opt \n");}
             ;

objectdef   : "[" indexed "]" {fprintf(yyout, MAG "Detected :" RESET"[ indexed ] \n");}
            | "[" elist   "]" {fprintf(yyout, MAG "Detected :" RESET"[ elist ] \n");}
            ;

elist       : /* empty */       {fprintf(yyout, MAG "Detected :" RESET"elist "YEL"(empty)"RESET"\n");}
            | expr com_expr_opt {fprintf(yyout, MAG "Detected :" RESET"expr com_expr_opt \n");}
            ;
            
indexed     : /* empty */                       {fprintf(yyout, MAG "Detected :" RESET"indexed "YEL" (empty) "RESET"\n");}
            | indexedelem com_indexedelem_opt   {fprintf(yyout, MAG "Detected :" RESET"indexedelem com_indexedelem_opt \n");}
            ;

indexedelem     : "{" expr ":" expr "}" {fprintf(yyout, MAG "Detected :" RESET"{ expr : expr } \n");}
                ;

com_indexedelem_opt : /* empty */                           {fprintf(yyout, MAG "Detected :" RESET"com_indexedelem_opt "YEL"(empty)"RESET"\n");}
                    | "," indexedelem com_indexedelem_opt   {fprintf(yyout, MAG "Detected :" RESET", indexedelem com_indexedelem_opt \n");}
                    ;

block           : "{" stmtList "}" {fprintf(yyout, MAG "Detected :" RESET"{ stmtList } \n");}
                ;

stmtList        : /* empty */   {fprintf(yyout, MAG "Detected :" RESET"stmtList "YEL" (empty)"RESET":\n");}
                | stmt stmtList {fprintf(yyout, MAG "Detected :" RESET"stmt stmtList \n");}
                ;

funcdef         : FUNCTION id_opt "(" idlist ")" block {fprintf(yyout, MAG "Detected :" RESET"FUNCTION id_opt ( idlist ) block \n");}
                ;

id_opt  : /* empty */   {fprintf(yyout, MAG "Detected :" RESET"id_opt "YEL" (empty) "RESET"\n");}
        | IDENT         {fprintf(yyout, MAG "Detected :" RESET"%s"CYN" -> "RESET"IDENT \n",yylval.stringVal);}
        ;

const           : INTCONST  {fprintf(yyout, MAG "Detected :" RESET"%d "CYN"-> "RESET"INTCONST \n",yylval.intVal);}
                | REALCONST {fprintf(yyout, MAG "Detected :" RESET"%d "CYN"-> "RESET"REALCONST \n",yylval.realVal);}
                | STRING    {fprintf(yyout, MAG "Detected :" RESET"%s" CYN"-> "RESET"STRING \n",yylval.stringVal);}
                | TRUE      {fprintf(yyout, MAG "Detected :" RESET"TRUE \n");}
                | FALSE     {fprintf(yyout, MAG "Detected :" RESET"FALSE \n");}
                | NIL       {fprintf(yyout, MAG "Detected :" RESET"NIL \n");}
                ;

idlist          : /* empty */           {fprintf(yyout, MAG "Detected :" RESET"idlist "YEL" (empty)"RESET"\n");}
                | IDENT com_id_opt      {fprintf(yyout, MAG "Detected :" RESET"IDENT com_id_opt \n");}
                ;

com_id_opt      : /* empty */           {fprintf(yyout, MAG "Detected :" RESET"com_id_opt "YEL" (empty)"RESET"\n");}
                | "," IDENT com_id_opt  {fprintf(yyout, MAG "Detected :" RESET", IDENT com_id_opt \n");}
                ;

ifstmt          : IF "(" expr ")" stmt else_stml_opt {fprintf(yyout, MAG "Detected :" RESET"IF ( expr ) stmt else_stml_opt \n");}
                ;

else_stml_opt   : /* empty */               {fprintf(yyout, MAG "Detected :" RESET"else_stml_opt "YEL"(empty)"RESET"\n");}
                | ELSE stmt                 {fprintf(yyout, MAG "Detected :" RESET"ELSE stmt \n");}
                ;

whilestmt       : WHILE "(" expr ")" stmt   {fprintf(yyout, MAG "Detected :" RESET"WHILE ( expr ) stmt \n");}
                ;

forstmt         : FOR "(" expr ";" expr ";" expr ")" stmt {fprintf(yyout, MAG "Detected :" RESET"FOR ( expr ; expr ; expr ) stmt \n");}
                ;

returnstmt      : RETURN expr_opt ";" {fprintf(yyout, MAG "Detected :" RESET"RETURN expr_opt ; \n");}
                ;

expr_opt        : /* empty */   {fprintf(yyout, MAG "Detected :" RESET"expr_opt "YEL" (empty)"RESET"\n");}
                | expr          {fprintf(yyout, MAG "Detected :" RESET"expr \n");}
                ;

%%