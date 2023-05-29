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

void cos_sin_impl(char * func){
    
    unsigned n = avm_totalactuals();
    if(n != 1){
        char * buffer = malloc(sizeof(char) * 128);
        sprintf(buffer, "one argument (not %d) expected in '%s'!", n, func);
        avm_error(buffer, currLine);
        free(buffer);
        return ;
    }
    avm_memcell_clear(&retval);
    avm_memcell *lib_arg = avm_getactual(0);  

    if(lib_arg->type != number_m){
        char * buffer = malloc(sizeof(char) * 128);
        sprintf(buffer, "'%s' takes only numeric arguments! not" YEL" %s" RESET, func, typeStrings[lib_arg->type]);
        avm_error(buffer, currLine);
        free(buffer);
    }
    else{
       
        retval.type = number_m;
        double rad = (M_PI / 180.0) * lib_arg->data.numVal;
        if(!strcmp(func, "sin")){
            double x = sin(rad);
            retval.data.numVal = round(x * 100000) / 100000; // Round to 5 decimal places because c is a garbage ass language, even stupider than js
        }
        else{
            double x = cos(rad);
            retval.data.numVal = round(x * 100000) / 100000;
        }
    }
}

void libfunc_cos(){

    cos_sin_impl("cos");

}