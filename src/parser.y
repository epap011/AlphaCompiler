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

%token AND OR NOT IF ELSE WHILE FOR FUNCTION RETURN BREAK CONTINUE LOCAL TRUE FALSE NIL

/*Kanones proseteristikotitas kai protereotitas (i protereotita einai bottom-up)*/
%nonassoc LP_ELSE
%nonassoc ELSE

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

stmt        : expr ";"                  {fprintf(yyout, MAG "Detected :" RESET"expr ;"CYN" ->"RESET" stmt \n");}
            | ifstmt                    {fprintf(yyout, MAG "Detected :" RESET"ifstmt"CYN" ->"RESET" stmt \n");}
            | whilestmt                 {fprintf(yyout, MAG "Detected :" RESET"whilestmt"CYN" ->"RESET" stmt \n");}
            | forstmt                   {fprintf(yyout, MAG "Detected :" RESET"forstmt"CYN" ->"RESET" stmt \n");}
            | returnstmt                {fprintf(yyout, MAG "Detected :" RESET"returnstmt"CYN" ->"RESET" stmt \n");}
            | BREAK ";"                 {fprintf(yyout, MAG "Detected :" RESET"BREAK ;"CYN""RESET"-> stmt\n");}
            | CONTINUE ";"              {fprintf(yyout, MAG "Detected :" RESET"CONTINUE"CYN""RESET"-> stmt ; \n");}
            | block                     {fprintf(yyout, MAG "Detected :" RESET"block"CYN" ->"RESET" stmt \n");}
            | funcdef                   {fprintf(yyout, MAG "Detected :" RESET"funcdef"CYN" ->"RESET" stmt \n");}
            | ";"                       {fprintf(yyout, MAG "Detected :" RESET"; "CYN""RESET"-> stmt\n");}
            ;           

expr        : assignexpr                {fprintf(yyout, MAG "Detected :" RESET"assignexpr"CYN" ->"RESET" expr \n");}
            | term                      {fprintf(yyout, MAG "Detected :" RESET"term"CYN" ->"RESET" expr \n");}
            | expr "+" expr              {fprintf(yyout, MAG "Detected :" RESET"expr + expr"CYN" ->"RESET" expr \n");}
            | expr "*" expr              {fprintf(yyout, MAG "Detected :" RESET"expr * expr"CYN" ->"RESET" expr \n");}
            | expr "-" expr              {fprintf(yyout, MAG "Detected :" RESET"expr - expr"CYN" ->"RESET" expr \n");}
            | expr "/" expr              {fprintf(yyout, MAG "Detected :" RESET"expr / expr"CYN" ->"RESET" expr \n");}
            | expr "%" expr              {fprintf(yyout, MAG "Detected :" RESET"expr % expr"CYN" ->"RESET" expr \n");}
            | expr EQ expr               {fprintf(yyout, MAG "Detected :" RESET"expr == expr"CYN" ->"RESET" expr \n");}
            | expr NEQ expr              {fprintf(yyout, MAG "Detected :" RESET"expr != expr"CYN" ->"RESET" expr \n");}
            | expr GT expr               {fprintf(yyout, MAG "Detected :" RESET"expr > expr"CYN" ->"RESET" expr \n");}
            | expr LT expr               {fprintf(yyout, MAG "Detected :" RESET"expr < expr"CYN" ->"RESET" expr \n");}
            | expr GTE expr              {fprintf(yyout, MAG "Detected :" RESET"expr >= expr"CYN" ->"RESET" expr \n");}
            | expr LTE expr              {fprintf(yyout, MAG "Detected :" RESET"expr <= expr"CYN" ->"RESET" expr \n");}
            | expr AND expr              {fprintf(yyout, MAG "Detected :" RESET"expr AND expr"CYN" ->"RESET" expr \n");}
            | expr OR expr               {fprintf(yyout, MAG "Detected :" RESET"expr OR expr"CYN" ->"RESET" expr \n");}
            ;                    

term        : "(" expr ")"              {fprintf(yyout, MAG "Detected :" RESET"( expr )"CYN" ->"RESET" term \n");}
            | "-" expr %prec UMINUS     {fprintf(yyout, MAG "Detected :" RESET"UMINUS expr"CYN" ->"RESET" term \n");}
            | NOT expr                  {fprintf(yyout, MAG "Detected :" RESET"NOT expr"CYN" ->"RESET" term \n");}
            | "++" lvalue               {fprintf(yyout, MAG "Detected :" RESET"++lvalue"CYN" ->"RESET" term \n");}
            | lvalue "++"               {fprintf(yyout, MAG "Detected :" RESET"lvalue++"CYN" ->"RESET" term \n");}
            | "--" lvalue               {fprintf(yyout, MAG "Detected :" RESET"--lvalue"CYN" ->"RESET" term \n");}
            | lvalue "--"               {fprintf(yyout, MAG "Detected :" RESET"lvalue--"CYN" ->"RESET" term \n");}
            | primary                   {fprintf(yyout, MAG "Detected :" RESET"primary"CYN" ->"RESET" term \n");}
            ;   

assignexpr  : lvalue "=" expr           {fprintf(yyout, MAG "Detected :" RESET"lvalue = expr"CYN" ->"RESET" assignexpr \n");}
            ;   

primary     : lvalue                    {fprintf(yyout, MAG "Detected :" RESET"lvalue"CYN" ->"RESET" primary \n");}
            | call                      {fprintf(yyout, MAG "Detected :" RESET"call"CYN" ->"RESET" primary \n");}
            | objectdef                 {fprintf(yyout, MAG "Detected :" RESET"objectdef"CYN" ->"RESET" primary \n");}
            | "(" funcdef ")"           {fprintf(yyout, MAG "Detected :" RESET"( funcdef )"CYN" ->"RESET" primary \n");}
            | const                     {fprintf(yyout, MAG "Detected :" RESET"const"CYN" ->"RESET" primary \n");}
            ;   

lvalue      : IDENT                     {fprintf(yyout, MAG "Detected :" RESET"%s"CYN" -> "RESET" IDENT"CYN" ->"RESET" lvalue \n",yylval.stringVal);}
            | LOCAL IDENT               {fprintf(yyout, MAG "Detected :" RESET"local %s"CYN" -> "RESET" LOCAL IDENT"CYN" ->"RESET" lvalue \n",yylval.stringVal);}
            | "::" IDENT                {fprintf(yyout, MAG "Detected :" RESET"::%s"CYN" -> "RESET" ::IDENT"CYN" ->"RESET" lvalue \n",yylval.stringVal);}
            | member                    {fprintf(yyout, MAG "Detected :" RESET"member"CYN" ->"RESET" lvalue \n");}
            ;   

member      : lvalue "." IDENT          {fprintf(yyout, MAG "Detected :" RESET"lvalue .IDENT"CYN" ->"RESET" member \n");}
            | lvalue "[" expr "]"       {fprintf(yyout, MAG "Detected :" RESET"lvalue ( expr )"CYN" ->"RESET" member \n");}
            | call "." IDENT            {fprintf(yyout, MAG "Detected :" RESET"call . IDENT"CYN" ->"RESET" member \n");}
            | call "[" expr "]"         {fprintf(yyout, MAG "Detected :" RESET"call ( expr )"CYN" ->"RESET" member \n");}
            ;

call        : call "(" elist ")"            {fprintf(yyout, MAG "Detected :" RESET"call ( elist )"CYN" ->"RESET" call \n");}
            | lvalue callsuffix             {fprintf(yyout, MAG "Detected :" RESET"lvalue callsuffix"CYN" ->"RESET" call \n");}
            | "(" funcdef ")" "(" elist ")" {fprintf(yyout, MAG "Detected :" RESET"( funcdef ) ( elist )"CYN" ->"RESET" call \n");}   
            ;

callsuffix  : normcall   {fprintf(yyout, MAG "Detected :" RESET"normcall"CYN" ->"RESET" callsuffix \n");}
            | methodcall {fprintf(yyout, MAG "Detected :" RESET"methodcall"CYN" ->"RESET" callsuffix \n");}
            ;

normcall    : "(" elist ")" {fprintf(yyout, MAG "Detected :" RESET"( elist )"CYN" ->"RESET" normcall \n");}
            ;

methodcall  : ".." IDENT "(" elist ")" {fprintf(yyout, MAG "Detected :" RESET".. IDENT ( elist )"CYN" ->"RESET" methodcall \n");}
            ;

com_expr_opt : /* empty */                  {fprintf(yyout, MAG "Detected :" RESET"com_expr_opt "YEL" (empty) "RESET"\n");}
             | COMMA expr com_expr_opt      {fprintf(yyout, MAG "Detected :" RESET"COMMA expr com_expr_opt \n");}
             ;

objectdef   : "[" indexed "]" {fprintf(yyout, MAG "Detected :" RESET"[ indexed ]"CYN" ->"RESET" objectdef \n");}
            | "[" elist "]" {fprintf(yyout, MAG "Detected :" RESET"[ elist ]"CYN" ->"RESET" objectdef \n");}
            ;

elist       : /* empty */       {fprintf(yyout, MAG "Detected :" RESET"elist "YEL"(empty)"RESET"\n");}
            | expr com_expr_opt {fprintf(yyout, MAG "Detected :" RESET"expr com_expr_opt"CYN" ->"RESET" elist \n");}
            ;
            
indexed     : /* empty */                       {fprintf(yyout, MAG "Detected :" RESET"indexed "YEL" (empty) "RESET"\n");}
            | indexedelem com_indexedelem_opt   {fprintf(yyout, MAG "Detected :" RESET"indexedelem com_indexedelem_opt"CYN" ->"RESET" indexed \n");}
            ;

indexedelem     : "{" expr ":" expr "}" {fprintf(yyout, MAG "Detected :" RESET"{ expr : expr }"CYN" ->"RESET" indexedelem \n");}
                ;

com_indexedelem_opt : /* empty */                           {fprintf(yyout, MAG "Detected :" RESET"com_indexedelem_opt "YEL"(empty)"RESET"\n");}
                    | "," indexedelem com_indexedelem_opt   {fprintf(yyout, MAG "Detected :" RESET", indexedelem com_indexedelem_opt \n");}
                    ;

block           : "{" stmtList "}" {fprintf(yyout, MAG "Detected :" RESET"{ stmtList }"CYN" ->"RESET" block \n");}
                ;

stmtList        : /* empty */   {fprintf(yyout, MAG "Detected :" RESET"stmtList "YEL" (empty)"RESET":\n");}
                | stmt stmtList {fprintf(yyout, MAG "Detected :" RESET"stmt stmtList"CYN" ->"RESET" stmtList \n");}
                ;

funcdef         : FUNCTION id_opt "(" idlist ")" block {fprintf(yyout, MAG "Detected :" RESET"FUNCTION id_opt ( idlist ) block"CYN" ->"RESET" funcdef \n");}
                ;

id_opt  : /* empty */   {fprintf(yyout, MAG "Detected :" RESET"id_opt "YEL" (empty) "RESET"\n");}
        | IDENT         {fprintf(yyout, MAG "Detected :" RESET"%s"CYN" -> "RESET"IDENT \n",yylval.stringVal);}
        ;

const           : INTCONST  {fprintf(yyout, MAG "Detected :" RESET"%d "CYN"-> "RESET"INTCONST"CYN"-> "RESET"const \n",yylval.intVal);}
                | REALCONST {fprintf(yyout, MAG "Detected :" RESET"%d "CYN"-> "RESET"REALCONST"CYN"-> "RESET"const \n",yylval.realVal);}
                | STRING    {fprintf(yyout, MAG "Detected :" RESET"%s" CYN"-> "RESET"STRING"CYN"-> "RESET"const \n",yylval.stringVal);}
                | TRUE      {fprintf(yyout, MAG "Detected :" RESET"TRUE"CYN"-> "RESET"const \n");}
                | FALSE     {fprintf(yyout, MAG "Detected :" RESET"FALSE"CYN"-> "RESET"const \n");}
                | NIL       {fprintf(yyout, MAG "Detected :" RESET"NIL"CYN"-> "RESET"const \n");}
                ;

idlist          : /* empty */           {fprintf(yyout, MAG "Detected :" RESET"idlist "YEL" (empty)"RESET"\n");}
                | IDENT com_id_opt      {fprintf(yyout, MAG "Detected :" RESET"IDENT com_id_opt \n");}
                ;

com_id_opt      : /* empty */           {fprintf(yyout, MAG "Detected :" RESET"com_id_opt "YEL" (empty)"RESET"\n");}
                | "," IDENT com_id_opt  {fprintf(yyout, MAG "Detected :" RESET", IDENT com_id_opt \n");}
                ;

ifstmt          : IF "(" expr ")" stmt %prec LP_ELSE {fprintf(yyout, MAG "Detected :" RESET"IF ( expr ) stmt"CYN"-> "RESET"ifstmt  \n");}
                | IF "(" expr ")" stmt ELSE stmt     {fprintf(yyout, MAG "Detected :" RESET"IF ( expr ) stmt ELSE stmt"CYN"-> "RESET"ifstmt \n");}
                ;

whilestmt       : WHILE "(" expr ")" stmt   {fprintf(yyout, MAG "Detected :" RESET"WHILE ( expr ) stmt"CYN"-> "RESET"whilestmt \n");}
                ;

forstmt         : FOR "(" elist ";" expr ";" elist ")" stmt {fprintf(yyout, MAG "Detected :" RESET"FOR ( expr ; expr ; expr ) stmt"CYN"-> "RESET"forstmt \n");}
                ;

returnstmt      : RETURN expr_opt ";" {fprintf(yyout, MAG "Detected :" RESET"RETURN expr_opt ;"CYN"-> "RESET"returnstmt \n");}
                ;

expr_opt        : /* empty */   {fprintf(yyout, MAG "Detected :" RESET"expr_opt "YEL" (empty)"RESET"\n");}
                | expr          {fprintf(yyout, MAG "Detected :" RESET"expr \n");}
                ;

%%