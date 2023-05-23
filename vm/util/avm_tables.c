#include "avm_types.h"


avm_table *avm_table_new(){

    avm_table *t = (avm_table *)malloc(sizeof(avm_table));
    AVM_WIPEOUT(*t);

    t->refCounter = t->total = 0;
    avm_table_buckets_init(t->strIndexed);
    avm_table_buckets_init(t->numIndexed);
    //Bono gia bool/userfunc/libfunc

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

void avm_memcell_clear(avm_memcell *m){}