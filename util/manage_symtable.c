#include <string.h>
#include "symbol_table.h"
#include "manage_symtable.h"

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

int formal_flag = 0;

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
        Symbol* symbol = symbol_create(name, 0, 0, LIBFUNC, 0);
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

        printf("-------- Scope #%d --------\n\n", i);

        while(current_symbol != NULL){
            printf("\""YEL"%s"RESET"\" "BLU"["RESET"%s"BLU"]"RESET" (line: "GRN"%d"RESET") (scope "GRN"%d"RESET")\n", current_symbol->name, str_type(current_symbol->symbol_type), current_symbol->line, current_symbol->scope);
            current_symbol = current_symbol->next_symbol_of_same_scope;
        }
    }
    printf("\n\n");
}

void increase_scope(unsigned int* scope){
    (*scope)++;
}

void decrease_scope(unsigned int* scope){
    (*scope)--;
}

//Checks if a function with that name is already declared (also checks if it is a library function)
void check_if_declared(SymbolTable* symTable, char* id, unsigned int scope){
    if(id[0] == '_') return; //If it is an unonymous function, don't check
    
    Symbol* tmp_symbol = symbol_table_scope_lookup(symTable, id, scope);

    if(tmp_symbol != NULL){
        formal_flag = 1;
        return;
    }
    
    if(is_id_built_in_function(id))
        formal_flag = 1;
        
}

int is_id_built_in_function(char* id){
    for(int i = 0; i < NUM_OF_LIB_FUNC; i++){
        if(strcmp(id, lib_functions[i]) == 0){
            return 1;
        }
    }
    return 0;
}

//Managing function from now on
void manage_id(SymbolTable* symTable, char* id, enum SymbolType type, unsigned int scope, unsigned int line){

        if(symbol_table_scope_lookup(symTable, id, 0) != NULL) return;
        if(symbol_table_scope_lookup(symTable, id, scope) != NULL) return;

        if(scope > 0) {
            for(int i = 1; i < scope; i++) { 
                if(symbol_table_scope_lookup(symTable, id, i) != NULL) {
                    
                    printf(RED"Error:"RESET" Variable "YEL"\"%s\""RESET" is not accessible (line: "GRN"%d"RESET")\n", id, line);
                    return;
                }
            }
        }

        char* name     = strdup(id);
        Symbol* symbol = symbol_create(name, scope, line, type, VAR);
        symbol_table_insert(symTable, symbol);
}

void manage_local_id(SymbolTable* symTable, char* id, unsigned int scope, unsigned int line){

        if(symbol_table_scope_lookup(symTable, id, scope) != NULL) return;

        if(is_id_built_in_function(id)) {
            printf(RED"Error:"RESET" Cannot shadow library function "YEL"\"%s\""RESET" (line: "GRN"%d"RESET") \n", id,line);
            return;
        }

        char* name     = strdup(id);
        Symbol* symbol = symbol_create(name, scope, line, scope == 0 ? GLOBAL : _LOCAL, VAR);
        symbol_table_insert(symTable, symbol);
}

void manage_global_id(SymbolTable* symTable, char* id, unsigned int scope, unsigned int line){

        if(symbol_table_scope_lookup(symTable, id, 0) != NULL) return;
        printf(RED"Error:"RESET" Variable \""YEL"%s"RESET"\" doesn't exists in global scope\n", id);
}

void manage_funcdef(SymbolTable* symTable, char* id, unsigned int scope, unsigned int line){

   if(is_id_built_in_function(id)) {
        printf(RED"Error:"RESET" Cannot shadow library function \""YEL"%s"RESET"\" \n", id);
        return;
   }
   
   Symbol* tmp_symbol = symbol_table_scope_lookup(symTable, id, scope);

    if(tmp_symbol != NULL){
        if(tmp_symbol->symbol_type == LIBFUNC)
            printf(RED"Error:"RESET" Cannot shadow library function \""YEL"%s"RESET"\" (line: "GRN"%d"RESET") \n", id, line);
        else
            printf(RED"Error:"RESET" Function \""YEL"%s"RESET"\" already declared in scope "GRN"%d"RESET"\n", id, scope);

        return;
    }

    char* name     = strdup(id);
    Symbol* symbol = symbol_create(name, scope, line, USERFUNC, FUNC);
    symbol_table_insert(symTable, symbol);
}

void manage_formal_id(SymbolTable* symTable, char* id, unsigned int scope, unsigned int line){

    if(formal_flag)
        return;
         
    if(is_id_built_in_function(id)) {
            printf(RED"Error:"RESET" Cannot declare variable \""YEL"%s"RESET"\", a library function exists with that name (line: "GRN"%d"RESET") \n", id, line);
            return;
        }

    if(symbol_table_scope_lookup(symTable, id, scope) != NULL){
        printf(RED"Error:"RESET" Formal variable \""YEL"%s"RESET"\" already declared in function \n", id);
        return;
    } 

    char* name     = strdup(id);
    Symbol* symbol = symbol_create(name, scope, line, FORMAL, VAR);
    symbol_table_insert(symTable, symbol);

}

void manage_lvalue_inc(SymbolTable* symTable, char* id, unsigned int scope, unsigned int line){

    if(symbol_table_scope_lookup(symTable, id, scope) == NULL){
        printf(RED"Error:"RESET" Variable \""YEL"%s"RESET"\" doesn't exists in scope "GRN"%d"RESET"\n", id, scope);
        return;
    } 


}