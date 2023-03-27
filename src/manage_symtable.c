#include "symbol_table.h"

void insert_lib_functions(SymbolTable * symTable){

    char lib_functions[12][18] = {
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

    for(int i = 0; i < 12; i++) {       
        char* name = lib_functions[i];
        Symbol * symbol = symbol_create(name, 0, 0, LIBFUNC, 0);
        symbol_table_insert(symTable, symbol);
    }

}

void symbol_table_print(SymbolTable * symTable){

    for(int i = 0; i < symTable->size; i++){
        printf("\n### Bucket %d ###\n", i);

        if(symTable->buckets[i] == NULL) continue;

        linked_list* bucket_list = symTable->buckets[i]->symbol_list;
        node* tmp = bucket_list->head;
        while(tmp != NULL){
            Symbol* symbol = (Symbol*)tmp->data;
            printf("\"%s\" [%d] (line %d) (scope %d)\n", symbol->name, symbol->symbol_type , symbol->line, symbol->scope);
            tmp = tmp->next;
        }
    }
}







