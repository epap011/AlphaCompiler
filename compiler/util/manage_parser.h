#ifndef MANAGE_PARSER_H
#define MANAGE_PARSER_H

#include "yacc_util.h"
#include "symbol_table.h"
#include "expression.h"
#include "quad.h"
#include "panoklist.h"

typedef struct Forprefix{
    unsigned int test;
    unsigned int enter;
} Forprefix;

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
void flip_offsets(linked_list* offsets);
void manage_lvalue_inc(SymbolTable* symTable, const char* id, unsigned int scope, unsigned int line);
void manage_lvalue_dec(SymbolTable* symTable, const char* id, unsigned int scope, unsigned int line);
expr* manage_func_call(expr* lvalue, expr* elist, unsigned int scope, unsigned int line);
void manage_assignment(SymbolTable* symTable, const char* id, unsigned int scope, unsigned int line);
void check_if_declared(SymbolTable* symTable, const char* id, unsigned int scope);
void manage_return(int line, int flag, expr* retval, Stack *retstack);

int check_lvalue(SymbolTable* symTable, const char* id, unsigned int scope, unsigned int line);
int is_id_built_in_function(const char* id);
int hide_symbol_on_scope(SymbolTable* symTable, const char* id, unsigned int scope);
int convert_to_bool(expr* expr);

void manage_program        (int debug, FILE* out);

stmt_t* manage_stmt_expr(int debug, FILE* out);
stmt_t* manage_stmt_ifstmt    (int debug, FILE* out, stmt_t* ifstmt);
stmt_t* manage_stmt_whilestmt (int debug, FILE* out);
stmt_t* manage_stmt_forstmt   (int debug, FILE* out);
stmt_t* manage_stmt_returnstmt(int debug, FILE* out);
stmt_t* manage_stmt_break     (int debug, FILE* out, int line, int flag);
stmt_t* manage_stmt_continue  (int debug, FILE* out, int line, int flag);
stmt_t* manage_stmt_block     (int debug, FILE* out);
stmt_t* manage_stmt_funcdef   (int debug, FILE* out);
stmt_t* manage_stmt_semicolon (int debug, FILE* out);

void manage_expr_assignexpr(int debug, FILE* out);
void manage_expr_term      (int debug, FILE* out);

expr* manage_arith_relop_emits(expr* expr1, expr* expr2, unsigned int scope, unsigned int line, enum iopcode op);
expr* manage_arithop_emits    (expr* expr1, expr* expr2, unsigned int scope, unsigned int line, enum iopcode op);
expr* manage_relop_emits      (expr* expr1, expr* expr2, unsigned int scope, unsigned int line, enum iopcode op);
expr* manage_boolop_emits(expr* expr1, expr* expr2, unsigned int scope, unsigned int line, enum iopcode op, unsigned int M_label);
expr* manage_boolop_bypass(expr* expr1, expr* expr2, unsigned int scope, unsigned int line, enum iopcode op);

expr* manage_expr_plus_expr (int debug, FILE* out, expr* expr1, expr* expr2, unsigned int scope, unsigned int line);
expr* manage_expr_mul_expr  (int debug, FILE* out, expr* expr1, expr* expr2, unsigned int scope, unsigned int line);
expr* manage_expr_minus_expr(int debug, FILE* out, expr* expr1, expr* expr2, unsigned int scope, unsigned int line);
expr* manage_expr_div_expr  (int debug, FILE* out, expr* expr1, expr* expr2, unsigned int scope, unsigned int line);
expr* manage_expr_mod_expr  (int debug, FILE* out, expr* expr1, expr* expr2, unsigned int scope, unsigned int line);
expr* manage_expr_eq_expr   (int debug, FILE* out, expr* expr1, expr* expr2, unsigned int scope, unsigned int line);
expr* manage_expr_neq_expr  (int debug, FILE* out, expr* expr1, expr* expr2, unsigned int scope, unsigned int line);
expr* manage_expr_gt_expr   (int debug, FILE* out, expr* expr1, expr* expr2, unsigned int scope, unsigned int line);
expr* manage_expr_lt_expr   (int debug, FILE* out, expr* expr1, expr* expr2, unsigned int scope, unsigned int line);
expr* manage_expr_gte_expr  (int debug, FILE* out, expr* expr1, expr* expr2, unsigned int scope, unsigned int line);
expr* manage_expr_lte_expr  (int debug, FILE* out, expr* expr1, expr* expr2, unsigned int scope, unsigned int line);
expr* manage_expr_and_expr  (int debug, FILE* out, expr* expr1, expr* expr2, unsigned int M_label, unsigned int scope, unsigned int line);
expr* manage_expr_or_expr   (int debug, FILE* out, expr* expr1, expr* expr2, unsigned int M_label, unsigned int scope, unsigned int line);

void manage_term_lpar_expr_rpar   (int debug, FILE* out);
expr* manage_term_uminus_expr(int debug, FILE* out, expr* u_expr, unsigned int scope, unsigned int line);
expr* manage_term_not_expr(int debug, FILE* out, expr* expr1, unsigned int scope, unsigned int line);
expr* manage_term_plusplus_lvalue  (int debug, FILE* out, SymbolTable* symTable, expr* lvalue, unsigned int scope, unsigned int line);
expr* manage_term_lvalue_plusplus  (int debug, FILE* out, SymbolTable* symTable, expr* lvalue, unsigned int scope, unsigned int line);
expr* manage_term_minusminus_lvalue(int debug, FILE* out, SymbolTable* symTable, expr* lvalue, unsigned int scope, unsigned int line);
expr* manage_term_lvalue_minusminus(int debug, FILE* out, SymbolTable* symTable, expr* lvalue, unsigned int scope, unsigned int line);
void manage_term_primary          (int debug, FILE* out);

expr* manage_assignexpr_lvalue_assign_expr(int debug, FILE* out, SymbolTable* symTable, expr* lvalue, expr* expr1, unsigned int scope, unsigned int line);

expr* manage_primary_lvalue(int debug, FILE* out, expr* lvalue, unsigned int scope, unsigned int line);
void manage_primary_call             (int debug, FILE* out);
void manage_primary_objectdef        (int debug, FILE* out);
expr* manage_primary_lpar_funcdef_rpar(int debug, FILE* out, Symbol* funcdef_s);
void manage_primary_const            (int debug, FILE* out);

expr* manage_lvalue_ident       (int debug, FILE* out, SymbolTable* symTable, char* id, enum SymbolType type, unsigned int scope, unsigned int line, ScopeStackList *tail);
expr* manage_lvalue_local_ident (int debug, FILE* out, SymbolTable* symTable, char* id, unsigned int scope, unsigned int line);
expr* manage_lvalue_global_ident(int debug, FILE* out, SymbolTable* symTable, char* id, unsigned int scope, unsigned int line);
expr* manage_lvalue_member      (int debug, FILE* out, expr* member);

expr* manage_memeber_lvalue_dot_ident(int debug, FILE* out, expr* lvalue, char* name, unsigned int scope, unsigned int line, int* normalcall_skip);
void  manage_memeber_lvalue_lbr_expr_rbr(int debug, FILE* out, expr* lvalue, expr* expr_list, expr** tableitem, unsigned int scope, unsigned int line);
expr* manage_member_call_dot_ident      (int debug, FILE* out, expr* call,  char* id, int* normalcall_skip);
expr* manage_member_call_lbr_expr_rbr   (int debug, FILE* out, expr* call, expr* expr1);

expr* manage_call_call_lpar_elist_rpar  (int debug, FILE* out, unsigned int scope, unsigned int line, expr* lvalue, expr* elist);
expr* manage_call_lvalue_callsuffix     (int debug, FILE* out, SymbolTable* symTable, expr* lvalue, int* normalcall_skip, unsigned int scope, unsigned int line, callexpr* c_expr);
expr* manage_call_lpar_funcdef_rpar_lpar_elist_rpar(int debug, FILE* out, unsigned int scope, unsigned int line, Symbol *funcdef, expr* elist);

callexpr* manage_callsuffix_normcall  (int debug, FILE* out, callexpr* c_expr);
callexpr* manage_callsuffix_methodcall(int debug, FILE* out, callexpr* c_expr);

callexpr* manage_normcall_lpar_elist_rpar(int debug, FILE* out, unsigned int method, expr* elist, char* name);

callexpr* manage_methodcall_ddot_ident_lpar_elist_rpar(int debug, FILE* out, int* normcall_skip, unsigned int method, expr* elist, char* name);

expr* manage_comexpropt_empty(int debug, FILE* out);
expr* manage_comexpropt_comma_expr_comexpropt(int debug, FILE* out, expr* expr1, expr* com_expr_opt);

expr* manage_objectdef_lbrace_indexed_rbrace(int debug, FILE* out, expr* indexed, unsigned int scope, unsigned int line);
expr* manage_objectdef_lbrace_elist_rbrace(int debug, FILE* out, expr* elist, unsigned int scope, unsigned int line);

expr* manage_elist_empty          (int debug, FILE* out);
expr* manage_elist_expr           (int debug, FILE* out);
expr* manage_elist_elist_comma_exp(int debug, FILE* out, expr* expr1, expr* com_expr_opt);

expr* manage_indexed_indexedelem_comindexedelemopt(int debug, FILE* out, expr* indexedelem, expr* com_indexedelem_opt);

expr* manage_indexedele_lcbrace_expr_colon_expr_rcbrace(int debug, FILE* out, expr* index, expr* value);

expr* manage_comindexedelemopt_empty(int debug, FILE* out);
expr* manage_comindexedelemopt_comma_indexedelem_comindexedelemopt(int debug, FILE* out, expr* indexedelem, expr* com_indexedelem_opt);

expr* manage_stmtList_stmt(int debug, FILE* out);
expr* manage_stmtList_stmt_stmtList(int debug, FILE* out);
expr* manage_stmtList_empty(int debug, FILE* out);

stmt_t* manage_ifstmt     (int debug, FILE* out, int ifprefix, stmt_t* stmt, unsigned int scope, unsigned int line);
stmt_t* manage_ifstmt_else(int debug, FILE* out, int ifprefix, stmt_t* stmt1, int elseprefix, stmt_t* stmt2, unsigned int scope, unsigned int line);
int   manage_ifprefix   (int debug, FILE* out, expr* expr1, unsigned int scope, unsigned int line);
int   manage_elseprefix (int debug, FILE* out, unsigned int scope, unsigned int line);
void short_circuit_emits(expr* result, unsigned int line, unsigned int scope);

#endif /* MANAGE_PARSER_H */