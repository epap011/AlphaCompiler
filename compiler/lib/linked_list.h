#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct node {
    void *data;
    struct node *next;
} node;

typedef struct linked_list {
    node *head;
    node *tail;
    int size;
} linked_list;

linked_list* create_linked_list();

void insert_at_the_end_to_linked_list(linked_list *list, void *data);
void insert_at_the_beginning_to_linked_list(linked_list *list, void *data);

void* get_from_linked_list(linked_list *list, int index);
void* get_first_from_linked_list(linked_list *list);
void* get_last_from_linked_list(linked_list *list);

void remove_from_linked_list(linked_list *list, int index);
void remove_first_from_linked_list(linked_list *list);
void remove_last_from_linked_list(linked_list *list);

void free_linked_list(linked_list *list);

#endif /* LINKED_LIST_H */