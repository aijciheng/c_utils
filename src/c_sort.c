#include "c_sort.h"

#include <stdio.h>

static inline void swap(void **value1, void **value2); 
static inline void pivot(int (*compare)(void *value1, void *value2),
                         void **values, int start, int end);

void select_sort(int (*compare)(void *value1, void *value2),
                 void **values, int start, int end){
    if (values == NULL) {
        return;
    }
    for (int i = start; i < end - 1; i++) {
        int t = i;
        for (int j = i + 1; j < end; j++) {
            if (compare(values[t], values[j]) > 0) {
                t = j;
            }
        }

        if (t != i) {
            swap(&values[t], &values[i]);
        }
    }
}

void quick_sort(int (*compare)(void *value1, void *value2),
                void **values, int start, int end) {
    if (values == NULL || start >= end) {
        return; 
    } 

    if (end - start <= 3) {
        select_sort(compare, values, start, end);
        return;
    }

    /* partition */
    pivot(compare, values, start, end);  
    void *pivot = values[end - 1];
    int i = start - 1;
    for (int j = start; j < end - 1; j++) {
        if (compare(values[j], pivot) <= 0) {
            i++;
            swap(&values[i], &values[j]);
        }
    }
    swap(&values[i + 1], &values[end - 1]);

    quick_sort(compare, values, start, i + 1);
    quick_sort(compare, values, i + 2, end);

}

static inline void swap(void **value1, void **value2) {
    void *temp = *value1; 
    *value1 = *value2;
    *value2 = temp;
}

static inline void pivot(int (*compare)(void *value1, void *value2),
                         void **values, int start, int end) {
    /* values[start] < values[end - 1] < values[middle] */
    int middle = (end - 1 + start) / 2;
    if (compare(values[start], values[middle]) > 0) {
        swap(&values[start], &values[middle]);
    }
    if (compare(values[start], values[end - 1]) > 0) {
        swap(&values[start], &values[end - 1]);
    }
    if (compare(values[end - 1], values[middle]) > 0) {
        swap(&values[end - 1], &values[middle]);
    }
}
