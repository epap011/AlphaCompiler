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

void libfunc_typeof(void){
    
    unsigned n = avm_totalactuals();

    if(n != 1){
        char * buffer = malloc(sizeof(char) * 128);
        sprintf(buffer, "one argument (not %d) expected in 'typeof'!", n);
        avm_error(buffer, currLine);
        free(buffer);
    }
    else{
        avm_memcell_clear(&retval);
        retval.type = string_m;
        retval.data.strVal = strdup(typeStrings[avm_getactual(0)->type]);
    }
}