#include "c_utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define N 10000

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
    return 0;
}
