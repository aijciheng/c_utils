#include "c_utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

int main(int argc, char **argv) {
    // create linkedlist
    LinkedList *linked_list = create_default_linkedlist();

    // ----------------------------stack----------------------------------------

    // add first
    linkedlist_add_first(linked_list, "1");
    linkedlist_add_first(linked_list, "2");
    linkedlist_add_first(linked_list, "3");

    // size 3
    assert(linkedlist_size(linked_list) == 3);
    printf("size 3 is ok.\n");

    // first
    assert(strcmp((char*)linkedlist_first(linked_list), "3") == 0);
    printf("first is ok.\n");

    // remove first
    char* c = (char*)linkedlist_remove_first(linked_list);
    assert(strcmp(c, "3") == 0);
    c = (char*)linkedlist_remove_first(linked_list);
    assert(strcmp(c, "2") == 0);
    c = (char*)linkedlist_remove_first(linked_list);
    assert(strcmp(c, "1") == 0);
    printf("remove first is ok.\n");

    // size 0
    assert(linkedlist_size(linked_list) == 0);
    printf("size 0 is ok.\n");

    // add last
    linkedlist_add_last(linked_list, "1");
    linkedlist_add_last(linked_list, "2");
    linkedlist_add_last(linked_list, "3");
    
    // size 3
    assert(linkedlist_size(linked_list) == 3);
    printf("size 3 is ok.\n");

    // last
    assert(strcmp((char*)linkedlist_last(linked_list), "3") == 0);
    printf("last is ok.\n");
     
    // remove last
    c = (char*)linkedlist_remove_last(linked_list);
    assert(strcmp(c, "3") == 0);
    c = (char*)linkedlist_remove_last(linked_list);
    assert(strcmp(c, "2") == 0);
    c = (char*)linkedlist_remove_last(linked_list);
    assert(strcmp(c, "1") == 0);
    printf("remove last is ok.\n");

    // size 0
    assert(linkedlist_size(linked_list) == 0);
    printf("size 0 is ok.\n");

    // ----------------------queue----------------------------------
    linkedlist_add_last(linked_list, "1");
    linkedlist_add_last(linked_list, "2");
    linkedlist_add_last(linked_list, "3");

    // add last remove first
    c = (char*)linkedlist_remove_first(linked_list);
    assert(strcmp(c, "1") == 0);
    c = (char*)linkedlist_remove_first(linked_list);
    assert(strcmp(c, "2") == 0);
    c = (char*)linkedlist_remove_first(linked_list);
    assert(strcmp(c, "3") == 0);
    printf("add last remove first is ok.\n");

    linkedlist_add_first(linked_list, "1");
    linkedlist_add_first(linked_list, "2");
    linkedlist_add_first(linked_list, "3");

    // add first remove last
    c = (char*)linkedlist_remove_last(linked_list);
    assert(strcmp(c, "1") == 0);
    c = (char*)linkedlist_remove_last(linked_list);
    assert(strcmp(c, "2") == 0);
    c = (char*)linkedlist_remove_last(linked_list);
    assert(strcmp(c, "3") == 0);
    printf("add first remove last is ok.\n");

    // destroy linkedlist
    destroy_linkedlist(linked_list);
    return 0;
}
