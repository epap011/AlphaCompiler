#include "symbol_table.h"

void insert_lib_functions(SymbolTable * symTable){

    char* lib_functions[12][18] = {
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

    for(int i = 0; i < 12; i++){
        
        char* name = lib_functions[i];
        Symbol * symbol = symbol_create(name, 0, 0, LIBFUNC, 0);
        symbol_table_insert(symTable, symbol);

    }

}

void symbol_table_print(SymbolTable * symTable){

    int current_scope = 0;

    for(int i = 0; i < symTable->size; i++){

        

        printf("------- Scope #%d -------\n",current_scope);

        linked_list* tmp = symTable->buckets[i]->symbol_list;
        while(tmp != NULL){
            Symbol * symbol = tmp->head;
            printf("\"%s\" [%s] (line %d) (scope %d) \n", symbol->name, symbol->symbol_type , symbol->line, symbol->scope);
                
            symbol = symbol->next;
        }     
    }

}







