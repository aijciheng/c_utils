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

CSet* create_set(size_t value_type_size_t) {
    CSet *cset = (CSet*)malloc(sizeof(CSet));
    if (cset != NULL) {
        cset->cmap = create_map(value_type_size_t);
    }
    return cset;
}

CSet* create_set_with_struct(size_t value_type_size_t,
                             long (*hash_code)(void *value),
                             int (*value_equals)(void *value1, void *value2)) {
    CSet *cset = (CSet*)malloc(sizeof(CSet));
    if (cset != NULL) {
        cset->cmap = create_map_with_struct(value_type_size_t, hash_code, value_equals);
    }
    return cset;
}

void set_add(CSet *cset, void *value) {
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

int set_contain(CSet *cset, void *value) {
    if (cset == NULL || value == NULL) {
        return 0;
    }
    
    return map_contain(cset->cmap, value);
}

CIterator* set_iterator(CSet *cset) {
    if (cset == NULL) {
        return NULL;
    }
    
    return map_iterator(cset->cmap);
}

void* set_iterator_value(CIterator *iterator) {
    if (iterator == NULL) {
        return NULL;
    }
    
    return map_iterator_value(iterator);
}

void* setnode_value(CSetNode *node) {
    return mapnode_value(node);
}

void destroy_set(CSet *cset) {
    if (cset == NULL) {
        return;
    }

    destroy_map(cset->cmap);
    free(cset);
}

