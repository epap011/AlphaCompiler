#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include "linked_list.h"
#include "scope_space.h"

enum SymbolType { GLOBAL, _LOCAL, FORMAL, USERFUNC, LIBFUNC }; //phase 2

enum symbol_t{ var_s, programfunc_s, libraryfunc_s};           //phase 3

typedef struct Symbol {
    int is_active;
    int is_variable;
    const char*  name;
    unsigned int scope;
    unsigned int line;
    enum SymbolType symbol_type;
    struct Symbol* next_symbol_of_same_scope;

    //phase 3
    enum symbol_t type;
    enum scopespace_t space;
    unsigned int offset;

} Symbol;

typedef struct SymbolTableBucket {
    linked_list* symbol_list;
} SymbolTableBucket;

typedef struct SymbolTable {
    SymbolTableBucket** buckets;
    unsigned int        size;
    unsigned int        scope_size;
    Symbol**            first_symbol_scopes;
    Symbol**            last_symbol_scopes;
}SymbolTable;

SymbolTable* symbol_table_create ();
void         symbol_table_destroy(SymbolTable* symbol_table);
void         symbol_table_insert (SymbolTable* symbol_table, Symbol*     symbol);
Symbol*      symbol_table_lookup (SymbolTable* symbol_table, const char* symbol);
void         symbol_table_hide   (SymbolTable* symbol_table, unsigned int scope );
Symbol*      symbol_table_scope_lookup (SymbolTable* symbol_table, const char* symbol, unsigned int scope);

Symbol* symbol_table_get_first_symbol_of_scope(SymbolTable* symbol_table, unsigned int scope);
Symbol* symbol_table_get_last_symbol_of_scope(SymbolTable* symbol_table, unsigned int scope);

Symbol* symbol_create(const char* name, unsigned int scope, unsigned int line, int symbol_type, int is_variable);
void update_last_symbol_of_scope(SymbolTable* symbol_table, Symbol* symbol);
int hash_function(const char* name, unsigned int size);

#endif /* SYMBOL_TABLE_H */