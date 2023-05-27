#include "avm_helpers.h"

extern int DEBUG;
extern unsigned currLine;
extern avm_memcell retval;
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