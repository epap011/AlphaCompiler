#include "execute.h"

extern avm_memcell ax, bx, cx;
extern avm_memcell retval;
extern unsigned top, topsp;
extern avm_memcell stack[AVM_STACKSIZE];
extern unsigned char executionFinished;

typedef double (*arithmetic_func_t)(double x, double y);

double add_impl(double x, double y){
    printf("Executed add\n");
    return x + y;
}

double sub_impl(double x, double y){
    printf("Executed sub\n");
    return x - y;
}

double mul_impl(double x, double y){
    printf("Executed mul\n");
    return x * y;
}

double div_impl(double x, double y){
    printf("Executed div\n");
    return x / y;
}

double mod_impl(double x, double y){
    printf("Executed mod\n");
    return ((unsigned) x) % ((unsigned) y);
}

arithmetic_func_t arithmeticFuncs[] = {
    add_impl,
    sub_impl,
    mul_impl,
    div_impl,
    mod_impl
};

void avm_assign(avm_memcell* lv, avm_memcell* rv){
    
    if(lv == rv)
        return;

    if(lv->type == table_m && 
       rv->type == table_m && 
       lv->data.tableVal == rv->data.tableVal)
        return;
    
    if(rv->type == undef_m)
        printf("Warrning : assigning from 'undef' content!\n");
    
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

void execute_arithmetic(instruction* instr){
    printf("execute_arithmetic\n");

    avm_memcell* lv;
    if(instr->result->type == number_a){
         lv = avm_translate_operand(instr->result, &cx);
    }
    else
         lv = avm_translate_operand(instr->result, (avm_memcell*) 0);
    avm_memcell* rv1 = avm_translate_operand(instr->arg1, &ax);
    avm_memcell* rv2 = avm_translate_operand(instr->arg2, &bx);

    printf("test\n");

    assert(lv && ((&stack[AVM_STACKSIZE - 1] >= lv && lv > &stack[top]) || lv == &retval));
    assert(rv1 && rv2);

    if(rv1->type != number_m || rv2->type != number_m ){
        printf("Error: not a number in arithmetic!\n");
        executionFinished = 1;
    }
    else{
        arithmetic_func_t op = arithmeticFuncs[instr->opcode - add_vm];
        avm_memcell_clear(lv);
        lv->type = number_m;
        lv->data.numVal = (*op)(rv1->data.numVal, rv2->data.numVal);
    }
}