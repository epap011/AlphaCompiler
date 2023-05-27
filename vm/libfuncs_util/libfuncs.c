#include "avm_helpers.h"
#include "avm_stack.h"
#include <math.h>

extern int DEBUG;
extern unsigned currLine;
extern avm_memcell retval;
extern unsigned top, topsp;
extern avm_memcell stack[AVM_STACKSIZE];
extern char * typeStrings[];

libfunc* libfuncs_list = (libfunc*)0;

void avm_registerlibfunc(char* id, library_func_t addr){

    libfunc* newLibFunc = (libfunc*)malloc(sizeof(libfunc));
    newLibFunc->id = strdup(id);
    newLibFunc->addr = addr;
    
    newLibFunc->next = libfuncs_list;
    libfuncs_list = newLibFunc;
}

library_func_t avm_getlibraryfunc(char* id){
    libfunc* temp = libfuncs_list;
    while(temp){
        if(!strcmp(temp->id, id)){
            return temp->addr;
        }
        temp = temp->next;
    }
    return NULL;
}


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

void libfunc_totalarguments(void){
    //Save topsp of previous activation record
    unsigned prev_topsp = avm_get_envvalue(topsp + AVM_SAVEDTOPSP_OFFSET);
    printf("PREV_TOPSP: %d\n", prev_topsp);
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
        
        if(endptr == lib_arg->data.strVal){
            char * buffer = malloc(sizeof(char) * 128);
            sprintf(buffer, "argument of 'strtonum' is not a number!");
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

void libfunc_sqrt(){

    unsigned n = avm_totalactuals();
    if(n != 1){
        char * buffer = malloc(sizeof(char) * 128);
        sprintf(buffer, "one argument (not %d) expected in 'sqrt'!", n);
        avm_error(buffer, currLine);
        free(buffer);
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