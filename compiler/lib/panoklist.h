#include "linked_list.h"
#include "quad.h"

linked_list* new_panoklist(int i);
linked_list* merge_panoklist(linked_list *l1, linked_list* l2);
int patch_panoklist(linked_list* list, int label);
void shift_panoklist(linked_list* list, int shift, int max);
void print_panoklist(linked_list* list); //for debugging