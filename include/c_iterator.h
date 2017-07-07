#ifndef C_ITERATOR_H_
#define C_ITERATOR_H_

/**
 * 迭代器
 */
typedef struct CIterator {
    void *iterator_impl;
    void* (*next)(void *iterator); 
    void (*destroy_iterator)(void *iterator);
} CIterator;

CIterator* create_iterator();
void* iterator_next(CIterator *iterator);
void destroy_iterator(CIterator *iterator);
void destroy_auto_iterator(CIterator **iterator);

#define Auto_CIterator CIterator* __attribute__ ((__cleanup__(destroy_auto_iterator)))

#endif
