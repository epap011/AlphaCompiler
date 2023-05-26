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

extern char * typeStrings[];
    
void execute_call(instruction* instr){
    avm_memcell* func = avm_translate_operand(instr->result, &ax);
    assert(func);
    switch(func->type){
        case userfunc_m:{
            amv_callsaveenvironment();
            pc = func->data.funcVal->iaddress;
            assert(pc < AVM_ENDING_PC);
            assert(code[pc]->opcode == funcenter_vm);
            break;
        }
        case string_m: avm_calllibfunc(func->data.strVal); break;
        case libfunc_m: avm_calllibfunc(func->data.libfuncVal); break;
        case table_m: avm_call_functor(func->data.tableVal); break;

        default:{
            char* error_text = malloc(sizeof(char) * 100);
            sprintf(error_text, "call: cannot bind "YEL"%s"RESET" to function!",typeStrings[func->type]);
            avm_error(error_text,currLine);
            free(error_text);
            executionFinished = 1;
        }
    }
}

void execute_pusharg(instruction* instr){
    avm_memcell *arg = avm_translate_operand(instr->result, &ax);
    assert(arg);

    avm_assign(&stack[top], arg);
    ++totalActuals;
    avm_dec_top();
}

void execute_funcenter(instruction* instr){
    avm_memcell* func = avm_translate_operand(instr->result, &ax);
    assert(func);
    assert(pc == func->data.funcVal->iaddress);

    totalActuals = 0;
    user_func_t* funcInfo = func->data.funcVal;

    topsp = top;
    top = top - funcInfo->total_locals;
}

void execute_funcexit(instruction* instr){
    unsigned oldTop = top;
    top = avm_get_envvalue(topsp + AVM_SAVEDTOP_OFFSET);
    pc = avm_get_envvalue(topsp + AVM_SAVEDPC_OFFSET);
    topsp = avm_get_envvalue(topsp + AVM_SAVEDTOPSP_OFFSET);

    while(++oldTop <= top)
        avm_memcell_clear(&stack[oldTop]);
}
