#include "avm_stack.h"
#include "instructions.h"
#include "parse_binfile.h"
#include "avm_types.h"
#include "avm_helpers.h"
#include "executions/execute.h"

#define AVM_NUMACTUALS_OFFSET   4
#define AVM_SAVEDPC_OFFSET      3
#define AVM_SAVEDTOP_OFFSET     2
#define AVM_SAVEDTOPSP_OFFSET   1

avm_memcell ax, bx, cx;
avm_memcell retval;
unsigned top, topsp;

unsigned char executionFinished = 0;
unsigned pc                     = 0;
unsigned currLine               = 0;
unsigned codeSize               = 0;
unsigned totalActuals           = 0;
instruction** code              = (instruction**) 0;
extern unsigned total_instr;
extern instruction** instructions;
extern avm_memcell stack[AVM_STACKSIZE];
extern unsigned globals_total;

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

tostring_func_t tostringFuncs[] = {

    number_tostring,
    string_tostring,
    bool_tostring,
    table_tostring,
    userfunc_tostring,
    libfunc_tostring,
    nil_tostring,
    undef_tostring
};


void execute_cycle(){
    if(executionFinished){         //exit due to other reasons (e.g. error)
        return;
    }
    else if(pc == AVM_ENDING_PC){  //all instructions executed
        executionFinished = 1;
        return;
    }
    else{
        printf("pc : %d  ", pc);
        assert(pc < AVM_ENDING_PC);
        instruction* instr = code[pc];
        assert(instr->opcode >= 0 
            && instr->opcode <= AVM_MAX_INSTRUCTIONS);
       
        if(instr->srcLine)
            currLine = instr->srcLine;
        
        unsigned oldPC = pc;
        (*executeFuncs[instr->opcode])(instr);
        if(pc == oldPC) //if pc chnged in execute, then it was a jump so we must not increase it
            ++pc;
        
        print_vm_state();
    }
}


void avm_initialize(){
    
    avm_initstack();
    top = AVM_STACKSIZE - globals_total - 1;
    topsp = AVM_STACKSIZE - 1;

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
    executionFinished = 1;
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
        execute_cycle();
    }
}

void avm_dec_top(void){
    if(!top){
        avm_error("stack overflow", currLine);
        executionFinished = 1;
    }
    else
        --top;
}

unsigned avm_get_envvalue(unsigned i){
    assert(stack[i].type == number_m);
    unsigned val = (unsigned) stack[i].data.numVal;
    assert(stack[i].data.numVal == ((double) val));
    return val;
}

void avm_push_envvalue(unsigned val){
    stack[top].type = number_m;
    stack[top].data.numVal = val;
    avm_dec_top();
}

void amv_callsaveenvironment(void){
    avm_push_envvalue(totalActuals);
    assert( code[pc]->opcode == call_vm );
    avm_push_envvalue(pc+1);
    avm_push_envvalue(top+totalActuals+2);
    avm_push_envvalue(topsp);
}



void avm_calllibfunc(char* id){
    printf("call libfunc %s\n", id);
}


//void avm_registerlibfunc(char* id, library_func_t addr){}

void avm_push_table_arg(avm_table* t){
    stack[top].type = table_m;
    avm_table_inc_refcounter(stack[top].data.tableVal = t);
    ++totalActuals;
    avm_dec_top();
}

void avm_call_functor(avm_table* t){
    cx.type = string_m;
    cx.data.strVal = strdup("()");
    avm_memcell* f = avm_table_getelem(t, &cx);
    if(!f)
        avm_error("in calling table: no '()' element found!", currLine);
    else if(f->type != table_m)
        avm_call_functor(f->data.tableVal);
    else if(f->type == userfunc_m){
        avm_push_table_arg(t);
        amv_callsaveenvironment();
        pc = f->data.funcVal->iaddress;
        assert(pc < AVM_ENDING_PC && code[pc]->opcode == funcenter_vm);
    }
    else
        avm_error("in calling table: '()' illegal element value!", currLine);
}

char* avm_tostring(avm_memcell* m){
    assert(m->type >= 0 && m->type <= undef_m);
    return (*tostringFuncs[m->type])(m);
}

char* number_tostring(avm_memcell* m){
    assert(m->type == number_m);
    char* str = malloc(sizeof(char) * 100);
    sprintf(str, "%lf", m->data.numVal);
    return str;
}

char* string_tostring(avm_memcell* m){
    assert(m->type == string_m);
    return strdup(m->data.strVal);
}

char* bool_tostring(avm_memcell* m){
    assert(m->type == bool_m);
    if(m->data.boolVal)
        return strdup("true");
    else
        return strdup("false");
}

char* table_tostring(avm_memcell* m){
    assert(m->type == table_m);
    return strdup("table");
}

char* userfunc_tostring(avm_memcell* m){
    assert(m->type == userfunc_m);
    return strdup(m->data.funcVal->name);
}


char* libfunc_tostring(avm_memcell* m){
    assert(m->type == libfunc_m);
    return strdup(m->data.libfuncVal);
}

char* nil_tostring(avm_memcell* m){
    return strdup("nil");
}

char* undef_tostring(avm_memcell* m){
    return strdup("undef");
}

unsigned avm_totalactuals(void){
    return avm_get_envvalue(topsp + AVM_NUMACTUALS_OFFSET);
}

avm_memcell* avm_getactual(unsigned i){
    assert(i < avm_totalactuals());
    return &stack[topsp + AVM_STACKENV_SIZE + 1 + i];
}


void libfunc_print(void){
    unsigned n = avm_totalactuals();
    unsigned i;
    for(i = 0; i < n; ++i){
        char* s = avm_tostring(avm_getactual(i));
        printf("%s", s);
        free(s);
    }
}
