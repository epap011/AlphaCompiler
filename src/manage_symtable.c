#include "symbol_table.h"
#include <string.h>

#define NUM_OF_LIB_FUNC 12

void insert_lib_functions(SymbolTable * symTable){

    char lib_functions[NUM_OF_LIB_FUNC][18] = {
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

    for(int i = 0; i < NUM_OF_LIB_FUNC; i++) {   
        char* name     = strndup(lib_functions[i], strlen(lib_functions[i])+1);    
        Symbol* symbol = symbol_create(name, 0, 0, LIBFUNC, 0);
        symbol_table_insert(symTable, symbol);
    }
}

//Move
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

    printf("\n---------------- Scope #0 ----------------\n\n");
    for(int i = 0; i < symTable->size; i++){

        if(symTable->buckets[i] == NULL) continue;

        linked_list* bucket_list = symTable->buckets[i]->symbol_list;
        node* tmp = bucket_list->head;
        while(tmp != NULL){
            Symbol* symbol = (Symbol*)tmp->data;
            printf("\"%s\" [%s] (line %d) (scope %d)\n", symbol->name, str_type(symbol->symbol_type) , symbol->line, symbol->scope);
            tmp = tmp->next;
        }
    }
    printf("\n");
}






