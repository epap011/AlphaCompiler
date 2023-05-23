#ifndef AVM_STACK_H
#define AVM_STACK_H

#include "avm_types.h"

#define AVM_STACKSIZE 4096

avm_memcell stack[AVM_STACKSIZE];

static void avm_initstack(void);

#endif // AVM_STACK_H