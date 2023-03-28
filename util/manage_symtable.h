#ifndef MANAGE_SYMTABLE_H
#define MANAGE_SYMTABLE_H

#include "symbol_table.h"

void        insert_lib_functions(SymbolTable * symTable);
const char* str_type(enum SymbolType type);
void        symbol_table_print(SymbolTable* symTable);
void manage_lvalue(SymbolTable* symTable, char* id, enum SymbolType type, unsigned int scope, unsigned int line);
void increase_scope(unsigned int* scope);
void decrease_scope(unsigned int* scope);

#endif /* MANAGE_SYMTABLE_H */