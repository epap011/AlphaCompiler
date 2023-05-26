#include "execute.h"
#include <stdio.h>
#include <assert.h>

extern avm_memcell ax, bx, cx;
extern avm_memcell retval;
extern unsigned top, topsp;
extern avm_memcell stack[AVM_STACKSIZE];
extern unsigned char executionFinished;
extern unsigned currLine;

extern char * typeStrings[];

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

    assert(instr->result);
    assert(instr->arg1);
    assert(instr->arg2);

    avm_memcell* lv  = avm_translate_operand(instr->result, (avm_memcell*) 0);
    avm_memcell* table    = avm_translate_operand(instr->arg1, &ax);
    avm_memcell* index  = avm_translate_operand(instr->arg2, &bx);

    assert(lv && ((&stack[AVM_STACKSIZE - 1] >= lv && lv > &stack[top])));
    assert(table && &stack[AVM_STACKSIZE - 1] >= table && table > &stack[top]);
    assert(index);

    avm_memcell_clear(lv);
    lv->type = nil_m;

    if(table->type != table_m){
        char* msg = malloc(sizeof(char) * 128);
        sprintf(msg, "illegal use of type " YEL "%s" RESET" as table", typeStrings[table->type]);
        avm_error(msg, currLine);
    }
    else{
        avm_memcell* content = avm_table_getelem(table->data.tableVal, index);
        if(content)
            avm_assign(lv, content);
        else{
            char* buffer = malloc(sizeof(char) * 128);
            sprintf(buffer, YEL "%s" RESET"[%s] not found !", typeStrings[table->type], typeStrings[index->type]);
            avm_warning(buffer, currLine);
            free(buffer);
        }
    }
}

void execute_tablesetelem(instruction* instr){
    printf("execute_tablesetelem\n");

    assert(instr->result);
    assert(instr->arg1);
    assert(instr->arg2);

    printf("result: %s\n", typeStrings[instr->result->type]);

    avm_memcell* table = avm_translate_operand(instr->result, (avm_memcell*) 0);
    avm_memcell* key   = avm_translate_operand(instr->arg1  , &ax);
    avm_memcell* value = avm_translate_operand(instr->arg2  , &bx);

    assert(table && &stack[AVM_STACKSIZE - 1] >= table && table > &stack[top]);
    assert(key && value);

    if(table->type != table_m){
        char* msg = malloc(sizeof(char) * 128);
        sprintf(msg, "illegal use of type " YEL "%s" RESET" as table", typeStrings[table->type]);
        avm_error(msg, currLine);
    }
    else{
        avm_table_setelem(table->data.tableVal, key, value);
    }
}

void execute_nop(instruction* instr){
    printf("execute_nop\n");
}

