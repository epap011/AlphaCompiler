#ifndef INSTRUCTION_H
#define INSTRUCTION_H

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

void make_operand(expr* e, vmarg* arg);
void make_numberoperand(vmarg* arg, double val);  //helper for const
void make_booloperand(vmarg* arg, unsigned val);  //helper for const
void make_retvaloperand(vmarg* arg);              //helper for return values


unsigned conts_newstring(char* s);
unsigned conts_newnumber(double n);
unsigned libfuncs_newused(char* s);
unsigned userfuncs_newfunc(Symbol* sym);


#endif /* INSTRUCTION_H */