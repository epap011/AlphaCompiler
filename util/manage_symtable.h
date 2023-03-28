#ifndef MANAGE_SYMTABLE_H
#define MANAGE_SYMTABLE_H

#include "symbol_table.h"

void insert_lib_functions(SymbolTable * symTable);
const char* str_type(enum SymbolType type);
void symbol_table_print(SymbolTable* symTable);

#endif /* MANAGE_SYMTABLE_H */