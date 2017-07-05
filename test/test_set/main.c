#include "c_utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

int main(int argc, char **argv) {
    // create set
    CSet *cset = create_default_set();

    // add
    set_add(cset, "test1");
    set_add(cset, "test1");
    set_add(cset, "test2");
    set_add(cset, "test3");

    // size
    int size = set_size(cset);
    printf("set size : %d\n", size);

    // contain
    assert(set_contain(cset, "test1") == 1);
    assert(set_contain(cset, "test0") == 0);
    printf("set contain ok.\n");

    // iterator
    CSetIterator it;
    set_iterator(cset, &it);
    int count = 0;
    for (CSetNode *node = set_next(&it); node != NULL; node = set_next(&it)) {
        count++;
        printf("%s\n", setnode_value(node));
    }
    assert(count == 3);
    printf("set iterator ok.\n");

    // foreach
    char *value;
    count = 0;
    set_foreach(cset, it, value) {
        count++;
        printf("%s\n", value); 
    }
    assert(count == 3);
    printf("set foreach ok.\n");

    // destroy set
    destroy_set(cset);
    return 0;
}
