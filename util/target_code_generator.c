#include "target_code_generator.h"
#include "quad.h"

typedef void (*generator_func_t)(quad*);

generator_func_t generators[] = {
    generate_ADD,         
    generate_SUB,         
    generate_MUL,         
    generate_DIV,         
    generate_MOD,         
    generate_NEWTABLE,    
    generate_TABLEGETELEM,
    generate_TABLESETELEM,
    generate_ASSIGN,      
    generate_NOP,         
    generate_JUMP,        
    generate_IF_EQ,       
    generate_IF_NOTEQ,    
    generate_IF_GREATER,  
    generate_IF_GREATEREQ,
    generate_IF_LESS,     
    generate_IF_LESSEQ,   
    generate_NOT,         
    generate_OR,          
    generate_PARAM,       
    generate_CALL,        
    generate_GETRETVAL,   
    generate_FUNCSTART,   
    generate_RETURN,      
    generate_FUNCEND,     
};

#include "target_code_generator.h"

void make_operand(expr* e, vmarg* arg){

    switch (e->type)
    {
    
    case var_e:
    case tableitem_e:
    case arithexpr_e:
    case boolexpr_e:
    case newtable_e: {
        assert(e->sym);
        arg->val = e->sym->offset;
        switch (e->sym->space)
        {
            case programvar: arg->type = global_a; break;
            case functionlocal: arg->type = local_a; break;
            case formalarg: arg->type = formal_a; break;
            default: assert(0);
        }
    } 
        break;

    case constbool_e: {
        arg->val = e->boolConst;
        arg->type = bool_a;
    }
        break;
    
    case conststring_e: {
        arg->val = consts_newstring(e->strConst); // make this function
        arg->type = string_a;
    }
        break;
    
    case constnum_e: {
        arg->val = consts_newnumber(e->numConst); // make this function
        arg->type = number_a;
    }
        break;

    case nil_e: 
        arg->type = nil_a; break;

    case programfunc_e: {
        arg->type = userfunc_a;
        arg->val = userfuncs_newfunc(e->sym); // make this function
    }
        break;

    case libraryfunc_e: {
        arg->type = libfunc_a;
        arg->val = libfuncs_newused(e->sym->name); // make this function
    }
        break;
    
    default: assert(0);
    }
}

void make_numberoperand(vmarg* arg, double val){
    arg->val = consts_newnumber(val);
    arg->type = number_a;
}   

void make_booloperand(vmarg* arg, unsigned val){
    arg->val = val;
    arg->type = bool_a;
}

void make_retvaloperand(vmarg* arg){
    arg->type = retval_a;
}


unsigned conts_newstring(char* s){

    return 0;
}
unsigned conts_newnumber(double n){
    
    return 0;
}
unsigned libfuncs_newused(char* s){

    return 0;
}
unsigned userfuncs_newfunc(Symbol* sym){

    return 0;
}
void generate(void) {
    int total_quads = nextQuadLabel();
    quad *quads = get_quads();
    for (unsigned i = 0; i < total_quads; ++i) {
        (*generators[quads[i].op])(quads+i);
    }
}