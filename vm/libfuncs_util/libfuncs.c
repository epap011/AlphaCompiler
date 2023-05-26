#include "avm_helpers.h"

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
            printf("Found libfunc %s\n", id);
            return temp->addr;
        }
        temp = temp->next;
    }
    return NULL;
}


void libfunc_print(void){
    unsigned n = avm_totalactuals();
    printf("kala eimai\n");
    unsigned i;
    for(i = 0; i < n; ++i){
        char* s = avm_tostring(avm_getactual(i));
        printf("%s", s);
        free(s);
    }
}

void libfunc_typeof(void){
    
}