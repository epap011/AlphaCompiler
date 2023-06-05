#ifndef AVM_TABLES_H
#define AVM_TABLES_H

#include "avm_types.h"

avm_table*   avm_table_new    (void);
void         avm_table_destroy(avm_table *t);
avm_memcell* avm_table_getelem(avm_table *t, avm_memcell *key);
void         avm_table_setelem(avm_table *t, avm_memcell *key, avm_memcell *value);
void avm_table_buckets_init   (avm_table_bucket **p);
void avm_table_buckets_destroy(avm_table_bucket **p);
void avm_table_inc_refcounter (avm_table *t);
void avm_table_dec_refcounter (avm_table *t);
int  key_exists(avm_table_bucket* bucket_head, avm_memcell key);
int  overwrite_key(avm_table_bucket* bucket_head, avm_memcell key, avm_memcell value);
unsigned hash_string(char *str);

#endif