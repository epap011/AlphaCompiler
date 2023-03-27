#include "symbol_table.h"

#define INITIAL_SYMBOL_TABLE_CAPACITY 32
#define INITIAL_SCOPE_CAPACITY 16

SymbolTable* symbol_table_create() {
    SymbolTable* symbol_table = (SymbolTable*)malloc(sizeof(SymbolTable));
    symbol_table->size        = INITIAL_SYMBOL_TABLE_CAPACITY;
    symbol_table->buckets     = (SymbolTableBucket**)malloc(sizeof(SymbolTableBucket*) * INITIAL_SYMBOL_TABLE_CAPACITY);
    symbol_table->first_symbol_scopes = hash_table_create(INITIAL_SCOPE_CAPACITY);
    symbol_table->last_symbol_scopes  = hash_table_create(INITIAL_SCOPE_CAPACITY);

    for(int i = 0; i < INITIAL_SYMBOL_TABLE_CAPACITY; i++) {
        symbol_table->buckets[i] = NULL;
    }

    for(int i = 0; i < INITIAL_SCOPE_CAPACITY; i++) {
        hash_table_insert(symbol_table->first_symbol_scopes, i, NULL);
        hash_table_insert(symbol_table->last_symbol_scopes,  i, NULL);
    }

    return symbol_table;
}

void symbol_table_destroy(SymbolTable* symbol_table) {
    for(int i = 0; i < symbol_table->size; i++) {
        if(symbol_table->buckets[i] != NULL) {
            free_linked_list(symbol_table->buckets[i]->symbol_list);
            free(symbol_table->buckets[i]);
        }
    }

    free(symbol_table->buckets);
    free(symbol_table);
}

void symbol_table_insert(SymbolTable* symbol_table, Symbol* symbol) {
    unsigned int hash = hash_function(symbol->value.var_var->name, symbol_table->size);

    if(symbol_table->buckets[hash] == NULL) {
        symbol_table->buckets[hash] = (SymbolTableBucket*)malloc(sizeof(SymbolTableBucket));
        symbol_table->buckets[hash]->symbol_list = create_linked_list();
    }

    if(symbol_table_get_first_symbol_of_scope(symbol_table, scope) == NULL) {
        symbol_table->first_symbol_scopes[symbol->value.var_var->scope] = symbol;
    }

    update_last_symbol_of_scope(symbol_table, symbol);


    insert_at_the_end_to_linked_list(symbol_table->buckets[hash]->symbol_list, symbol);
}

SymbolTableBucket* symbol_table_lookup(SymbolTable* symbol_table, const char* symbol) {
    unsigned int hash = hash_function(symbol, symbol_table->size);

    if(symbol_table->buckets[hash] == NULL) {
        return NULL;
    }

    linked_list* list = symbol_table->buckets[hash]->symbol_list;

    for(int i = 0; i < list->size; i++) {
        Symbol* current_symbol = (Symbol*)get_from_linked_list(list, i);

        if(strcmp(current_symbol->value.var_var->name, symbol) == 0) {
            return symbol_table->buckets[hash];
        }
    }

    return NULL;
}

void symbol_table_hide(SymbolTable* symbol_table, unsigned int scope) {
    for(int i = 0; i < symbol_table->size; i++) {
        if(symbol_table->buckets[i] != NULL) {
            linked_list* list = symbol_table->buckets[i]->symbol_list;

            for(int j = 0; j < list->size; j++) {
                Symbol* current_symbol = (Symbol*)get_from_linked_list(list, j);

                if(current_symbol->value.var_var->scope == scope) {
                    current_symbol->is_active = 0;
                }
            }
        }
    }
}

Symbol* symbol_create(const char* name, unsigned int scope, unsigned int line, int symbol_type, int is_variable) {
    Symbol* symbol = (Symbol*)malloc(sizeof(Symbol));
    
    symbol->is_active   = 1;
    symbol->symbol_type = symbol_type;
    symbol->is_variable = is_variable;
    symbol->next_symbol_of_same_scope = NULL;

    if(is_variable) {
        symbol->value.var_var = (Variable*)malloc(sizeof(Variable));
        symbol->value.var_var->name  = name;
        symbol->value.var_var->scope = scope;
        symbol->value.var_var->line  = line;
    }
    else { //is function
        symbol->value.func_var = (Function*)malloc(sizeof(Function));
        symbol->value.func_var->name  = name;
        symbol->value.func_var->scope = scope;
        symbol->value.func_var->line  = line;
        symbol->value.func_var->args  = NULL;
    }

    return symbol;
}

void update_last_symbol_of_scope(SymbolTable* symbol_table, Symbol* symbol) {
    if(symbol->is_variable) {
        symbol_table->last_symbol_scopes[symbol->value.var_var->scope] = symbol;
    }
    else {
        symbol_table->last_symbol_scopes[symbol->value.var_var->scope] = symbol;
    }
}

Symbol* symbol_table_get_last_symbol_of_scope(SymbolTable* symbol_table, unsigned int scope) {
    return (Symbol*)hash_table_get_by_index(symbol_table->last_symbol_scopes, scope);
}

Symbol* symbol_table_get_first_symbol_of_scope(SymbolTable* symbol_table, unsigned int scope) {
    return (Symbol*)hash_table_get_by_index(symbol_table->first_symbol_scopes, scope);
}
