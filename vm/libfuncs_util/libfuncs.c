#include "avm_helpers.h"
#include "avm_stack.h"
#include <math.h>

extern int DEBUG;
extern unsigned currLine;
extern avm_memcell retval;
extern unsigned top, topsp;
extern avm_memcell stack[AVM_STACKSIZE];
extern char * typeStrings[];

libfunc* libfuncs_list = (libfunc*)0;

void avm_registerlibfunc(char* id, library_func_t addr){

    libfunc* newLibFunc = (libfunc*)malloc(sizeof(libfunc));
    newLibFunc->id = strdup(id);
    newLibFunc->addr = addr;
    
    newLibFunc->next = libfuncs_list;
    libfuncs_list = newLibFunc;
}

library_func_t avm_getlibraryfunc(char* id){
    libfunc* temp = libfuncs_list;
    while(temp){
        if(!strcmp(temp->id, id)){
            return temp->addr;
        }
        temp = temp->next;
    }
    return NULL;
}


void libfunc_print(void){
    unsigned n = avm_totalactuals();
    
    if(DEBUG) printf(BLU"AUTO TO PRINT EINAI TIS LIBFUNC: "RESET);
    unsigned i;
    for(i = 0; i < n; ++i){

        char* s = avm_tostring(avm_getactual(i));
        printf("%s", s);
        free(s);
    }
}

void libfunc_typeof(void){
    
    unsigned n = avm_totalactuals();

    if(n != 1){
        char * buffer = malloc(sizeof(char) * 128);
        sprintf(buffer, "one argument (not %d) expected in 'typeof'!", n);
        avm_error(buffer, currLine);
        free(buffer);
    }
    else{
        avm_memcell_clear(&retval);
        retval.type = string_m;
        retval.data.strVal = strdup(typeStrings[avm_getactual(0)->type]);
    }
}

void libfunc_totalarguments(void){
    //Save topsp of previous activation record
    unsigned prev_topsp = avm_get_envvalue(topsp + AVM_SAVEDTOPSP_OFFSET);
    avm_memcell_clear(&retval);

    if(!prev_topsp){    //if prev_topsp == 0, then we are in global scope
        char * buffer = malloc(sizeof(char) * 128);
        sprintf(buffer, "'totalarguments' called outside of a function!");
        avm_warning(buffer, currLine);
        free(buffer);
        retval.type = nil_m;
    }
    else{
        retval.type = number_m;
        retval.data.numVal = avm_get_envvalue(prev_topsp + AVM_NUMACTUALS_OFFSET);
    }
}

void libfunc_argument(void){
    unsigned prev_topsp = avm_get_envvalue(topsp + AVM_SAVEDTOPSP_OFFSET);
    avm_memcell_clear(&retval);

    if(!prev_topsp){    
        char * buffer = malloc(sizeof(char) * 128);
        sprintf(buffer, "'argument' called outside of a function!");
        avm_warning(buffer, currLine);
        free(buffer);
        retval.type = nil_m;
    }
    else{

        unsigned n = avm_totalactuals();
        if(n != 1){
            char * buffer = malloc(sizeof(char) * 128);
            sprintf(buffer, "one argument (not %d) expected in 'argument'!", n);
            avm_error(buffer, currLine);
            free(buffer);
            return ;
        }

        unsigned totalArgs = avm_get_envvalue(prev_topsp + AVM_NUMACTUALS_OFFSET);
        avm_memcell *lib_arg = avm_getactual(0);  //argument of 'argument' function

        if(lib_arg->type != number_m){
            char * buffer = malloc(sizeof(char) * 128);
            sprintf(buffer, "'argument' takes only numeric arguments! not" YEL" %s" RESET, typeStrings[lib_arg->type]);
            avm_error(buffer, currLine);
            free(buffer);
        }
        else if(lib_arg->data.numVal < 0 || lib_arg->data.numVal > totalArgs){
            char * buffer = malloc(sizeof(char) * 128);
            sprintf(buffer, "argument must be in range [0, %d]!", totalArgs);
            avm_error(buffer, currLine);
            free(buffer);
        }
        else
            retval = stack[prev_topsp + AVM_STACKENV_SIZE + 1 + (int)lib_arg->data.numVal];

    }
}

void libfunc_strtonum(){

    unsigned n = avm_totalactuals();
    if(n != 1){
        char * buffer = malloc(sizeof(char) * 128);
        sprintf(buffer, "one argument (not %d) expected in 'strtonum'!", n);
        avm_error(buffer, currLine);
        free(buffer);
    }
    else{
        avm_memcell_clear(&retval);
        avm_memcell *lib_arg = avm_getactual(0);  //argument of 'libfunc' function
        
        if(lib_arg->type != string_m){
            char * buffer = malloc(sizeof(char) * 128);
            sprintf(buffer, "'strtonum' takes only string arguments! not" YEL" %s" RESET, typeStrings[lib_arg->type]);
            avm_error(buffer, currLine);
            free(buffer);
        }
        
        char *endptr;
        double val = strtod(lib_arg->data.strVal, &endptr);
        
        if(endptr == lib_arg->data.strVal){
            char * buffer = malloc(sizeof(char) * 128);
            sprintf(buffer, "convertion faile! argument of 'strtonum' is not a number!");
            avm_warning(buffer, currLine);
            free(buffer);
            retval.type = nil_m;
        }
        else{
            retval.type = number_m;
            retval.data.numVal = val;
        }
    }
}

void libfunc_sqrt(){

    unsigned n = avm_totalactuals();
    if(n != 1){
        char * buffer = malloc(sizeof(char) * 128);
        sprintf(buffer, "one argument (not %d) expected in 'sqrt'!", n);
        avm_error(buffer, currLine);
        free(buffer);
        return ;
    }

    avm_memcell *lib_arg = avm_getactual(0);  

    if(lib_arg->type != number_m){
        char * buffer = malloc(sizeof(char) * 128);
        sprintf(buffer, "'sqrt' takes only numeric arguments! not" YEL" %s" RESET, typeStrings[lib_arg->type]);
        avm_error(buffer, currLine);
        free(buffer);
    }
    else{
        if(lib_arg->data.numVal < 0){
            char * buffer = malloc(sizeof(char) * 128);
            sprintf(buffer, "argument of 'sqrt' must be positive!");
            avm_warning(buffer, currLine);
            free(buffer);
            retval.type = nil_m;
        }
        else{
            avm_memcell_clear(&retval);
            retval.type = number_m;
            retval.data.numVal = sqrt(lib_arg->data.numVal);
        }
    }
}

void cos_sin_impl(char * func){
    
    unsigned n = avm_totalactuals();
    if(n != 1){
        char * buffer = malloc(sizeof(char) * 128);
        sprintf(buffer, "one argument (not %d) expected in '%s'!", n, func);
        avm_error(buffer, currLine);
        free(buffer);
        return ;
    }

    avm_memcell *lib_arg = avm_getactual(0);  

    if(lib_arg->type != number_m){
        char * buffer = malloc(sizeof(char) * 128);
        sprintf(buffer, "'%s' takes only numeric arguments! not" YEL" %s" RESET, func, typeStrings[lib_arg->type]);
        avm_error(buffer, currLine);
        free(buffer);
    }
    else{
        avm_memcell_clear(&retval);
        retval.type = number_m;
        if(!strcmp(func, "sin"))
            retval.data.numVal = sin(lib_arg->data.numVal);
        else
            retval.data.numVal = cos(lib_arg->data.numVal);
    }
}

void libfunc_cos(){

    cos_sin_impl("cos");

}

void libfunc_sin(){

    cos_sin_impl("sin");
}

void libfunc_input(){

    unsigned n = avm_totalactuals();
    if(n > 0){
        char * buffer = malloc(sizeof(char) * 128);
        sprintf(buffer, "no arguments expected in 'input'!");
        avm_error(buffer, currLine);
        free(buffer);
        return;
    }

    char * str;
    size_t len = 0;
    getline(&str, &len, stdin);

   str[strcspn(str, "\n")] = '\0'; //remove newline

    avm_memcell_clear(&retval);

    if(str[0] == '"' && str[strlen(str) -1] == '"'){  //first way of user to give a string inside quotes
        retval.type = string_m;
        str[strlen(str) -1] = '\0';               //remove last quote   
        retval.data.strVal = strdup(str + 1);     //remove first quote
    }
    else if(!strcmp(str, "true")){
        retval.type = bool_m;
        retval.data.boolVal = 1;
    }
    else if(!strcmp(str, "false")){
        retval.type = bool_m;
        retval.data.boolVal = 0;
    }
    else if(!strcmp(str, "nil"))
        retval.type = nil_m;
    else{
        char *endptr;
        double val = strtod(str, &endptr);

        if(endptr == str){                  //second way of user to give a string without quotes
            retval.type = string_m;
            retval.data.strVal = strdup(str);
        }
        else{
            retval.type = number_m;
            retval.data.numVal = val;
        }
    }
}

void libfunc_objecttotalmembers(){

    unsigned n = avm_totalactuals();
    if(n != 1){
        char * buffer = malloc(sizeof(char) * 128);
        sprintf(buffer, "one argument (not %d) expected in 'objecttotalmembers'!", n);
        avm_error(buffer, currLine);
        free(buffer);
        return;
    }

    avm_memcell *lib_arg = avm_getactual(0);

    if(lib_arg->type != table_m){
        char * buffer = malloc(sizeof(char) * 128);
        sprintf(buffer, "'objecttotalmembers' takes only table arguments! not" YEL" %s" RESET, typeStrings[lib_arg->type]);
        avm_error(buffer, currLine);
        free(buffer);
    }
    else{
        avm_memcell_clear(&retval);
        retval.type = number_m;
        retval.data.numVal = lib_arg->data.tableVal->total;
    }
}


void libfunc_objectmemberkeys(){

    unsigned n = avm_totalactuals();
    if(n != 1){
        char * buffer = malloc(sizeof(char) * 128);
        sprintf(buffer, "one argument (not %d) expected in 'objectmemberkeys'!", n);
        avm_error(buffer, currLine);
        free(buffer);
        return ;
    }

    avm_memcell *lib_arg = avm_getactual(0);

    if(lib_arg->type != table_m){
        char * buffer = malloc(sizeof(char) * 128);
        sprintf(buffer, "'objectmemberkeys' takes only table arguments! not" YEL" %s" RESET, typeStrings[lib_arg->type]);
        avm_error(buffer, currLine);
        free(buffer);
    }
    else{

        avm_table *old_table = lib_arg->data.tableVal;
        avm_table *new_table = avm_table_new();
        
        avm_memcell *new_key = malloc(sizeof(avm_memcell));
        new_key->type = number_m;

        int totals_found = 0, i = 0;

        while(totals_found < old_table->total || i < AVM_TABLE_HASHSIZE){
            if(old_table->numIndexed[i] != NULL){
                new_key->data.numVal = totals_found++;
                avm_table_setelem(new_table, new_key, &old_table->numIndexed[i]->key);
            }
            if(old_table->strIndexed[i] != NULL){
                new_key->data.numVal = totals_found++;
                avm_table_setelem(new_table, new_key, &old_table->strIndexed[i]->key);
            }
            if(old_table->boolIndexed[i] != NULL){
                new_key->data.numVal = totals_found++;
                avm_table_setelem(new_table, new_key, &old_table->boolIndexed[i]->key);
            }
            if(old_table->tableIndexed[i] != NULL){
                new_key->data.numVal = totals_found++;
                avm_table_setelem(new_table, new_key, &old_table->tableIndexed[i]->key);
            }
            if(old_table->userfuncIndexed[i] != NULL){
                new_key->data.numVal = totals_found++;
                avm_table_setelem(new_table, new_key, &old_table->userfuncIndexed[i]->key);
            }
            if(old_table->libfuncIndexed[i] != NULL){
                new_key->data.numVal = totals_found++;
                avm_table_setelem(new_table, new_key, &old_table->libfuncIndexed[i]->key);
            }
            i++;
        }
        retval.type = table_m;
        retval.data.tableVal = new_table;
    }
}

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