#include "expression.h"
#include "quad.h"

expr* new_expr(enum expr_t type){
    expr* e = (expr*)malloc(sizeof(expr));
    memset(e, 0, sizeof(expr));

    e->next = (expr*)0;
    e->type = type;

    return e;
}

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
    e->hidden_var = NULL;

    return e;   
}

expr* new_const_num(double n){
    
    expr* e = new_expr(constnum_e);
    e->numConst = n;

    return e;
}

expr* new_const_string(char *str){
    
    expr* e = new_expr(conststring_e);
    e->strConst = strdup(str);

    return e;
}

expr* new_const_bool(int flag){
    
    expr* e = new_expr(constbool_e);
    e->boolConst = flag;


    return e;
}

expr* new_const_nil(){
     
     expr* e = new_expr(nil_e);

    return e;
}

expr* new_member_item(expr* lv, char* name, unsigned int scope, unsigned int line){
    lv = emit_if_tableitem(lv, scope, line);
    expr* ti = new_expr(tableitem_e);
    ti->sym = lv->sym;
    ti->index = new_const_string(name);
    return ti;
}