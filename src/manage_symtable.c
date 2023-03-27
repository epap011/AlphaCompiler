#include "lib/symbol_table.h"

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
        
        Symbol * symbol = symbol_create(name, 0, 0, LIBFUNC, 0);
        symbol_table_insert(symTable, symbol);

    }

}

void symbol_table_print(SymbolTable * symTable){

    while(symTable != NULL){
            
            printf("------- Scope #0 -------\n");
            for(int i = 0; i < symTable->size; i++){
                linked_list tmp = symTable->buckets[i]->symbol_list;
                while(tmp != NULL){
                    printf("\"%s\" [%s] (line %d) (scope %d) \n", tmp->symbol->value.var_var->name, tmp->symbol->value.var_var->type, tmp->symbol->line, tmp->symbol->scope);
                
                    tmp = tmp->next;
                }
            }
    }

}







