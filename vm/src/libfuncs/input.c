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

        if(*endptr != '\0'){                  //second way of user to give a string without quotes
            retval.type = string_m;
            retval.data.strVal = strdup(str);
        }
        else{
            retval.type = number_m;
            retval.data.numVal = val;
        }
    }
}