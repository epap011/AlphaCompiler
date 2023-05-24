#include "execute.h"

extern avm_memcell ax, bx, cx;
extern avm_memcell retval;
extern unsigned top, topsp;
extern avm_memcell stack[AVM_STACKSIZE];

void avm_assign(avm_memcell* lv, avm_memcell* rv){
    
    if(lv == rv)
        return;

    if(lv->type == table_m && 
       rv->type == table_m && 
       lv->data.tableVal == rv->data.tableVal)
        return;
    
    if(rv->type == undef_m)
        printf("assigning from 'undef' content!\n");
    
    avm_memcell_clear(lv);

    memcpy(lv, rv, sizeof(avm_memcell));

    if(lv->type == string_m)
        lv->data.strVal = strdup(rv->data.strVal);

    else if(lv->type == table_m)
        avm_table_inc_refcounter(lv->data.tableVal);
    
}

void execute_assign(instruction* instr){
    printf("execute_assign\n");

    avm_memcell* lv = avm_translate_operand(instr->result, (avm_memcell*) 0);
    avm_memcell* rv = avm_translate_operand(instr->arg1, &ax);

    assert(lv && ((&stack[AVM_STACKSIZE - 1] >= lv && lv > &stack[top]) || lv == &retval));
    assert(rv);

    avm_assign(lv, rv);
}

void execute_add(instruction* instr){
    printf("execute_add\n");
}

void execute_sub(instruction* instr){
    printf("execute_sub\n");
}

void execute_mul(instruction* instr){
    printf("execute_mul\n");
}

void execute_div(instruction* instr){
    printf("execute_div\n");
}

void execute_mod(instruction* instr){
    printf("execute_mod\n");
}