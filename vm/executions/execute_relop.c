#include "execute.h"
#include <stdio.h>

extern avm_memcell ax, bx, cx;
extern avm_memcell retval;
extern unsigned top, topsp;
extern unsigned pc;
extern avm_memcell stack[AVM_STACKSIZE];
extern unsigned char executionFinished;

extern unsigned currLine;


tobool_func_t toboolFuncs[] = {
    number_tobool,
    string_tobool,
    bool_tobool,
    table_tobool,
    userfunc_tobool,
    libfunc_tobool,
    nil_tobool,
    undef_tobool
};

char * typeStrings[] = {
    "number",
    "string",
    "bool",
    "table",
    "userfunc",
    "libfunc",
    "nil",
    "undef"
};

unsigned char avm_tobool(avm_memcell * m){
    assert(m->type >= 0 && m->type < undef_m);
    return (*toboolFuncs[m->type])(m);
}

unsigned char number_tobool  (avm_memcell * m){return m->data.numVal != 0;}
unsigned char string_tobool  (avm_memcell * m){return m->data.strVal[0] != 0;}
unsigned char bool_tobool    (avm_memcell * m){return m->data.boolVal;}
unsigned char table_tobool   (avm_memcell * m){return 1;}
unsigned char userfunc_tobool(avm_memcell * m){return 1;}
unsigned char libfunc_tobool (avm_memcell * m){return 1;}
unsigned char nil_tobool     (avm_memcell * m){return 0;}
unsigned char undef_tobool   (avm_memcell * m){return 0;}

void execute_jeq(instruction* instr){
    printf("execute_jeq\n");

    assert(instr->result->type == label_a);

    avm_memcell* rv1 = avm_translate_operand(instr->arg1, &ax);
    avm_memcell* rv2 = avm_translate_operand(instr->arg2, &bx);

    unsigned char result = 0;

    if(rv1->type == undef_m || rv2->type == undef_m)
        avm_error("'undef' involved in equality!", currLine);

    else if(rv1->type == nil_m || rv2->type == nil_m)
        result = rv1->type == nil_m && rv2->type == nil_m;

    else if(rv1->type == bool_m || rv2->type == bool_m)
        result = (avm_tobool(rv1) == avm_tobool(rv2));

    else if(rv1->type != rv2->type){
        char * buffer = malloc(sizeof(char) * 512);
        sprintf(buffer, "%s == %s is illegal!", typeStrings[rv1->type], typeStrings[rv2->type]);
        avm_error(buffer, currLine);
    }
    else{ //rv1 == rv2
        //equality check for each case
        if(rv1->type == number_m)
            result = rv1->data.numVal == rv2->data.numVal;
        else if(rv1->type == string_m)
            result = !strcmp(rv1->data.strVal, rv2->data.strVal);
        else if(rv1->type == table_m)
            result = rv1->data.tableVal == rv2->data.tableVal;
        else if(rv1->type == userfunc_m)
            result = rv1->data.funcVal == rv2->data.funcVal;
        else if(rv1->type == libfunc_m)
            result = !strcmp(rv1->data.libfuncVal, rv2->data.libfuncVal);
    }

    //if there is no runtime error and result is true we have to jump, so we set the pc to the label
    if(!executionFinished && result) 
        pc = instr->result->val;
}

void execute_jne(instruction* instr){
    printf("execute_jne\n");
}

void execute_jle(instruction* instr){
    printf("execute_jle\n");
}

void execute_jge(instruction* instr){
    printf("execute_jge\n");
}

void execute_jlt(instruction* instr){
    printf("execute_jlt\n");
}

void execute_jgt(instruction* instr){
    printf("execute_jgt\n");
}

void execute_jmp(instruction* instr){
    printf("execute_jmp\n");
}