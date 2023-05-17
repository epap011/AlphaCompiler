#ifndef INSTRUCTION_H
#define INSTRUCTION_H

typedef struct vmarg {
    vmarg_t type;
    unsigned val;
} vmarg_t;

typedef struct instuction {
    //vmopcode opcode;
    vmarg_t result;
    vmarg_t arg1;
    vmarg_t arg2;
    unsigned int srcLine;
} instruction_t;


#endif /* INSTRUCTION_H */