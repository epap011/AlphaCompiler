#ifndef AVM_TYPES_H
#define AVM_TYPES_H

#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "instructions.h"

#define RED   "\x1b[31m"
#define GRN   "\x1b[32m"
#define YEL   "\x1b[33m"
#define BLU   "\x1b[34m"
#define MAG   "\x1b[35m"
#define CYN   "\x1b[36m"
#define RESET "\x1b[0m"


#define AVM_WIPEOUT(m) memset(&(m), 0, sizeof(m))
#define AVM_TABLE_HASHSIZE 211


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
    avm_table_bucket *numIndexed[AVM_TABLE_HASHSIZE];
    avm_table_bucket *strIndexed[AVM_TABLE_HASHSIZE];
    //Bonus : avm_table_bucket for bool/userfunc/libfunc
    
    unsigned total; //Anti gia total counter sunolikwn stoixeiwn mporoume na exoume ksexwristes metavlites gia kathe hash table

}avm_table;


avm_table *avm_table_new(void);
void avm_table_destroy(avm_table *t);
avm_memcell *avm_table_getelem(avm_table *t, avm_memcell *key);
void avm_table_setelem(avm_table *t, avm_memcell *key, avm_memcell *value);

void avm_table_buckets_init(avm_table_bucket **p);
void avm_table_buckets_destroy(avm_table_bucket **p);

void avm_table_inc_refcounter(avm_table *t);
void avm_table_dec_refcounter(avm_table *t);

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