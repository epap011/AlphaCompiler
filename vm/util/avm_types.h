#ifndef AVM_TYPES_H
#define AVM_TYPES_H

#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "avm_types.h"

#define RED   "\x1b[31m"
#define GRN   "\x1b[32m"
#define YEL   "\x1b[33m"
#define BLU   "\x1b[34m"
#define MAG   "\x1b[35m"
#define CYN   "\x1b[36m"
#define RESET "\x1b[0m"


#define AVM_WIPEOUT(m) memset(&(m), 0, sizeof(m))
#define AVM_TABLE_HASHSIZE 211

enum vmopcode{
    assign_vm, add_vm, sub_vm, mul_vm, div_vm, mod_vm,  
    jmp_vm, jeq_vm, jne_vm, jle_vm, jge_vm, jlt_vm, jgt_vm, 
    call_vm, pusharg_vm, funcenter_vm, funcexit_vm, 
    newtable_vm, tablegetelem_vm, tablesetelem_vm, nop_vm
};

enum vmarg_t{
    global_a,
    local_a,
    formal_a,
    number_a,
    string_a,
    bool_a,
    nil_a,
    userfunc_a,
    libfunc_a,
    retval_a,
    label_a,
    undef_a
};

typedef struct vmarg {
    enum vmarg_t type;
    unsigned val;
} vmarg;

typedef struct instuction {
    enum vmopcode opcode;
    vmarg* result;
    vmarg* arg1;
    vmarg* arg2;
    unsigned int srcLine;
} instruction;

typedef struct user_func_t {
    unsigned iaddress;
    unsigned total_locals;
    const char* name;
} user_func_t;

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

struct avm_table;

typedef struct avm_memcell {
    avm_memcell_t type;
    union {
        double numVal;
        char* strVal;
        unsigned char boolVal;
        struct avm_table* tableVal;
        user_func_t* funcVal;
        char* libfuncVal;
    } data;
}avm_memcell;

typedef void (*memclear_func_t) (avm_memcell*);

typedef struct avm_table_bucket {
    
    avm_memcell key;
    avm_memcell value;
    struct avm_table_bucket *next;

}avm_table_bucket;

typedef struct avm_table {
   
    unsigned refCounter;
    avm_table_bucket *numIndexed     [AVM_TABLE_HASHSIZE];
    avm_table_bucket *strIndexed     [AVM_TABLE_HASHSIZE];
    avm_table_bucket *boolIndexed    [AVM_TABLE_HASHSIZE];
    avm_table_bucket *libfuncIndexed [AVM_TABLE_HASHSIZE];
    avm_table_bucket *userfuncIndexed[AVM_TABLE_HASHSIZE];
    avm_table_bucket *tableIndexed   [AVM_TABLE_HASHSIZE];
    unsigned total;
    unsigned total_nums;
    unsigned total_strings;
    unsigned total_bools;
    unsigned total_libfuncs;
    unsigned total_userfuncs;
    unsigned total_tables;
}avm_table;

void avm_memcell_clear(avm_memcell *m);
void memclear_string(avm_memcell *m);
void memclear_table(avm_memcell *m);
void print_memcell_value(avm_memcell *m);
unsigned hash_string(char *str);

avm_memcell* avm_translate_operand(vmarg* arg, avm_memcell* reg);

void avm_error(char* message, unsigned line);
void avm_warning(char* message, unsigned line);

void print_vm_state();

#endif // AVM_TYPES_H