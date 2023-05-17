#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include "expression.h"

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
    vmarg_t type;
    unsigned val;
} vmarg;

typedef struct instuction {
    //vmopcode opcode;
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