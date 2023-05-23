#include "avm_stack.h"

avm_memcell stack[AVM_STACKSIZE];

void avm_initstack(){
    for(unsigned i = 0; i < AVM_STACKSIZE; ++i){
        AVM_WIPEOUT(stack[i]);
        stack[i].type = undef_m;
    }
}