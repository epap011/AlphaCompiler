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

void libfunc_argument(void){
    unsigned prev_topsp = avm_get_envvalue(topsp + AVM_SAVEDTOPSP_OFFSET);
    avm_memcell_clear(&retval);

    if(!prev_topsp){    
        char * buffer = malloc(sizeof(char) * 128);
        sprintf(buffer, "'argument' called outside of a function!");
        avm_warning(buffer, currLine);
        free(buffer);
        retval.type = nil_m;
    }
    else{

        unsigned n = avm_totalactuals();
        if(n != 1){
            char * buffer = malloc(sizeof(char) * 128);
            sprintf(buffer, "one argument (not %d) expected in 'argument'!", n);
            avm_error(buffer, currLine);
            free(buffer);
            return ;
        }

        unsigned totalArgs = avm_get_envvalue(prev_topsp + AVM_NUMACTUALS_OFFSET);
        avm_memcell *lib_arg = avm_getactual(0);  //argument of 'argument' function

        if(lib_arg->type != number_m){
            char * buffer = malloc(sizeof(char) * 128);
            sprintf(buffer, "'argument' takes only numeric arguments! not" YEL" %s" RESET, typeStrings[lib_arg->type]);
            avm_error(buffer, currLine);
            free(buffer);
        }
        else if(lib_arg->data.numVal < 0 || lib_arg->data.numVal > totalArgs){
            char * buffer = malloc(sizeof(char) * 128);
            sprintf(buffer, "argument must be in range [0, %d]!", totalArgs);
            avm_error(buffer, currLine);
            free(buffer);
        }
        else
            retval = stack[prev_topsp + AVM_STACKENV_SIZE + 1 + (int)lib_arg->data.numVal];

    }
}