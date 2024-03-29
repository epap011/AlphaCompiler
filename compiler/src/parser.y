%{
    #include "yacc_util.h"
    #include "manage_parser.h"
    #include "symbol_table.h"
    #include "scope_space.h"
    #include "expression.h"
    #include "quad.h"

    #define DEBUG_PRINT 1
    #define IS_GLOBAL scope > 0 ? _LOCAL : GLOBAL

    unsigned int scope = 0;
    unsigned int actual_line = 0;
    int anonym_func_cnt = 0;
    int anonym_var_cnt = 0;
    Stack *func_line_stack;
    Stack *scope_offset_stack;
    Stack *loop_flag_stack;
    ScopeStackList *in_function_tail; //we use this "stack" to add a flag for every new scope opening (1 if in function, 0 if not)

    int loop_flag          = 0;
    int return_flag        = 0;
    int normcall_skip      = 0;       // we want to manage_function_call only when a function is called, not when a method is called
    int loop_counter       = 0;

    int is_function_block  = 0;  // 0: not in function block, 1: in function block
    int is_function_active = 0;  // 0: not in function, > 0 in function

    Symbol* func_sym;

    unsigned formal_counter;
    Stack *formal_stack;

    //variable offset counters
    extern unsigned int programVarOffset;
    extern unsigned int functionLocalOffset;
    extern unsigned int formalArgOffset;
    extern unsigned int scopeSpaceCounter; //determines current offset
    
    extern unsigned int currQuad;
    Stack *quad_stack;   //for quad labels
    Stack *ret_stack;   //for return labels
%}

%start program

%union{
    int intVal;
    double realVal;
    char *stringVal;
    struct Symbol *symbolVal;
    struct expr *exprVal;
    struct callexpr *callexprVal;
    struct Forprefix *forprefixVal;
    struct stmt_t *stmtVal;
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

%type<intVal>    ifprefix elseprefix whilestart whilecond M N1 N2 N3
%type<stringVal> id_opt com_id_opt
%type<symbolVal> funcprefix funcdef
%type<exprVal>   expr expr_opt assignexpr term const lvalue member call primary 
%type<exprVal>   objectdef
%type<exprVal>   elist
%type<exprVal>   indexedelem com_indexedelem_opt indexed
%type<callexprVal>   methodcall normcall callsuffix
%type<forprefixVal> forprefix
%type<stmtVal>   stmt stmtList loopstmt break continue block ifstmt whilestmt forstmt returnstmt

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

program     : stmtList      {manage_program(DEBUG_PRINT, yyout);}
            | /*empty*/
            ;   

stmt        : expr ";"      {short_circuit_emits($1,yylineno,scope); $$ = manage_stmt_expr      (DEBUG_PRINT, yyout);}
            | ifstmt        {$$ = manage_stmt_ifstmt    (DEBUG_PRINT, yyout, $1);}
            | whilestmt     {$$ = manage_stmt_whilestmt (DEBUG_PRINT, yyout);}
            | forstmt       {$$ = manage_stmt_forstmt   (DEBUG_PRINT, yyout);}
            | returnstmt    {$$ = manage_stmt_returnstmt(DEBUG_PRINT, yyout);}
            | break         {manage_stmt_break(DEBUG_PRINT, yyout, yylineno, loop_flag);      $$ = $1; }
            | continue      {manage_stmt_continue  (DEBUG_PRINT, yyout, yylineno, loop_flag); $$ = $1;}
            | block         {manage_stmt_block     (DEBUG_PRINT, yyout); $$ = $1; }
            | funcdef       {$$ = manage_stmt_funcdef   (DEBUG_PRINT, yyout);}
            | ";"           {$$ = manage_stmt_semicolon (DEBUG_PRINT, yyout);}
            ;           

expr        : assignexpr        {manage_expr_assignexpr(DEBUG_PRINT, yyout);}
            | term              {manage_expr_term      (DEBUG_PRINT, yyout);}
            | expr "+" expr     {$$ = manage_expr_plus_expr (DEBUG_PRINT, yyout, $1, $3, scope, yylineno);}
            | expr "*" expr     {$$ = manage_expr_mul_expr  (DEBUG_PRINT, yyout, $1, $3, scope, yylineno);}
            | expr "-" expr     {$$ = manage_expr_minus_expr(DEBUG_PRINT, yyout, $1, $3, scope, yylineno);}
            | expr "/" expr     {$$ = manage_expr_div_expr  (DEBUG_PRINT, yyout, $1, $3, scope, yylineno);}
            | expr "%" expr     {$$ = manage_expr_mod_expr  (DEBUG_PRINT, yyout, $1, $3, scope, yylineno);}
            | expr EQ expr      {short_circuit_emits($1,yylineno,scope); $$ = manage_expr_eq_expr   (DEBUG_PRINT, yyout, $1, $3, scope, yylineno);}
            | expr NEQ expr     {short_circuit_emits($1,yylineno,scope); $$ = manage_expr_neq_expr  (DEBUG_PRINT, yyout, $1, $3, scope, yylineno);}
            | expr GT expr      {$$ = manage_expr_gt_expr   (DEBUG_PRINT, yyout, $1, $3, scope, yylineno);}
            | expr LT expr      {$$ = manage_expr_lt_expr   (DEBUG_PRINT, yyout, $1, $3, scope, yylineno);}
            | expr GTE expr     {$$ = manage_expr_gte_expr  (DEBUG_PRINT, yyout, $1, $3, scope, yylineno);}
            | expr LTE expr     {$$ = manage_expr_lte_expr  (DEBUG_PRINT, yyout, $1, $3, scope, yylineno);}
            | expr AND M expr   {$$ = manage_expr_and_expr  (DEBUG_PRINT, yyout, $1, $4, $3, scope, yylineno);}
            | expr OR  M expr   {$$ = manage_expr_or_expr   (DEBUG_PRINT, yyout, $1, $4, $3, scope, yylineno);}
            ;                   

term        : "(" expr ")"          {manage_term_lpar_expr_rpar        (DEBUG_PRINT, yyout); $$ = $2;}
            | "-" expr %prec UMINUS {$$ = manage_term_uminus_expr      (DEBUG_PRINT, yyout, $2, scope,  yylineno);}
            | NOT expr              {$$ = manage_term_not_expr         (DEBUG_PRINT, yyout, $2, scope, yylineno);}
            | "++" lvalue           {$$ = manage_term_plusplus_lvalue  (DEBUG_PRINT, yyout, symTable, $2, scope, yylineno);}
            | lvalue "++"           {$$ = manage_term_lvalue_plusplus  (DEBUG_PRINT, yyout, symTable, $1, scope, yylineno);}
            | "--" lvalue           {$$ = manage_term_minusminus_lvalue(DEBUG_PRINT, yyout, symTable, $2, scope, yylineno);}
            | lvalue "--"           {$$ = manage_term_lvalue_minusminus(DEBUG_PRINT, yyout, symTable, $1, scope, yylineno);}
            | primary               {manage_term_primary                (DEBUG_PRINT, yyout);}
            ;   

assignexpr  : lvalue "=" expr       {short_circuit_emits($3,yylineno,scope); $$ = manage_assignexpr_lvalue_assign_expr(DEBUG_PRINT, yyout, symTable, $1, $3, scope, yylineno);}
            ;   

primary     : lvalue                {if($1 != NULL) $$ = manage_primary_lvalue(DEBUG_PRINT, yyout, $1, scope, yylineno);}
            | call                  {manage_primary_call                      (DEBUG_PRINT, yyout);}
            | objectdef             {manage_primary_objectdef                 (DEBUG_PRINT, yyout);}
            | "(" funcdef ")"       {$$ = manage_primary_lpar_funcdef_rpar         (DEBUG_PRINT, yyout, $2);} //EDw file exeis douleia
            | const                 {manage_primary_const                     (DEBUG_PRINT, yyout);}
            ;   

lvalue      : IDENT                 {$$ = manage_lvalue_ident       (DEBUG_PRINT, yyout, symTable, yylval.stringVal, IS_GLOBAL, scope, yylineno, in_function_tail);}
            | LOCAL IDENT           {$$ = manage_lvalue_local_ident (DEBUG_PRINT, yyout, symTable, yylval.stringVal, scope, yylineno);}
            | "::" IDENT            {$$ = manage_lvalue_global_ident(DEBUG_PRINT, yyout, symTable, yylval.stringVal, scope, yylineno);}
            | member                {$$ = manage_lvalue_member      (DEBUG_PRINT, yyout, $1);}
            ;   

member      : lvalue "." IDENT      {$$ = manage_memeber_lvalue_dot_ident   (DEBUG_PRINT, yyout, $1, $3, scope, yylineno, &normcall_skip);}
            | lvalue "[" expr "]"   {     manage_memeber_lvalue_lbr_expr_rbr(DEBUG_PRINT, yyout, $1, $3, &$$, scope, yylineno);} /*dollar assignment happens in function*/
            | call "." IDENT        {$$ = manage_member_call_dot_ident      (DEBUG_PRINT, yyout, $1, $3, &normcall_skip);} 
            | call "[" expr "]"     {     manage_member_call_lbr_expr_rbr   (DEBUG_PRINT, yyout, $1, $3, &$$, scope, yylineno);} /*dollar assignment happens in function*/
            ;

call        : call "(" elist ")"            {$$ = manage_call_call_lpar_elist_rpar(DEBUG_PRINT, yyout, scope, yylineno, $1, $3);}
            | lvalue callsuffix             {$$ = manage_call_lvalue_callsuffix   (DEBUG_PRINT, yyout, symTable, $1, &normcall_skip, scope, yylineno, $2);}
            | "(" funcdef ")" "(" elist ")" {short_circuit_emits($5,yylineno,scope); $$ = manage_call_lpar_funcdef_rpar_lpar_elist_rpar(DEBUG_PRINT, yyout, scope, yylineno, $2, $5);}
            ;

callsuffix  : normcall   {$$ = manage_callsuffix_normcall  (DEBUG_PRINT, yyout, $1);} 
            | methodcall {$$ = manage_callsuffix_methodcall(DEBUG_PRINT, yyout, $1);} 
            ;

normcall    : "(" elist ")" { $$ = manage_normcall_lpar_elist_rpar(DEBUG_PRINT, yyout,0,$2,NULL);}
            ;

methodcall  : ".." IDENT "(" elist ")" { $$ = manage_methodcall_ddot_ident_lpar_elist_rpar(DEBUG_PRINT, yyout, &normcall_skip,1,$4,strdup($2));}
            ;

objectdef   : "[" indexed "]" {$$ = manage_objectdef_lbrace_indexed_rbrace(DEBUG_PRINT, yyout, $2, scope, yylineno);}
            | "[" elist   "]" {$$ = manage_objectdef_lbrace_elist_rbrace(DEBUG_PRINT, yyout,$2, scope, yylineno);}
            ;

elist       : /* empty */      {$$ = manage_elist_empty(DEBUG_PRINT, yyout);} //NULL
            | expr             {short_circuit_emits($1,yylineno,scope); manage_elist_expr(DEBUG_PRINT, yyout); $$ = $1;}
            | elist COMMA expr {short_circuit_emits($3,yylineno,scope); $$ = manage_elist_elist_comma_exp(DEBUG_PRINT, yyout, $1, $3);}
            ;
            
indexed     : indexedelem com_indexedelem_opt {$$ = manage_indexed_indexedelem_comindexedelemopt(DEBUG_PRINT, yyout, $1, $2);}
            ;

indexedelem     : "{" expr ":" expr "}" {$$ = manage_indexedele_lcbrace_expr_colon_expr_rcbrace(DEBUG_PRINT, yyout, $2, $4);}
                ;

com_indexedelem_opt : /* empty */                         {$$ = manage_comindexedelemopt_empty(DEBUG_PRINT, yyout);} //NULL
                    | "," indexedelem com_indexedelem_opt {$$ = manage_comindexedelemopt_comma_indexedelem_comindexedelemopt(DEBUG_PRINT, yyout, $2, $3);}
                    ;

block           : "{" {increase_scope(&scope); 
                    if(is_function_block){          
                        in_function_tail = SSL_Push(in_function_tail,1);
                        is_function_block=0;
                    }
                    else
                        in_function_tail = SSL_Push(in_function_tail,0);
                        }     
                                stmtList "}" {
                                                                symbol_table_hide(symTable,scope);
                                                                decrease_scope(&scope);
                                                                in_function_tail = SSL_Pop(in_function_tail);
                                                                fprintf(yyout, MAG "Detected :" RESET"{ stmtList }"CYN" ->"RESET" block \n");
                                                                $$ = $3;
                                                             }
                | "{" {increase_scope(&scope); 
                    if(is_function_block){          
                        in_function_tail = SSL_Push(in_function_tail,1);
                        is_function_block=0;
                    }
                    else
                        in_function_tail = SSL_Push(in_function_tail,0);
                        }     
                             "}" {
                                symbol_table_hide(symTable,scope);
                                decrease_scope(&scope);
                                in_function_tail = SSL_Pop(in_function_tail);
                                fprintf(yyout, MAG "Detected :" RESET"{  }"CYN" ->"RESET" block \n");
                                $$ = make_stmt();
                                }
                                
                ;

stmtList        : stmt           {manage_stmtList_stmt        (DEBUG_PRINT, yyout); $$ = $1; }
                | stmtList stmt  {manage_stmtList_stmt_stmtList(DEBUG_PRINT, yyout);
                                 $$ = make_stmt();
                                 if($1 != NULL && $2 != NULL) {
                                    $$->break_list   = merge_list($1->break_list, $2->break_list); 
                                    $$->cont_list    = merge_list($1->cont_list , $2->cont_list );
                                 }
                                 }

                ;

                /*Please for the shake of our sanity leave that as it is.*/                                                           
funcdef         : funcprefix                            
                                 "("                    {   increase_scope(&scope); 
                                                            unsigned int *p_x = (unsigned int*)malloc(sizeof(unsigned int));
                                                            *p_x = currScopeOffset(); 
                                                            if(!scope_offset_stack) scope_offset_stack = new_stack(); 
                                                            push(scope_offset_stack,p_x); 
                                                            enterScopeSpace(); 
                                                            resetFormalArgsOffset();
                                                        } 
                                    idlist ")"          {
                                                        flip_formal_offsets();
                                                        decrease_scope(&scope); enterScopeSpace(); resetFunctionLocalsOffset();
                                                        return_flag++;
                                                        is_function_block=1;
                                                        is_function_active++;
                                                        if(!loop_flag_stack) loop_flag_stack = new_stack();
                                                        int* loop_flag_ptr = malloc(sizeof(int));
                                                        *loop_flag_ptr = loop_flag;
                                                        push(loop_flag_stack,loop_flag_ptr);
                                                        loop_flag = 0;
                                                        } 
                                               block    {
                                                            fprintf(yyout, MAG "Detected :" RESET"funcprefix ( idlist ) block"CYN" ->"RESET" funcdef \n"); 
                                                            formal_flag = 0; //reset flag
                                                            return_flag--;
                                                            is_function_active--;
                                                            loop_flag = *(int*)pop(loop_flag_stack);

                                                //An einai null paei na pei oti einai i periptwsi pou uparxei idi sunartisi me auto to onoma (i lib) kai epomenos to agnooume (glitonei kai to seg :D)
                                                            if($1 != NULL) $1->totalLocals = currScopeOffset(); 
                                                            exitScopeSpace();
                                                            restoreCurrScopeOffset(*(unsigned int *)pop(scope_offset_stack));

                                                            if($$ != NULL) emit(funcend, NULL, NULL, new_lvalue_expr($$), -1, yylineno);
                                                            patchLabel(*(unsigned int *)pop(quad_stack), nextQuadLabel());

                                                            void *ret_s, *ret_s_s;
                                                            ret_s = pop(ret_stack);
                                                            while ( (ret_s_s = pop(ret_s) ))
                                                                    patchLabel( *(unsigned int *)ret_s_s, (nextQuadLabel()-1) );
                                                         }
                                                                                                             
                                                                                            
                ;

funcprefix : FUNCTION id_opt {
                            fprintf(yyout, MAG "Detected :" RESET"FUNCTION id_opt "CYN" ->"RESET" funcprefix \n"); 
                            if(!func_line_stack){func_line_stack=new_stack();}  
                            unsigned int* tmp_line = malloc(sizeof(unsigned int)); 
                            *tmp_line = yylineno;
                            push(func_line_stack,tmp_line);
                            //Kanoume check edw gia na settaroume to flag stin periptwsi pou i sunartisi uparxei (i einai lib)
                            check_if_declared(symTable,$2,scope);
                            //Kanoume to manage edw giati olokliros o kanonas anagetai otan kleisei to block
                            //alla emeis theloume na mpenei sto symbol table molis tin doume
                            $$ = manage_funcdef(symTable, $2, scope,*(unsigned int *)pop(func_line_stack)); 

                            if(!ret_stack) ret_stack = new_stack();
                            push(ret_stack,new_stack());    //Stack of stacks for return quads.
                            
                            if(!quad_stack) quad_stack = new_stack();
                            unsigned int *p_quad = (unsigned int*)malloc(sizeof(unsigned int));
                            *p_quad = currQuad; 
                            push(quad_stack, p_quad);
                            emit(jump, NULL, NULL, NULL, -1, yylineno);
                            if($$ != NULL) 
                                emit(funcstart, NULL, NULL, new_lvalue_expr($$), -1, yylineno);
                            }
                            ;

id_opt  : /* empty */ { //giving a name to anonymous functions
                        fprintf(yyout, MAG "Detected :" RESET"id_opt "YEL" (empty) "RESET"\n"); 
                        char buffer[255]; 
                        sprintf(buffer, "_anonymous_f%d", anonym_func_cnt++); 
                        $$ = strdup(buffer); 
                    }
        | IDENT       {fprintf(yyout, MAG "Detected :" RESET"%s"CYN" -> "RESET"IDENT \n",yylval.stringVal);}
        ;

const           : INTCONST  {fprintf(yyout, MAG "Detected :" RESET"%d"CYN"-> "RESET"INTCONST"CYN"-> "RESET"const \n",yylval.intVal); $$ = new_const_num((double)$1);}
                | REALCONST {fprintf(yyout, MAG "Detected :" RESET"%lf"CYN"-> "RESET"REALCONST"CYN"-> "RESET"const \n",yylval.realVal); $$ = new_const_num($1);}
                | STRING    {fprintf(yyout, MAG "Detected :" RESET"%s"CYN"-> "RESET"STRING"CYN"-> "RESET"const \n",yylval.stringVal); $$ = new_const_string($1);}
                | TRUE      {fprintf(yyout, MAG "Detected :" RESET"TRUE"CYN"-> "RESET"const \n"); $$ = new_const_bool(1);}
                | FALSE     {fprintf(yyout, MAG "Detected :" RESET"FALSE"CYN"-> "RESET"const \n"); $$ = new_const_bool(0);}
                | NIL       {fprintf(yyout, MAG "Detected :" RESET"NIL"CYN"-> "RESET"const \n"); $$ = new_const_nil();}
                ;

idlist          : /* empty */          {fprintf(yyout, MAG "Detected :" RESET"idlist"YEL" (empty)"RESET"\n");}
                | IDENT com_id_opt     {fprintf(yyout, MAG "Detected :" RESET"IDENT com_id_opt \n"); manage_formal_id(symTable, $1, scope, yylineno);}
                ;

com_id_opt      : /* empty */          {fprintf(yyout, MAG "Detected :" RESET"com_id_opt"YEL" (empty)"RESET"\n");}
                | "," IDENT com_id_opt {fprintf(yyout, MAG "Detected :" RESET", IDENT com_id_opt \n"); manage_formal_id(symTable, $2, scope, yylineno);}
                ;

ifstmt          : ifprefix stmt %prec LP_ELSE   {$$ = manage_ifstmt     (DEBUG_PRINT, yyout, $1, $2, scope, yylineno);}
                | ifprefix stmt elseprefix stmt {$$ = manage_ifstmt_else(DEBUG_PRINT, yyout, $1, $2, $3, $4, scope, yylineno);}
                ;

ifprefix        : IF "(" expr ")" {short_circuit_emits($3,yylineno,scope); $$ = manage_ifprefix(DEBUG_PRINT, yyout, $3, scope, yylineno);}

elseprefix      : ELSE {$$ = manage_elseprefix(DEBUG_PRINT, yyout, scope, yylineno);}
                ;

whilestmt       : whilestart whilecond  { if(!loop_flag_stack) loop_flag_stack = new_stack();
                                          int* loop_flag_ptr = malloc(sizeof(int));
                                          *loop_flag_ptr = loop_flag;
                                          push(loop_flag_stack,loop_flag_ptr);
                                          loop_flag = 1;
                                        } 
                                        loopstmt{   loop_flag = *(int*)pop(loop_flag_stack);
                                                    emit(jump, NULL, NULL, NULL, $1, yylineno);
                                                    patchLabel($2, nextQuadLabel());
                                                    patch_list($4->break_list, nextQuadLabel());
                                                    patch_list($4->cont_list , $1);
                                                    fprintf(yyout, MAG "Detected :" RESET"WHILE ( expr ) stmt"CYN"-> "RESET"whilestmt \n");
                                                }
                ;

whilestart      : WHILE {$$ = nextQuadLabel();}
                ;

whilecond       : "(" expr ")"  {short_circuit_emits($2,yylineno,scope);
                                 emit(if_eq, $2, new_const_bool(1), NULL, nextQuadLabel()+2, yylineno);  
                                 $$ = nextQuadLabel();
                                 emit(jump, NULL, NULL, NULL, 0, yylineno);
                                }
                ;

forstmt         : forprefix N1 elist ")" N2 {   if(!loop_flag_stack) loop_flag_stack = new_stack();
                                                int* loop_flag_ptr = malloc(sizeof(int));
                                                *loop_flag_ptr = loop_flag;
                                                push(loop_flag_stack,loop_flag_ptr);
                                                loop_flag = 1;
                                            }  
                                            loopstmt N3 {  loop_flag = *(int*)pop(loop_flag_stack);
                                                    fprintf(yyout, MAG "Detected :" RESET"FOR ( elist ; expr ; elist ) stmt"CYN"-> "RESET"forstmt \n");

                                                    patchLabel($1->enter, $5+1);     //true    jump
                                                    patchLabel($2, nextQuadLabel()); //false   jump
                                                    patchLabel($5, $1->test);        //loop    jump
                                                    patchLabel($8, $2+1);            //closure jump

                                                    patch_list($7->break_list, nextQuadLabel());
                                                    patch_list($7->cont_list, $2+1);
                                                }
                    ; 

forprefix       : FOR "(" elist ";" M expr ";" {
                                            short_circuit_emits($6,yylineno,scope);
                                            Forprefix* forprefix = (Forprefix*)malloc(sizeof(Forprefix));
                                            forprefix->test  = $5;
                                            forprefix->enter = nextQuadLabel();
                                            
                                            emit(if_eq, $6, new_const_bool(1), NULL, 0, yylineno);

                                            $$ = forprefix;
                                        }
                ;
                    

N1              : {$$ = nextQuadLabel(); emit(jump, NULL, NULL, NULL, 0, yylineno);} 
                ;

N2              : {$$ = nextQuadLabel(); emit(jump, NULL, NULL, NULL, 0, yylineno);} 
                ;

N3              : {$$ = nextQuadLabel(); emit(jump, NULL, NULL, NULL, 0, yylineno);} 
                ;      

M               : {$$ = nextQuadLabel();}
                ;

loopstart       : {++loop_counter;}
                ;

loopend         : {--loop_counter;}
                ;

loopstmt        : loopstart stmt loopend {$$ = $2; fprintf(yyout, MAG "Detected :" RESET"stmt"CYN"-> "RESET"loopstmt \n");}

break           : BREAK    ";" {$$ = make_stmt(); 
                                $$->break_list = new_list(nextQuadLabel()); 
                                emit(jump, NULL, NULL, NULL, 0, yylineno);
                               }
                ;

continue        : CONTINUE ";" {$$ = make_stmt(); 
                                $$->cont_list  = new_list(nextQuadLabel());
                                emit(jump, NULL, NULL, NULL, 0, yylineno);
                               }
                ;

returnstmt      : RETURN expr_opt ";" {fprintf(yyout, MAG "Detected :" RESET"RETURN expr_opt ;"CYN"-> "RESET"returnstmt \n");
                                        short_circuit_emits($2,yylineno,scope);
                                        manage_return(yylineno, return_flag, $2, ret_stack);}
                ;

expr_opt        : /* empty */ {fprintf(yyout, MAG "Detected :" RESET"expr_opt "YEL" (empty)"RESET"\n"); $$ = NULL;}
                | expr        {fprintf(yyout, MAG "Detected :" RESET"expr \n");}
                ;

%%