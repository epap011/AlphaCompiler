#ifndef _EXECUTE_H_
#define _EXECUTE_H_

#include "instructions.h"
#include <assert.h>
#include <stdio.h>
#include "avm_types.h"
#include "avm_stack.h"

#define AVM_MAX_INSTRUCTIONS (unsigned) nop_vm

typedef void (*execute_func_t)(instruction *);
typedef unsigned char (*tobool_func_t)(avm_memcell *);

#define execute_add execute_arithmetic
#define execute_sub execute_arithmetic
#define execute_mul execute_arithmetic
#define execute_div execute_arithmetic
#define execute_mod execute_arithmetic

#define execute_jle execute_relational
#define execute_jge execute_relational
#define execute_jlt execute_relational
#define execute_jgt execute_relational


void execute_arithmetic(instruction* instr);
void execute_assign(instruction * instr);

void execute_jmp(instruction * instr);

void execute_relational(instruction * instr);
void execute_jeq(instruction * instr);
void execute_jne(instruction * instr);

unsigned char avm_tobool(avm_memcell * m);
unsigned char number_tobool(avm_memcell * m);
unsigned char string_tobool(avm_memcell * m);
unsigned char bool_tobool(avm_memcell * m);
unsigned char table_tobool(avm_memcell * m);
unsigned char userfunc_tobool(avm_memcell * m);
unsigned char libfunc_tobool(avm_memcell * m);
unsigned char nil_tobool(avm_memcell * m);
unsigned char undef_tobool(avm_memcell * m);


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