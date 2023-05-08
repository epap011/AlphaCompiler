#include "expression.h"
#include "quad.h"

//Returns 1 if operation is illegal, 0 otherwise
int check_arith(expr* e, FILE* out, unsigned int line, char* op){

    if(e->type == constbool_e || e->type == boolexpr_e){
        fprintf(out, ""RED"Error:"RESET" Illegal expression type \""YEL"Boolean"RESET"\" for %s operation (line: " GRN "%d" RESET ")\n",op, line);
        return 1;
    }
    else if(  e->type == conststring_e){
        fprintf(out, ""RED"Error:"RESET" Illegal expression type \""YEL"String"RESET"\" for %s operation (line: " GRN "%d" RESET ")\n",op, line);
        return 1;
    }
    else if(e->type == nil_e){
        fprintf(out, ""RED"Error:"RESET" Illegal expression type \""YEL"NIL"RESET"\" for %s operation (line: " GRN "%d" RESET ")\n",op, line);
        return 1;
    }
    else if ( e->type == newtable_e){
        fprintf(out, ""RED"Error:"RESET" Illegal expression type \""YEL"table definition"RESET"\" for %s operation (line: " GRN "%d" RESET ")\n",op, line);
        return 1;
    }
    else if (e->type == programfunc_e){
        fprintf(out, ""RED"Error:"RESET" Illegal expression type \""YEL"function"RESET"\" for %s operation (line: " GRN "%d" RESET ")\n",op, line);
        return 1;
    }
    else if(e->type == libraryfunc_e){
        fprintf(out, ""RED"Error:"RESET" Illegal expression type \""YEL"Library function"RESET"\" for %s operation (line: " GRN "%d" RESET ")\n",op, line);
        return 1;
    }

    return 0;
}

expr* new_expr(enum expr_t type){
    expr* e = (expr*)malloc(sizeof(expr));
    memset(e, 0, sizeof(expr));

    e->next = (expr*)0;
    e->type = type;
    e->hidden_var = NULL;

    e->truelist = -1;   //null
    e->falselist = -1;

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

    e->truelist = -1;   //null
    e->falselist = -1;


    return e;   
}

expr* new_const_num(double n){
    
    expr* e = new_expr(constnum_e);
    e->numConst = n;

    e->hidden_var = NULL;

    e->truelist = -1;   //null
    e->falselist = -1;


    return e;
}

expr* new_const_string(char *str){
    
    expr* e = new_expr(conststring_e);
    e->strConst = strdup(str);
    
    e->hidden_var = NULL;

    e->truelist = -1;   //null
    e->falselist = -1;

    return e;
}

expr* new_const_bool(int flag){
    
    expr* e = new_expr(constbool_e);
    e->boolConst = flag;
    
    e->hidden_var = NULL;

    e->truelist = -1;   //null
    e->falselist = -1;

    return e;
}

expr* new_const_nil(){
     
    expr* e = new_expr(nil_e);

    e->hidden_var = NULL;

    e->truelist = -1;   //null
    e->falselist = -1;

    return e;
}

expr* new_member_item(expr* lv, char* name, unsigned int scope, unsigned int line){
    lv = emit_if_tableitem(lv, scope, line);
    expr* ti = new_expr(tableitem_e);
    ti->sym = lv->sym;
    ti->index = new_const_string(name);
    ti->hidden_var = NULL;

    ti->truelist = -1;   //null
    ti->falselist = -1;

    return ti;
}

callexpr* new_callexpr(unsigned int method, expr* elist, char* name){
    callexpr* e = (callexpr*)malloc(sizeof(callexpr));
    memset(e, 0, sizeof(callexpr));
    
    e->method = method;
    e->elist = elist;
    e->name = name;
    
    return e;
}