#ifndef STACK_H
#define STACK_H

#include <stdio.h>

typedef struct Node {
    void *data;
    struct Node *next;
} Node;

typedef struct Stack {
    Node *top;
    int size;
} Stack;

Stack *new_stack();

void push(Stack *stack, void *data);

void *pop(Stack *stack);

void *peek(Stack *stack);

void free_stack(Stack *stack);

#endif /*STACK_H*/

/*ScopeStackList
* Stack-List you can traverse backwards
* Necessary to bookkeep proximity of identifiers, to nearest function block
*
*   usage:	tail=SSL_Push(tail,flag);	    //push (returns tail ptr)
*	        tail=SSL_Pop(tail,flag);    	//pop (returns tail ptr)
*
*   	    tmp=tail;		    	        //peek (traverse)
*   	    while(tmp->prev) {tmp=tmp->prev;}
*/
typedef struct ScopeStackList{
	int flag;
	struct ScopeStackList *prev;
} ScopeStackList;

ScopeStackList *SSL_Push(ScopeStackList *tail, int flag);

ScopeStackList *SSL_Pop(ScopeStackList *tail);

void SSL_Print(ScopeStackList *tail);