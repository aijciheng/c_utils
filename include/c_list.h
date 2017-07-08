#ifndef C_LIST_H_
#define C_LIST_H_

/**
 *c list简单实现
 *
 */
typedef struct CList {
    void **array;
    int size;
    int capacity;
} CList;

CList* create_default_list();
void list_add(CList *clist, void *value);
void* list_get(CList *clist, int index);
int list_size(CList *clist);
void list_remove(CList *clist, int index);

/* 1:大于,0:等于,-1:小于 升序*/
void list_sort(CList *clist, int (*compare)(void *value1, void *value2));
void destroy_list(CList *clist);

#endif
