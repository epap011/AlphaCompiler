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

void expand();
void emit(enum iopcode op, expr* arg1, expr* arg2, expr* result, unsigned label, unsigned line);
expr* emit_if_tableitem(expr* e, unsigned int scope, unsigned int line);
const char* iopcode_tostring(enum iopcode);
void printQuads();

//for functions
unsigned nextQuadLabel();
void patchLabel(unsigned quadNo, unsigned label);


#endif /* QUAD_H */