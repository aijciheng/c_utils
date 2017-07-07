#ifndef C_MAP_H_
#define C_MAP_H_

#include <stdio.h>

#include "c_iterator.h"

typedef struct CMapNode {
    void *key;
    void *value;
    struct CMapNode *next;
} CMapNode;

typedef struct CMapKeyConf {
    size_t key_type_size_t;
    long (*hash_code)(void *key);
    int (*key_equals)(void *key1, void *key2);
} CMapKeyConf;

/**
 *   c简单实现的map
 *
 */
typedef struct CMap {
    float loadfactor; //是否需要重新分配内存的因素
    int threshold; //是否决定要重新分配内存
    int capacity; //容量 
    int size; //当前已经存放的数量
    CMapNode* *buckets; //存放的桶
    CMapKeyConf *key_conf; //key的配置信息
} CMap;

/** 创建默认map
 *  key:value->(char*:void*)
 */
CMap* create_default_map();

/**
 * 仅当key为除char*和struct类型之外的基本数据类型使用
 * 如:char,short,int,long,float等
 * key_type_size_t:基本数据类型的size_t,如int,则sizeof(int)
 */
CMap* create_map(size_t key_type_size_t);

/**
 * 当key为struct类型则应该使用该函数创建map
 * 理论上，该函数适用于所有类型的key,如数组指针
 * key_type_size_t:key类型的size_t
 * 如:
 * struct Key{int a;short b;};
 * sizeof(Key)
 * hash_code:函数,将key值转换为long值
 * 如:
 * long hash_code(void *key) {
 *  Key *k = (Key*)key;
 *  return (k->a << 32) | k->b;
 * }
 * key_equals:函数,判断两个key值是否相等,1:表示相等,0:表示不相等
 * 如:
 * int key_equals(void *key1, void *key2) {
 *  Key *k1 = (Key*)key1;
 *  Key *k2 = (Key*)key2;
 *  return k1->a == k2->a && k1->b == k2->b;
 * }
 */
CMap* create_map_with_struct(size_t key_type_size_t,
                             long (*hash_code)(void *key),
                             int (*key_equals)(void *key1, void *key2));

/** 存放数据 key:value
 *   key: \0结尾
 */
void map_put(CMap *cmap, void *key, void *value);

/* 获取value数据 */
void* map_get(CMap *cmap, void *key);

/* 删除key数据 */
void map_remove(CMap *cmap, void *key);

/* 获取当前map已经使用的大小 */
int map_size(CMap *cmap);

/* 是否包含key值 1:包含 0:不包含 */
int map_contain(CMap *cmap, void *key);

/* 销毁map */
void destroy_map(CMap *cmap);

/* map迭代器 */
CIterator* map_iterator(CMap *cmap);

/* 迭代器当前状态获取key */
void* map_iterator_key(CIterator *iterator);

/* 迭代器当前状态获取value */
void* map_iterator_value(CIterator *iterator);

/* 获取key */
void* mapnode_key(CMapNode *node);

/* 获取value */
void* mapnode_value(CMapNode *node);

#define map_foreach(map, key, value) \
    for(Auto_CIterator it = map_iterator(map); \
        iterator_next(it) != NULL && \
        ((key = map_iterator_key(it)) && (value = map_iterator_value(it)));)
#endif
