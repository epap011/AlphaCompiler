#include "symbol_table.h"

#define INITIAL_SYMBOL_TABLE_CAPACITY 32
#define INITIAL_SCOPE_CAPACITY 16

SymbolTable* symbol_table_create() {
    SymbolTable* symbol_table = (SymbolTable*)malloc(sizeof(SymbolTable));
    symbol_table->size        = INITIAL_SYMBOL_TABLE_CAPACITY;
    symbol_table->buckets     = (SymbolTableBucket**)malloc(sizeof(SymbolTableBucket*) * INITIAL_SYMBOL_TABLE_CAPACITY);
    symbol_table->first_symbol_scopes = (Symbol**)malloc(sizeof(Symbol*) * INITIAL_SCOPE_CAPACITY);
    symbol_table->last_symbol_scopes  = (Symbol**)malloc(sizeof(Symbol*) * INITIAL_SCOPE_CAPACITY);
    symbol_table->scope_size          = INITIAL_SCOPE_CAPACITY;

    for(int i = 0; i < INITIAL_SYMBOL_TABLE_CAPACITY; i++) {
        symbol_table->buckets[i] = NULL;
    }

    for(int i = 0; i < INITIAL_SCOPE_CAPACITY; i++) {
        symbol_table->first_symbol_scopes[i] = NULL;
        symbol_table->last_symbol_scopes[i]  = NULL;
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

int hash_function(const char* key, unsigned int size) {
    int i = 0;
    int ascii_sum = 0;

    while(key[i] != '\0')
        ascii_sum += key[i++];

    return ascii_sum % size;
}

void symbol_table_insert(SymbolTable* symbol_table, Symbol* symbol) {
    unsigned int index = hash_function(symbol->name, symbol_table->size);

    if( symbol_table->buckets[index] == NULL) {
        symbol_table->buckets[index] = (SymbolTableBucket*)malloc(sizeof(SymbolTableBucket));
        symbol_table->buckets[index]->symbol_list = create_linked_list();
    }

    unsigned int scope = symbol->scope;
    if(symbol_table_get_first_symbol_of_scope(symbol_table, scope) == NULL)
        symbol_table->first_symbol_scopes[scope] = symbol;
    else
        symbol_table->last_symbol_scopes[scope]->next_symbol_of_same_scope = symbol;    
    
    update_last_symbol_of_scope(symbol_table, symbol);
}

Symbol* symbol_table_lookup(SymbolTable* symbol_table, const char* symbol) {
    unsigned int index = hash_function(symbol, symbol_table->size);
    
    if(symbol_table->buckets[index] != NULL) {
        linked_list* symbol_list  = symbol_table->buckets[index]->symbol_list;
        node*        current_node = symbol_list->head;

        while(current_node != NULL) {
            Symbol* current_symbol = (Symbol*)current_node->data;

            if(strcmp(current_symbol->name, symbol) == 0 && current_symbol->is_active) {
                return current_symbol;
            }

            current_node = current_node->next;
        }
    }

    return NULL;
}

Symbol* symbol_table_scope_lookup(SymbolTable* symbol_table, const char* symbol, unsigned int scope) {
    Symbol* first_symbol_of_scope = symbol_table_get_first_symbol_of_scope(symbol_table, scope);

    if(first_symbol_of_scope != NULL) {
        Symbol* current_symbol = first_symbol_of_scope;

        while(current_symbol != NULL) {
            if(current_symbol->is_active && strcmp(current_symbol->name, symbol) == 0) {
                return current_symbol;
            }

            current_symbol = current_symbol->next_symbol_of_same_scope;
        }
    }

    return NULL;
}

void symbol_table_hide(SymbolTable* symbol_table, unsigned int scope) {
    Symbol* first_symbol_of_scope = symbol_table_get_first_symbol_of_scope(symbol_table, scope);

    if(first_symbol_of_scope != NULL) {
        Symbol* current_symbol = first_symbol_of_scope;

        while(current_symbol != NULL) {
            current_symbol->is_active = 0;
            current_symbol = current_symbol->next_symbol_of_same_scope;
        }
    }
}

Symbol* symbol_create(const char* name, unsigned int scope, unsigned int line, int symbol_type, int is_variable) {
    Symbol* symbol = (Symbol*)malloc(sizeof(Symbol));
    
    symbol->is_active   = 1;
    symbol->is_variable = is_variable;
    symbol->name  = name;
    symbol->scope = scope;
    symbol->line  = line;
    symbol->symbol_type = symbol_type;
    symbol->next_symbol_of_same_scope = NULL;

    return symbol;
}

void update_last_symbol_of_scope(SymbolTable* symbol_table, Symbol* symbol) {
    symbol_table->last_symbol_scopes[symbol->scope] = symbol;
}

Symbol* symbol_table_get_last_symbol_of_scope(SymbolTable* symbol_table, unsigned int scope) {
    return symbol_table->last_symbol_scopes[scope];
}

Symbol* symbol_table_get_first_symbol_of_scope(SymbolTable* symbol_table, unsigned int scope) {
    return symbol_table->first_symbol_scopes[scope];
}