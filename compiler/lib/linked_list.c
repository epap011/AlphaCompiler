#include <stdlib.h>
#include "linked_list.h"

linked_list* create_linked_list() {
    linked_list *new_list = (linked_list*) malloc(sizeof(linked_list));
    new_list->head = NULL;
    new_list->tail = NULL;
    new_list->size = 0;

    return new_list;
}

void insert_at_the_end_to_linked_list(linked_list *list, void *data) {
    node *new_node = (node*) malloc(sizeof(node));
    new_node->data = data;
    new_node->next = NULL;

    if (list->head == NULL) {
        list->head = new_node;
        list->tail = new_node;
    } else {
        list->tail->next = new_node;
        list->tail = new_node;
    }

    list->size++;
}

void insert_at_the_beginning_to_linked_list(linked_list *list, void *data) {
    node *new_node = (node*) malloc(sizeof(node));
    new_node->data = data;
    new_node->next = list->head;

    if (list->head == NULL) {
        list->tail = new_node;
    }

    list->head = new_node;
    list->size++;
}

void *get_from_linked_list(linked_list *list, int index) {
    if (index < 0 || index >= list->size) {
        return NULL;
    }

    node *current = list->head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }

    return current->data;
}

void *get_first_from_linked_list(linked_list *list) {
    return get_from_linked_list(list, 0);
}

void *get_last_from_linked_list(linked_list *list) {
    return get_from_linked_list(list, list->size - 1);
}

void remove_from_linked_list(linked_list *list, int index) {
    if (index < 0 || index >= list->size) {
        return;
    }

    node *current = list->head;
    node *previous = NULL;
    for (int i = 0; i < index; i++) {
        previous = current;
        current = current->next;
    }

    if (previous == NULL) {
        list->head = current->next;
    } else {
        previous->next = current->next;
    }

    if (current->next == NULL) {
        list->tail = previous;
    }

    free(current);
    list->size--;
}

void remove_first_from_linked_list(linked_list *list) {
    remove_from_linked_list(list, 0);
}

void remove_last_from_linked_list(linked_list *list) {
    remove_from_linked_list(list, list->size - 1);
}

void free_linked_list(linked_list *list) {
    while (list->head != NULL) {
        node *current = list->head;
        list->head = current->next;
        free(current);
    }

    free(list);
}