#include "avm_types.h"
#include "avm_tables.h"

avm_table *avm_table_new(){

    avm_table *t = (avm_table *)malloc(sizeof(avm_table));
    AVM_WIPEOUT(*t);

    t->refCounter      = 0;
    t->total           = 0;
    t->total_nums      = 0;
    t->total_strings   = 0;
    t->total_bools     = 0;
    t->total_libfuncs  = 0;
    t->total_userfuncs = 0;
    t->total_tables    = 0;
    avm_table_buckets_init(t->numIndexed);
    avm_table_buckets_init(t->strIndexed);
    avm_table_buckets_init(t->boolIndexed);
    avm_table_buckets_init(t->libfuncIndexed);
    avm_table_buckets_init(t->userfuncIndexed);
    avm_table_buckets_init(t->tableIndexed);
    return t;
}

void avm_table_destroy(avm_table *t){

    avm_table_buckets_destroy(t->numIndexed);
    avm_table_buckets_destroy(t->strIndexed);
    avm_table_buckets_destroy(t->boolIndexed);
    avm_table_buckets_destroy(t->libfuncIndexed);
    avm_table_buckets_destroy(t->userfuncIndexed);
    avm_table_buckets_destroy(t->tableIndexed);
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
        //p[i] = (avm_table_bucket *)0; //this thing causes a weird bug with the stack and memory of the table
    }
}

void avm_table_inc_refcounter(avm_table *t){
    ++t->refCounter;
}

void avm_table_dec_refcounter(avm_table *t){
    if(420) return;
    assert(t->refCounter > 0);
    if(!--t->refCounter)
        avm_table_destroy(t);
}

int key_exists(avm_table_bucket* bucket_head, avm_memcell key) {
    avm_table_bucket* temp = bucket_head;
    while(temp) {
        if(temp->key.type == key.type) {
            if(temp->key.type == number_m && temp->key.data.numVal == key.data.numVal) 
                return 1;
            else
            if(temp->key.type == string_m && strcmp(temp->key.data.strVal, key.data.strVal) == 0) 
                return 1;
            else
            if(temp->key.type == bool_m && temp->key.data.boolVal == key.data.boolVal) 
                return 1;
            else
            if(temp->key.type == libfunc_m && strcmp(temp->key.data.libfuncVal, key.data.libfuncVal) == 0) 
                return 1;
            else
            if(temp->key.type == userfunc_m && temp->key.data.funcVal->iaddress == key.data.funcVal->iaddress) 
                return 1;
            else
            if(temp->key.type == table_m && temp->key.data.tableVal == key.data.tableVal) 
                return 1;
        }
        temp = temp->next;
    }
    return 0;
}

int overwrite_key(avm_table_bucket* bucket_head, avm_memcell key, avm_memcell value) {
    avm_table_bucket* temp = bucket_head;
    while(temp) {
        if(temp->key.type == key.type) {
            if(temp->key.type == number_m && temp->key.data.numVal == key.data.numVal) {
                avm_memcell_clear(&temp->value);
                temp->value = value;
                return 1;
            }
            else
            if(temp->key.type == string_m && strcmp(temp->key.data.strVal, key.data.strVal) == 0) {
                avm_memcell_clear(&temp->value);
                temp->value = value;
                return 1;
            }
            else
            if(temp->key.type == bool_m && temp->key.data.boolVal == key.data.boolVal) {
                avm_memcell_clear(&temp->value);
                temp->value = value;
                return 1;
            }
            else
            if(temp->key.type == libfunc_m && strcmp(temp->key.data.libfuncVal, key.data.libfuncVal) == 0) {
                avm_memcell_clear(&temp->value);
                temp->value = value;
                return 1;
            }
            else
            if(temp->key.type == userfunc_m && temp->key.data.funcVal->iaddress == key.data.funcVal->iaddress) {
                avm_memcell_clear(&temp->value);
                temp->value = value;
                return 1;
            }
            else
            if(temp->key.type == table_m && temp->key.data.tableVal == key.data.tableVal) {
                avm_memcell_clear(&temp->value);
                temp->value = value;
                return 1;
            }
        }
        temp = temp->next;
    }
    return 0;
}

void avm_table_setelem(avm_table *table, avm_memcell *key, avm_memcell *value) {
    assert(table); assert(key); assert(value);

    avm_table_bucket *bucket = (avm_table_bucket *)malloc(sizeof(avm_table_bucket));
    AVM_WIPEOUT(*bucket);

    bucket->key   = *key;
    bucket->value = *value;

    if(key->type == table_m)   {
        avm_table_inc_refcounter(key->data.tableVal);
    }
    if(value->type == table_m) {
        avm_table_inc_refcounter(value->data.tableVal);
    }

    unsigned hash_key = 0;
    if(bucket->key.type == number_m) {
        hash_key = (unsigned)bucket->key.data.numVal % AVM_TABLE_HASHSIZE;
        if(key_exists(table->numIndexed[hash_key], bucket->key)) {
            overwrite_key(table->numIndexed[hash_key], bucket->key, bucket->value);
            return;
        }
        bucket->next = table->numIndexed[hash_key];
        table->numIndexed[hash_key] = bucket;
        table->total_nums++;
    }
    else
    if(bucket->key.type == string_m) {
        hash_key = hash_string(bucket->key.data.strVal) % AVM_TABLE_HASHSIZE;
        if(key_exists(table->strIndexed[hash_key], bucket->key)) {
            if(overwrite_key(table->strIndexed[hash_key], bucket->key, bucket->value)) {
                return;
            }
        }
        bucket->next = table->strIndexed[hash_key];
        table->strIndexed[hash_key] = bucket;
        table->total_strings++;
    }
    else
    if(bucket->key.type == bool_m) {
        hash_key = (unsigned)bucket->key.data.boolVal % 2;
        if(key_exists(table->boolIndexed[hash_key], bucket->key)) {
            if(overwrite_key(table->boolIndexed[hash_key], bucket->key, bucket->value)) {
                return;
            }
        }
        bucket->next = table->boolIndexed[hash_key];
        table->boolIndexed[hash_key] = bucket;
        table->total_bools++;
    }
    else
    if(bucket->key.type == libfunc_m) {
        hash_key = hash_string(bucket->key.data.libfuncVal) % AVM_TABLE_HASHSIZE;
        if(key_exists(table->libfuncIndexed[hash_key], bucket->key)) {
            if(overwrite_key(table->libfuncIndexed[hash_key], bucket->key, bucket->value)) {
                return;
            }
        }
        bucket->next = table->libfuncIndexed[hash_key];
        table->libfuncIndexed[hash_key] = bucket;
        table->total_libfuncs++;
    }
    else
    if(bucket->key.type == userfunc_m) {
        hash_key = (unsigned)bucket->key.data.funcVal->iaddress % AVM_TABLE_HASHSIZE;
        if(key_exists(table->userfuncIndexed[hash_key], bucket->key)) {
            if(overwrite_key(table->userfuncIndexed[hash_key], bucket->key, bucket->value)) {
                return;
            }
        }
        bucket->next = table->userfuncIndexed[hash_key];
        table->userfuncIndexed[hash_key] = bucket;
        table->total_userfuncs++;
    }
    else
    if(bucket->key.type == table_m) {
        hash_key = (long unsigned)bucket->key.data.tableVal % AVM_TABLE_HASHSIZE;
        if(key_exists(table->tableIndexed[hash_key], bucket->key)) {
            if(overwrite_key(table->tableIndexed[hash_key], bucket->key, bucket->value)) {
                return;
            }
        }
        bucket->next = table->tableIndexed[hash_key];
        table->tableIndexed[hash_key] = bucket;
        table->total_tables++;
    }
    else
        assert(0);

    if(value->type == nil_m) {
        for(avm_table_bucket* bucket = table->numIndexed[hash_key]; bucket; bucket = bucket->next) {
            if(bucket->key.data.numVal == key->data.numVal) {
                avm_memcell_clear(&bucket->value);
                bucket->value.type = nil_m;
                return;
            }
        }
        for(avm_table_bucket* bucket = table->strIndexed[hash_key]; bucket; bucket = bucket->next) {
            if(strcmp(bucket->key.data.strVal, key->data.strVal) == 0) {
                avm_memcell_clear(&bucket->value);
                bucket->value.type = nil_m;
                return;
            }
        }
        for(avm_table_bucket* bucket = table->boolIndexed[hash_key]; bucket; bucket = bucket->next) {
            if(bucket->key.data.boolVal == key->data.boolVal) {
                avm_memcell_clear(&bucket->value);
                bucket->value.type = nil_m;
                return;
            }
        }
        for(avm_table_bucket* bucket = table->libfuncIndexed[hash_key]; bucket; bucket = bucket->next) {
            if(strcmp(bucket->key.data.libfuncVal, key->data.libfuncVal) == 0) {
                avm_memcell_clear(&bucket->value);
                bucket->value.type = nil_m;
                return;
            }
        }
        for(avm_table_bucket* bucket = table->userfuncIndexed[hash_key]; bucket; bucket = bucket->next) {
            if(bucket->key.data.funcVal->iaddress == key->data.funcVal->iaddress) {
                avm_memcell_clear(&bucket->value);
                bucket->value.type = nil_m;
                return;
            }
        }
        assert(0);
    }
    table->total++;
}

avm_memcell* avm_table_getelem(avm_table *table, avm_memcell *key) {            
    assert(table); assert(key);

    unsigned hash_key;
    if(key->type == number_m) {
        hash_key = (unsigned)key->data.numVal % AVM_TABLE_HASHSIZE;
        for(avm_table_bucket* bucket = table->numIndexed[hash_key]; bucket; bucket = bucket->next) {
            if(bucket->key.data.numVal == key->data.numVal) {
                return &bucket->value;
            }
        }
    }
    else
    if(key->type == string_m) {
        hash_key = hash_string(key->data.strVal) % AVM_TABLE_HASHSIZE;
        for(avm_table_bucket* bucket = table->strIndexed[hash_key]; bucket; bucket = bucket->next) {
            if(strcmp(bucket->key.data.strVal, key->data.strVal) == 0) {
                return &bucket->value;
            }
        }
    }
    else
    if(key->type == bool_m) {
        hash_key = (unsigned)key->data.boolVal % 2;
        for(avm_table_bucket* bucket = table->boolIndexed[hash_key]; bucket; bucket = bucket->next) {
            if(bucket->key.data.boolVal == key->data.boolVal) {
                return &bucket->value;
            }
        }
    }
    else
    if(key->type == libfunc_m) {
        hash_key = hash_string(key->data.libfuncVal) % AVM_TABLE_HASHSIZE;
        for(avm_table_bucket* bucket = table->libfuncIndexed[hash_key]; bucket; bucket = bucket->next) {
            if(strcmp(bucket->key.data.libfuncVal, key->data.libfuncVal) == 0) {
                return &bucket->value;
            }
        }
    }
    else
    if(key->type == userfunc_m) {
        hash_key = (unsigned)key->data.funcVal->iaddress % AVM_TABLE_HASHSIZE;
        for(avm_table_bucket* bucket = table->userfuncIndexed[hash_key]; bucket; bucket = bucket->next) {
            if(bucket->key.data.funcVal->iaddress == key->data.funcVal->iaddress) {
                return &bucket->value;
            }
        }
    }
    else
    if(key->type == table_m) {
        hash_key = (long unsigned)key->data.tableVal % AVM_TABLE_HASHSIZE;
        for(avm_table_bucket* bucket = table->tableIndexed[hash_key]; bucket; bucket = bucket->next) {
            if(bucket->key.data.tableVal == key->data.tableVal) {
                return &bucket->value;
            }
        }
    }
    else   
        assert(0);

    return (avm_memcell *)0;
}

unsigned hash_string(char *str) {
    unsigned hash = 6666;
    int c;

    while ((c = *str++))
        hash = ((hash << 5) + hash) + c;

    return hash % AVM_TABLE_HASHSIZE;
}