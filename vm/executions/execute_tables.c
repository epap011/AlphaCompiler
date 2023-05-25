#include "execute.h"
#include <stdio.h>
#include <assert.h>

extern avm_memcell ax, bx, cx;
extern avm_memcell retval;
extern unsigned top, topsp;
extern avm_memcell stack[AVM_STACKSIZE];
extern unsigned char executionFinished;

extern unsigned currLine;

void execute_newtable(instruction* instr){
    printf("execute_newtable\n");

    avm_memcell* lv = avm_translate_operand(instr->result, (avm_memcell*) 0);
    assert(lv && ((&stack[AVM_STACKSIZE - 1] >= lv && lv > &stack[top]) || lv == &retval));

    avm_memcell_clear(lv);

    lv->type = table_m;
    lv->data.tableVal = avm_table_new();
    avm_table_inc_refcounter(lv->data.tableVal);
}

void execute_tablegetelem(instruction* instr){
    printf("execute_tablegetelem\n");
}

void execute_tablesetelem(instruction* instr){
    printf("execute_tablesetelem\n");
}

void execute_nop(instruction* instr){
    printf("execute_nop\n");
}

