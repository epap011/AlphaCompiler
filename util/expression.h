#include "symboltable.h"


enum expr_t{

    var_e,
    tableitem_e,

    programfunc_e,
    libraryfunc_e,

    arithexpr_e,
    boolexpr_e,
    assignexpr_e,
    newtable_e,

    constnum_e,
    constbool_e,
    conststring_e,

    nil_e

};

struct expr{

    expr_t type;
    Symbol* sym;
    expr* index;
    double numConst;
    char* strConst;
    unsigned char boolConst;
    expr* next;

};