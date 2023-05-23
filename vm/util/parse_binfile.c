#include "instructions.h"
#include "parse_binfile.h"

FILE* bin_file;

void parse_bin_file(FILE* b) {

    bin_file = b;

    printf("\n------< Parsing Bin File >------\n");

    fread(&magic_number, sizeof(unsigned), 1, bin_file);
    printf("magic-number: %u\n", magic_number);

    if(magic_number != 340200501) {
        printf("Wrong magic number\n");
        exit(1);
    }

    fread(&globals_total, sizeof(unsigned), 1, bin_file);
    printf("total globals: %u\n", globals_total);

    fread(&numbers_total, sizeof(unsigned), 1, bin_file);
    printf("total numbers: %u\n", numbers_total);
    numbers = (double*) malloc(sizeof(double) * numbers_total);
    for (unsigned i = 0; i < numbers_total; ++i) {
        fread(&numbers[i], sizeof(double), 1, bin_file);
        printf("number[%u] = %f\n", i, numbers[i]);
    }
    
    fread(&strings_total, sizeof(unsigned), 1, bin_file);
    printf("total strings: %u\n", strings_total);
    strings = (char**) malloc(sizeof(char*) * strings_total);
    for (unsigned i = 0; i < strings_total; ++i) {
        strings[i] = get_string();
        printf("string[%u] = %s\n", i, strings[i]);
    }
    
    
    fread(&libfuncs_total, sizeof(unsigned), 1, bin_file);
    printf("total libfuncs: %u\n", libfuncs_total);
    libfuncs = (char**) malloc(sizeof(char*) * libfuncs_total);
    for (unsigned i = 0; i < libfuncs_total; ++i) {
        libfuncs[i] = get_string();
        printf("libfuncs[%u] = %s\n", i, libfuncs[i]);
    }

    
    fread(&userfuncs_total, sizeof(unsigned), 1, bin_file);
    printf("total userfuncs: %u\n", userfuncs_total);
    userfuncs = (user_func_t*) malloc(sizeof(user_func_t) * userfuncs_total);
    for (unsigned i = 0; i < userfuncs_total; ++i) {
        fread(&userfuncs[i].iaddress, sizeof(unsigned), 1, bin_file);
        fread(&userfuncs[i].total_locals, sizeof(unsigned), 1, bin_file);
        userfuncs[i].name = get_string();
        printf("userfuncs[%u] = %u %u %s\n", i, userfuncs[i].iaddress, userfuncs[i].total_locals, userfuncs[i].name);
    }

    
    fread(&total_instr, sizeof(unsigned), 1, bin_file);
    printf("total instructions: %u\n", total_instr);
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

        printf("%s %s %d %s %d %s %d %d\n", vmopcode_to_string(in->opcode), vmarg_t_to_string(in->result->type), in->result->val, vmarg_t_to_string(in->arg1->type), in->arg1->val, vmarg_t_to_string(in->arg2->type), in->arg2->val, in->srcLine);  
    }
    printf("------< End of Parsing Bin file >------\n");
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

char* vmopcode_to_string(enum vmopcode op) {
    switch(op) {
        case assign_vm:       return "assign_vm";
        case add_vm:          return "add_vm";
        case sub_vm:          return "sub_vm";
        case mul_vm:          return "mul_vm";
        case div_vm:          return "div_vm";
        case mod_vm:          return "mod_vm";
        case not_vm:          return "not_vm";
        case jmp_vm:          return "jmp_vm";
        case jeq_vm:          return "jeq_vm";
        case jne_vm:          return "jne_vm";
        case jle_vm:          return "jle_vm";
        case jge_vm:          return "jge_vm";
        case jlt_vm:          return "jlt_vm";
        case jgt_vm:          return "jgt_vm";
        case call_vm:         return "call_vm";
        case pusharg_vm:      return "pusharg_vm";
        case funcenter_vm:    return "funcenter_vm";
        case funcexit_vm:     return "funcexit_vm";
        case newtable_vm:     return "newtable_vm";
        case tablegetelem_vm: return "tablegetelem_vm";
        case tablesetelem_vm: return "tablesetelem_vm";
        case nop_vm:          return "nop_vm";
        default:              return "unknown_vm";
    }
}

char* vmarg_t_to_string(enum vmarg_t arg) {
    switch(arg) {
        case label_a:     return "label";
        case global_a:    return "global";
        case formal_a:    return "formal";
        case local_a:     return "local";
        case number_a:    return "number";
        case string_a:    return "string";
        case bool_a:      return "bool";
        case nil_a:       return "nil";
        case userfunc_a:  return "userfunc";
        case libfunc_a:   return "libfunc";
        case retval_a:    return "retval";
        case undef_a:     return "NULL";
        default:          return "unknown";
    }
}