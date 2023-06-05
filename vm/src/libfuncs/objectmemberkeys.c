#include "avm_helpers.h"
#include "../stack/avm_stack.h"
#include "../tables/avm_tables.h"
#include <math.h>

extern int DEBUG;
extern unsigned currLine;
extern avm_memcell retval;
extern unsigned top, topsp;
extern avm_memcell stack[AVM_STACKSIZE];
extern char * typeStrings[];

void libfunc_objectmemberkeys(){

    avm_memcell_clear(&retval);
    unsigned n = avm_totalactuals();
    if(n != 1){
        char * buffer = malloc(sizeof(char) * 128);
        sprintf(buffer, "one argument (not %d) expected in 'objectmemberkeys'!", n);
        avm_error(buffer, currLine);
        free(buffer);
        retval.type = nil_m;
        return ;
    }

    avm_memcell *lib_arg = avm_getactual(0);

    if(lib_arg->type != table_m){
        char * buffer = malloc(sizeof(char) * 128);
        sprintf(buffer, "'objectmemberkeys' takes only table arguments! not" YEL" %s" RESET, typeStrings[lib_arg->type]);
        avm_error(buffer, currLine);
        free(buffer);
        retval.type = nil_m;
    }
    else{

        avm_table *old_table = lib_arg->data.tableVal;
        avm_table *new_table = avm_table_new();
        
        avm_memcell *new_key = malloc(sizeof(avm_memcell));
        new_key->type = number_m;

        int totals_found = 0, i = 0;

        while(totals_found < old_table->total && i < AVM_TABLE_HASHSIZE){
            if(old_table->numIndexed[i] != NULL){
                avm_table_bucket* temp = old_table->numIndexed[i];
                while(temp != NULL){
                    new_key->data.numVal = totals_found;
                    avm_table_setelem(new_table, new_key, &old_table->numIndexed[i]->key);
                    if(temp->value.type != nil_m)
                        totals_found++;
                    temp = temp->next;
                }
                
            }
            if(old_table->strIndexed[i] != NULL){
                avm_table_bucket* temp = old_table->strIndexed[i];
                while(temp != NULL){
                    new_key->data.numVal = totals_found;
                    avm_table_setelem(new_table, new_key, &old_table->strIndexed[i]->key);
                    if(temp->value.type != nil_m)
                        totals_found++;
                    temp = temp->next;
                }
            }
            if(old_table->boolIndexed[i] != NULL){
                avm_table_bucket* temp = old_table->boolIndexed[i];
                while(temp != NULL){
                    new_key->data.numVal = totals_found;
                    avm_table_setelem(new_table, new_key, &old_table->boolIndexed[i]->key);
                    if(temp->value.type != nil_m)
                        totals_found++;
                    temp = temp->next;
                }
            }
            if(old_table->tableIndexed[i] != NULL){
                avm_table_bucket* temp = old_table->tableIndexed[i];
                while(temp != NULL){
                    new_key->data.numVal = totals_found;
                    avm_table_setelem(new_table, new_key, &old_table->tableIndexed[i]->key);
                    if(temp->value.type != nil_m)
                        totals_found++;
                    temp = temp->next;
                }
            }
            if(old_table->userfuncIndexed[i] != NULL){
                avm_table_bucket* temp = old_table->userfuncIndexed[i];
                while(temp != NULL){
                    new_key->data.numVal = totals_found;
                    avm_table_setelem(new_table, new_key, &old_table->userfuncIndexed[i]->key);
                    if(temp->value.type != nil_m)
                        totals_found++;
                    temp = temp->next;
                }
            }
            if(old_table->libfuncIndexed[i] != NULL){
                avm_table_bucket* temp = old_table->libfuncIndexed[i];
                while(temp != NULL){
                    new_key->data.numVal = totals_found;
                    avm_table_setelem(new_table, new_key, &old_table->libfuncIndexed[i]->key);
                    if(temp->value.type != nil_m)
                        totals_found++;
                    temp = temp->next;
                }
            }
            i++;
        }
        retval.type = table_m;
        retval.data.tableVal = new_table;
        avm_table_inc_refcounter(new_table);    }
}