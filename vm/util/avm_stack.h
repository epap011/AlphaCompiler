#ifndef AVM_STACK_H
#define AVM_STACK_H

#include "avm_table.h"
#include "../avm.h"


#define AVM_STACKSIZE 4096
#define AVM_WIPEOUT(m) memset(&(m), 0, sizeof(m))


avm_memcell stack[AVM_STACKSIZE];

static void avm_initstack(void);

#endif // AVM_STACK_H