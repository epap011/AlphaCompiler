#include "expression.h"


enum iopcode{

    assign, add, sub, mul, div, mod, uminus,
    and, or, not,
    if_eq, if_noteq, if_lesseq, if_greatereq, if_less, if_greater,
    call, param, ret, getretval,
    funcstart, funcend,
    tablecreate, tablegetelem, tablesetelem,
    jump
};


struct quad{

    iopcode op;
    expr* result;
    expr* arg1;
    expr* arg2;
    unsigned label;
    unsigned line;

};
