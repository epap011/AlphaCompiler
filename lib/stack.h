#ifndef STACK_H
#define STACK_H

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