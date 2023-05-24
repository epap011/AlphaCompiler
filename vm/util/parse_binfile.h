#ifndef PARSER_BINFILE_H
#define PARSER_BINFILE_H

#include <stdio.h>
#include <stdlib.h>
#include "avm_types.h"
#include "instructions.h"

void parse_bin_file(FILE* bin_file);
char* get_string();
char* vmarg_t_to_string(enum vmarg_t arg);
char* vmopcode_to_string(enum vmopcode opcode);

double consts_getnumber          (unsigned index);
char* consts_getstring           (unsigned index);
char* libfuncs_getused           (unsigned index);
user_func_t* userfuncs_getfunc  (unsigned index);

#endif  // PARSER_BINFILE_H