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

void libfunc_objecttotalmembers(){

    avm_memcell_clear(&retval);
    unsigned n = avm_totalactuals();
    if(n != 1){
        char * buffer = malloc(sizeof(char) * 128);
        sprintf(buffer, "one argument (not %d) expected in 'objecttotalmembers'!", n);
        avm_error(buffer, currLine);
        free(buffer);
        retval.type = nil_m;
        return;
    }

    avm_memcell *lib_arg = avm_getactual(0);

    if(lib_arg->type != table_m){
        char * buffer = malloc(sizeof(char) * 128);
        sprintf(buffer, "'objecttotalmembers' takes only table arguments! not" YEL" %s" RESET, typeStrings[lib_arg->type]);
        avm_error(buffer, currLine);
        free(buffer);
        retval.type = nil_m;
    }
    else{
        retval.type = number_m;
        retval.data.numVal = lib_arg->data.tableVal->total;
    }
}