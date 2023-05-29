#include "avm_helpers.h"
#include "../stack/avm_stack.h"
#include "../tables/avm_tables.h"
#include <math.h>

extern int DEBUG;
extern unsigned currLine;
extern avm_memcell retval;
extern unsigned top, topsp;
extern avm_memcell stack[AVM_STACKSIZE];
extern char * typeStrings[];

void libfunc_print(void){
    unsigned n = avm_totalactuals();
    
    if(DEBUG) printf(BLU"AUTO TO PRINT EINAI TIS LIBFUNC: "RESET);
    unsigned i;
    for(i = 0; i < n; ++i){

        char* s = avm_tostring(avm_getactual(i));
        printf("%s", s);
        free(s);
    }
}
