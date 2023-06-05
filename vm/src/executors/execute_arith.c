#include "execute.h"
#include "../tables/avm_tables.h"

extern avm_memcell ax, bx, cx;
extern avm_memcell retval;
extern unsigned top, topsp;
extern avm_memcell stack[AVM_STACKSIZE];
extern unsigned char executionFinished;

extern unsigned currLine;
extern char * typeStrings[];

extern int DEBUG;

char* typeArithOP[] = {
    "undef",
    "+",
    "-",
    "*",
    "/",
    (char *)'%'
};


typedef double (*arithmetic_func_t)(double x, double y);

double add_impl(double x, double y){
    if(DEBUG) printf("Executed add\n");
    return x + y;
}

double sub_impl(double x, double y){
    if(DEBUG) printf("Executed sub\n");
    return x - y;
}

double mul_impl(double x, double y){
    if(DEBUG) printf("Executed mul\n");
    return x * y;
}

double div_impl(double x, double y){
    if(DEBUG) printf("Executed div\n");
    if(y == 0){
        avm_error("Cant divide by  0", currLine);
        executionFinished = 1;
    }
     return x / y;
}

double mod_impl(double x, double y){
    if(DEBUG) printf("Executed mod\n");
    return ((unsigned) x) % ((unsigned) y);
}

arithmetic_func_t arithmeticFuncs[] = {
    add_impl,
    sub_impl,
    mul_impl,
    div_impl,
    mod_impl
};

void execute_arithmetic(instruction* instr){
    if(DEBUG) printf("execute_arithmetic\n");

    avm_memcell* lv;
    if(instr->result->type == number_a)  //result is a constnum when both args are consts -> we need to use the third register
         lv = avm_translate_operand(instr->result, &cx);
    else
         lv = avm_translate_operand(instr->result, (avm_memcell*) 0);
    avm_memcell* rv1 = avm_translate_operand(instr->arg1, &ax);
    avm_memcell* rv2 = avm_translate_operand(instr->arg2, &bx);

    if(instr->result->type != number_a) //when result is a constnum, this assert doesnt have meaning
        assert((&stack[AVM_STACKSIZE - 1] >= lv && lv > &stack[top]) || lv == &retval);
    assert(lv);
    assert(rv1 && rv2);

    if(rv1->type != number_m || rv2->type != number_m ){
        char *buffer = malloc(sizeof(char) * 256);
        sprintf(buffer, "not a number in arithmetic operation ("YEL"%s" RESET " %s"YEL" %s" RESET")!", typeStrings[rv1->type], typeArithOP[instr->opcode], typeStrings[rv2->type]);
        avm_error(buffer, currLine);  
        free(buffer);
    }   
    else{
        arithmetic_func_t op = arithmeticFuncs[instr->opcode - add_vm];
        avm_memcell_clear(lv);
        lv->type = number_m;
        lv->data.numVal = (*op)(rv1->data.numVal, rv2->data.numVal);
    }
}