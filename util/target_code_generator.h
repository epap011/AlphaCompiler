#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include "quad.h"

#include "expression.h"

enum vmopcode{
    assign_vm, add_vm, sub_vm, mul_vm, div_vm, mod_vm, 
    not_vm, 
    jeq_vm, jne_vm, jle_vm, jge_vm, jlt_vm, jgt_vm, 
    call_vm, pusharg_vm, funcenter_vm, funcexit_vm, 
    newtable_vm, tablegetelem_vm, tablesetelem_vm, nop_vm
};

enum vmarg_t{

    global_a,
    local_a,
    formal_a,
    number_a,
    string_a,
    bool_a,
    nil_a,
    userfunc_a,
    libfunc_a,
    retval_a
};

typedef struct vmarg {
    enum vmarg_t type;
    unsigned val;
} vmarg;

typedef struct instuction {
    enum vmopcode opcode;
    vmarg result;
    vmarg arg1;
    vmarg arg2;
    unsigned int srcLine;
} instruction;

void make_operand      (expr* e, vmarg* arg);
void make_numberoperand(vmarg* arg, double val);  //helper for const
void make_booloperand  (vmarg* arg, unsigned val);//helper for const
void make_retvaloperand(vmarg* arg);              //helper for return values

unsigned conts_newstring  (char* s);
unsigned conts_newnumber  (double n);
unsigned libfuncs_newused (char* s);
unsigned userfuncs_newfunc(Symbol* sym);

extern void generate_ADD         (quad* quad);
extern void generate_SUB         (quad* quad);
extern void generate_MUL         (quad* quad);
extern void generate_DIV         (quad* quad);
extern void generate_MOD         (quad* quad);
extern void generate_NEWTABLE    (quad* quad);
extern void generate_TABLEGETELEM(quad* quad);
extern void generate_TABLESETELEM(quad* quad);
extern void generate_ASSIGN      (quad* quad);
extern void generate_NOP         (quad* quad);
extern void generate_JUMP        (quad* quad);
extern void generate_IF_EQ       (quad* quad);
extern void generate_IF_NOTEQ    (quad* quad);
extern void generate_IF_GREATER  (quad* quad);
extern void generate_IF_GREATEREQ(quad* quad);
extern void generate_IF_LESS     (quad* quad);
extern void generate_IF_LESSEQ   (quad* quad);
extern void generate_NOT         (quad* quad);
extern void generate_OR          (quad* quad);
extern void generate_PARAM       (quad* quad);
extern void generate_CALL        (quad* quad);
extern void generate_GETRETVAL   (quad* quad);
extern void generate_FUNCSTART   (quad* quad);
extern void generate_RETURN      (quad* quad);
extern void generate_FUNCEND     (quad* quad);
extern void generate_UMINUS      (quad* quad);
extern void generate_AND         (quad* quad);

#endif /* INSTRUCTION_H */