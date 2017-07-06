#include "c_utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

void test_string_set();
void test_int_set();
void test_struct_set();
void test_char_array_set();

typedef struct Value {
    int int_value;
    short short_value;
} Value;

long hash_code(void *value) {
    Value *v = (Value*)value;
    return (long)(v->int_value) << 32 | v->short_value;
}

int value_equals(void *value1, void *value2) {
    Value  *v1 = (Value*)value1;
    Value *v2 = (Value*)value2;

    return v1->int_value == v2->int_value &&
            v1->short_value == v2->short_value;
}

int main(int argc, char **argv) {
    // test string set
    test_string_set();

    // test int set
    test_int_set();

    // test struct set
    test_struct_set();

    // test char array set
    test_char_array_set();
    return 0;
}

void test_string_set() {
    // create set
    CSet *cset = create_default_set();

    // add
    set_add(cset, "test1");
    set_add(cset, "test1");
    set_add(cset, "test2");
    set_add(cset, "test3");

    // size
    int size = set_size(cset);
    printf("string set size : %d\n", size);

    // contain
    assert(set_contain(cset, "test1") == 1);
    assert(set_contain(cset, "test0") == 0);
    printf("string set contain ok.\n");

    // iterator
    CSetIterator it;
    set_iterator(cset, &it);
    int count = 0;
    for (CSetNode *node = set_next(&it); node != NULL; node = set_next(&it)) {
        count++;
    }
    assert(count == 3);
    printf("string set iterator ok.\n");

    // foreach
    char *value;
    count = 0;
    set_foreach(cset, it, value) {
        count++;
    }
    assert(count == 3);
    printf("string set foreach ok.\n");

    // destroy set
    destroy_set(cset);
    printf("string set is ok.\n");
}

void test_int_set() {
    // create set
    CSet *cset = create_set(sizeof(int));

    // add
    int num1 = 1;
    int num2 = 2;
    int num3 = 3;
    int num4 = 4;
    set_add(cset, &num1);
    set_add(cset, &num2);
    set_add(cset, &num3);
    set_add(cset, &num3);

    // size
    int size = set_size(cset);
    printf("int set size : %d\n", size);

    // contain
    assert(set_contain(cset, &num1) == 1);
    assert(set_contain(cset, &num4) == 0);
    printf("int set contain ok.\n");

    // iterator
    CSetIterator it;
    set_iterator(cset, &it);
    int count = 0;
    for (CSetNode *node = set_next(&it); node != NULL; node = set_next(&it)) {
        count++;
    }
    assert(count == 3);
    printf("int set iterator ok.\n");

    // foreach
    char *value;
    count = 0;
    set_foreach(cset, it, value) {
        count++;
    }
    assert(count == 3);
    printf("int set foreach ok.\n");

    // destroy set
    destroy_set(cset);
    printf("int set is ok.\n");
}

void test_struct_set() {
    // create set
    CSet *cset = create_set(sizeof(Value));

    // add
    Value num1 = {1, 1};
    Value num2 = {2, 2};
    Value num3 = {3, 3};
    Value num4 = {4, 4};
    set_add(cset, &num1);
    set_add(cset, &num2);
    set_add(cset, &num3);
    set_add(cset, &num3);

    // size
    int size = set_size(cset);
    printf("struct set size : %d\n", size);

    // contain
    assert(set_contain(cset, &num1) == 1);
    assert(set_contain(cset, &num4) == 0);
    printf("struct set contain ok.\n");

    // iterator
    CSetIterator it;
    set_iterator(cset, &it);
    int count = 0;
    for (CSetNode *node = set_next(&it); node != NULL; node = set_next(&it)) {
        count++;
    }
    assert(count == 3);
    printf("struct set iterator ok.\n");

    // foreach
    char *value;
    count = 0;
    set_foreach(cset, it, value) {
        count++;
    }
    assert(count == 3);
    printf("struct set foreach ok.\n");

    // destroy set
    destroy_set(cset);
    printf("struct set is ok.\n");
}

long char_array_hash_code(void *value) {
    long h = 0;
    char *v = *((char**)value);
    for (int i = 0; i < strlen(v); i++) {
        h =  h * 31 + ((unsigned char*)v)[i];
    }

    return h;
}

int char_array_value_equals(void *value1, void *value2) {
    char *v1 = *((char**)value1);
    char *v2 = *((char**)value2);
    return strcmp(v1, v2) == 0;
}

void test_char_array_set() {
    // create set
    CSet *cset = create_set_with_struct(sizeof(char*), char_array_hash_code, char_array_value_equals);

    // add
    char *value1 = "test1";
    char *value2 = "test2";
    char *value3 = "test3";
    char *value4 = "test4";
    set_add(cset, &value1);
    set_add(cset, &value1);
    set_add(cset, &value2);
    set_add(cset, &value3);

    // size
    int size = set_size(cset);
    printf("char array set size : %d\n", size);

    // contain
    assert(set_contain(cset, &value1) == 1);
    assert(set_contain(cset, &value4) == 0);
    printf("char array set contain ok.\n");

    // iterator
    CSetIterator it;
    set_iterator(cset, &it);
    int count = 0;
    for (CSetNode *node = set_next(&it); node != NULL; node = set_next(&it)) {
        count++;
    }
    assert(count == 3);
    printf("char array set iterator ok.\n");

    // foreach
    void *value;
    count = 0;
    set_foreach(cset, it, value) {
        count++;
    }
    assert(count == 3);
    printf("char array set foreach ok.\n");

    // destroy set
    destroy_set(cset);
    printf("char array set is ok.\n");
}
