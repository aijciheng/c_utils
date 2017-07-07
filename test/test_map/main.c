#include "c_utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define COUNT 100000

void test_string_map();
void test_int_map();
void test_struct_map();
void test_char_array_map();
typedef struct Key {
    int int_value;
    short short_value;
} Key;

long hash_code(void *key) {
    Key *k = (Key*)key;
    return (long)(k->int_value) << 32 | k->short_value;
}

int key_equals(void *key1, void *key2) {
    Key *k1 = (Key*)key1;
    Key *k2 = (Key*)key2;

    return k1->int_value == k2->int_value &&
            k1->short_value == k2->short_value;
}
 
int main(int argc, char **argv) {
    // test string map
    test_string_map();

    // test int map
    test_int_map();

    // test struct map
    test_struct_map();

    // test char array map
    test_char_array_map();
    return 0;
}

void test_string_map() {
    // create map
    CMap *map = create_default_map();

    // map put
    char key[100];
    char **contain_values = (char**)malloc(sizeof(char*) * COUNT);
    for (int i = 0; i < COUNT; i++) {
        char *value = (char*)malloc(sizeof(char) * 100);
        contain_values[i] = value;
        sprintf(key, "key%d", i);
        sprintf(value, "value:%d\n", i);
        map_put(map, key, value);
    }
    
    // test map size
    assert(COUNT == map->size);
    printf("size : %d\n", map->size);
    printf("capacity : %d\n", map->capacity);

    // test map get
    char *temp_value = (char*)map_get(map, "key567");
    assert(strcmp(temp_value, "value:567\n") == 0);
    printf("key567:%s", temp_value);

    // test map change
    map_put(map, "key567", "change567");
    temp_value = (char*)map_get(map, "key567");
    assert(strcmp(temp_value, "change567") == 0);
    printf("key567 change value : %s\n", temp_value);

    // test map remove
    map_remove(map, "key567");
    temp_value = (char*)map_get(map, "key567");
    assert(temp_value == NULL);
    printf("key567 remove value : %s\n", temp_value);
    
    // test map contain
    assert(map_contain(map, "key0") == 1);
    assert(map_contain(map, "key567") == 0);

    // test map iterator
    CIterator *iterator = map_iterator(map);
    int count = 0;
    for (CMapNode *node = iterator_next(iterator); node != NULL; node = iterator_next(iterator)) {
        count++;
    }
    destroy_iterator(iterator);
    assert(count == COUNT - 1);    
    printf("count : %d\n", count);

    // test map foreach
    char *tkey;
    void *tvalue;
    count = 0;
    map_foreach(map, tkey, tvalue) {
       count++; 
    }
    assert(count == COUNT - 1);
    printf("count : %d\n", count);

    // print qps
    long start_time = get_current_time();
    long temp_start_time, temp_end_time, cost_time = 0;
    for (int i = 0; i < COUNT; i++) {
        sprintf(key, "key%d", i);
        char *value = (char*)map_get(map, key);
    }
    long end_time = get_current_time();
    cost_time = end_time - start_time;
    printf("total cost : %ldms, avg : %fms, qps : %f\n", cost_time, 
            cost_time * 1.0f / COUNT, COUNT * 1.0f / (cost_time * 1.0f / 1000 ));

    // map destroy
    destroy_map(map);

    // free
    for (int i = 0; i < COUNT; i++) {
        free(contain_values[i]);
    }
    free(contain_values);
    printf("test string map is ok.\n");
}

void test_int_map() {
    // create map
    CMap *map = create_map(sizeof(int));

    // map put
    char **contain_values = (char**)malloc(sizeof(char*) * COUNT);
    for (int i = 0; i < COUNT; i++) {
        char *value = (char*)malloc(sizeof(char) * 100);
        contain_values[i] = value;
        sprintf(value, "value:%d\n", i);
        map_put(map, &i, value);
    }

    // test map size
    int size = map_size(map);
    assert(size == COUNT);
    printf("test int map size %d is ok\n", size);

    // test map get
    int a = 3;
    char *value = (char*)map_get(map, &a);
    assert(strcmp(value, "value:3\n") == 0);
    printf("test int map get is ok\n");

    // test map change
    map_put(map, &a, "change3");
    value = (char*)map_get(map, &a);
    assert(strcmp(value, "change3") == 0);
    printf("test int map change is ok.\n");

    // test map remove
    map_remove(map, &a);
    value = (char*)map_get(map, &a);
    assert(value == NULL);
    assert(map_size(map) == (COUNT - 1));
    printf("test int map remove is ok.\n");

    // test map contain
    assert(map_contain(map, &a) == 0);
    a = 4; 
    assert(map_contain(map, &a) == 1);
    printf("test int map contain is ok.\n");

    // test map iterator
    CIterator *iterator = map_iterator(map);
    int count = 0;
    for (CMapNode *node = iterator_next(iterator); node != NULL; node = iterator_next(iterator)) {
        count++;
    }
    destroy_iterator(iterator);
    assert(count == COUNT - 1);    
    printf("test int map iterator is ok.\n");

    // test map foreach
    int *tkey;
    char *tvalue;
    count = 0;
    map_foreach(map, tkey, tvalue) {
        count++;
    }
    assert(count == COUNT - 1);
    printf("test int map foreach is ok.\n");

    // map destroy
    destroy_map(map);
    
    // free
    for (int i = 0; i < COUNT; i++) {
        free(contain_values[i]);
    }
    free(contain_values);
    printf("test int map is ok.\n");
}

void test_struct_map() {
    // create map
    CMap *map = create_map_with_struct(sizeof(Key), hash_code, key_equals);

    // map put
    char **contain_values = (char**)malloc(sizeof(char*) * COUNT);
    for (int i = 0; i < COUNT; i++) {
        char *value = (char*)malloc(sizeof(char) * 100);
        contain_values[i] = value;
        sprintf(value, "value:%d\n", i);
        Key key;
        key.int_value = i;
        key.short_value = i;
        map_put(map, &key, value);
    }

    // test map size
    int size = map_size(map);
    assert(size == COUNT);
    printf("test struct map size %d is ok\n", size);

    // test map get
    Key key;
    key.int_value = (int)3;
    key.short_value = (int)3;
    char *value = (char*)map_get(map, &key);
    assert(strcmp(value, "value:3\n") == 0);
    printf("test struct map get is ok\n");

    // test map change
    map_put(map, &key, "change3");
    value = (char*)map_get(map, &key);
    assert(strcmp(value, "change3") == 0);
    printf("test struct map change is ok.\n");

    // test map remove
    map_remove(map, &key);
    value = (char*)map_get(map, &key);
    assert(value == NULL);
    assert(map_size(map) == (COUNT - 1));
    printf("test key map remove is ok.\n");

    // test map contain
    assert(map_contain(map, &key) == 0);
    key.int_value = 4;
    key.short_value = 4;
    assert(map_contain(map, &key) == 1);
    printf("test struct map contain is ok.\n");

    // test map iterator
    CIterator *iterator = map_iterator(map);
    int count = 0;
    for (CMapNode *node = iterator_next(iterator); node != NULL; node = iterator_next(iterator)) {
        count++;
    }
    destroy_iterator(iterator);
    assert(count == COUNT - 1);    
    printf("test struct map iterator is ok.\n");

    // test map foreach
    Key *tkey;
    char *tvalue;
    count = 0;
    map_foreach(map, tkey, tvalue) {
        count++;
    }
    assert(count == COUNT - 1);
    printf("test struct map foreach is ok.\n");

    // map destroy
    destroy_map(map);
    
    // free
    for (int i = 0; i < COUNT; i++) {
        free(contain_values[i]);
    }
    free(contain_values);
    printf("test struct map is ok.\n");
}

long char_array_hash_code(void *key) {
    long h = 0;
    char *k = *((char**)key);
    for (int i = 0; i < strlen(k); i++) {
        h =  h * 31 + ((unsigned char*)k)[i];
    }

    return h;
}

int char_array_key_equals(void *key1, void *key2) {
    char *k1 = *((char**)key1);
    char *k2 = *((char**)key2);
    return strcmp(k1, k2) == 0;
}

void test_char_array_map() {
    // create map
    CMap *map = create_map_with_struct(sizeof(char*), char_array_hash_code, char_array_key_equals);

    // map put
    char **contain_keys = (char**)malloc(sizeof(char*) * COUNT);
    char **contain_values = (char**)malloc(sizeof(char*) * COUNT);
    for (int i = 0; i < COUNT; i++) {
        char *key = (char*)malloc(sizeof(char) * 100);
        char *value = (char*)malloc(sizeof(char) * 100);
        contain_keys[i] = key;
        contain_values[i] = value;
        sprintf(key, "key%d", i);
        sprintf(value, "value:%d\n", i);
        map_put(map, &key, value);
    }

    // test map size
    assert(COUNT == map->size);
    printf("test char array map size is ok.\n");

    // test map get
    char *temp_value = (char*)map_get(map, &contain_keys[567]);
    assert(strcmp(temp_value, "value:567\n") == 0);
    printf("test char array map get is ok.\n");

    // test map change
    map_put(map, &contain_keys[567], "change567");
    temp_value = (char*)map_get(map, &contain_keys[567]);
    assert(strcmp(temp_value, "change567") == 0);
    printf("test char array map change is ok.\n");

    // test map remove
    map_remove(map, &contain_keys[567]);
    temp_value = (char*)map_get(map, &contain_keys[567]);
    assert(temp_value == NULL);
    printf("test char array map remove is ok.\n");
    
    // test map contain
    assert(map_contain(map, &contain_keys[0]) == 1);
    assert(map_contain(map, &contain_keys[567]) == 0);
    printf("test char array map contain is ok.\n");

    // test map iterator
    CIterator *iterator = map_iterator(map);
    int count = 0;
    for (CMapNode *node = iterator_next(iterator); node != NULL; node = iterator_next(iterator)) {
        count++;
    }
    destroy_iterator(iterator);
    assert(count == COUNT - 1);    
    printf("test char array map iterator is ok.\n");

    // test map foreach
    char *tkey;
    void *tvalue;
    count = 0;
    map_foreach(map, tkey, tvalue) {
       count++; 
    }
    assert(count == COUNT - 1);
    printf("test char array map foreach is ok.\n");

    // map destroy
    destroy_map(map);

    // free
    for (int i = 0; i < COUNT; i++) {
        free(contain_keys[i]);
        free(contain_values[i]);
    }
    free(contain_keys);
    free(contain_values);
    printf("test char array map is ok.\n");

}
