#ifndef AVM_STACK_H
#define AVM_STACK_H

#include "avm_types.h"

#define AVM_STACKSIZE 4
#define AVM_STACKENV_SIZE 4

void avm_initstack();
void print_vm_stack();

#endif // AVM_STACK_H