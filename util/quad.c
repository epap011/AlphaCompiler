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