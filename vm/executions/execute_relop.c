#include "execute.h"
#include <stdio.h>

extern avm_memcell ax, bx, cx;
extern avm_memcell retval;
extern unsigned top, topsp;
extern unsigned pc;
extern avm_memcell stack[AVM_STACKSIZE];
extern unsigned char executionFinished;

extern unsigned currLine;

typedef double (*cmp_func_t)(double x, double y);


double jle_impl(double x, double y){
    printf("Executed <=>\n");
    return x <= y;
}

double jge_impl(double x, double y){
    printf("Executed >=\n");
    return x >= y;
}

double jlt_impl(double x, double y){
    printf("Executed <\n");
    return x < y;
}

double jgt_impl(double x, double y){
    printf("Executed >\n");
    return x > y;
}

cmp_func_t RelationalFuncs[] = {
    jle_impl, 
    jge_impl, 
    jlt_impl, 
    jgt_impl,
};


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

char* TypeRelOp[] = {
    "<=",
    ">=",
    "<",
    ">"
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

void execute_jeq_neq(instruction *instr, char * op){
    assert(instr->result->type == label_a);

    avm_memcell* rv1 = avm_translate_operand(instr->arg1, &ax);
    avm_memcell* rv2 = avm_translate_operand(instr->arg2, &bx);

    unsigned char result = 0;

    if(rv1->type == undef_m || rv2->type == undef_m){
        char * buffer = malloc(sizeof(char) * 128);
        sprintf(buffer, "'undef' involved in %s!", strcmp(op,"==") == 0 ? "equality" : "unequality");
        avm_error(buffer, currLine);
        free(buffer);
    }

    else if(rv1->type == nil_m || rv2->type == nil_m)
        result = rv1->type == nil_m && rv2->type == nil_m;

    else if(rv1->type == bool_m || rv2->type == bool_m)
        result = (avm_tobool(rv1) == avm_tobool(rv2));

    else if(rv1->type != rv2->type){
        char * buffer = malloc(sizeof(char) * 256);
        sprintf(buffer, YEL"%s" RESET" %s " YEL"%s"RESET" is illegal!", typeStrings[rv1->type], op, typeStrings[rv2->type]);
        avm_error(buffer, currLine);
        free(buffer);
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

    
    if(!executionFinished ){ //if there are no errors 
        if(result && strcmp(op, "==") == 0) //result is true and operation is equality check, we have to jump (so we set the pc to the label)
            pc = instr->result->val;
        else if(!result && strcmp(op, "!=") == 0) //result is false and operation is unequality check, we have to jump
            pc = instr->result->val;
    }
}

void execute_jeq(instruction* instr){
    printf("execute_jeq\n");

    execute_jeq_neq(instr, "==");    
}

void execute_jne(instruction* instr){
    printf("execute_jne\n");

    execute_jeq_neq(instr, "!=");
}

void execute_relational(instruction * instr){
    printf("execute_relational\n");

    assert(instr->result->type == label_a);

    avm_memcell* rv1 = avm_translate_operand(instr->arg1, &ax);
    avm_memcell* rv2 = avm_translate_operand(instr->arg2, &bx);

    unsigned char result = 0;

    assert(rv1 && rv2);

    if(rv1->type != number_m || rv2->type != number_m ){
        char *buffer = malloc(sizeof(char) * 256);
        sprintf(buffer, "not a number in relational comparison (" YEL "%s" RESET" %s " YEL"%s" RESET")!", typeStrings[rv1->type], TypeRelOp[instr->opcode - jle_vm], typeStrings[rv2->type]);
        avm_error(buffer, currLine);  
        free(buffer);
    }
    else{
        cmp_func_t operation = RelationalFuncs[instr->opcode - jle_vm];
        result = (*operation)(rv1->data.numVal, rv2->data.numVal);
    }

    if(!executionFinished && result)
        pc = instr->result->val;
}

void execute_jmp(instruction* instr){
    printf("execute_jmp\n");

    assert(instr->result->type == label_a);
    pc = instr->result->val;
}   