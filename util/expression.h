#ifndef EXPR_H
#define EXPR_H

#include "symbol_table.h"

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

#endif /* EXPR_H */