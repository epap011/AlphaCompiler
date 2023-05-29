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

void libfunc_sqrt(){

    unsigned n = avm_totalactuals();
    if(n != 1){
        char * buffer = malloc(sizeof(char) * 128);
        sprintf(buffer, "one argument (not %d) expected in 'sqrt'!", n);
        avm_error(buffer, currLine);
        free(buffer);
        return ;
    }

    avm_memcell *lib_arg = avm_getactual(0);  

    if(lib_arg->type != number_m){
        char * buffer = malloc(sizeof(char) * 128);
        sprintf(buffer, "'sqrt' takes only numeric arguments! not" YEL" %s" RESET, typeStrings[lib_arg->type]);
        avm_error(buffer, currLine);
        free(buffer);
    }
    else{
        if(lib_arg->data.numVal < 0){
            char * buffer = malloc(sizeof(char) * 128);
            sprintf(buffer, "argument of 'sqrt' must be positive!");
            avm_warning(buffer, currLine);
            free(buffer);
            retval.type = nil_m;
        }
        else{
            avm_memcell_clear(&retval);
            retval.type = number_m;
            retval.data.numVal = sqrt(lib_arg->data.numVal);
        }
    }
}