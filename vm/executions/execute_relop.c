#include "execute.h"
#include <stdio.h>


tobool_func_t toboolFuncs[] = {
    number_tobool,
    string_tobool,
    bool_tobool,
    table_tobool,
    userfunc_tobool,
    libfunc_tobool,
    nil_tobool,
    undef_tobool
};

unsigned char avm_tobool(avm_memcell * m){
    assert(m->type >= 0 && m->type < undef_m);
    return (*toboolFuncs[m->type])(m);
}

unsigned char number_tobool  (avm_memcell * m){return m->data.numVal != 0;}
unsigned char string_tobool  (avm_memcell * m){return m->data.strVal[0] != 0;}
unsigned char bool_tobool    (avm_memcell * m){return m->data.boolVal;}
unsigned char table_tobool   (avm_memcell * m){return 1;}
unsigned char userfunc_tobool(avm_memcell * m){return 1;}
unsigned char libfunc_tobool (avm_memcell * m){return 1;}
unsigned char nil_tobool     (avm_memcell * m){return 0;}
unsigned char undef_tobool   (avm_memcell * m){return 0;}

void execute_jeq(instruction* instr){
    printf("execute_jeq\n");

    assert(instr->result == label_a);
}

void execute_jne(instruction* instr){
    printf("execute_jne\n");
}

void execute_jle(instruction* instr){
    printf("execute_jle\n");
}

void execute_jge(instruction* instr){
    printf("execute_jge\n");
}

void execute_jlt(instruction* instr){
    printf("execute_jlt\n");
}

void execute_jgt(instruction* instr){
    printf("execute_jgt\n");
}

void execute_jmp(instruction* instr){
    printf("execute_jmp\n");
}