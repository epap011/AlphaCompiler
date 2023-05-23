#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

enum vmopcode{
    assign_vm, add_vm, sub_vm, mul_vm, div_vm, mod_vm, 
    not_vm, 
    jmp_vm, jeq_vm, jne_vm, jle_vm, jge_vm, jlt_vm, jgt_vm, 
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
    retval_a,
    label_a,
    undef_a
};

typedef struct vmarg {
    enum vmarg_t type;
    unsigned val;
} vmarg;

typedef struct instuction {
    enum vmopcode opcode;
    vmarg* result;
    vmarg* arg1;
    vmarg* arg2;
    unsigned int srcLine;
} instruction;

typedef struct user_func_t {
    unsigned iaddress;
    unsigned total_locals;
    const char* name;
} user_func_t;

#endif // INSTRUCTIONS_H