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

//Managing function from now on
Symbol*  manage_id(SymbolTable* symTable, char* id, enum SymbolType type, unsigned int scope, unsigned int line, ScopeStackList *tail){
        
        Symbol* sym = symbol_table_scope_lookup(symTable, id, scope);
        if(sym != NULL) return sym; //check current scope

        //flag purpose: check if a variable with the same name is declared in a higher scope
        int flag = 0;
        ScopeStackList* tmp  = tail;
        if(scope > 0) {                                     //check all other scopes except global
            for(int i = scope - 1; i > 0; i--) {
                Symbol* tmp_symbol = symbol_table_scope_lookup(symTable, id, i);
                
                if(tmp != NULL) flag = tmp->flag;
                
                if(tmp_symbol != NULL && tmp_symbol->is_variable) {
                    if(flag == 1){
                        fprintf(out_file,RED"Error:"RESET" Variable \""YEL"%s"RESET"\" is not accessible (line: "GRN"%d"RESET")\n", id, line);        
                        return NULL; //KEEP THAT IN MIND!!!!
                    }
                    else
                        return tmp_symbol;
                }
                if(tmp != NULL) tmp = tmp->prev;
            }
        }
        sym = symbol_table_scope_lookup(symTable, id, 0);//check global scope
        if(sym != NULL) return sym;  

        char* name     = strdup(id);
        Symbol* symbol = symbol_create(name, scope, line, type, VAR, var_s, currScopeSpace(), currScopeOffset());
        incCurrScopeOffset();

        symbol_table_insert(symTable, symbol);
        return symbol;
}

Symbol* manage_local_id(SymbolTable* symTable, const char* id, unsigned int scope, unsigned int line){

        Symbol* sym = symbol_table_scope_lookup(symTable, id, scope);
        if(sym != NULL) return sym;

        if(is_id_built_in_function(id)) {
            fprintf(out_file,RED"Error:"RESET" Cannot declare (shadow) Variable with library function name \""YEL"%s"RESET"\" (line: "GRN"%d"RESET") \n", id,line);
            return NULL;
        }

        char* name     = strdup(id);
        Symbol* symbol = symbol_create(name, scope, line, scope == 0 ? GLOBAL : _LOCAL, VAR, var_s, currScopeSpace(), currScopeOffset());
        incCurrScopeOffset();

        symbol_table_insert(symTable, symbol);

        return symbol;
}

Symbol* manage_global_id(SymbolTable* symTable, const char* id, unsigned int scope, unsigned int line){

        Symbol* sym =  symbol_table_scope_lookup(symTable, id, 0);
        if(sym != NULL) return sym;
        fprintf(out_file,RED"Error:"RESET" Variable \""YEL"%s"RESET"\" doesn't exist in global scope (line: "GRN"%d"RESET") \n", id, line);

        return NULL;
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

void manage_expr_plus_expr(int debug, FILE* out, expr* expr1, expr* expr2) {
    if(debug) fprintf(out, MAG "Detected :" RESET"expr + expr"CYN" ->"RESET" expr \n");
}

void manage_expr_mul_expr(int debug, FILE* out, expr* expr1, expr* expr2) {
    if(debug) fprintf(out, MAG "Detected :" RESET"expr * expr"CYN" ->"RESET" expr \n");
}

void manage_expr_minus_expr(int debug, FILE* out, expr* expr1, expr* expr2) {
    if(debug) fprintf(out, MAG "Detected :" RESET"expr - expr"CYN" ->"RESET" expr \n");
}

void manage_expr_div_expr(int debug, FILE* out, expr* expr1, expr* expr2) {
    if(debug) fprintf(out, MAG "Detected :" RESET"expr / expr"CYN" ->"RESET" expr \n");
}

void manage_expr_mod_expr(int debug, FILE* out, expr* expr1, expr* expr2) {
    if(debug) fprintf(out, MAG "Detected :" RESET"expr MOD expr"CYN" ->"RESET" expr \n");
}

void manage_expr_eq_expr(int debug, FILE* out, expr* expr1, expr* expr2) {
    if(debug) fprintf(out, MAG "Detected :" RESET"expr == expr"CYN" ->"RESET" expr \n");
}

void manage_expr_neq_expr(int debug, FILE* out, expr* expr1, expr* expr2) {
    if(debug) fprintf(out, MAG "Detected :" RESET"expr != expr"CYN" ->"RESET" expr \n");
}

void manage_expr_gt_expr(int debug, FILE* out, expr* expr1, expr* expr2) {
    if(debug) fprintf(out, MAG "Detected :" RESET"expr > expr"CYN" ->"RESET" expr \n");
}

void manage_expr_lt_expr(int debug, FILE* out, expr* expr1, expr* expr2) {
    if(debug) fprintf(out, MAG "Detected :" RESET"expr < expr"CYN" ->"RESET" expr \n");
}

void manage_expr_gte_expr(int debug, FILE* out, expr* expr1, expr* expr2) {
    if(debug) fprintf(out, MAG "Detected :" RESET"expr >= expr"CYN" ->"RESET" expr \n");
}

void manage_expr_lte_expr(int debug, FILE* out, expr* expr1, expr* expr2) {
    if(debug) fprintf(out, MAG "Detected :" RESET"expr <= expr"CYN" ->"RESET" expr \n");
}

void manage_expr_and_expr(int debug, FILE* out, expr* expr1, expr* expr2) {
    if(debug) fprintf(out, MAG "Detected :" RESET"expr AND expr"CYN" ->"RESET" expr \n");
}

void manage_expr_or_expr(int debug, FILE* out, expr* expr1, expr* expr2) {
    if(debug) fprintf(out, MAG "Detected :" RESET"expr OR expr"CYN" ->"RESET" expr \n");
}

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

void manage_assignexpr_lvalue_assign_expr(int debug, FILE* out, SymbolTable* symTable, expr* lvalue, expr* expr1, unsigned int scope, unsigned int line) {
    if(debug) fprintf(out, MAG "Detected :" RESET"lvalue = expr"CYN" ->"RESET" assignexpr \n");
    if(lvalue != NULL) {
        if(is_id_built_in_function(lvalue->sym->name)){
            fprintf(out_file,RED"Error:"RESET" Cannot assign to a library function \""YEL"%s"RESET"\" (line: "GRN"%d"RESET") \n", lvalue->sym->name, line);
            return;
        }

        for(int i = scope; i >= 0; i--) {
            Symbol* tmp_symbol = symbol_table_scope_lookup(symTable, lvalue->sym->name, i); 
            if(tmp_symbol != NULL){
                if( tmp_symbol->symbol_type == USERFUNC) 
                    fprintf(out_file,RED"Error:"RESET" Cannot assign to a function \""YEL"%s"RESET"\" (line: "GRN"%d"RESET") \n", lvalue->sym->name, line);
                return;
            } 
        }
    }
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