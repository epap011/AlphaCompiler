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

void libfunc_strtonum(){

    unsigned n = avm_totalactuals();
    if(n != 1){
        char * buffer = malloc(sizeof(char) * 128);
        sprintf(buffer, "one argument (not %d) expected in 'strtonum'!", n);
        avm_error(buffer, currLine);
        free(buffer);
    }
    else{
        avm_memcell_clear(&retval);
        avm_memcell *lib_arg = avm_getactual(0);  //argument of 'libfunc' function
        
        if(lib_arg->type != string_m){
            char * buffer = malloc(sizeof(char) * 128);
            sprintf(buffer, "'strtonum' takes only string arguments! not" YEL" %s" RESET, typeStrings[lib_arg->type]);
            avm_error(buffer, currLine);
            free(buffer);
        }
        
        char *endptr;
        double val = strtod(lib_arg->data.strVal, &endptr);
        
        if(*endptr != '\0'){
            char * buffer = malloc(sizeof(char) * 128);
            sprintf(buffer, "convertion failed! argument of 'strtonum' is not a number!");
            avm_warning(buffer, currLine);
            free(buffer);
            retval.type = nil_m;
        }
        else{
            retval.type = number_m;
            retval.data.numVal = val;
        }
    }
}