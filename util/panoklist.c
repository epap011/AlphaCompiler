#include "panoklist.h"

linked_list* new_panoklist(int i) { // (i == -1) -> empty panoklist
    int* p_i;
    linked_list* new_list = create_linked_list();

    if(i != -1){
        p_i = (int*) malloc(sizeof(int));
        *p_i = i;
        insert_at_the_end_to_linked_list(new_list, p_i);
    }

    return new_list;
}

linked_list* merge_panoklist(linked_list *l1, linked_list* l2){
    if(!l1 && !l2) return NULL;
    else if(!l1) return l2;
    else if(!l2) return l1; 
    else {
        linked_list* new_list = create_linked_list();
        node* i = l1->head;
        while(i){
            insert_at_the_end_to_linked_list(new_list, i->data);
            i = i->next;
        }
        i = l2->head;
        while(i){
            insert_at_the_end_to_linked_list(new_list, i->data);
            i = i->next;
        }
        return new_list;
    }
}

int patch_panoklist(linked_list* list, int label){
    if ( !list || !(list->head) ) return 0;
    node* i = list->head;
    while(i){
        int* p_i = (int*) i->data;
        get_quads()[*p_i].label = label;
        i = i->next;
    }
    return 1;
}

void print_panoklist(linked_list* list){
    if ( !list )
        printf("-> nonexistent\n");
    else if ( !(list->head) )
        printf("-> empty\n");
    else{
        node* i = list->head;
        while(i){
            int* p_i = (int*) i->data;
            printf("-> %d ", *p_i+1);
            i = i->next;
        }
        printf("\n");
    }
}