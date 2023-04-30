#include "expression.h"

expr* new_lvalue_expr(Symbol* sym){
    assert(sym);
    expr* e = (expr*)malloc(sizeof(expr));
    memset(e, 0, sizeof(expr));
    
    e->next = (expr*)0;
    e->sym = sym;

    switch(sym->type){
        case var_s          : e->type = var_e; break;
        case programfunc_s  : e->type = programfunc_e; break;
        case libraryfunc_s  : e->type = libraryfunc_e; break;
        default : assert(0);
    }

    return e;   
}

expr* new_const_num(double n){
    expr* e = (expr*)malloc(sizeof(expr));
    memset(e, 0, sizeof(expr));

    e->next = (expr*)0;
    e->numConst = n;
    e->type = constnum_e;
}