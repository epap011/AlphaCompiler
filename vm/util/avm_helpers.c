// something to string
// memclear stuff

#include "avm_helpers.h"
#include "../src/tables/avm_tables.h"

memclear_func_t memclarFuncs[] = {

    0,  /*number*/
    memclear_string,
    0, /*bool*/
    memclear_table,
    0, /*userfunc*/
    0, /*libfunc*/
    0, /*nil*/
    0  /*undef*/
};

tostring_func_t tostringFuncs[] = {
    number_tostring,
    string_tostring,
    bool_tostring,
    table_tostring,
    userfunc_tostring,
    libfunc_tostring,
    nil_tostring,
    undef_tostring
};

char* avm_tostring(avm_memcell* m){
    assert(m->type >= 0 && m->type <= undef_m);
    return (*tostringFuncs[m->type])(m);
}

char* number_tostring(avm_memcell* m){
    assert(m->type == number_m);
    char* str = malloc(sizeof(char) * 100);
    sprintf(str, "%lf", m->data.numVal);
    return str;
}

char* string_tostring(avm_memcell* m){
    assert(m->type == string_m);
    return strdup(m->data.strVal);
}

char* bool_tostring(avm_memcell* m){
    assert(m->type == bool_m);
    if(m->data.boolVal)
        return strdup("true");
    else
        return strdup("false");
}

char* userfunc_tostring(avm_memcell* m){
    assert(m->type == userfunc_m);
    char* buffer = malloc(sizeof(char) * 256);
    sprintf(buffer, "user function : %d", m->data.funcVal->iaddress);
    return buffer;
}


char* libfunc_tostring(avm_memcell* m){
    assert(m->type == libfunc_m);
    char* buffer = malloc(sizeof(char) * 256);
    sprintf(buffer, "library function : %s", m->data.libfuncVal);
    return buffer;
}

char* nil_tostring(avm_memcell* m){
    return strdup("nil");
}

char* undef_tostring(avm_memcell* m){
    return strdup("undef");
}

void key_value_pair_to_string(avm_table_bucket* bucket, char** content, unsigned* total_chars, unsigned* initial_capacity){
    char* key   = avm_tostring(&bucket->key);
    char* value = avm_tostring(&bucket->value);
    *total_chars += strlen(key) + 1 + strlen(value) + 1 + 6;
    if(*total_chars > *initial_capacity){
        *initial_capacity = *total_chars * 2;
        *content = (char*) realloc(*content, sizeof(char) * *initial_capacity);
    }
    strcat(*content, "{"); strcat(*content, key); strcat(*content, " : "); strcat(*content, value); strcat(*content, "} ");
}

char* table_tostring(avm_memcell* m) {
    assert(m->type == table_m);
    avm_table* table = m->data.tableVal;
    unsigned i = 0, totals_found = 0, total_chars = 0, initial_capacity = 16384;
    
    char* content = (char*) malloc(sizeof(char) * initial_capacity);
    memset((void *)content, 0, initial_capacity);

    sprintf(content, "[ "); total_chars += 2;
    while(totals_found < table->total && i < AVM_TABLE_HASHSIZE){
        if(table->total_nums > 0 && table->numIndexed[i] != NULL){
            avm_table_bucket* temp = table->numIndexed[i];
            while(temp != NULL){
                key_value_pair_to_string(temp, &content, &total_chars, &initial_capacity);
                totals_found++;
                temp = temp->next;
            }
        }
        if(table->total_strings > 0 && table->strIndexed[i] != NULL) {
            avm_table_bucket* temp = table->strIndexed[i];
            while(temp != NULL){
                key_value_pair_to_string(temp, &content, &total_chars, &initial_capacity);
                totals_found++;
                temp = temp->next;
            }
        }
        if(table->total_bools > 0 && table->boolIndexed[i] != NULL) {
            avm_table_bucket* temp = table->boolIndexed[i];
            while(temp != NULL){
                key_value_pair_to_string(temp, &content, &total_chars, &initial_capacity);
                totals_found++;
                temp = temp->next;
            }
        }
        if(table->total_tables > 0 && table->tableIndexed[i] != NULL) {
            avm_table_bucket* temp = table->tableIndexed[i];
            while(temp != NULL){
                key_value_pair_to_string(temp, &content, &total_chars, &initial_capacity);
                totals_found++;
                temp = temp->next;
            }
        }
        if(table->total_userfuncs > 0 && table->userfuncIndexed[i] != NULL) {
            avm_table_bucket* temp = table->userfuncIndexed[i];
            while(temp != NULL){
                key_value_pair_to_string(temp, &content, &total_chars, &initial_capacity);
                totals_found++;
                temp = temp->next;
            }
        }
        if(table->total_libfuncs > 0 && table->libfuncIndexed[i] != NULL) {
            avm_table_bucket* temp = table->libfuncIndexed[i];
            while(temp != NULL){
                key_value_pair_to_string(temp, &content, &total_chars, &initial_capacity);
                totals_found++;
                temp = temp->next;
            }
        }
        i++;
    }

    strcat(content, "]\0");
    return content;
}

void memclear_string(avm_memcell *m){
    assert(m->data.strVal);
    free(m->data.strVal);
}

void memclear_table(avm_memcell *m){
    assert(m->data.tableVal);
    avm_table_dec_refcounter(m->data.tableVal);
}

void avm_memcell_clear(avm_memcell *m){
    if(m->type != undef_m){
        memclear_func_t f = memclarFuncs[m->type];
        if(f)
            (*f)(m);
        m->type = undef_m;
    }
}

char* register_type_to_string(avm_memcell_t type) {
    switch (type) {
        case number_m:
            return "number";
        case string_m:
            return "string";
        case bool_m:
            return "bool";
        case table_m:
            return "table";
        case userfunc_m:
            return "userfunc";
        case libfunc_m:
            return "libfunc";
        case nil_m:
            return "nil";
        case undef_m:
            return "undef";
        default:
            return "Unknown type";
    }
}

void print_memcell_value(avm_memcell *m) {
    switch(m->type) {
        case number_m:
            printf("%lf", m->data.numVal);
            break;
        case string_m:
            printf("%s", m->data.strVal);
            break;
        case bool_m:
            printf("%d", m->data.boolVal);
            break;
        case table_m:
            printf("table");
            break;
        case userfunc_m:
            printf("userfunc");
            break;
        case libfunc_m:
            printf("libfunc");
            break;
        case nil_m:
            printf("nil");
            break;
        case undef_m:
            printf("undef");
            break;
        default:
            printf("Unknown type");
            break;
    }
}