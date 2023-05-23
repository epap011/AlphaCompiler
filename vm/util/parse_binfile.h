#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <stdio.h>
#include <stdlib.h>

unsigned magic_number;
unsigned globals_total;
unsigned numbers_total;   double*       numbers;
unsigned strings_total;   char**        strings;
unsigned libfuncs_total;  char**        libfuncs;
unsigned userfuncs_total; user_func_t*  userfuncs;
unsigned total_instr;     instruction** instructions;




void parse_bin_file(FILE* bin_file);
char* get_string();
char* vmarg_t_to_string(enum vmarg_t arg);
char* vmopcode_to_string(enum vmopcode opcode);

#endif  // INSTRUCTION_H