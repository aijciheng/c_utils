#include "utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define COUNT 100000
 
int main(int argc, char **argv) {
    CMap *map = create_default_map();
    char key[100];
    long start_time = get_current_time();
    char **contain_values = (char**)malloc(sizeof(char*) * COUNT);
    for (int i = 0; i < COUNT; i++) {
        char *value = (char*)malloc(sizeof(char) * 100);
        contain_values[i] = value;
        sprintf(key, "key%d", i);
        sprintf(value, "value:%d\n", i);
        map_put(map, key, value);
//        printf("%s->%s", key, (char*)map_get(map, key));
    }
    long end_time = get_current_time();
    printf("cost time : %ldms.\n", end_time - start_time);
    assert(COUNT == map->size);
    printf("size : %d\n", map->size);
    printf("capacity : %d\n", map->capacity);
    char *temp_value = (char*)map_get(map, "key567");
    assert(strcmp(temp_value, "value:567\n") == 0);
    printf("key567:%s", temp_value);

    map_put(map, "key567", "change567");
    temp_value = (char*)map_get(map, "key567");
    assert(strcmp(temp_value, "change567") == 0);
    printf("key567 change value : %s\n", temp_value);

    // test remove
    map_remove(map, "key567");
    temp_value = (char*)map_get(map, "key567");
    assert(temp_value == NULL);
    printf("key567 remove value : %s\n", temp_value);
    
    // test contain
    assert(map_contain(map, "key0") == 1);
    assert(map_contain(map, "key567") == 0);

    // test iterator
    MapIterator iterator;
    map_iterator(map, &iterator);
    int count = 0;
    for (CMapNode *node = map_next(&iterator); node != NULL; node = map_next(&iterator)) {
        count++;
    }
    assert(count == COUNT - 1);    
    printf("count : %d\n", count);

    // test foreach
    char *tkey;
    void *tvalue;
    count = 0;
    map_foreach(map, tkey, tvalue) {
       count++; 
    }
    assert(count == COUNT - 1);
    printf("count : %d\n", count);


    start_time = get_current_time();
    long temp_start_time, temp_end_time, cost_time = 0;
    for (int i = 0; i < COUNT; i++) {
        sprintf(key, "key%d", i);
        char *value = (char*)map_get(map, key);
    }
    end_time = get_current_time();
    cost_time = end_time - start_time;
    printf("total cost : %ldms, avg : %fms, qps : %f\n", cost_time, 
            cost_time * 1.0f / COUNT, COUNT * 1.0f / (cost_time * 1.0f / 1000 ));
    destroy_map(map);

    for (int i = 0; i < COUNT; i++) {
        free(contain_values[i]);
    }
    free(contain_values);

    return 0;
}
