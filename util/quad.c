#include "quad.h"

quad* quads = (quad *) 0;
unsigned int total = 0;
unsigned int currQuad = 0;

void expand(){

    assert(total == currQuad);
    quad *p = (quad *)malloc(NEW_SIZE);
    if(quads){
        memcpy(p, quads, CURR_SIZE);
        free(quads);
    }

    quads = p;
    total += EXPAND_SIZE;
}   


void emit(enum iopcode op, expr *arg1, expr *arg2, expr *result, unsigned label, unsigned line){
    if(currQuad == total)
        expand();

    quad *p = quads + currQuad++;
    p->op = op;
    p->arg1 = arg1;
    p->arg2 = arg2;
    p->result = result;
    p->label = label;
    p->line = line;
}

expr* emit_if_tableitem(expr* e, unsigned int scope, unsigned int line){
    if(e->type != tableitem_e)
        return e;

    else{
        expr* result = new_expr(var_e);
        //new temp symbol
        result->sym = symbol_table_insert(symTable, symbol_create(str_int_merge("_t",anonym_var_cnt++), scope, line, scope == 0 ? GLOBAL : _LOCAL, 1, var_s, currScopeSpace(), currScopeOffset()));
        incCurrScopeOffset();

        result->truelist = -1;
        result->falselist = -1;

        emit(tablegetelem, e, e->index, result, -1, yylineno);
        return result;
    }
}

unsigned int nextQuadLabel(){
        return currQuad;
}

void patchLabel(unsigned quadNo, unsigned label){
    assert(quadNo < currQuad);
    quads[quadNo].label = label;
}

void printQuads(){
    int i;
    for(i = 0; i < currQuad; i++){
        printf("%-2d: OP: "BLU"%-12s"RESET"\t", i + 1, iopcode_tostring(quads[i].op));
        if(quads[i].result != NULL) {
            if(quads[i].result->sym != NULL)
                printf(" RESULT: "YEL"%-15s"RESET"\t", quads[i].result->sym->name);
        }
        else
            printf(" RESULT: "RED"NULL           "RESET"\t");   

        if(quads[i].arg1 != NULL){
            if(quads[i].arg1->type == var_e         ||
               quads[i].arg1->type == arithexpr_e   ||
               quads[i].arg1->type == libraryfunc_e || 
               quads[i].arg1->type == programfunc_e ||
               quads[i].arg1->type == boolexpr_e    ||
               quads[i].arg1->type == tableitem_e   ||
               quads[i].arg1->type == newtable_e)
                printf(" ARG1: "YEL"%-15s"RESET"\t", quads[i].arg1->sym->name);
            else if(quads[i].arg1->type == constnum_e) {
                if(quads[i].arg1->sym != NULL)
                    printf(" ARG1: "YEL"%-15s"RESET"\t", quads[i].arg1->sym->name);
                else
                    printf(" ARG1: "YEL"%-15.2f"RESET"\t", quads[i].arg1->numConst);
            }
            else if(quads[i].arg1->type == constbool_e)
                printf(" ARG1: "YEL"%-15s"RESET"\t", quads[i].arg1->boolConst ? "true" : "false");
            else if(quads[i].arg1->type == conststring_e){
                int spacing = 13 - count_str(quads[i].arg1->strConst);
                printf(" ARG1: \""YEL"%s"RESET"\"", quads[i].arg1->strConst);
                for(int i = 0; i < spacing; i++)
                    printf(" ");
                printf("\t");
            }
            else if(quads[i].arg1->type == nil_e)
                printf(" ARG1: "YEL"nil            "RESET"\t");
            else 
                printf("ARG1: Something is wrong");
        }
        else
            printf(" ARG1: "RED"NULL           "RESET"\t");
        if(quads[i].arg2 != NULL){
            if(quads[i].arg2->type == var_e         ||
               quads[i].arg2->type == arithexpr_e   ||
               quads[i].arg2->type == libraryfunc_e || 
               quads[i].arg2->type == programfunc_e ||
               quads[i].arg2->type == boolexpr_e    ||
               quads[i].arg2->type == tableitem_e   ||
               quads[i].arg2->type == newtable_e)
                printf(" ARG2: "YEL"%-15s"RESET"\t", quads[i].arg2->sym->name);
            else if(quads[i].arg2->type == constnum_e) {
                if(quads[i].arg2->sym != NULL)
                    printf(" ARG2: "YEL"%-15s"RESET"\t", quads[i].arg2->sym->name);
                else
                    printf(" ARG2: "YEL"%-15.2f"RESET"\t", quads[i].arg2->numConst);
            }
            else if(quads[i].arg2->type == constbool_e)
                printf(" ARG2: "YEL"%-15s"RESET"\t", quads[i].arg2->boolConst ? "true" : "false");
            else if(quads[i].arg2->type == conststring_e){
                int spacing = 13 - count_str(quads[i].arg2->strConst);
                printf(" ARG2: \""YEL"%s"RESET"\"", quads[i].arg2->strConst);
                for(int i = 0; i < spacing; i++)
                    printf(" ");
                printf("\t");
            }
            else if(quads[i].arg2->type == nil_e)
                printf(" ARG2: "YEL"nil            "RESET"\t");
            else 
                printf("ARG2: Something is wrong");
        }
        else
            printf(" ARG2: "RED"NULL           "RESET"\t");
        if (quads[i].label == -1)
            printf(" LABEL: UNSET\t");
        else
            printf(" LABEL: %d  \t", quads[i].label+1);
        printf("LINE: "GRN"%d"RESET"\n", quads[i].line);
    }
}

const char* iopcode_tostring(enum iopcode op){
    switch (op)
    {
        case assign: return "assign";
        case add: return "add";
        case sub: return "sub";
        case mul: return "mul";
        case i_div: return "div";
        case mod: return "mod";
        case uminus: return "uminus";
        case and: return "and";
        case or: return "or";
        case not: return "not";
        case if_eq: return "if_eq";
        case if_noteq: return "if_noteq";
        case if_lesseq: return "if_lesseq";
        case if_greatereq: return "if_greatereq";
        case if_less: return "if_less";
        case if_greater: return "if_greater";
        case call: return "call";
        case param: return "param";
        case ret: return "return";
        case getretval: return "getretval";
        case funcstart: return "funcstart";
        case funcend: return "funcend";
        case tablecreate: return "tablecreate";
        case tablegetelem: return "tablegetelem";
        case tablesetelem: return "tablesetelem";
        case jump: return "jump";
        default:
            return "unknown";
    }
}

int count_str(const char* str){

    int i = 0;
    int count = 0;
    while(str[i] != '\0'){
        if(str[i] == '\\' && str[i+1] == 't')
            count += 7;
        count++;
        i++;
    }
    return count;
}

quad* get_quads(){
    return quads;
}

/*Quad list related functions*/

stmt_t* make_stmt() {
    stmt_t* stmt = (stmt_t*)malloc(sizeof(stmt_t));
    stmt->break_list = 0;
    stmt->cont_list  = 0;
    return stmt;
}

int new_list(int i) {
    get_quads()[i].label = 0;
    return i;
}

int merge_list(int l1, int l2) {
    if(!l1) return l2;
    else
    if(!l2) return l1; 
    else {
        int i = l1;
        while(get_quads()[i].label != 0) i = get_quads()[i].label;
        get_quads()[i].label = l2;
        return l1;
    }
}

void patch_list(int list, int label) {
    while(list) {
        int next = get_quads()[list].label;
        get_quads()[list].label = label;
        list = next;
    }
}