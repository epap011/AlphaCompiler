#include "execute.h"
#include <stdio.h>

void execute_jmp(instruction* instr){
    printf("execute_jmp\n");
}

void execute_jeq(instruction* instr){
    printf("execute_jeq\n");
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