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
instruction** code              = (instruction**) 0;
extern unsigned total_instr;
extern instruction** instructions;
extern avm_memcell stack[AVM_STACKSIZE];

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

char* register_type_to_string(avm_memcell_t type) {
    switch (type) {
        case number_m:
            return "number";
        case string_m:
            return "string";
        case bool_m:
            return "bool";
        case table_m:
            return "table";
        case userfunc_m:
            return "userfunc";
        case libfunc_m:
            return "libfunc";
        case nil_m:
            return "nil";
        case undef_m:
            return "undef";
        default:
            return "Unknown type";
    }
}

void print_memcell_value(avm_memcell *m) {
    switch(m->type) {
        case number_m:
            printf("%lf", m->data.numVal);
            break;
        case string_m:
            printf("%s", m->data.strVal);
            break;
        case bool_m:
            printf("%d", m->data.boolVal);
            break;
        case table_m:
            printf("table");
            break;
        case userfunc_m:
            printf("userfunc");
            break;
        case libfunc_m:
            printf("libfunc");
            break;
        case nil_m:
            printf("nil");
            break;
        case undef_m:
            printf("undef");
            break;
        default:
            printf("Unknown type");
            break;
    }
}

void print_vm_state() {
    printf("-----------< VM STATE >-----------\n");
    printf("pc : %d\n", pc);
    
    printf("ax: ");        print_memcell_value(&ax);     printf("(%s)", register_type_to_string(ax.type));
    printf(" | bx: ");     print_memcell_value(&bx);     printf("(%s)", register_type_to_string(bx.type));
    printf(" | cx: ");     print_memcell_value(&cx);     printf("(%s)", register_type_to_string(cx.type));
    printf(" | retVal: "); print_memcell_value(&retval); printf("(%s)", register_type_to_string(retval.type));
    
    printf("\ntop: %u | topsp: %u\n", top, topsp);
    print_vm_stack();
    printf("----------------------------------\n");
}


avm_memcell* avm_translate_operand(vmarg* arg, avm_memcell* reg){
    
    switch(arg->type){
        case global_a: return &stack[AVM_STACKSIZE-1-arg->val];
        case local_a: return &stack[topsp-arg->val];
        case formal_a: return &stack[topsp+AVM_STACKENV_SIZE+1+arg->val];
        case retval_a: return &retval;
        case number_a: {
            reg->type = number_m;
            reg->data.numVal = consts_getnumber(arg->val);
            return reg;
        }
        case string_a: {
            reg->type = string_m;
            reg->data.strVal = strdup(consts_getstring(arg->val));
            return reg;
        }
        case bool_a: {
            reg->type = bool_m;
            reg->data.boolVal = arg->val;
            return reg;
        }
        case nil_a: {
            reg->type = nil_m;
            return reg;
        }
        case userfunc_a: {
            reg->type = userfunc_m;
            reg->data.funcVal = userfuncs_getfunc(arg->val);
            return reg;
        }
        case libfunc_a: {
            reg->type = libfunc_m;
            reg->data.libfuncVal = strdup(libfuncs_getused(arg->val));
            return reg;
        }
        default: assert(0);
    }
}

void avm_error(char* message, unsigned line){
    fprintf(stderr, RED"Error: "RESET" %s (line " GRN "%d "RESET")\n", message, line);
}
void avm_warning(char* message, unsigned line){
    fprintf(stderr, RED"Warning: "RESET" %s (line " GRN "%d "RESET")\n", message, line);
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
        print_vm_state();
        execute_cycle();
    }
}