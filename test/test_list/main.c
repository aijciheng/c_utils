#include "c_utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define N 10000

int compare(void *value1, void *value2) {
    return strcmp((char*)value1, (char*)value2);
}

int main(int argc, char **argv) {
    CList *list = create_default_list();
    char **contain_array = (char**)malloc(sizeof(char*) * N);
    for (int i = 0; i < N; i++) {
        char *value = (char*)malloc(sizeof(char) * 100);
        contain_array[i] = value;
        sprintf(value, "test%d", i);
        list_add(list, value);
    }

    // test size
    assert(list_size(list) == N);
    printf("size:%d\n", list_size(list));
    printf("capacity:%d\n", list->capacity);
    
    //test get index 3 
    char* value = list_get(list, 3);
    assert(strcmp(value, "test3") == 0);
    printf("value:%s\n", value);

    //test remove
    list_remove(list, 3);
    int new_size = N - 1;
    assert(list_size(list) == new_size);
    printf("size:%d\n", list_size(list));
    value = list_get(list, 3);
    assert(strcmp(value, "test4") == 0);
    printf("value:%s\n", value);
    value = list_get(list, N - 2);
    printf("value:%s\n", value);

    destroy_list(list);

    for (int i = 0; i < N; i++) {
        free(contain_array[i]);
    }
    free(contain_array);

    // test sort
    list = create_default_list();

    // add
    list_add(list, "1");
    list_add(list, "3434");
    list_add(list, "23");

    // print
    for (int i = 0; i < list_size(list); i++) {
        printf("%d->%s\n", i, (char*)list_get(list, i));
    }

    // sort
    list_sort(list, compare);

    // print
    assert(strcmp((char*)list_get(list, 0), "1") == 0);
    assert(strcmp((char*)list_get(list, 1), "23") == 0);
    assert(strcmp((char*)list_get(list, 2), "3434") == 0);
    for (int i = 0; i < list_size(list); i++) {
        printf("%d->%s\n", i, (char*)list_get(list, i));
    }
    
    // destroy
    destroy_list(list);
    return 0;
}
