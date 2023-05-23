
#ifndef AVM_H
#define AVM_H

#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>


typedef enum avm_memcell_t {
    number_m ,
    string_m ,
    bool_m ,
    table_m ,
    userfunc_m ,
    libfunc_m ,
    nil_m ,
    undef_m
} avm_memcell_t;


typedef struct avm_memcell {
    avm_memcell_t type;
    union {
        double numVal;
        char* strVal;
        unsigned char boolVal;
        avm_table* tableVal;
        unsigned funcVal;
        char* libfuncVal;
    } data;
}avm_memcell;

#endif //AVM_H