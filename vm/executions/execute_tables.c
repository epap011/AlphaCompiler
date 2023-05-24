#include "execute.h"
#include <stdio.h>

void execute_newtable(instruction* instr){
    printf("execute_newtable\n");
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

