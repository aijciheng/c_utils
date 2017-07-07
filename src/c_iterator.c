#include "c_iterator.h"

#include <stdlib.h>

CIterator* create_iterator() {
    return (CIterator*)malloc(sizeof(CIterator));
}

void destroy_auto_iterator(CIterator **iterator) {
    if (iterator == NULL) {
        return;
    }
    
    destroy_iterator(*iterator);
}

void* iterator_next(CIterator *iterator) {
    if (iterator == NULL) {
        return NULL;
    }

    return iterator->next(iterator->iterator_impl);
}

void destroy_iterator(CIterator *iterator) {
    if (iterator == NULL) {
        return;
    }

    iterator->destroy_iterator(iterator->iterator_impl);
    free(iterator);
}
