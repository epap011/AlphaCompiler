#ifndef QUAD_H
#define QUAD_H

#include "expression.h"
#include "symbol_table.h"
#include "yacc_util.h"
#include <assert.h>


#define EXPAND_SIZE 1024
#define CURR_SIZE (total*sizeof(quad))
#define NEW_SIZE (EXPAND_SIZE*sizeof(quad)+CURR_SIZE)

//to div einai dilomeno sto stdlib 
enum iopcode{

    assign, add, sub, mul, i_div, mod, uminus,
    and, or, not, 
    if_eq, if_noteq, if_lesseq, if_greatereq, if_less, if_greater,
    call, param, ret, getretval,
    funcstart, funcend,
    tablecreate, tablegetelem, tablesetelem,
    jump
};

typedef struct quad{

    enum iopcode op;
    expr* result;
    expr* arg1;
    expr* arg2;
    unsigned label;
    unsigned line;

} quad;

typedef struct stmt_t {
    int break_list;
    int cont_list;
} stmt_t;

void expand();
void emit(enum iopcode op, expr* arg1, expr* arg2, expr* result, unsigned label, unsigned line);
void emit_target(enum iopcode op, expr *arg1, expr *arg2, expr *result, int target, unsigned label, unsigned line);
expr* emit_if_tableitem(expr* e, unsigned int scope, unsigned int line);
const char* iopcode_tostring(enum iopcode);
void printQuads();
void shiftQuads(int number, int offset);
int count_str(const char* str);
quad* get_quads();

//for functions
unsigned nextQuadLabel();
void patchLabel(unsigned quadNo, unsigned label);


stmt_t* make_stmt ();
int     new_list  (int i);
int     merge_list(int l1, int l2);
void    patch_list(int list, int label);
void    back_patch(int list, int label);
void patch_jump_to_jump_labels();
int is_int(double num);
void quads_to_external_file();
#endif /* QUAD_H */