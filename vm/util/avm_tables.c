#include "avm_types.h"


avm_table *avm_table_new(){

    avm_table *t = (avm_table *)malloc(sizeof(avm_table));
    AVM_WIPEOUT(*t);

    t->refCounter = t->total = 0;
    avm_table_buckets_init(t->strIndexed);
    return t;
}

void avm_table_destroy(avm_table *t){

    avm_table_buckets_destroy(t->strIndexed);
    avm_table_buckets_destroy(t->numIndexed);
    free(t);

}

void avm_table_buckets_init(avm_table_bucket **p){

    for(unsigned i = 0; i < AVM_TABLE_HASHSIZE; ++i)
        p[i] = (avm_table_bucket *)0;

}

void avm_table_buckets_destroy(avm_table_bucket **p){

    for(unsigned i = 0; i < AVM_TABLE_HASHSIZE; ++i, ++p){

        for(avm_table_bucket *b = *p; b;){

            avm_table_bucket *del = b;
            b = b->next;
            avm_memcell_clear(&del->key);
            avm_memcell_clear(&del->value);
            free(del);
        }
        p[i] = (avm_table_bucket *)0;

    }
}

void avm_table_inc_refcounter(avm_table *t){
    ++t->refCounter;
}

void avm_table_dec_refcounter(avm_table *t){
    assert(t->refCounter > 0);
    if(!--t->refCounter)
        avm_table_destroy(t);
}

void avm_table_setelem(avm_table *table, avm_memcell *key, avm_memcell *value) {
    assert(table); assert(key); assert(value);

    avm_table_bucket *bucket = (avm_table_bucket *)malloc(sizeof(avm_table_bucket));
    AVM_WIPEOUT(*bucket);

    bucket->key   = *key;
    bucket->value = *value;

    unsigned hash_key;
    //for now only numbers are supported
    if(bucket->key.type == number_m) 
        hash_key = (unsigned)bucket->key.data.numVal % AVM_TABLE_HASHSIZE;
    else
    if(bucket->key.type == string_m)
        hash_key = hash_string(bucket->key.data.strVal) % AVM_TABLE_HASHSIZE;
    else    
        assert(0);

    bucket->next = table->numIndexed[hash_key];
    table->numIndexed[hash_key] = bucket;
    table->total++;
}

avm_memcell* avm_table_getelem(avm_table *table, avm_memcell *key) {
    assert(table); assert(key);

    unsigned hash_key;
    //for now only numbers are supported
    if(key->type == number_m) 
        hash_key = (unsigned)key->data.numVal % AVM_TABLE_HASHSIZE;
    else 
        assert(0);

    avm_memcell* ret = (avm_memcell *)malloc(sizeof(avm_memcell));
    for(avm_table_bucket* bucket = table->numIndexed[hash_key]; bucket; bucket = bucket->next) {
        if(bucket->key.data.numVal == key->data.numVal) {
            printf("#####found#####\n");
            return &bucket->value;
        }
    }

    ret->type = nil_m;
    return ret;
}

unsigned hash_string(char *str) {
    unsigned hash = 6666;
    int c;

    while ((c = *str++))
        hash = ((hash << 5) + hash) + c;

    return hash % AVM_TABLE_HASHSIZE;
}