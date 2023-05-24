#ifndef _EXECUTE_H_
#define _EXECUTE_H_

#include "instructions.h"
#include <assert.h>
#include <stdio.h>
#include "avm_types.h"
#include "avm_stack.h"

#define AVM_MAX_INSTRUCTIONS (unsigned) nop_vm

typedef void (*execute_func_t)(instruction *);

#define execute_add execute_arithmetic
#define execute_sub execute_arithmetic
#define execute_mul execute_arithmetic
#define execute_div execute_arithmetic
#define execute_mod execute_arithmetic


void execute_arithmetic(instruction* instr);
void execute_assign(instruction * instr);
/*void execute_add(instruction * instr);
void execute_sub(instruction * instr);
void execute_mul(instruction * instr); 
void execute_div(instruction * instr);
void execute_mod(instruction * instr);*/

void execute_jmp(instruction * instr);

void execute_jeq(instruction * instr);
void execute_jne(instruction * instr);
void execute_jle(instruction * instr);
void execute_jge(instruction * instr);
void execute_jlt(instruction * instr);
void execute_jgt(instruction * instr);

void execute_call(instruction * instr);
void execute_pusharg(instruction * instr);
void execute_funcenter(instruction * instr);
void execute_funcexit(instruction * instr);

void execute_newtable(instruction * instr);
void execute_tablegetelem(instruction * instr);
void execute_tablesetelem(instruction * instr);

void execute_nop(instruction * instr);

void avm_assign (avm_memcell * lv, avm_memcell * rv);

#endif // _EXECUTE_H_