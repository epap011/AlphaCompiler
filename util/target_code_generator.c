#include "target_code_generator.h"
#include "quad.h"

typedef void (*generator_func_t)(quad*);

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
            arg->val = conts_newstring(e->strConst); // make this function
            arg->type = string_a;
            break;
        
        case constnum_e:
            arg->val = conts_newnumber(e->numConst); // make this function
            arg->type = number_a;
            break;

        case nil_e: 
            arg->type = nil_a; 
            break;

        case programfunc_e:
            arg->type = userfunc_a;
            arg->val = userfuncs_newfunc(e->sym); // make this function
            break;

        case libraryfunc_e:
            arg->type = libfunc_a;
            arg->val = libfuncs_newused(e->sym->name); // make this function
            break;
        
        default: assert(0);
    }
}

void make_numberoperand(vmarg* arg, double val){
    arg->val = conts_newnumber(val);
    arg->type = number_a;
}   

void make_booloperand(vmarg* arg, unsigned val){
    arg->val = val;
    arg->type = bool_a;
}

void make_retvaloperand(vmarg* arg){ arg->type = retval_a; }

unsigned conts_newstring  (char* s)    {return 0;}
unsigned conts_newnumber  (double n)   {return 0;}
unsigned libfuncs_newused (char* s)    {return 0;}
unsigned userfuncs_newfunc(Symbol* sym){return 0;}

void generate(void) {
    int total_quads = nextQuadLabel();
    quad *quads = get_quads();
    for (unsigned i = 0; i < total_quads; ++i) {
        (*generators[quads[i].op])(quads+i);
    }
}

void emit_instruction(instruction* t){}

void generate_ASSIGN(quad* q) {}

void generate_ADD   (quad* q) {
    instruction* i = (instruction*) malloc(sizeof(instruction));
    i->opcode  = add_vm;
    i->result  = (vmarg*) malloc(sizeof(vmarg));
    i->arg1    = (vmarg*) malloc(sizeof(vmarg));
    i->arg2    = (vmarg*) malloc(sizeof(vmarg));
    i->srcLine = q->line;

    make_operand(q->result, i->result);
    make_operand(q->arg1  , i->arg1);
    make_operand(q->arg2  , i->arg2); 

    emit_instruction(i);
}

void generate_SUB   (quad* q) {
    instruction* i = (instruction*) malloc(sizeof(instruction));
    i->opcode  = sub_vm;
    i->result  = (vmarg*) malloc(sizeof(vmarg));
    i->arg1    = (vmarg*) malloc(sizeof(vmarg));
    i->arg2    = (vmarg*) malloc(sizeof(vmarg));
    i->srcLine = q->line;

    make_operand(q->result, i->result);
    make_operand(q->arg1  , i->arg1);
    make_operand(q->arg2  , i->arg2); 

    emit_instruction(i);
}

void generate_MUL   (quad* q) {
    instruction* i = (instruction*) malloc(sizeof(instruction));
    i->opcode  = mul_vm;
    i->result  = (vmarg*) malloc(sizeof(vmarg));
    i->arg1    = (vmarg*) malloc(sizeof(vmarg));
    i->arg2    = (vmarg*) malloc(sizeof(vmarg));
    i->srcLine = q->line;

    make_operand(q->result, i->result);
    make_operand(q->arg1  , i->arg1);
    make_operand(q->arg2  , i->arg2); 

    emit_instruction(i);
}

void generate_DIV   (quad* q) {
    instruction* i = (instruction*) malloc(sizeof(instruction));
    i->opcode  = div_vm;
    i->result  = (vmarg*) malloc(sizeof(vmarg));
    i->arg1    = (vmarg*) malloc(sizeof(vmarg));
    i->arg2    = (vmarg*) malloc(sizeof(vmarg));
    i->srcLine = q->line;

    make_operand(q->result, i->result);
    make_operand(q->arg1  , i->arg1);
    make_operand(q->arg2  , i->arg2); 

    emit_instruction(i);    
}
void generate_MOD   (quad* q) {}
void generate_UMINUS(quad* q) {}
void generate_AND   (quad* q) {}
void generate_OR    (quad* q) {}
void generate_NOT   (quad* q) {}
void generate_IF_EQ (quad* q) {}
void generate_IF_NOTEQ(quad* q) {}
void generate_IF_LESSEQ(quad* q) {}
void generate_IF_GREATEREQ(quad* q) {}
void generate_IF_LESS(quad* q) {}
void generate_IF_GREATER(quad* q) {}
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