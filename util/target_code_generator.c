#include "target_code_generator.h"
#include "quad.h"
#include "linked_list.h"

typedef void (*generator_func_t)(quad*);

linked_list* num_const_list;
linked_list* str_const_list;
linked_list* lib_func_list;
linked_list* user_func_list;
linked_list* instructions_list;

unsigned first_stmt_counter = 1;

FILE* output_txt_file;
FILE* output_bin_file;

generator_func_t generators[] = {
    generate_ASSIGN,     
    generate_ADD,
    generate_SUB,
    generate_MUL,
    generate_DIV,
    generate_MOD,
    generate_UMINUS,
    generate_AND,
    generate_OR,
    generate_NOT,
    generate_IF_EQ,
    generate_IF_NOTEQ,
    generate_IF_LESSEQ,
    generate_IF_GREATEREQ,
    generate_IF_LESS,
    generate_IF_GREATER,
    generate_CALL,
    generate_PARAM,
    generate_RETURN,
    generate_GETRETVAL,
    generate_FUNCSTART,
    generate_FUNCEND,
    generate_NEWTABLE,
    generate_TABLEGETELEM,
    generate_TABLESETELEM,
    generate_JUMP,
    generate_NOP
};

void make_operand(expr* e, vmarg* arg){
    assert(e != NULL);
    assert(arg != NULL);
    switch (e->type) {
        case var_e:
        case tableitem_e:
        case arithexpr_e:
        case boolexpr_e:
        case newtable_e:
            assert(e->sym);
            arg->val = e->sym->offset;
            switch (e->sym->space) {
                case programvar: 
                    arg->type = global_a; 
                    break;
                case functionlocal: 
                    arg->type = local_a; 
                    break;
                case formalarg: 
                    arg->type = formal_a; 
                    break;
                default: assert(0);
            }
            break;

        case constbool_e:
            arg->val = e->boolConst;
            arg->type = bool_a;
            break;

        case conststring_e:
            arg->val = consts_newstring(e->strConst); 
            arg->type = string_a;
            break;
        
        case constnum_e:
            arg->val = consts_newnumber(e->numConst);
            arg->type = number_a;
            break;

        case nil_e: 
            arg->type = nil_a; 
            break;

        case programfunc_e:
            arg->type = userfunc_a;
            arg->val = userfuncs_newfunc(e->sym);
            break;

        case libraryfunc_e:
            arg->type = libfunc_a;
            arg->val = libfuncs_newused(e->sym->name); 
            break;
        
        default: assert(0);
    }
}

/**Helper functions for const values*/
void make_numberoperand(vmarg* arg, double val){
    arg->val = consts_newnumber(val);
    arg->type = number_a;
}   

void make_booloperand(vmarg* arg, unsigned val){
    arg->val = val;
    arg->type = bool_a;
}

void make_retvaloperand(vmarg* arg){ arg->type = retval_a; }

/**End of helpers*/

unsigned consts_newstring(char* s) {
    if(str_const_list == NULL) str_const_list = create_linked_list();
    char *str = strdup(s);
    insert_at_the_end_to_linked_list(str_const_list, str);
    return str_const_list->size - 1;
}
 
unsigned consts_newnumber(double n) {
    if(num_const_list == NULL) num_const_list = create_linked_list();
    double *num = (double*) malloc(sizeof(double));
    *num = n;
    insert_at_the_end_to_linked_list(num_const_list, num);
    return num_const_list->size - 1;
}

unsigned userfuncs_newfunc (Symbol* sym){
    if(user_func_list == NULL) user_func_list = create_linked_list();

    user_func_t *tmp = (user_func_t *)malloc(sizeof(user_func_t));
    tmp->iaddress = sym->iaddress;
    tmp->total_locals = sym->totalLocals;
    tmp->name = sym->name;

    insert_at_the_end_to_linked_list(user_func_list, tmp);

    return user_func_list->size - 1;
}

unsigned libfuncs_newused (const char* s)    {
    if(lib_func_list == NULL) lib_func_list = create_linked_list();
    char *str = strdup(s);
    insert_at_the_end_to_linked_list(lib_func_list, str);
    return lib_func_list->size - 1;
}

void generate(void) {
    int total_quads = nextQuadLabel();
    quad *quads = get_quads();
    for (unsigned i = 0; i < total_quads; ++i) {
        (*generators[quads[i].op])(quads+i);
    }
}

void emit_instruction(instruction* i){
    if(instructions_list == NULL) instructions_list = create_linked_list();
    insert_at_the_end_to_linked_list(instructions_list, i);
}

void generate_ARITHM(quad* q, enum vmopcode op) {
    instruction* i = (instruction*) malloc(sizeof(instruction));
    i->opcode  = op;
    i->result  = (vmarg*) malloc(sizeof(vmarg));
    i->arg1    = (vmarg*) malloc(sizeof(vmarg));
    i->arg2    = (vmarg*) malloc(sizeof(vmarg));
    assign_line_only_on_first_stms(q, i);

    make_operand(q->result, i->result);
    make_operand(q->arg1  , i->arg1);
    make_operand(q->arg2  , i->arg2); 

    emit_instruction(i);
}

void generate_RELATIONAL(quad* q, enum vmopcode op) {
    instruction* i = (instruction*) malloc(sizeof(instruction));
    i->opcode  = op;
    i->result  = (vmarg*) malloc(sizeof(vmarg));
    i->arg1    = (vmarg*) malloc(sizeof(vmarg));
    i->arg2    = (vmarg*) malloc(sizeof(vmarg));
    assign_line_only_on_first_stms(q, i);

    make_operand(q->arg1, i->arg1);
    make_operand(q->arg2, i->arg2);

    i->result->type = label_a;
    i->result->val  = q->label;

    emit_instruction(i);
}

void generate_ASSIGN(quad* q) {
    instruction* i = (instruction*) malloc(sizeof(instruction));
    i->opcode  = assign_vm;
    i->result  = (vmarg*) malloc(sizeof(vmarg));
    i->arg1    = (vmarg*) malloc(sizeof(vmarg));
    i->arg2    = NULL;
    assign_line_only_on_first_stms(q, i);

    make_operand(q->result, i->result);
    make_operand(q->arg1  , i->arg1);

    emit_instruction(i);
}

void generate_ADD   (quad* q) {generate_ARITHM(q, add_vm);}
void generate_SUB   (quad* q) {generate_ARITHM(q, sub_vm);}
void generate_MUL   (quad* q) {generate_ARITHM(q, mul_vm);}
void generate_DIV   (quad* q) {generate_ARITHM(q, div_vm);}
void generate_MOD   (quad* q) {generate_ARITHM(q, mod_vm);}

void generate_UMINUS(quad* q) {
    instruction* i = (instruction*) malloc(sizeof(instruction));
    i->opcode  = mul_vm;
    i->result  = (vmarg*) malloc(sizeof(vmarg));
    i->arg1    = (vmarg*) malloc(sizeof(vmarg));
    i->arg2    = (vmarg*) malloc(sizeof(vmarg));
    assign_line_only_on_first_stms(q, i);

    make_operand(q->result, i->result);
    make_operand(q->arg1  , i->arg1);
    make_numberoperand(i->arg2, -1);

    emit_instruction(i);
}

void generate_AND   (quad* q) {}
void generate_OR    (quad* q) {}
void generate_NOT   (quad* q) {}

void generate_IF_EQ       (quad* q) {generate_RELATIONAL(q, jeq_vm);}
void generate_IF_NOTEQ    (quad* q) {generate_RELATIONAL(q, jne_vm);}
void generate_IF_LESSEQ   (quad* q) {generate_RELATIONAL(q, jle_vm);}
void generate_IF_GREATEREQ(quad* q) {generate_RELATIONAL(q, jge_vm);}
void generate_IF_LESS     (quad* q) {generate_RELATIONAL(q, jlt_vm);}
void generate_IF_GREATER  (quad* q) {generate_RELATIONAL(q, jgt_vm);}
void generate_JUMP        (quad* q) {
    instruction* i = (instruction*) malloc(sizeof(instruction));
    i->opcode  = jmp_vm;
    i->result = (vmarg*) malloc(sizeof(vmarg));
    i->arg1    = NULL;
    i->arg2    = NULL;
    assign_line_only_on_first_stms(q, i);

    i->result->type = label_a;
    i->result->val  = q->label;

    emit_instruction(i);
}

void generate_CALL(quad* q) {
    //q->arg1->sym->taddress = nextinstructionlabel();
    instruction* i = (instruction*) malloc(sizeof(instruction));
    i->opcode      = call_vm;
    i->result      = NULL;
    i->arg2        = NULL;
    assign_line_only_on_first_stms(q, i);

    if(q->arg1) {
        i->arg1 = (vmarg*) malloc(sizeof(vmarg));
        make_operand(q->arg1, i->arg1);
    }

    emit_instruction(i);
}

void generate_PARAM(quad* q) {
    //q->arg1->sym->taddress = nextinstructionlabel();
    instruction* i = (instruction*) malloc(sizeof(instruction));
    i->opcode      = pusharg_vm;
    i->result      = NULL;
    i->arg1        = NULL;
    i->arg2        = NULL;
    assign_line_only_on_first_stms(q, i);

    if(q->arg1) {
        i->arg1 = (vmarg*) malloc(sizeof(vmarg));
        make_operand(q->arg1, i->arg1);
    }

    emit_instruction(i);
}
void generate_RETURN(quad* q) {
    instruction* i = (instruction*) malloc(sizeof(instruction));
    i->opcode      = assign_vm;
    i->result      = (vmarg*) malloc(sizeof(vmarg));
    i->arg1        = NULL;
    i->arg2        = NULL;
    assign_line_only_on_first_stms(q, i);

    make_retvaloperand(i->result);
    if(q->result != NULL){
        i->arg1 = (vmarg*) malloc(sizeof(vmarg));
        make_operand(q->arg1, i->arg1);
    }

    emit_instruction(i);
}
void generate_GETRETVAL(quad* q) {
    //q->arg1->sym->taddress = nextinstructionlabel();
    instruction* i = (instruction*) malloc(sizeof(instruction));
    i->opcode      = assign_vm;
    i->result      = NULL;
    i->arg1        = (vmarg*) malloc(sizeof(vmarg));
    i->arg2        = NULL;
    assign_line_only_on_first_stms(q, i);

    if(q->result) {
        i->result = (vmarg*) malloc(sizeof(vmarg));
        make_operand(q->result, i->result);
    }

    make_retvaloperand(i->arg1);
    emit_instruction(i);
}
void generate_FUNCSTART(quad* q) {
    //q->arg1->sym->taddress = nextinstructionlabel();
    instruction* i = (instruction*) malloc(sizeof(instruction));
    i->opcode      = funcenter_vm;
    i->result      = (vmarg*) malloc(sizeof(vmarg));
    i->arg1        = NULL;
    i->arg2        = NULL;
    assign_line_only_on_first_stms(q, i);

    make_operand(q->result, i->result);

    emit_instruction(i);
}
void generate_FUNCEND(quad* q) {
    instruction* i = (instruction*) malloc(sizeof(instruction));
    i->opcode      = funcexit_vm;
    i->result      = (vmarg*) malloc(sizeof(vmarg));
    i->arg1        = NULL;
    i->arg2        = NULL;
    assign_line_only_on_first_stms(q, i);

    make_operand(q->result, i->result);

    emit_instruction(i);
}

void generate_NEWTABLE(quad* q) {
    instruction* i = (instruction*) malloc(sizeof(instruction));
    i->opcode  = newtable_vm;
    i->result  = (vmarg*) malloc(sizeof(vmarg));
    i->arg1    = NULL;
    i->arg2    = NULL;
    assign_line_only_on_first_stms(q, i);

    make_operand(q->result, i->result);

    emit_instruction(i);
}
void generate_TABLEGETELEM(quad* q) {generate_ARITHM(q,tablegetelem_vm);}
void generate_TABLESETELEM(quad* q) {generate_ARITHM(q,tablesetelem_vm);}

void generate_NOP(quad* q) {
    instruction* i = (instruction*) malloc(sizeof(instruction));
    i->opcode  = nop_vm;
    i->result  = NULL;
    i->arg1    = NULL;
    i->arg2    = NULL;
    assign_line_only_on_first_stms(q, i);

    emit_instruction(i);
}

//This function is just for debugging purposes only. VM takes a binary file as input
void print_instructions() {

    if(instructions_list != NULL) 
        fprintf(output_txt_file, "total instructions : %u\n", instructions_list->size);
    else{
        fprintf(output_txt_file, "total instructions : 0\n");
        return;
    }
    
    fprintf(output_txt_file, "-------- Instructions --------\n");
    node* curr = instructions_list->head;
    int i = 0;
    while(curr != NULL) {
        fprintf(output_txt_file, "%-2d: ", i++);
        instruction* i = (instruction*) curr->data;
        fprintf(output_txt_file, "OP: %-15s ", vmopcode_to_string(i->opcode));
        if(i->result != NULL) 
            fprintf(output_txt_file, "RESULT: %-8s, %-6d", vmarg_t_to_string(i->result->type), i->result->val);
         else 
            fprintf(output_txt_file, "RESULT: %-16s", "");

        if(i->arg1 != NULL) 
            fprintf(output_txt_file, "ARG1: %-8s, %-6d", vmarg_t_to_string(i->arg1->type), i->arg1->val);
         else 
            fprintf(output_txt_file, "ARG1: %-16s", "");
        
        if(i->arg2 != NULL)
            fprintf(output_txt_file, "ARG2: %-8s, %-6d", vmarg_t_to_string(i->arg2->type), i->arg2->val);
         else 
            fprintf(output_txt_file, "ARG2: %-16s", "");

        fprintf(output_txt_file, "srcLine: %-2d\n",i->srcLine);

        curr = curr->next;
    }
}

void print_constnums() {
    if(num_const_list != NULL) 
        fprintf(output_txt_file, "total numbers : %u\n", num_const_list->size);
    else{
        fprintf(output_txt_file, "total numbers : 0\n");
        return;
    }
    fprintf(output_txt_file, "-------- Constnums Table --------\n");

    node* curr = num_const_list->head;
    int i = 0;
    while(curr != NULL) {
        fprintf(output_txt_file, "index: %-2d ", i++);
        double num = *(double *)(curr->data);
        if(num == (int)num)
            fprintf(output_txt_file, "value: %-3d\n", (int)num);
        else
            fprintf(output_txt_file, "value: %-3.5f\n", num);
        curr = curr->next;
    }
    fprintf(output_txt_file, "\n");
}

void print_conststrings() {
    if(str_const_list != NULL) 
        fprintf(output_txt_file, "total strings : %u\n", str_const_list->size);
    else{
        fprintf(output_txt_file, "total strings : 0\n");
        return;
    }

    fprintf(output_txt_file, "-------- Strings Table --------\n");

    node* curr = str_const_list->head;
    int i = 0;
    while(curr != NULL) {
        fprintf(output_txt_file, "index: %-2d ", i++);
        fprintf(output_txt_file, "value: %-10s\n", (char *)(curr->data));
        curr = curr->next;
    }
    fprintf(output_txt_file, "\n");
}

void print_libfuncs() {
    if(lib_func_list != NULL) 
        fprintf(output_txt_file, "total lib funcs : %u\n", lib_func_list->size);
    else{
        fprintf(output_txt_file, "total lib funcs : 0\n");
        return;
    }

    fprintf(output_txt_file, "-------- Libfuncs Table --------\n");

    node* curr = lib_func_list->head;
    int i = 0;
    while(curr != NULL) {
        fprintf(output_txt_file, "index: %-2d: ", i++);
        fprintf(output_txt_file, "value: %-10s\n", (char *)(curr->data));
        curr = curr->next;
    }
    fprintf(output_txt_file, "\n");
}

void print_userfuncs() {
    if(user_func_list != NULL) 
        fprintf(output_txt_file, "total user funcs : %u\n", user_func_list->size);
    else{
        fprintf(output_txt_file, "total user funcs : 0\n");
        return;
    }
    
    fprintf(output_txt_file, "-------- Userfuncs Table --------\n");

    node* curr = user_func_list->head;
    int i = 0;
    while(curr != NULL) {
        user_func_t* tmp = (user_func_t*) curr->data;
        fprintf(output_txt_file, "index: %-2d ", i++);
        fprintf(output_txt_file, "adress: %-2d\t local size: %-2d \t id: %-10s\n", tmp->iaddress, tmp->total_locals, tmp->name);
        curr = curr->next;
    }
    fprintf(output_txt_file, "\n");
}

void generate_txt_file() {
    unsigned magic_number  = 340200501;

    if(!output_txt_file) output_txt_file = fopen("binary.txt", "w");

    fprintf(output_txt_file, "magicnumber : %u\n", magic_number);
    print_constnums();
    print_conststrings();
    print_userfuncs();
    print_libfuncs();
    print_instructions();

}

void generate_bin_file() {
    unsigned magic_number    = 340200501;
    unsigned numbers_total   = num_const_list    != NULL ? num_const_list->size    : 0;
    unsigned strings_total   = str_const_list    != NULL ? str_const_list->size    : 0;
    unsigned libfuncs_total  = lib_func_list     != NULL ? lib_func_list->size     : 0;
    unsigned userfuncs_total = user_func_list    != NULL ? user_func_list->size    : 0;
    unsigned total_instr     = instructions_list != NULL ? instructions_list->size : 0;

    if(!output_bin_file) output_bin_file = fopen("binary.abc", "wb");

    fwrite(&magic_number, sizeof(unsigned), 1, output_bin_file);
    fwrite(&magic_number, sizeof(unsigned), 1, output_bin_file);
    
    fwrite(&numbers_total, sizeof(unsigned), 1, output_bin_file);
    node* curr = num_const_list != NULL ? num_const_list->head : NULL;
    while(curr != NULL) {
        double num = *(double *)(curr->data);
        fwrite(&num, sizeof(double), 1, output_bin_file);
        curr = curr->next;
    }

    fwrite(&strings_total, sizeof(unsigned), 1, output_bin_file);
    curr = str_const_list != NULL ? str_const_list->head : NULL;
    while(curr != NULL) {
        char* str = (char *)(curr->data);
        fwrite(str, sizeof(char), strlen(str) + 1, output_bin_file);
        curr = curr->next;
    }

    fwrite(&libfuncs_total , sizeof(unsigned), 1, output_bin_file);
    curr = lib_func_list != NULL ? lib_func_list->head : NULL;
    while(curr != NULL) {
        char* str = (char *)(curr->data);
        fwrite(str, sizeof(char), strlen(str) + 1, output_bin_file);
        curr = curr->next;
    }

    fwrite(&userfuncs_total, sizeof(unsigned), 1, output_bin_file);
    curr = user_func_list != NULL ? user_func_list->head : NULL;
    while(curr != NULL) {
        user_func_t* tmp = (user_func_t*) curr->data;
        fwrite(&tmp->iaddress    , sizeof(unsigned), 1, output_bin_file);
        fwrite(&tmp->total_locals, sizeof(unsigned), 1, output_bin_file);
        const char* str = tmp->name;
        fwrite(str, sizeof(char), strlen(str) + 1, output_bin_file);
        curr = curr->next;
    }
    
    fwrite(&total_instr, sizeof(unsigned), 1, output_bin_file);
    curr = instructions_list != NULL ? instructions_list->head : NULL;
    while(curr != NULL) {
        fwrite(&(((instruction*)curr->data)->opcode), sizeof(enum vmopcode), 1, output_bin_file);
        if(((instruction*)curr->data)->result)fwrite(&(((instruction*)curr->data)->result->type), sizeof(enum vmarg_t) , 1, output_bin_file);
        if(((instruction*)curr->data)->result)fwrite(&(((instruction*)curr->data)->result->val) , sizeof(unsigned)     , 1, output_bin_file);
        if(((instruction*)curr->data)->arg1)  fwrite(&(((instruction*)curr->data)->arg1->type)  , sizeof(enum vmarg_t) , 1, output_bin_file);
        if(((instruction*)curr->data)->arg1)  fwrite(&(((instruction*)curr->data)->arg1->val)   , sizeof(unsigned)     , 1, output_bin_file);
        if(((instruction*)curr->data)->arg2)  fwrite(&(((instruction*)curr->data)->arg2->type)  , sizeof(enum vmarg_t) , 1, output_bin_file);
        if(((instruction*)curr->data)->arg2)  fwrite(&(((instruction*)curr->data)->arg2->val)   , sizeof(unsigned)     , 1, output_bin_file);
        fwrite(&(((instruction*)curr->data)->srcLine), sizeof(unsigned), 1, output_bin_file);
        curr = curr->next;
    }
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
        default:          return "unknown";
    }
}

void assign_line_only_on_first_stms(quad* q, instruction* i) {
    if(q->line == first_stmt_counter) {
        i->srcLine = q->line;
        first_stmt_counter++;
    }
    else {
        i->srcLine = 0;
    }
}

