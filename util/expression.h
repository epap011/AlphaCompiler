#ifndef EXPR_H
#define EXPR_H

#include "symbol_table.h"
#include <assert.h>

enum expr_t{

    var_e,            //symbol
    tableitem_e,      //index

    programfunc_e,    //symbol
    libraryfunc_e,    //symbol

    arithexpr_e,      //unused
    boolexpr_e,       //unused
    assignexpr_e,     //unused

    newtable_e,      //table create

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

    struct expr* hidden_var;

} expr;

expr* new_expr(enum expr_t type);

expr* new_lvalue_expr(Symbol* sym);
expr* new_const_num(double n);
expr* new_const_string(char *str);
expr* new_const_bool(int flag);
expr* new_const_nil();
expr* new_member_item(expr* lv, char* name, unsigned int scope, unsigned int line);

#endif /* EXPR_H */