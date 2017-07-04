#include "c_list.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEFAULT_CAPACITY 10

static void ensure_list(CList *clist, int min_capacity);
static void grow(CList *clist, int min_capacity);

CList* create_default_list() {
    CList* c_list = (CList*)malloc(sizeof(CList));
    if (c_list != NULL) {
        c_list->array = (void**)malloc(sizeof(void*) * DEFAULT_CAPACITY);
        c_list->size = 0;
        c_list->capacity = DEFAULT_CAPACITY;
    }
    return c_list;
}


void list_add(CList *clist, void *value) {
    ensure_list(clist, clist->size + 1);

    clist->array[clist->size++] = value;
}

void* list_get(CList *clist, int index) {
    if (index >= clist->size || index < 0) {
        return NULL;
    }

    return clist->array[index];
}

int list_size(CList *clist) {
    return clist->size;
}

void list_remove(CList *clist, int index) {
    if (index >= clist->size || index < 0) {
        return;
    }

    for (int i = index; i < clist->size - 1; i++) {
        clist->array[i] = clist->array[i + 1];
    } 
    clist->array[clist->size - 1] = NULL;
    clist->size--;
}

void destroy_list(CList *clist) {
    if (clist != NULL) {
        free(clist->array);
        free(clist);
    }
}

static void ensure_list(CList *clist, int min_capacity) {
    if (min_capacity - clist->capacity > 0) {
        grow(clist, min_capacity);
    }
}

static void grow(CList *clist, int min_capacity) {
    int new_capacity = clist->capacity + (clist->capacity >> 1);
    if (new_capacity < min_capacity) {
        new_capacity = min_capacity;
    }
    void **new_array = (void**)malloc(sizeof(void*) * new_capacity);
    if (new_array != NULL) {
        memcpy(new_array, clist->array, sizeof(void*) * clist->capacity);
    }
    void **old_array = clist->array;
    clist->array = new_array;
    clist->capacity = new_capacity;

    free(old_array);
}


