#include "execute.h"
#include <stdio.h>

void execute_call(instruction* instr){
    printf("execute_call\n");
}

void execute_pusharg(instruction* instr){
    printf("execute_pusharg\n");
}

void execute_funcenter(instruction* instr){
    printf("execute_funcenter\n");
}

void execute_funcexit(instruction* instr){
    printf("execute_funcexit\n");
}
