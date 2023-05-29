#include "avm_types.h"
#include "executors/execute.h"
#include "stack/avm_stack.h"
#include "parse_binfile.h"
#include "avm_helpers.h"
#include "tables/avm_tables.h"

#define MAX_INT 10
#define AVM_ENDING_PC codeSize
  
void avm_initialize();
void execute_cycle();

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

int DEBUG = 0;

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

int main(int argc, char** argv){

    FILE* bin_file = NULL;
    char* filename = "../compiler/binary.abc";

    if(!(bin_file = fopen(filename, "rb"))){
          fprintf(stderr, "Could not open input file: %s\n", filename);
          exit(EXIT_FAILURE);
    }

    parse_bin_file(bin_file);
    AVM_ENDING_PC = total_instr;

    avm_initialize();
    code = instructions;
    while(!executionFinished){
        execute_cycle();
    }
}

void avm_initialize(){
    
    avm_initstack();
    top = AVM_STACKSIZE - globals_total - 1;
    // topsp = 0; // den xreiazetai initialize, kathws ginetai otan exoume klisi sunartisis

    //init library functions below
    avm_registerlibfunc("print"             , libfunc_print);
    avm_registerlibfunc("typeof"            , libfunc_typeof);
    avm_registerlibfunc("totalarguments"    , libfunc_totalarguments);
    avm_registerlibfunc("argument"          , libfunc_argument);
    avm_registerlibfunc("strtonum"          , libfunc_strtonum);
    avm_registerlibfunc("sqrt"              , libfunc_sqrt);
    avm_registerlibfunc("cos"               , libfunc_cos);
    avm_registerlibfunc("sin"               , libfunc_sin);
    avm_registerlibfunc("input"             , libfunc_input);
    avm_registerlibfunc("objecttotalmembers", libfunc_objecttotalmembers);
    avm_registerlibfunc("objectmemberkeys"  , libfunc_objectmemberkeys);
    avm_registerlibfunc("objectcopy"        , libfunc_objectcopy);
}

void execute_cycle(){
    
    if(executionFinished){         //exit due to other reasons (e.g. error)
        return;
    }
    else if(pc == AVM_ENDING_PC){  //all instructions executed
        executionFinished = 1;
        return;
    }
    else{
       if(DEBUG) printf("pc : %d  ", pc);
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
        
        if(DEBUG) print_vm_state();
    }
}

avm_memcell* avm_translate_operand(vmarg* arg, avm_memcell* reg){
    switch(arg->type){
        case global_a: return &stack[AVM_STACKSIZE-1-arg->val];
        case local_a: return &stack[topsp-arg->val];
        case formal_a: {
            if( arg->val < avm_totalactuals())
                return &stack[topsp+AVM_STACKENV_SIZE+1+arg->val];
            else{
                char* s = malloc(strlen("Stack corruption: formal argument  is out of bounds") + MAX_INT + 1);
                sprintf(s, "Stack corruption: formal argument %d is out of bounds", arg->val);
                avm_error(s, arg->val);
            }
        }
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

void print_vm_state() {
    printf("-----------< VM STATE >-----------\n");
    
    printf("ax: ");        print_memcell_value(&ax);     printf("(%s)", register_type_to_string(ax.type));
    printf(" | bx: ");     print_memcell_value(&bx);     printf("(%s)", register_type_to_string(bx.type));
    printf(" | cx: ");     print_memcell_value(&cx);     printf("(%s)", register_type_to_string(cx.type));
    printf(" | retVal: "); print_memcell_value(&retval); printf("(%s)", register_type_to_string(retval.type));
    
    printf("\ntop: %u | topsp: %u\n", top, topsp);
    print_vm_stack();
    printf("----------------------------------\n");
    getchar();
}

void avm_error(char* message, unsigned line){
    fprintf(stderr, RED"Error: "RESET" %s (line " GRN "%d "RESET")\n", message, line);
    executionFinished = 1;
}

void avm_warning(char* message, unsigned line){
    fprintf(stderr, MAG"Warning: "RESET" %s (line " GRN "%d "RESET")\n", message, line);
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
    if(DEBUG) printf("call libfunc %s\n", id);

    library_func_t f = avm_getlibraryfunc(id);
    if(!f){
        char * buffer = malloc(sizeof(char) * 100);
        sprintf(buffer, "unsupported lib func "YEL"%s"RESET" called!", id);
        avm_error(buffer, currLine);
        executionFinished = 1;
        free(buffer);
    }
    else{
        topsp = top;
        totalActuals = 0;
        (*f)(); //this is actually funcenter
        if(DEBUG) printf("\nlibfuc :");
        if(!executionFinished)
            execute_funcexit((instruction*) 0);
    }

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
    else if(f->type == table_m)
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

unsigned avm_totalactuals(void){
    return avm_get_envvalue(topsp + AVM_NUMACTUALS_OFFSET);
}

avm_memcell* avm_getactual(unsigned i){
    assert(i < avm_totalactuals());
    return &stack[topsp + AVM_STACKENV_SIZE + 1 + i];
}