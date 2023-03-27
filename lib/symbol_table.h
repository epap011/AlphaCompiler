#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include "linked_list.h"
#include "hash_table.h"

typedef struct Variable {
    const char*  name;
    unsigned int scope;
    unsigned int line;
} Variable;

typedef struct Function {
    const char*  name;
    unsigned int scope;
    unsigned int line;
    linked_list* args;
} Function;

enum SymbolType { GLOBAL, LOCAL, FORMAL, USERFUNC, LIBFUNC };

typedef struct Symbol {
    int is_active;
    int is_variable;
    union {
        Variable *var_var;
        Function *func_var;
    } value;

    enum SymbolType symbol_type;

    Symbol* next_symbol_of_same_scope;
} Symbol;

typedef struct SymbolTableBucket {
    linked_list* symbol_list;
} SymbolTableBucket;

typedef struct SymbolTable {
    SymbolTableBucket** buckets;
    unsigned int        size;
    Symbol**            first_symbol_scopes;
    Symbol**            last_symbol_scopes;
}SymbolTable;

SymbolTable*       symbol_table_create ();
void               symbol_table_destroy(SymbolTable* symbol_table);
void               symbol_table_insert (SymbolTable* symbol_table, Symbol*      symbol);
SymbolTableBucket* symbol_table_lookup (SymbolTable* symbol_table, const char*  id);
void               symbol_table_hide   (SymbolTable* symbol_table, unsigned int scope );

Symbol* symbol_create(SymbolTable* symbol_table, const char* name, unsigned int scope, unsigned int line, int symbol_type, int is_variable);
void update_last_symbol_of_scope(SymbolTable* symbol_table, Symbol* symbol)
#endif /* SYMBOL_TABLE_H */