#include "execute.h"
#include <stdio.h>
#include <assert.h>

extern avm_memcell ax, bx, cx;
extern avm_memcell retval;
extern unsigned top, topsp;
extern avm_memcell stack[AVM_STACKSIZE];
extern unsigned char executionFinished;
extern unsigned currLine;

extern char* register_type_to_string(avm_memcell_t type);

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

    assert(instr->result);
    assert(instr->arg1);
    assert(instr->arg2);

    printf("result: %s\n", register_type_to_string(instr->result->type));

    avm_memcell* table = avm_translate_operand(instr->result, (avm_memcell*) 0);
    avm_memcell* key   = avm_translate_operand(instr->arg1  , &ax);
    avm_memcell* value = avm_translate_operand(instr->arg2  , &bx);

    assert(table && &stack[AVM_STACKSIZE - 1] >= table && table > &stack[top]);
    assert(key && value);

    if(table->type != table_m){
        char* msg = malloc(sizeof(char) * 128);
        sprintf(msg, "illegal use of type %s as table", register_type_to_string(table->type));
        avm_error(msg, currLine);
    }
    else{
        avm_table_setelem(table->data.tableVal, key, value);
    }
}

void execute_nop(instruction* instr){
    printf("execute_nop\n");
}

