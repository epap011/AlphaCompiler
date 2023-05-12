#ifndef EXPR_H
#define EXPR_H

#include "symbol_table.h"
#include <assert.h>

enum expr_t{

    var_e,            //symbol
    tableitem_e,      //lvalue[]

    programfunc_e,    //symbol
    libraryfunc_e,    //symbol

    arithexpr_e,      //hidden var - arithop
    boolexpr_e,       
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
    struct expr* next;          //for elist/indexed

    struct expr* hidden_var;

    linked_list* truelist;
    linked_list* falselist;

    unsigned int firstQuad;

} expr;

typedef struct callexpr{
    unsigned int method;
    expr* elist;
    char* name;
} callexpr;

int check_arith(expr* e, FILE* error_out, unsigned int line, char* op);

expr* new_expr(enum expr_t type);

expr* new_lvalue_expr(Symbol* sym);
expr* new_const_num(double n);
expr* new_const_string(char *str);
expr* new_const_bool(int flag);
expr* new_const_nil();
expr* new_member_item(expr* lv, char* name, unsigned int scope, unsigned int line);
callexpr* new_callexpr(unsigned int method, expr* elist, char* name);

#endif /* EXPR_H */