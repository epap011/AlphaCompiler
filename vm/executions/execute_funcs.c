#include "execute.h"
#include "avm_helpers.h"
#include <stdio.h>

#define AVM_ENDING_PC codeSize

extern avm_memcell ax, bx, cx;
extern avm_memcell retval;
extern unsigned top, topsp;
extern unsigned pc;
extern avm_memcell stack[AVM_STACKSIZE];
extern unsigned char executionFinished;
extern instruction **code;
extern unsigned codeSize;

extern unsigned currLine;
extern unsigned totalActuals;

void execute_call(instruction* instr){
    avm_memcell* func = avm_translate_operand(&instr->result, &ax);
    assert(func);
    switch(func->type){
        case userfunc_m:{
            amv_callsaveenvironment();
            pc = func->data.funcVal;
            assert(pc < AVM_ENDING_PC);
            assert(code[pc]->opcode == funcenter_vm);
            break;
        }
        case string_m: avm_calllibfunc(func->data.strVal); break;
        case libfunc_m: avm_calllibfunc(func->data.libfuncVal); break;
        case table_m: avm_call_functor(func->data.tableVal); break;

        default:{
            char* s = avm_tostring(func);
            avm_error("call: cannot bind '%s' to function!", s);
            free(s);
            executionFinished = 1;
        }
    }
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
