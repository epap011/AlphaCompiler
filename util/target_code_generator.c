#include "target_code_generator.h"
#include "quad.h"
#include "linked_list.h"

typedef void (*generator_func_t)(quad*);

linked_list* num_const_list;
linked_list* str_const_list;
linked_list* lib_func_list;
linked_list* user_func_list;
linked_list* instructions_list;

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
    switch (e->type) {
        case var_e:
            break;
        case tableitem_e:
            break;
        case arithexpr_e:
            break;
        case boolexpr_e:
            break;
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
            arg->val = e->sym->taddress; //we might need to change this
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
    i->srcLine = q->line;

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
    i->srcLine = q->line;

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
    i->srcLine = q->line;

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
    i->srcLine = q->line;

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
    i->srcLine = q->line;

    i->result->type = label_a;
    i->result->val  = q->label;

    emit_instruction(i);
}

void generate_CALL(quad* q) {
    //q->arg1->sym->taddress = nextinstructionlabel();
    instruction* i = (instruction*) malloc(sizeof(instruction));
    i->opcode      = call_vm;
    i->result      = NULL;
    i->arg1        = (vmarg*) malloc(sizeof(vmarg));
    i->arg2        = NULL;

    make_operand(q->result, i->arg1);
    emit_instruction(i);
}

void generate_PARAM(quad* q) {
    //q->arg1->sym->taddress = nextinstructionlabel();
    instruction* i = (instruction*) malloc(sizeof(instruction));
    i->opcode      = pusharg_vm;
    i->result      = NULL;
    i->arg1        = (vmarg*) malloc(sizeof(vmarg));
    i->arg2        = NULL;

    make_operand(q->result, i->arg1);
    emit_instruction(i);
}
void generate_RETURN(quad* q) {
    instruction* i = (instruction*) malloc(sizeof(instruction));
    i->opcode      = assign_vm;
    i->result      = (vmarg*) malloc(sizeof(vmarg));
    i->arg1        = NULL;
    i->arg2        = NULL;

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
    i->result      = (vmarg*) malloc(sizeof(vmarg));
    i->arg1        = (vmarg*) malloc(sizeof(vmarg));
    i->arg2        = NULL;
    
    make_operand(q->result, i->result);
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

    make_operand(q->result, i->result);

    emit_instruction(i);
}
void generate_FUNCEND(quad* q) {
    instruction* i = (instruction*) malloc(sizeof(instruction));
    i->opcode      = funcexit_vm;
    i->result      = (vmarg*) malloc(sizeof(vmarg));
    i->arg1        = NULL;
    i->arg2        = NULL;

    make_operand(q->result, i->result);

    emit_instruction(i);
}

void generate_NEWTABLE(quad* q) {
    instruction* i = (instruction*) malloc(sizeof(instruction));
    i->opcode  = newtable_vm;
    i->result  = (vmarg*) malloc(sizeof(vmarg));
    i->arg1    = NULL;
    i->arg2    = NULL;
    i->srcLine = q->line;

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
    i->srcLine = q->line;

    emit_instruction(i);
}

void print_instructions() {

    printf("\n-------- Instructions --------\n");
    node* curr = instructions_list->head;
    while(curr != NULL) {
        instruction* i = (instruction*) curr->data;
        enum vmopcode op = i->opcode;
        unsigned result_index = i->result != NULL ? i->result->val : -1;
        unsigned arg1_index   = i->arg1   != NULL ? i->arg1->val   : -1;
        unsigned arg2_index   = i->arg2   != NULL ? i->arg2->val   : -1;
        
        printf("%d : OP: %s", i->srcLine, vmopcode_to_string(op));
        
        printf("\t\t RESULT: ");
        if(i->result != NULL) {
            if(i->result->type == number_a)
                printf("%s,%d:%lf", vmarg_t_to_string(i->result->type), result_index, *(double*)get_from_linked_list(num_const_list, result_index));
            else
            if(i->result->type == string_a)
                printf("%s,%d:%s", vmarg_t_to_string(i->result->type), result_index, (char*)get_from_linked_list(str_const_list, result_index));
            else
            if(i->result->type == bool_a)
                printf("%s,%d:%d", vmarg_t_to_string(i->result->type), result_index, i->result->val);

            else
            if(i->result->type == libfunc_a)
                printf("%s,%d:%s", vmarg_t_to_string(i->result->type), result_index, (char*)get_from_linked_list(lib_func_list, result_index));
            else
            if(i->result->type == userfunc_a)
                printf("%s,%d:%d", vmarg_t_to_string(i->result->type), result_index, *(int*)get_from_linked_list(user_func_list, result_index));
            else
                printf("NULL, ");
        }
        else printf("NULL, ");
        
        printf("\t\t ARG1: ");
        if(i->arg1 != NULL) {
            if(i->arg1->type == number_a)
                printf("%s,%d:%lf", vmarg_t_to_string(i->arg1->type), arg1_index, *(double*)get_from_linked_list(num_const_list, arg1_index));
            else
            if(i->arg1->type == string_a)
                printf("%s,%d:%s", vmarg_t_to_string(i->arg1->type), arg1_index, (char*)get_from_linked_list(str_const_list, arg1_index));
            else
            if(i->arg1->type == bool_a)
                printf("%s,%d:%d", vmarg_t_to_string(i->arg1->type), arg1_index, i->arg1->val);
            else
            if(i->arg1->type == libfunc_a)
                printf("%s,%d:%s", vmarg_t_to_string(i->arg1->type), arg1_index, (char*)get_from_linked_list(lib_func_list, arg1_index));
            else
            if(i->arg1->type == userfunc_a)
                printf("%s,%d:%d", vmarg_t_to_string(i->arg1->type), arg1_index, *(int*)get_from_linked_list(user_func_list, arg1_index));
            else
                printf("NULL, ");
        }
        else printf("NULL, ");

        printf("\t\t ARG2: ");
        if(i->arg2 != NULL) {
            if(i->arg2->type == number_a)
                printf("%s,%d:%lf", vmarg_t_to_string(i->arg2->type), arg2_index, *(double*)get_from_linked_list(num_const_list, arg2_index));
            else
            if(i->arg2->type == string_a)
                printf("%s,%d:%s", vmarg_t_to_string(i->arg2->type), arg2_index, (char*)get_from_linked_list(str_const_list, arg2_index));
            else
            if(i->arg2->type == bool_a)
                printf("%s,%d:%d", vmarg_t_to_string(i->arg2->type), arg2_index, i->arg2->val);
            else
            if(i->arg2->type == libfunc_a)
                printf("%s,%d:%s", vmarg_t_to_string(i->arg2->type), arg2_index, (char*)get_from_linked_list(lib_func_list, arg2_index));
            else
            if(i->arg2->type == userfunc_a)
                printf("%s,%d:%d", vmarg_t_to_string(i->arg2->type), arg2_index, *(int*)get_from_linked_list(user_func_list, arg2_index));
            else
                printf("NULL, ");
        }
        else printf("NULL, ");
        

        printf("\n");
        curr = curr->next;
    }
    printf("------------------------------\n");
}

char* vmopcode_to_string(enum vmopcode op) {
    switch(op) {
        case assign_vm:       return "assign";
        case add_vm:          return "add";
        case sub_vm:          return "sub";
        case mul_vm:          return "mul";
        case div_vm:          return "div";
        case mod_vm:          return "mod";
        case not_vm:          return "not";
        case jmp_vm:          return "jump";
        case jeq_vm:          return "jeq";
        case jne_vm:          return "jne";
        case jle_vm:          return "jle";
        case jge_vm:          return "jge";
        case jlt_vm:          return "jlt";
        case jgt_vm:          return "jgt";
        case call_vm:         return "call";
        case pusharg_vm:      return "pusharg";
        case funcenter_vm:    return "funcenter";
        case funcexit_vm:     return "funcexit";
        case newtable_vm:     return "newtable";
        case tablegetelem_vm: return "tablegetelem";
        case tablesetelem_vm: return "tablesetelem";
        case nop_vm:          return "nop";
        default:              return "unknown";
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


