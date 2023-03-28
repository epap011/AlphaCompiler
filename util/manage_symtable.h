#ifndef MANAGE_SYMTABLE_H
#define MANAGE_SYMTABLE_H

#include "symbol_table.h"

void        insert_lib_functions(SymbolTable * symTable);
const char* str_type(enum SymbolType type);
void        symbol_table_print(SymbolTable* symTable);
void increase_scope  (unsigned int* scope);
void decrease_scope  (unsigned int* scope);
void manage_id       (SymbolTable* symTable, char* id, enum SymbolType type, unsigned int scope, unsigned int line);
void manage_local_id (SymbolTable* symTable, char* id, unsigned int scope, unsigned int line);
void manage_global_id(SymbolTable* symTable, char* id, unsigned int scope, unsigned int line);
void manage_funcdef  (SymbolTable* symTable, char* id, unsigned int scope, unsigned int line);
void manage_formal_id(SymbolTable* symTable, char* id, unsigned int scope, unsigned int line);
void check_if_declared(SymbolTable* symTable, char* id, unsigned int scope);

#endif /* MANAGE_SYMTABLE_H */