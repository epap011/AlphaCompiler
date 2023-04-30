#ifndef EXPR_H
#define EXPR_H

#include "symbol_table.h"
#include <assert.h>

enum expr_t{

    var_e,            //symbol
    tableitem_e,      //index

    programfunc_e,    //symbol
    libraryfunc_e,    //symbol

    arithexpr_e, 
    boolexpr_e,
    assignexpr_e,
    newtable_e,

    constnum_e,
    constbool_e,
    conststring_e,

    nil_e

};

typedef struct expr{

    enum expr_t type;
    Symbol* sym;
    struct expr* index;  
    double numConst;
    char* strConst;
    unsigned char boolConst;
    struct expr* next;

} expr;

expr* lvalue_expr(Symbol* sym);
expr* new_const_num(double n);

#endif /* EXPR_H */