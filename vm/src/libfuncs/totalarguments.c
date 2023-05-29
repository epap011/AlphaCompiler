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

void libfunc_totalarguments(void){
    //Save topsp of previous activation record
    unsigned prev_topsp = avm_get_envvalue(topsp + AVM_SAVEDTOPSP_OFFSET);
    avm_memcell_clear(&retval);

    if(!prev_topsp){    //if prev_topsp == 0, then we are in global scope
        char * buffer = malloc(sizeof(char) * 128);
        sprintf(buffer, "'totalarguments' called outside of a function!");
        avm_warning(buffer, currLine);
        free(buffer);
        retval.type = nil_m;
    }
    else{
        retval.type = number_m;
        retval.data.numVal = avm_get_envvalue(prev_topsp + AVM_NUMACTUALS_OFFSET);
    }
}