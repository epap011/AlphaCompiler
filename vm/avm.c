#include "avm_stack.h"
#include "instructions.h"
#include "parse_binfile.h"
#include "avm_types.h"
#include "executions/execute.h"

avm_memcell ax, bx, cx;
avm_memcell retval;
unsigned top, topsp;

unsigned char executionFinished = 0;
unsigned pc                     = 0;
unsigned currLine               = 0;
unsigned codeSize               = 0;
instruction** code               = (instruction**) 0;
extern unsigned total_instr;
extern instruction** instructions;

#define AVM_ENDING_PC codeSize  

execute_func_t executeFuncs[] = {

    execute_assign,
    execute_add,
    execute_sub,
    execute_mul,
    execute_div,
    execute_mod,
    execute_jmp,
    execute_jeq,
    execute_jne,
    execute_jle,
    execute_jge,
    execute_jlt,
    execute_jgt,
    execute_call,
    execute_pusharg,
    execute_funcenter,
    execute_funcexit,
    execute_newtable,
    execute_tablegetelem,
    execute_tablesetelem,
    execute_nop
};

void execute_cycle(){
    if(executionFinished){
        return;
    }
    else if(pc == AVM_ENDING_PC){
        executionFinished = 1;
        return;
    }
    else{
        assert(pc < AVM_ENDING_PC);
        instruction* instr = code[pc];
        assert(instr->opcode >= 0 
            && instr->opcode <= AVM_MAX_INSTRUCTIONS);
       
        if(instr->srcLine)
            currLine = instr->srcLine;
        
        unsigned oldPC = pc;
        (*executeFuncs[instr->opcode])(instr);
        if(pc == oldPC)
            ++pc;
    }
    printf("Kanw kati : %d\n", pc);
}


void avm_initialize(){
    
    avm_initstack();
    top = 0;
    topsp = 0;

    //init library functions below
}

memclear_func_t memclarFuncs[] = {

    0,  /*number*/
    memclear_string,
    0, /*bool*/
    memclear_table,
    0, /*userfunc*/
    0, /*libfunc*/
    0, /*nil*/
    0  /*undef*/
};

void memclear_string(avm_memcell *m){
    assert(m->data.strVal);
    free(m->data.strVal);
}

void memclear_table(avm_memcell *m){
    assert(m->data.tableVal);
    avm_table_dec_refcounter(m->data.tableVal);
}

void avm_memcell_clear(avm_memcell *m){
    if(m->type != undef_m){
        memclear_func_t f = memclarFuncs[m->type];
        if(f)
            (*f)(m);
        m->type = undef_m;
    }
}


int main(int argc, char** argv){

    FILE* bin_file = NULL;

    if(argc != 2){
        printf("Invalid arguments.\n");
        exit(EXIT_FAILURE);
    }
    else if(!(bin_file = fopen(argv[1], "rb"))){
          fprintf(stderr, "Could not open input file: %s\n", argv[1]);
          exit(EXIT_FAILURE);
    }

    parse_bin_file(bin_file);
    AVM_ENDING_PC = total_instr;
    printf("Total instructions: %d\n", AVM_ENDING_PC);

    avm_initialize();
    code = instructions;
    while(!executionFinished){
        execute_cycle();
    }
}

