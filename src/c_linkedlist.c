#include "c_linkedlist.h"

#include <stdio.h>
#include <stdlib.h>

LinkedList* create_default_linkedlist() {
    LinkedList *linkedlist = (LinkedList*)malloc(sizeof(LinkedList));
    if (linkedlist != NULL) {
        linkedlist->size = 0;
        linkedlist->root = NULL;
        linkedlist->end = NULL;
    }
    return linkedlist;
}

void linkedlist_add_first(LinkedList *linkedlist, void *value) {
    LinkedNode *linked_node = (LinkedNode*)malloc(sizeof(LinkedNode));
    if (linked_node == NULL) {
        return;
    }
    linked_node->value = value;
    linked_node->pre = NULL;
    linked_node->next = linkedlist->root;
    linkedlist->root = linked_node;
    linkedlist->size++;

    if (linkedlist->end == NULL) {
        linkedlist->end = linkedlist->root;
    }
}

void* linkedlist_first(LinkedList *linkedlist) {
    if (linkedlist == NULL || linkedlist->root = NULL) {
        return NULL;
    }    
    
    return linkedlist->root->value;
}

void* linkedlist_first(LinkedList *linkedlist) {
    if (linkedlist == NULL || linkedlist == NULL) {
        return NULL;
    }

    
}
