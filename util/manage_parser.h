#ifndef MANAGE_PARSER_H
#define MANAGE_PARSER_H

#include "yacc_util.h"
#include "symbol_table.h"
#include "expression.h"

void        insert_lib_functions(SymbolTable * symTable);
const char* str_type(enum SymbolType type);
void        symbol_table_print(SymbolTable* symTable);
void increase_scope  (unsigned int* scope);
void decrease_scope  (unsigned int* scope);
Symbol* manage_id       (SymbolTable* symTable, char* id, enum SymbolType type, unsigned int scope, unsigned int line, ScopeStackList *tail);
Symbol* manage_local_id (SymbolTable* symTable, const char* id, unsigned int scope, unsigned int line);
Symbol* manage_global_id(SymbolTable* symTable, const char* id, unsigned int scope, unsigned int line);
Symbol* manage_funcdef  (SymbolTable* symTable, char* id, unsigned int scope, unsigned int line);
void manage_formal_id(SymbolTable* symTable, const char* id, unsigned int scope, unsigned int line);
void manage_lvalue_inc(SymbolTable* symTable, const char* id, unsigned int scope, unsigned int line);
void manage_lvalue_dec(SymbolTable* symTable, const char* id, unsigned int scope, unsigned int line);
void manage_func_call(SymbolTable* symTable, const char* id, unsigned int scope, unsigned int line);
void manage_assignment(SymbolTable* symTable, const char* id, unsigned int scope, unsigned int line);
void check_if_declared(SymbolTable* symTable, const char* id, unsigned int scope);
void manage_return(int line, int flag);

int check_lvalue(SymbolTable* symTable, const char* id, unsigned int scope, unsigned int line);
int is_id_built_in_function(const char* id);
int hide_symbol_on_scope(SymbolTable* symTable, const char* id, unsigned int scope);

void manage_program        (int debug, FILE* out);

void manage_stmt_expr      (int debug, FILE* out);
void manage_stmt_ifstmt    (int debug, FILE* out);
void manage_stmt_whilestmt (int debug, FILE* out);
void manage_stmt_forstmt   (int debug, FILE* out);
void manage_stmt_returnstmt(int debug, FILE* out);
void manage_stmt_break     (int debug, FILE* out, int line, int flag);
void manage_stmt_continue  (int debug, FILE* out, int line, int flag);
void manage_stmt_block     (int debug, FILE* out);
void manage_stmt_funcdef   (int debug, FILE* out);
void manage_stmt_semicolon (int debug, FILE* out);

void manage_expr_assignexpr(int debug, FILE* out);
void manage_expr_term      (int debug, FILE* out);
void manage_expr_plus_expr (int debug, FILE* out, expr* expr1, expr* expr2);
void manage_expr_mul_expr  (int debug, FILE* out, expr* expr1, expr* expr2);
void manage_expr_minus_expr(int debug, FILE* out, expr* expr1, expr* expr2);
void manage_expr_div_expr  (int debug, FILE* out, expr* expr1, expr* expr2);
void manage_expr_mod_expr  (int debug, FILE* out, expr* expr1, expr* expr2);
void manage_expr_eq_expr   (int debug, FILE* out, expr* expr1, expr* expr2);
void manage_expr_neq_expr  (int debug, FILE* out, expr* expr1, expr* expr2);
void manage_expr_gt_expr   (int debug, FILE* out, expr* expr1, expr* expr2);
void manage_expr_lt_expr   (int debug, FILE* out, expr* expr1, expr* expr2);
void manage_expr_gte_expr  (int debug, FILE* out, expr* expr1, expr* expr2);
void manage_expr_lte_expr  (int debug, FILE* out, expr* expr1, expr* expr2);
void manage_expr_and_expr  (int debug, FILE* out, expr* expr1, expr* expr2);
void manage_expr_or_expr   (int debug, FILE* out, expr* expr1, expr* expr2);

void manage_term_lpar_expr_rpar   (int debug, FILE* out);
void manage_term_uminus_expr      (int debug, FILE* out);
void manage_term_not_expr         (int debug, FILE* out);
void manage_term_plusplus_lvalue  (int debug, FILE* out, SymbolTable* symTable, expr* expr, unsigned int scope, unsigned int line);
void manage_term_lvalue_plusplus  (int debug, FILE* out, SymbolTable* symTable, expr* expr, unsigned int scope, unsigned int line);
void manage_term_minusminus_lvalue(int debug, FILE* out, SymbolTable* symTable, expr* expr, unsigned int scope, unsigned int line);
void manage_term_lvalue_minusminus(int debug, FILE* out, SymbolTable* symTable, expr* expr, unsigned int scope, unsigned int line);
void manage_term_primary          (int debug, FILE* out);


void manage_primary_lvalue           (int debug, FILE* out);
void manage_primary_call             (int debug, FILE* out);
void manage_primary_objectdef        (int debug, FILE* out);
void manage_primary_lpar_funcdef_rpar(int debug, FILE* out);
void manage_primary_const            (int debug, FILE* out);

#endif /* MANAGE_PARSER_H */