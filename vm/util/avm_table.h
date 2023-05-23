#ifndef AVM_TABLE_H
#define AVM_TABLE_H

#include "../avm.h"

#define AVM_TABLE_HASHSIZE 211

typedef struct avm_table_bucket {
    
    avm_memcell key;
    avm_memcell value;
    struct avm_table_bucket *next;

}avm_table_bucket;

typedef struct avm_table {
   
    unsigned refCounter;
    avm_table_bucket *strIndexed[AVM_TABLE_HASHSIZE];
    avm_table_bucket *numIndexed[AVM_TABLE_HASHSIZE];
    //Bonus : avm_table_bucket for bool/userfunc/libfunc
    
    unsigned total; //Anti gia total counter sunolikwn stoixeiwn mporoume na exoume ksexwristes metavlites gia kathe hash table

}avm_table;


avm_table *avm_table_new(void);
void avm_table_destroy(avm_table *t);
avm_memcell *avm_table_getelem(avm_table *t, avm_memcell *key);
void avm_table_setelem(avm_table *t, avm_memcell *key, avm_memcell *value);

void avm_table_inc_refcounter(avm_table *t);
void avm_table_dec_refcounter(avm_table *t);

void avm_table_buckets_init(avm_table_bucket **p);
void avm_table_buckets_destroy(avm_table_bucket **p);

void avm_memcell_clear(avm_memcell *m);

#endif // AVM_TABLE_H