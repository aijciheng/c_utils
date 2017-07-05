#include "c_set.h"

#include <stdio.h>
#include <stdlib.h>

CSet* create_default_set() {
    CSet *cset = (CSet*)malloc(sizeof(CSet));
    if (cset != NULL) {
        cset->cmap = create_default_map();
    }
    return cset;
}

void set_add(CSet *cset, char *value) {
    if (cset == NULL || value == NULL) {
        return;
    }

    map_put(cset->cmap, value, value);
}

int set_size(CSet *cset) {
    if (cset == NULL) {
        return 0;
    }

    return map_size(cset->cmap);
}

int set_contain(CSet *cset, char *value) {
    if (cset == NULL || value == NULL) {
        return 0;
    }
    
    return map_contain(cset->cmap, value);
}

void set_iterator(CSet *cset, CSetIterator *iterator) {
    if (cset == NULL || iterator == NULL) {
        return;
    }
    
    map_iterator(cset->cmap, iterator);
}

CSetNode* set_next(CSetIterator *iterator) {
    return map_next(iterator);
}

char* setnode_value(CSetNode *node) {
    return mapnode_value(node);
}

void destroy_set(CSet *cset) {
    if (cset == NULL) {
        return;
    }

    destroy_map(cset->cmap);
    free(cset);
}

