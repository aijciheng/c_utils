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
    if (linkedlist == NULL || value == NULL) {
        return;
    }
    LinkedNode *linked_node = (LinkedNode*)malloc(sizeof(LinkedNode));
    if (linked_node == NULL) {
        return;
    }
    linked_node->value = value;
    linked_node->pre = NULL;
    linked_node->next = linkedlist->root;
    if (linked_node->next != NULL) {
        linked_node->next->pre = linked_node;
    }
    
    linkedlist->root = linked_node;
    linkedlist->size++;

    if (linkedlist->end == NULL) {
        linkedlist->end = linkedlist->root;
    }
}

void* linkedlist_first(LinkedList *linkedlist) {
    if (linkedlist == NULL || linkedlist->root == NULL) {
        return NULL;
    }    
    
    return linkedlist->root->value;
}

void* linkedlist_remove_first(LinkedList *linkedlist) {
    if (linkedlist == NULL || linkedlist->root == NULL) {
        return NULL;
    }

    LinkedNode *node = linkedlist->root;
    if (node != NULL) {
        if (node->next != NULL) {
            node->next->pre = NULL;
        }
        linkedlist->root = node->next;
        linkedlist->size--;
        if (node == linkedlist->end) {
            linkedlist->end = NULL;
        }
        void *value = node->value;
        free(node);
        return value;
    } 

    return NULL;
}

void linkedlist_add_last(LinkedList *linkedlist, void *value) {
    if (linkedlist == NULL || value == NULL) {
        return;
    }

    LinkedNode *linked_node = (LinkedNode*)malloc(sizeof(LinkedNode));
    if (linked_node == NULL) {
        return;
    }
    linked_node->value = value;
    linked_node->pre = linkedlist->end;
    linked_node->next = NULL;
    if (linked_node->pre != NULL) {
        linked_node->pre->next = linked_node;
    }

    linkedlist->end = linked_node;
    linkedlist->size++;

    if (linkedlist->root == NULL) {
        linkedlist->root = linkedlist->end;
    }

}

void* linkedlist_last(LinkedList *linkedlist) {
    if (linkedlist == NULL || linkedlist->end == NULL) {
        return NULL;
    }

    return linkedlist->end->value;
}

void* linkedlist_remove_last(LinkedList *linkedlist) {
    if (linkedlist == NULL || linkedlist == NULL) {
        return NULL;
    }

    LinkedNode *node = linkedlist->end;
    if (node != NULL) {
        if (node->pre != NULL) {
            node->pre->next = NULL;
        }
        linkedlist->end = node->pre;
        linkedlist->size--;
        if (node == linkedlist->root) {
            linkedlist->root = NULL;
        }
        void *value = node->value;
        free(node);
        return value;
    } 
    return NULL;
}

int linkedlist_size(LinkedList *linkedlist) {
    if (linkedlist == NULL) {
        return 0;
    } 

    return linkedlist->size;
}

void destroy_linkedlist(LinkedList *linkedlist) {
    if (linkedlist == NULL) {
        return;
    }

    LinkedNode *node = linkedlist->root;
    LinkedNode *next = NULL;
    while (node != NULL) {
        next = node->next;
        free(node);
        node = next;
    }
    free(linkedlist);
}
