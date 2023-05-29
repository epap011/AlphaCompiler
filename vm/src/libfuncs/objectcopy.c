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

void libfunc_objectcopy(){

    unsigned n = avm_totalactuals();
    if(n != 1){
        char * buffer = malloc(sizeof(char) * 128);
        sprintf(buffer, "one argument (not %d) expected in 'objectcopy'!", n);
        avm_error(buffer, currLine);
        free(buffer);
        return ;
    }

    avm_memcell *lib_arg = avm_getactual(0);

    if(lib_arg->type != table_m){
        char * buffer = malloc(sizeof(char) * 128);
        sprintf(buffer, "'objectcopy' takes only table arguments! not" YEL" %s" RESET, typeStrings[lib_arg->type]);
        avm_error(buffer, currLine);
        free(buffer);
    }
    else{
        avm_table *old_table = lib_arg->data.tableVal;
        avm_table *new_table = avm_table_new();

        int totals_found = 0, i = 0;

        while(totals_found < old_table->total || i < AVM_TABLE_HASHSIZE){
            if(old_table->numIndexed[i] != NULL){
                avm_table_setelem(new_table, &old_table->numIndexed[i]->key, &old_table->numIndexed[i]->value);
                totals_found++;
            }
            if(old_table->strIndexed[i] != NULL){
                avm_table_setelem(new_table, &old_table->strIndexed[i]->key, &old_table->strIndexed[i]->value);
                totals_found++;
            }
            if(old_table->boolIndexed[i] != NULL){
                avm_table_setelem(new_table, &old_table->boolIndexed[i]->key, &old_table->boolIndexed[i]->value);
                totals_found++;
            }
            if(old_table->tableIndexed[i] != NULL){  
                avm_table_setelem(new_table, &old_table->tableIndexed[i]->key, &old_table->tableIndexed[i]->value);
                totals_found++;
            }
            if(old_table->userfuncIndexed[i] != NULL){
                avm_table_setelem(new_table, &old_table->userfuncIndexed[i]->key, &old_table->userfuncIndexed[i]->value);
                totals_found++;
            }
            if(old_table->libfuncIndexed[i] != NULL){
                avm_table_setelem(new_table, &old_table->libfuncIndexed[i]->key, &old_table->libfuncIndexed[i]->value);
                totals_found++;
            }
            i++;
        }
        retval.type = table_m;
        retval.data.tableVal = new_table;
    }
}