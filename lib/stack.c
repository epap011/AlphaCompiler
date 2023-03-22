#include "stack.h"
#include <stdlib.h>

Stack* new_stack() {
    Stack *stack = malloc(sizeof(Stack));
    stack->top = NULL;
    stack->size = 0;
    return stack;
}

void push(Stack *stack, void *data) {
    Node *node = malloc(sizeof(Node));
    node->data  = data;
    node->next  = stack->top;
    stack->top  = node;
}

void *pop(Stack *stack) {
    if (stack->top == NULL) {
        return NULL;
    }
    Node *node = stack->top;
    stack->top = node->next;
    void *data = node->data;
    free(node);
    return data;
}

void *peek(Stack *stack) {
    if (stack->top == NULL) {
        return NULL;
    }
    return stack->top->data;
}

void delete_stack(Stack *stack) {
    while (stack->top != NULL) {
        Node *node = stack->top;
        stack->top = node->next;
        free(node);
    }
}