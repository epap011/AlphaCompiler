#include "target_code_generator.h"
#include "quad.h"
#include "linked_list.h"

typedef void (*generator_func_t)(quad*);

linked_list* num_const_list;
linked_list* str_const_list;
linked_list* lib_func_list;
linked_list* user_func_list;

generator_func_t generators[] = {
    generate_ASSIGN,     
    generate_ADD,
    generate_SUB,
    generate_MUL,
    generate_DIV,
    generate_MOD,
    generate_UMINUS,
    generate_AND,
    generate_OR,
    generate_NOT,
    generate_IF_EQ,
    generate_IF_NOTEQ,
    generate_IF_LESSEQ,
    generate_IF_GREATEREQ,
    generate_IF_LESS,
    generate_IF_GREATER,
    generate_CALL,
    generate_PARAM,
    generate_RETURN,
    generate_GETRETVAL,
    generate_FUNCSTART,
    generate_FUNCEND,
    generate_NEWTABLE,
    generate_TABLEGETELEM,
    generate_TABLESETELEM,
    generate_JUMP,
    generate_NOP
};

void make_operand(expr* e, vmarg* arg){
    switch (e->type) {
        case var_e:
            break;
        case tableitem_e:
            break;
        case arithexpr_e:
            break;
        case boolexpr_e:
            break;
        case newtable_e:
            assert(e->sym);
            arg->val = e->sym->offset;
            switch (e->sym->space) {
                case programvar: 
                    arg->type = global_a; 
                    break;
                case functionlocal: 
                    arg->type = local_a; 
                    break;
                case formalarg: 
                    arg->type = formal_a; 
                    break;
                default: assert(0);
            }
            break;

        case constbool_e:
            arg->val = e->boolConst;
            arg->type = bool_a;
            break;

        case conststring_e:
            arg->val = consts_newstring(e->strConst); 
            arg->type = string_a;
            break;
        
        case constnum_e:
            arg->val = consts_newnumber(e->numConst);
            arg->type = number_a;
            break;

        case nil_e: 
            arg->type = nil_a; 
            break;

        case programfunc_e:
            arg->type = userfunc_a;
            arg->val = e->sym->taddress; //we might need to change this
            break;

        case libraryfunc_e:
            arg->type = libfunc_a;
            arg->val = libfuncs_newused(e->sym->name); 
            break;
        
        default: assert(0);
    }
}

/**Helper functions for const values*/
void make_numberoperand(vmarg* arg, double val){
    arg->val = consts_newnumber(val);
    arg->type = number_a;
}   

void make_booloperand(vmarg* arg, unsigned val){
    arg->val = val;
    arg->type = bool_a;
}

void make_retvaloperand(vmarg* arg){ arg->type = retval_a; }

/**End of helpers*/

unsigned consts_newstring(char* s) {
    if(str_const_list == NULL) str_const_list = create_linked_list();
    char *str = strdup(s);
    insert_at_the_end_to_linked_list(str_const_list, str);
    return str_const_list->size - 1;
}
 
unsigned consts_newnumber(double n) {
    if(num_const_list == NULL) num_const_list = create_linked_list();
    double *num = (double*) malloc(sizeof(double));
    *num = n;
    insert_at_the_end_to_linked_list(num_const_list, num);
    return num_const_list->size - 1;
}

unsigned libfuncs_newused (const char* s)    {
    if(lib_func_list == NULL) lib_func_list = create_linked_list();
    char *str = strdup(s);
    insert_at_the_end_to_linked_list(lib_func_list, str);
    return lib_func_list->size - 1;
}

void generate(void) {
    int total_quads = nextQuadLabel();
    quad *quads = get_quads();
    for (unsigned i = 0; i < total_quads; ++i) {
        (*generators[quads[i].op])(quads+i);
    }
}

void emit_instruction(instruction* t){}

void generate_ARITHM(quad* q, enum vmopcode op) {
    instruction* i = (instruction*) malloc(sizeof(instruction));
    i->opcode  = op;
    i->result  = (vmarg*) malloc(sizeof(vmarg));
    i->arg1    = (vmarg*) malloc(sizeof(vmarg));
    i->arg2    = (vmarg*) malloc(sizeof(vmarg));
    i->srcLine = q->line;

    make_operand(q->result, i->result);
    make_operand(q->arg1  , i->arg1);
    make_operand(q->arg2  , i->arg2); 

    emit_instruction(i);
}

void generate_RELATIONAL(quad* q, enum vmopcode op) {
    instruction* i = (instruction*) malloc(sizeof(instruction));
    i->opcode  = op;
    i->result  = NULL;
    i->arg1    = (vmarg*) malloc(sizeof(vmarg));
    i->arg2    = (vmarg*) malloc(sizeof(vmarg));
    i->srcLine = q->line;

    make_operand(q->arg1, i->arg1);
    make_operand(q->arg2, i->arg2);

    emit_instruction(i);
}

void generate_ASSIGN(quad* q) {}

void generate_ADD   (quad* q) {generate_ARITHM(q, add_vm); }

void generate_SUB   (quad* q) {generate_ARITHM(q, sub_vm);}

void generate_MUL   (quad* q) {generate_ARITHM(q, mul_vm);}

void generate_DIV   (quad* q) {generate_ARITHM(q, div_vm);}

void generate_MOD   (quad* q) {generate_ARITHM(q, mod_vm);}

void generate_UMINUS(quad* q) {
    instruction* i = (instruction*) malloc(sizeof(instruction));
    i->opcode  = mul_vm;
    i->result  = (vmarg*) malloc(sizeof(vmarg));
    i->arg1    = (vmarg*) malloc(sizeof(vmarg));
    i->arg2    = (vmarg*) malloc(sizeof(vmarg));
    i->srcLine = q->line;

    make_operand(q->result, i->result);
    make_operand(q->arg1  , i->arg1);
    make_numberoperand(i->arg2, -1);

    emit_instruction(i);

}


void generate_AND   (quad* q) {}
void generate_OR    (quad* q) {}
void generate_NOT   (quad* q) {}

void generate_IF_EQ       (quad* q) {generate_RELATIONAL(q, jeq_vm);}
void generate_IF_NOTEQ    (quad* q) {generate_RELATIONAL(q, jne_vm);}
void generate_IF_LESSEQ   (quad* q) {generate_RELATIONAL(q, jle_vm);}
void generate_IF_GREATEREQ(quad* q) {generate_RELATIONAL(q, jge_vm);}
void generate_IF_LESS     (quad* q) {generate_RELATIONAL(q, jlt_vm);}
void generate_IF_GREATER  (quad* q) {generate_RELATIONAL(q, jgt_vm);}

void generate_CALL(quad* q) {}
void generate_PARAM(quad* q) {}
void generate_RETURN(quad* q) {}
void generate_GETRETVAL(quad* q) {}
void generate_FUNCSTART(quad* q) {}
void generate_FUNCEND(quad* q) {}
void generate_NEWTABLE(quad* q) {}
void generate_TABLEGETELEM(quad* q) {}
void generate_TABLESETELEM(quad* q) {}
void generate_JUMP(quad* q) {}
void generate_NOP(quad* q) {}