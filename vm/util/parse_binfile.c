#include "parse_binfile.h"
#include "avm_stack.h"

FILE* bin_file;

extern unsigned top, topsp;
extern avm_memcell stack[AVM_STACKSIZE];
extern avm_memcell retval;

unsigned magic_number;
unsigned globals_total;
unsigned numbers_total;   double*       numbers;
unsigned strings_total;   char**        strings;
unsigned libfuncs_total;  char**        libfuncs;
unsigned userfuncs_total; user_func_t*  userfuncs;
unsigned total_instr;     instruction** instructions;

void parse_bin_file(FILE* b) {

    bin_file = b;

    fread(&magic_number, sizeof(unsigned), 1, bin_file);

    if(magic_number != 340200501) 
        exit(1);
    

    fread(&globals_total, sizeof(unsigned), 1, bin_file);

    fread(&numbers_total, sizeof(unsigned), 1, bin_file);

    numbers = (double*) malloc(sizeof(double) * numbers_total);
    for (unsigned i = 0; i < numbers_total; ++i) 
        fread(&numbers[i], sizeof(double), 1, bin_file);
       
    fread(&strings_total, sizeof(unsigned), 1, bin_file);

    strings = (char**) malloc(sizeof(char*) * strings_total);
    for (unsigned i = 0; i < strings_total; ++i) 
        strings[i] = get_string();
    
    fread(&libfuncs_total, sizeof(unsigned), 1, bin_file);
    libfuncs = (char**) malloc(sizeof(char*) * libfuncs_total);
    for (unsigned i = 0; i < libfuncs_total; ++i) 
        libfuncs[i] = get_string();

    fread(&userfuncs_total, sizeof(unsigned), 1, bin_file);

    userfuncs = (user_func_t*) malloc(sizeof(user_func_t) * userfuncs_total);
    for (unsigned i = 0; i < userfuncs_total; ++i) {
        fread(&userfuncs[i].iaddress, sizeof(unsigned), 1, bin_file);
        fread(&userfuncs[i].total_locals, sizeof(unsigned), 1, bin_file);
        userfuncs[i].name = get_string();
    }

    
    fread(&total_instr, sizeof(unsigned), 1, bin_file);
    instructions = (instruction**) malloc(sizeof(instruction*) * total_instr);
    for (unsigned i = 0; i < total_instr; ++i) {
        instruction* in = (instruction*) malloc(sizeof(instruction));
        in->result = (vmarg*) malloc(sizeof(vmarg));
        in->arg1   = (vmarg*) malloc(sizeof(vmarg));
        in->arg2   = (vmarg*) malloc(sizeof(vmarg));

        fread(&in->opcode      , sizeof(enum vmopcode), 1, bin_file);
        fread(&in->result->type, sizeof(enum vmarg_t) , 1, bin_file);
        fread(&in->result->val , sizeof(unsigned)     , 1, bin_file);
        fread(&in->arg1->type  , sizeof(enum vmarg_t) , 1, bin_file);
        fread(&in->arg1->val   , sizeof(unsigned)     , 1, bin_file);
        fread(&in->arg2->type  , sizeof(enum vmarg_t) , 1, bin_file);
        fread(&in->arg2->val   , sizeof(unsigned)     , 1, bin_file);
        fread(&in->srcLine     , sizeof(unsigned)     , 1, bin_file);

        instructions[i] = in;
    }
}

char* get_string() {
    int size = 2048;
    char* str = (char*) malloc(sizeof(char) * size);
    char c;
    int i = 0;
    while((c = getc(bin_file)) != '\0') {
        str[i++] = c;
        if(i == size) {
            size *= 2;
            str = (char*) realloc(str, sizeof(char) * size);
        }
    }
    return str;
}

double consts_getnumber(unsigned index){
    return numbers[index];
}

char* consts_getstring(unsigned index){
    return strings[index];
}
char* libfuncs_getused(unsigned index){
    return libfuncs[index];
}
user_func_t* userfuncs_getfunc(unsigned index){
    return &userfuncs[index];
}
