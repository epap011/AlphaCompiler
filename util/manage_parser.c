#include <string.h>
#include "symbol_table.h"
#include "yacc_util.h"
#include "manage_parser.h"
#include "quad.h"

#define RED   "\x1b[31m"
#define GRN   "\x1b[32m"
#define YEL   "\x1b[33m"
#define BLU   "\x1b[34m"
#define MAG   "\x1b[35m"
#define CYN   "\x1b[36m"
#define RESET "\x1b[0m"

#define FUNC 0
#define VAR  1

#define NUM_OF_LIB_FUNC 12

int formal_flag = 0;    //Usage: if a function is already declared (or is a built-in ), we don't want to insert it in the symbol table and wee need this flag to skip the formal arguments as well
extern FILE * out_file;

char lib_functions[NUM_OF_LIB_FUNC][19] = {
    "print",
    "input",
    "objectmemberkeys",
    "objecttotalmembers",
    "objectcopy",
    "totalarguments",
    "argument",
    "typeof",
    "strtonum",
    "sqrt",
    "cos",
    "sin"
};

void insert_lib_functions(SymbolTable * symTable){

    for(int i = 0; i < NUM_OF_LIB_FUNC; i++) {   
        char* name     = strdup(lib_functions[i]);    
        Symbol* symbol = symbol_create(name, 0, 0, LIBFUNC, 0,libraryfunc_s,-1,-1);
        symbol_table_insert(symTable, symbol);
    }
}

//Move to another file?
const char* str_type(enum SymbolType type){
    switch (type){
        case USERFUNC:  return "user function";
        case LIBFUNC:   return "library function";
        case GLOBAL:    return "global variable";
        case FORMAL:    return "formal variable";
        case _LOCAL:    return "local variable";    
        
        default:       return "INVALID";
    }
}

void symbol_table_print(SymbolTable* symTable){

    for(int i = 0; i < symTable->scope_size; i++){
        Symbol* current_symbol = symTable->first_symbol_scopes[i];
        if(current_symbol == NULL) continue;

        fprintf(out_file,"\n-------- Scope #%d --------\n\n", i);

        while(current_symbol != NULL){
            if(current_symbol->type == var_s)
                fprintf(out_file,"\""YEL"%s"RESET"\" "BLU"["RESET"%s"BLU"]"RESET" (line: "GRN"%d"RESET") (scope "GRN"%d"RESET") (space: "GRN"%d"RESET") (offset "GRN"%d"RESET") \n", current_symbol->name, str_type(current_symbol->symbol_type), current_symbol->line, current_symbol->scope, current_symbol->space, current_symbol->offset);
            else
                fprintf(out_file,"\""YEL"%s"RESET"\" "BLU"["RESET"%s"BLU"]"RESET" (line: "GRN"%d"RESET") (scope "GRN"%d"RESET") (iaddress "GRN"%d"RESET") (totalLocals "GRN"%d"RESET") \n", current_symbol->name, str_type(current_symbol->symbol_type), current_symbol->line, current_symbol->scope, current_symbol->iaddress, current_symbol->totalLocals);
            current_symbol = current_symbol->next_symbol_of_same_scope;
        }
    }
    fprintf(out_file,"\n\n");
}

void increase_scope(unsigned int* scope){
    (*scope)++;
}

void decrease_scope(unsigned int* scope){
    (*scope)--;
}

//Checks if a function with that name is already declared (also checks if it is a library function)
void check_if_declared(SymbolTable* symTable, const char* id, unsigned int scope){
    if(id[0] == '_') return; //If it is an unonymous function, don't check
    
    Symbol* tmp_symbol = symbol_table_scope_lookup(symTable, id, scope);

    if(tmp_symbol != NULL){
        formal_flag = 1;
        return;
    }
    
    if(is_id_built_in_function(id))
        formal_flag = 1;
        
}

int is_id_built_in_function(const char* id){
    for(int i = 0; i < NUM_OF_LIB_FUNC; i++){
        if(strcmp(id, lib_functions[i]) == 0){
            return 1;
        }
    }
    return 0;
}

Symbol* manage_funcdef(SymbolTable* symTable, char* id, unsigned int scope, unsigned int line){

   if(is_id_built_in_function(id)) {
        fprintf(out_file,RED"Error:"RESET" Cannot shadow library function \""YEL"%s"RESET"\" (line: "GRN"%d"RESET") \n", id, line);
        return NULL;
   }
   
   Symbol* tmp_symbol = symbol_table_scope_lookup(symTable, id, scope);

    if(tmp_symbol != NULL){
        if(tmp_symbol->symbol_type == LIBFUNC)
            fprintf(out_file,RED"Error:"RESET" Cannot shadow library function \""YEL"%s"RESET"\" (line: "GRN"%d"RESET") \n", id, line);
        else
            fprintf(out_file,RED"Error:"RESET" Function \""YEL"%s"RESET"\" already declared in scope "GRN"%d"RESET" (line: "GRN"%d"RESET") \n", id, scope,line);

        return NULL;
    }

    char* name     = strdup(id);
    Symbol* symbol = symbol_create(name, scope, line, USERFUNC, FUNC, programfunc_s, -1, -1);
    
    //phase 3 quad number
    symbol->iaddress    = nextQuadLabel();

    symbol_table_insert(symTable, symbol);
    return symbol;
}

void manage_formal_id(SymbolTable* symTable, const char* id, unsigned int scope, unsigned int line){

    if(formal_flag)
        return;
         
    if(is_id_built_in_function(id)) {
            fprintf(out_file,RED"Error:"RESET" Cannot declare variable \""YEL"%s"RESET"\", a library function exist with that name (line: "GRN"%d"RESET") \n", id, line);
            return;
        }

    if(symbol_table_scope_lookup(symTable, id, scope) != NULL){
        fprintf(out_file,RED"Error:"RESET" Formal variable \""YEL"%s"RESET"\" already declared in function (line: "GRN"%d"RESET")\n", id, line);
        return;
    } 

    char* name     = strdup(id);
    Symbol* symbol = symbol_create(name, scope, line, FORMAL, VAR, var_s, currScopeSpace(), currScopeOffset());
    incCurrScopeOffset();

    symbol_table_insert(symTable, symbol);

}

int check_lvalue(SymbolTable* symTable, const char* id, unsigned int scope, unsigned int line){
    
    for (int i = 0; i <= scope; i++){   //we need to check all scopes 
        Symbol *tmp_symbol = symbol_table_scope_lookup(symTable, id, i);
        if(tmp_symbol != NULL && (tmp_symbol->symbol_type == USERFUNC || tmp_symbol->symbol_type == LIBFUNC)){
            fprintf(out_file,RED "Error:" RESET " Cannot apply arithmetic operation on function \"" YEL "%s" RESET "\" (line: " GRN "%d" RESET ")\n", id, line);
            return 1;
        }
        else        
            return 0;
    }
    return 0;
}

void manage_func_call(SymbolTable* symTable, const char* id, unsigned int scope, unsigned int line) {

    //check if the function exists
    if(is_id_built_in_function(id)) return;

    for(int i = 0; i <= scope; i++) {
        Symbol* tmp_symbol = symbol_table_scope_lookup(symTable, id, i); 
        if(tmp_symbol != NULL) 
            return;
    }

    fprintf(out_file,RED"Error:"RESET" Function \""YEL"%s"RESET"\" doesn't exist (line: "GRN"%d"RESET")\n", id, line);
    hide_symbol_on_scope(symTable, id, scope);
}

int hide_symbol_on_scope(SymbolTable* symTable, const char* id, unsigned int scope) {
    Symbol* tmp_symbol = symbol_table_scope_lookup(symTable, id, scope);
    if(tmp_symbol != NULL) {
        tmp_symbol->is_active = 0;
        //must decrement anonym_var_counter when hiding a hidden var symbol
        return 1;
    }

    return 0;
}

void manage_return(int line, int flag){
    if(!flag)
        fprintf(out_file,RED"Error:"RESET" \""YEL"return"RESET"\" should be part of a function (line: "GRN"%d"RESET")\n", line);
}

void manage_program (int debug, FILE* out) {
    if(debug) fprintf(out, MAG "Detected :" RESET"program stmtList \n");
}

void manage_stmt_expr(int debug, FILE* out) {
    if(debug) fprintf(out, MAG "Detected :" RESET"expr;"CYN" ->"RESET" stmt \n");
}

void manage_stmt_ifstmt(int debug, FILE* out) {
    if(debug) fprintf(out, MAG "Detected :" RESET"ifstmt"CYN" ->"RESET" stmt \n");
}

void manage_stmt_whilestmt(int debug, FILE* out) {
    if(debug) fprintf(out, MAG "Detected :" RESET"whilestmt"CYN" ->"RESET" stmt \n");
}

void manage_stmt_forstmt(int debug, FILE* out) {
    if(debug) fprintf(out, MAG "Detected :" RESET"forstmt"CYN" ->"RESET" stmt \n");
}

void manage_stmt_returnstmt(int debug, FILE* out) {
    if(debug) fprintf(out, MAG "Detected :" RESET"returnstmt"CYN" ->"RESET" stmt \n");
}

void manage_stmt_block     (int debug, FILE* out) {
    if(debug) fprintf(out, MAG "Detected :" RESET"block"CYN" ->"RESET" stmt \n");
}

void manage_stmt_break(int debug, FILE* out, int line, int flag){
    if(debug) fprintf(yyout, MAG "Detected :" RESET"BREAK ;"CYN""RESET"-> stmt \n");
    if(!flag)
        fprintf(out_file,RED"Error:"RESET" \""YEL"break; "RESET"\" should be part of a for/while loop (line: "GRN"%d"RESET")\n", line);
}

void manage_stmt_continue(int debug, FILE* out, int line, int flag){
    if(debug) fprintf(yyout, MAG "Detected :" RESET"CONTINUE"CYN""RESET"-> while;\n");
    if(!flag)
        fprintf(out_file,RED"Error:"RESET" \""YEL"continue"RESET"\" should be part of a for/while loop (line: "GRN"%d"RESET")\n", line);
}

void manage_stmt_funcdef   (int debug, FILE* out) {
    if(debug) fprintf(out, MAG "Detected :" RESET"funcdef"CYN" ->"RESET" stmt \n");
}

void manage_stmt_semicolon (int debug, FILE* out) {
    if(debug) fprintf(out, MAG "Detected :" RESET";"CYN""RESET" -> stmt \n");
}

void manage_expr_assignexpr(int debug, FILE* out) {
    if(debug) fprintf(yyout, MAG "Detected :" RESET"assignexpr"CYN" ->"RESET" expr \n");
}

void manage_expr_term(int debug, FILE* out) {
    if(debug) fprintf(yyout, MAG "Detected :" RESET"term"CYN" ->"RESET" expr \n");
}

/**Arithmetic / relop expressions here**/

expr* manage_arith_relop_emits(expr* expr1, expr* expr2, unsigned int scope, unsigned int line, enum iopcode op){
    expr* result;
    if ( (expr1->type == var_e || expr1->type == constnum_e || expr1->type == constbool_e) &&
         (expr2->type == var_e || expr2->type == constnum_e || expr1->type == constbool_e) ){ //check if arithmetic operands are variables or constants
        result = new_lvalue_expr(symbol_table_insert(symTable, symbol_create(str_int_merge("_t",anonym_var_cnt++), scope, line, scope == 0 ? GLOBAL : _LOCAL, VAR, var_s, currScopeSpace(), currScopeOffset())));
        incCurrScopeOffset();
        emit(op, expr1, expr2, result, -1, line);
        return result;
    }
    return NULL;
}

expr* manage_expr_plus_expr(int debug, FILE* out, expr* expr1, expr* expr2, unsigned int scope, unsigned int line) {
    if(debug) fprintf(out, MAG "Detected :" RESET"expr + expr"CYN" ->"RESET" expr \n");

    return manage_arith_relop_emits(expr1, expr2, scope, line, add);
}

expr* manage_expr_mul_expr(int debug, FILE* out, expr* expr1, expr* expr2, unsigned int scope, unsigned int line) {
    if(debug) fprintf(out, MAG "Detected :" RESET"expr * expr"CYN" ->"RESET" expr \n");
    
    return manage_arith_relop_emits(expr1, expr2, scope, line, mul);
}

expr* manage_expr_minus_expr(int debug, FILE* out, expr* expr1, expr* expr2, unsigned int scope, unsigned int line) {
    if(debug) fprintf(out, MAG "Detected :" RESET"expr - expr"CYN" ->"RESET" expr \n");

    return manage_arith_relop_emits(expr1, expr2, scope, line, sub);
}

expr* manage_expr_div_expr(int debug, FILE* out, expr* expr1, expr* expr2, unsigned int scope, unsigned int line) {
    if(debug) fprintf(out, MAG "Detected :" RESET"expr / expr"CYN" ->"RESET" expr \n");

    return manage_arith_relop_emits(expr1, expr2, scope, line, i_div);
}

expr* manage_expr_mod_expr(int debug, FILE* out, expr* expr1, expr* expr2, unsigned int scope, unsigned int line) {
    if(debug) fprintf(out, MAG "Detected :" RESET"expr MOD expr"CYN" ->"RESET" expr \n");
 
    return manage_arith_relop_emits(expr1, expr2, scope, line, mod);
}

expr* manage_expr_eq_expr(int debug, FILE* out, expr* expr1, expr* expr2, unsigned int scope, unsigned int line) {
    if(debug) fprintf(out, MAG "Detected :" RESET"expr == expr"CYN" ->"RESET" expr \n");

    return manage_arith_relop_emits(expr1, expr2, scope, line, if_eq);
}

expr* manage_expr_neq_expr(int debug, FILE* out, expr* expr1, expr* expr2, unsigned int scope, unsigned int line) {
    if(debug) fprintf(out, MAG "Detected :" RESET"expr != expr"CYN" ->"RESET" expr \n");
    
    return manage_arith_relop_emits(expr1, expr2, scope, line, if_noteq);
}

expr* manage_expr_gt_expr(int debug, FILE* out, expr* expr1, expr* expr2, unsigned int scope, unsigned int line) {
    if(debug) fprintf(out, MAG "Detected :" RESET"expr > expr"CYN" ->"RESET" expr \n");
   
    return manage_arith_relop_emits(expr1, expr2, scope, line, if_greater);
}

expr* manage_expr_lt_expr(int debug, FILE* out, expr* expr1, expr* expr2, unsigned int scope, unsigned int line) {
    if(debug) fprintf(out, MAG "Detected :" RESET"expr < expr"CYN" ->"RESET" expr \n");
   
    return manage_arith_relop_emits(expr1, expr2, scope, line, if_less);
}

expr* manage_expr_gte_expr(int debug, FILE* out, expr* expr1, expr* expr2, unsigned int scope, unsigned int line) {
    if(debug) fprintf(out, MAG "Detected :" RESET"expr >= expr"CYN" ->"RESET" expr \n");
  
    return manage_arith_relop_emits(expr1, expr2, scope, line, if_greatereq);
}

expr* manage_expr_lte_expr(int debug, FILE* out, expr* expr1, expr* expr2, unsigned int scope, unsigned int line) {
    if(debug) fprintf(out, MAG "Detected :" RESET"expr <= expr"CYN" ->"RESET" expr \n");
    
    return manage_arith_relop_emits(expr1, expr2, scope, line, if_lesseq);
}

expr* manage_expr_and_expr(int debug, FILE* out, expr* expr1, expr* expr2, unsigned int scope, unsigned int line) {
    if(debug) fprintf(out, MAG "Detected :" RESET"expr AND expr"CYN" ->"RESET" expr \n");
 
    return manage_arith_relop_emits(expr1, expr2, scope, line, and);
}

expr* manage_expr_or_expr(int debug, FILE* out, expr* expr1, expr* expr2, unsigned int scope, unsigned int line) {
    if(debug) fprintf(out, MAG "Detected :" RESET"expr OR expr"CYN" ->"RESET" expr \n");
    
    return manage_arith_relop_emits(expr1, expr2, scope, line, or); 
}
/**End of Arithmetic / relop**/

void manage_term_lpar_expr_rpar(int debug, FILE* out) {
    if(debug) fprintf(out, MAG "Detected :" RESET"( expr )"CYN" ->"RESET" term \n");
}

void manage_term_uminus_expr(int debug, FILE* out) {
    if(debug) fprintf(out, MAG "Detected :" RESET"UMINUS expr"CYN" ->"RESET" term \n");
}

void manage_term_not_expr(int debug, FILE* out) {
    if(debug) fprintf(out, MAG "Detected :" RESET"NOT expr"CYN" ->"RESET" term \n");
}

void manage_term_plusplus_lvalue(int debug, FILE* out, SymbolTable* symTable, expr* expr, unsigned int scope, unsigned int line) {
    if(debug) fprintf(out, MAG "Detected :" RESET"++lvalue"CYN" ->"RESET" term \n");
    if(expr != NULL) check_lvalue(symTable, expr->sym->name, scope, line); //Gia tin fasi 3 -> an epistrepsei 1 paei na pei oti einai function kai den kanoume prakseis
}

void manage_term_lvalue_plusplus(int debug, FILE* out, SymbolTable* symTable, expr* expr, unsigned int scope, unsigned int line) {
    if(debug) fprintf(out, MAG "Detected :" RESET"lvalue++"CYN" ->"RESET" term \n");
    if(expr != NULL) check_lvalue(symTable, expr->sym->name, scope, line); //Gia tin fasi 3 -> an epistrepsei 1 paei na pei oti einai function kai den kanoume prakseis
}

void manage_term_minusminus_lvalue(int debug, FILE* out, SymbolTable* symTable, expr* expr, unsigned int scope, unsigned int line) {
    if(debug) fprintf(out, MAG "Detected :" RESET"--lvalue"CYN" ->"RESET" term \n");
    if(expr != NULL) check_lvalue(symTable, expr->sym->name, scope, line); //Gia tin fasi 3 -> an epistrepsei 1 paei na pei oti einai function kai den kanoume prakseis
}

void manage_term_lvalue_minusminus(int debug, FILE* out, SymbolTable* symTable, expr* expr, unsigned int scope, unsigned int line) {
    if(debug) fprintf(out, MAG "Detected :" RESET"lvalue--"CYN" ->"RESET" term \n");
    if(expr != NULL) check_lvalue(symTable, expr->sym->name, scope, line); //Gia tin fasi 3 -> an epistrepsei 1 paei na pei oti einai function kai den kanoume prakseis
}

void manage_term_primary(int debug, FILE* out) {
    if(debug) fprintf(out, MAG "Detected :" RESET"primary"CYN" ->"RESET" term \n");
}

expr* manage_assignexpr_lvalue_assign_expr(int debug, FILE* out, SymbolTable* symTable, expr* lvalue, expr* expr1, unsigned int scope, unsigned int line) {
    if(debug) fprintf(out, MAG "Detected :" RESET"lvalue = expr"CYN" ->"RESET" assignexpr \n");
    if(lvalue != NULL) {
        if(is_id_built_in_function(lvalue->sym->name)){
            fprintf(out_file,RED"Error:"RESET" Cannot assign to a library function \""YEL"%s"RESET"\" (line: "GRN"%d"RESET") \n", lvalue->sym->name, line);
            return NULL;
        }

        for(int i = scope; i >= 0; i--) {
            Symbol* tmp_symbol = symbol_table_scope_lookup(symTable, lvalue->sym->name, i); 
            if(tmp_symbol != NULL){
                if( tmp_symbol->symbol_type == USERFUNC) {
                    fprintf(out_file,RED"Error:"RESET" Cannot assign to a function \""YEL"%s"RESET"\" (line: "GRN"%d"RESET") \n", lvalue->sym->name, line);
                    return NULL;
                }
                else{
                    emit(assign, expr1, NULL, lvalue, -1, line);

                    //Creating an extra hidden var to store lvalue (FAQ : 18)
                    expr* result;
                    result = new_lvalue_expr(symbol_table_insert(symTable, symbol_create(str_int_merge("_t",anonym_var_cnt++), scope, line, scope == 0 ? GLOBAL : _LOCAL, VAR, var_s, currScopeSpace(), currScopeOffset())));
                    incCurrScopeOffset();
                    emit(assign, lvalue, NULL, result, -1, line);

                    lvalue->hidden_var = result; //making the lvalue point to the hidden var (to find it when we need it)

                    return lvalue;
                }
            }
        }
    }
    return NULL;
}

void manage_primary_lvalue(int debug, FILE* out) {
    if(debug) fprintf(out, MAG "Detected :" RESET"lvalue"CYN" ->"RESET" primary \n");
}

void manage_primary_call(int debug, FILE* out) {
    if(debug) fprintf(out, MAG "Detected :" RESET"call"CYN" ->"RESET" primary \n");
}

void manage_primary_objectdef(int debug, FILE* out) {
    if(debug) fprintf(out, MAG "Detected :" RESET"objectdef"CYN" ->"RESET" primary \n");
}

void manage_primary_lpar_funcdef_rpar(int debug, FILE* out) {
    if(debug) fprintf(out, MAG "Detected :" RESET"( funcdef )"CYN" ->"RESET" primary \n");
}

void manage_primary_const(int debug, FILE* out) {
    if(debug) fprintf(out, MAG "Detected :" RESET"const"CYN" ->"RESET" primary \n");
}

expr* manage_lvalue_ident(int debug, FILE* out, SymbolTable* symTable, char* id, enum SymbolType type, unsigned int scope, unsigned int line, ScopeStackList *tail) {
    
    if(debug) fprintf(out, MAG "Detected :" RESET"%s"CYN" ->"RESET" IDENT"CYN" ->"RESET" lvalue \n",id);

    Symbol* sym = symbol_table_scope_lookup(symTable, id, scope); //check current scope
    if(sym != NULL) {
        return new_lvalue_expr(sym);
    }

    //flag purpose: check if a variable with the same name is declared in a higher scope
    int flag = 0;
    ScopeStackList* tmp = tail;
    if(scope > 0) { //check all other scopes except global
        for(int i = scope - 1; i > 0; i--) {
            Symbol* tmp_symbol = symbol_table_scope_lookup(symTable, id, i);
            
            if(tmp != NULL) flag = tmp->flag;
            
            if(tmp_symbol != NULL && tmp_symbol->is_variable) {
                if(flag == 1){
                    fprintf(out_file,RED"Error:"RESET" Variable \""YEL"%s"RESET"\" is not accessible (line: "GRN"%d"RESET")\n", id, line);        
                    return NULL;
                }
                else {
                    return new_lvalue_expr(tmp_symbol);
                }
            }
            if(tmp != NULL) tmp = tmp->prev;
        }
    }

    sym = symbol_table_scope_lookup(symTable, id, 0);//check global scope
    if(sym != NULL) new_lvalue_expr(sym);  

    char* name     = strdup(id);
    Symbol* symbol = symbol_create(name, scope, line, type, VAR, var_s, currScopeSpace(), currScopeOffset());
    incCurrScopeOffset();
    symbol_table_insert(symTable, symbol);

    return new_lvalue_expr(symbol);
}

expr* manage_lvalue_local_ident(int debug, FILE* out, SymbolTable* symTable, char* id, unsigned int scope, unsigned int line) {
    if(debug) fprintf(out, MAG "Detected :" RESET"local \"%s\""CYN" ->"RESET" LOCAL IDENT"CYN" ->"RESET" lvalue \n", id);

    Symbol* sym = symbol_table_scope_lookup(symTable, id, scope);
    if(sym != NULL) return new_lvalue_expr(sym);

    if(is_id_built_in_function(id)) {
        fprintf(out_file,RED"Error:"RESET" Cannot declare (shadow) Variable with library function name \""YEL"%s"RESET"\" (line: "GRN"%d"RESET") \n", id,line);
        return NULL;
    }

    char* name     = strdup(id);
    Symbol* symbol = symbol_create(name, scope, line, scope == 0 ? GLOBAL : _LOCAL, VAR, var_s, currScopeSpace(), currScopeOffset());
    incCurrScopeOffset();

    symbol_table_insert(symTable, symbol);

    return new_lvalue_expr(symbol);
}

expr* manage_lvalue_global_ident(int debug, FILE* out, SymbolTable* symTable, char* id, unsigned int scope, unsigned int line) {
    if(debug) fprintf(out, MAG "Detected :" RESET"::%s"CYN" ->"RESET" ::IDENT"CYN" ->"RESET" lvalue \n", id);

    Symbol* sym =  symbol_table_scope_lookup(symTable, id, 0);
    if(sym != NULL) return new_lvalue_expr(sym);
    fprintf(out_file,RED"Error:"RESET" Variable \""YEL"%s"RESET"\" doesn't exist in global scope (line: "GRN"%d"RESET") \n", id, line);

    return NULL;
}

expr* manage_lvalue_member(int debug, FILE* out, expr* member) {
    if(debug) fprintf(out, MAG "Detected :" RESET"member"CYN" ->"RESET" lvalue \n");
    return member;
}

expr* manage_memeber_lvalue_dot_ident(int debug, FILE* out, expr* lvalue, int* normalcall_skip) {
    if(debug) fprintf(out, MAG "Detected :" RESET"lvalue .IDENT"CYN" ->"RESET" member \n");
    *normalcall_skip = 1;
    return NULL;
}

expr* manage_memeber_lvalue_lbr_expr_rbr(int debug, FILE* out, expr* lvalue, expr* expr1) {
    if(debug) fprintf(out, MAG "Detected :" RESET"lvalue [ expr ]"CYN" ->"RESET" member \n");
    return NULL;
}

expr* manage_member_call_dot_ident(int debug, FILE* out, expr* call, char* id, int* normalcall_skip) {
    if(debug) fprintf(out, MAG "Detected :" RESET"call . IDENT"CYN" ->"RESET" member \n");
    *normalcall_skip = 1;
    
    //keep in mind that this expression has only the name of the symbol and nothing else
    expr* e_for_name = (expr*)malloc(sizeof(expr));
    e_for_name->sym  = (Symbol*)malloc(sizeof(Symbol));
    e_for_name->sym->name = id;
    
    return e_for_name;
}

expr* manage_member_call_lbr_expr_rbr(int debug, FILE* out, expr* call, expr* expr1) {
    if(debug) fprintf(out, MAG "Detected :" RESET"call [ expr ]"CYN" ->"RESET" member \n");
    return NULL;
}

expr* manage_call_call_lpar_elist_rpar  (int debug, FILE* out) {
    if(debug) fprintf(yyout, MAG "Detected :" RESET"call ( elist )"CYN" ->"RESET" call \n");
    return NULL;
}

expr* manage_call_lvalue_callsuffix(int debug, FILE* out, SymbolTable* symTable, expr* lvalue, int* normalcall_skip, unsigned int scope, unsigned int line) {
    if(debug) fprintf(out, MAG "Detected :" RESET"lvalue callsuffix"CYN" ->"RESET" call \n");

    if(!normalcall_skip) {
        if(lvalue != NULL) {
            manage_func_call(symTable, lvalue->sym->name, scope, line);
        }
    }

    *normalcall_skip = 0;
    return NULL;
}

expr* manage_call_lpar_funcdef_rpar_lpar_elist_rpar(int debug, FILE* out) {
    if(debug) fprintf(out, MAG "Detected :" RESET"( funcdef ) ( elist )"CYN" ->"RESET" call \n");
    return NULL;
}

expr* manage_callsuffix_normcall  (int debug, FILE* out) {
    if(debug) fprintf(out, MAG "Detected :" RESET"normcall"CYN" ->"RESET" callsuffix \n");
    return NULL;
}

expr* manage_callsuffix_methodcall(int debug, FILE* out) {
    if(debug) fprintf(out, MAG "Detected :" RESET"methodcall"CYN" ->"RESET" callsuffix \n");
    return NULL;
}

expr* manage_normcall_lpar_elist_rpar(int debug, FILE* out) {
    if(debug) fprintf(out, MAG "Detected :" RESET"( elist )"CYN" ->"RESET" normcall \n");
    return NULL;
}

expr* manage_methodcall_ddot_ident_lpar_elist_rpar(int debug, FILE* out, int* normallcall_skip) {
    if(debug) fprintf(out, MAG "Detected :" RESET".. IDENT ( elist )"CYN" ->"RESET" methodcall \n");
    *normallcall_skip = 1;
    return NULL;
}

expr* manage_comexpropt_empty(int debug, FILE* out) {
    if(debug) fprintf(out, MAG "Detected :" RESET"com_expr_opt"YEL" (empty) "RESET"\n");
    return NULL;
}

expr* manage_comexpropt_comma_expr_comexpropt(int debug, FILE* out) {
    if(debug) fprintf(out, MAG "Detected :" RESET"COMMA expr com_expr_opt \n");
    return NULL;
}

expr* manage_objectdef_lbrace_indexed_rbrace(int debug, FILE* out) {
    if(debug) fprintf(out, MAG "Detected :" RESET"[ indexed ]"CYN" ->"RESET" objectdef \n");
    return NULL;
}

expr* manage_objectdef_lbrace_elist_rbrace  (int debug, FILE* out) {
    if(debug) fprintf(out, MAG "Detected :" RESET"[ elist ]"CYN" ->"RESET" objectdef \n");
    return NULL;
}

expr* manage_elist_empty(int debug, FILE* out) {
    if(debug) fprintf(out, MAG "Detected :" RESET"elist"YEL" (empty)"RESET"\n");
    return NULL;
}

expr* manage_elist_expr_comexpropt(int debug, FILE* out) {
    if(debug) fprintf(out, MAG "Detected :" RESET"expr com_expr_opt"CYN" ->"RESET" elist \n");
    return NULL;
}

expr* manage_indexed_indexedelem_comindexedelemopt(int debug, FILE* out) {
    if(debug) fprintf(out, MAG "Detected :" RESET"indexedelem com_indexedelem_opt"CYN" ->"RESET" indexed \n");
    return NULL;
}

expr* manage_indexedele_lcbrace_expr_colon_expr_rcbrace(int debug, FILE* out) {
    if(debug) fprintf(out, MAG "Detected :" RESET"{ expr : expr }"CYN" ->"RESET" indexedelem \n");
    return NULL;
}

expr* manage_comindexedelemopt_empty(int debug, FILE* out) {
    if(debug) fprintf(out, MAG "Detected :" RESET"com_indexedelem_opt "YEL"(empty)"RESET"\n");
    return NULL;
}

expr* manage_comindexedelemopt_comma_indexedelem_comindexedelemopt(int debug, FILE* out) {
    if(debug) fprintf(out, MAG "Detected :" RESET", indexedelem com_indexedelem_opt \n");
    return NULL;
}

expr* manage_stmtList_empty(int debug, FILE* out) {
    if(debug) fprintf(out, MAG "Detected :" RESET"stmtList"YEL" (empty)"RESET":\n");
    return NULL;
}

expr* manage_stmtList_stmt_stmtList(int debug, FILE* out) {
    if(debug) fprintf(out, MAG "Detected :" RESET"stmt stmtList"CYN" ->"RESET" stmtList \n");
    return NULL;
}