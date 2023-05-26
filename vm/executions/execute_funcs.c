#include "execute.h"
#include <stdio.h>

extern avm_memcell ax, bx, cx;
extern avm_memcell retval;
extern unsigned top, topsp;
extern unsigned pc;
extern avm_memcell stack[AVM_STACKSIZE];
extern unsigned char executionFinished;

extern unsigned currLine;
extern unsigned totalActuals;

void execute_call(instruction* instr){
    printf("execute_call\n");
}

void execute_pusharg(instruction* instr){
    avm_memcell *arg = avm_translate_operand(&instr->result, &ax);
    assert(arg);

    avm_assign(&stack[top], arg);
    ++totalActuals;
    avm_dec_top();
}

void execute_funcenter(instruction* instr){
    printf("execute_funcenter\n");
}

void execute_funcexit(instruction* instr){
    printf("execute_funcexit\n");
}
