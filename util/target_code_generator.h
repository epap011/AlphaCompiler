#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include "quad.h"

#include "expression.h"

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
    label_a
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

void make_operand      (expr* e, vmarg* arg);
void make_numberoperand(vmarg* arg, double val);  //helper for const
void make_booloperand  (vmarg* arg, unsigned val);//helper for const
void make_retvaloperand(vmarg* arg);              //helper for return values

unsigned consts_newstring  (char* s);
unsigned consts_newnumber  (double n);
unsigned libfuncs_newused  (const char* s);

char* vmopcode_to_string(enum vmopcode op);
char* vmarg_t_to_string (enum vmarg_t arg);

void generate             ();
void generate_ADD         (quad* quad);
void generate_SUB         (quad* quad);
void generate_MUL         (quad* quad);
void generate_DIV         (quad* quad);
void generate_MOD         (quad* quad);
void generate_NEWTABLE    (quad* quad);
void generate_TABLEGETELEM(quad* quad);
void generate_TABLESETELEM(quad* quad);
void generate_ASSIGN      (quad* quad);
void generate_NOP         (quad* quad);
void generate_JUMP        (quad* quad);
void generate_IF_EQ       (quad* quad);
void generate_IF_NOTEQ    (quad* quad);
void generate_IF_GREATER  (quad* quad);
void generate_IF_GREATEREQ(quad* quad);
void generate_IF_LESS     (quad* quad);
void generate_IF_LESSEQ   (quad* quad);
void generate_NOT         (quad* quad);
void generate_OR          (quad* quad);
void generate_PARAM       (quad* quad);
void generate_CALL        (quad* quad);
void generate_GETRETVAL   (quad* quad);
void generate_FUNCSTART   (quad* quad);
void generate_RETURN      (quad* quad);
void generate_FUNCEND     (quad* quad);
void generate_UMINUS      (quad* quad);
void generate_AND         (quad* quad);

void emit_instruction  (instruction* t);
void print_instructions();

#endif /* INSTRUCTION_H */