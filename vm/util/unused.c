#include "instructions.h"

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
