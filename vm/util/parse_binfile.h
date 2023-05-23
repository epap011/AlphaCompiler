#ifndef PARSER_BINFILE_H
#define PARSER_BINFILE_H

#include <stdio.h>
#include <stdlib.h>

void parse_bin_file(FILE* bin_file);
char* get_string();
char* vmarg_t_to_string(enum vmarg_t arg);
char* vmopcode_to_string(enum vmopcode opcode);

#endif  // PARSER_BINFILE_H