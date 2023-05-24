#include "avm_stack.h"

avm_memcell stack[AVM_STACKSIZE];

void avm_initstack(){
    for(unsigned i = 0; i < AVM_STACKSIZE; ++i){
        AVM_WIPEOUT(stack[i]);
        stack[i].type = undef_m;
    }
}

void print_vm_stack() {
    for (int i = AVM_STACKSIZE-1; i >= 0; i--) {
        printf("stack[%d]: ", i);
        switch (stack[i].type) {
            case number_m:
                printf("%lf\n", stack[i].data.numVal);
                break;
            case string_m:
                printf("%s\n", stack[i].data.strVal);
                break;
            case bool_m:
                printf("%d\n", stack[i].data.boolVal);
                break;
            case table_m:
                printf("table\n");
                break;
            case userfunc_m:
                printf("userfunc\n");
                break;
            case libfunc_m:
                printf("libfunc\n");
                break;
            case nil_m:
                printf("nil\n");
                break;
            case undef_m:
                printf("undef\n");
                break;
            default:
                printf("Unknown type\n");
                break;
        }
    }
}