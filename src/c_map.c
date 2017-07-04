#include "c_map.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEFAULT_CAPATICY 256
#define DEFAULT_LOADFACTOR 0.75

static void put_entry(CMap *cmap, int i, char *key, void *value);
static void add_entry(CMap *cmap, int i, char *key, void *value);
static void resize(CMap *cmap, int new_capacity);
static int index_for(char *key, int len);
static int contain_key(CMap *cmap, char *key);

CMap* create_map(int num) {
    if (num <= 0) {
        num = DEFAULT_CAPATICY;
    } 
    CMap *cmap = (CMap*)malloc(sizeof(CMap));
    if (cmap != NULL) {
        cmap->buckets = (CMapNode**)malloc(sizeof(CMapNode*) * num);
        if (cmap->buckets != NULL) {
            memset(cmap->buckets, 0, sizeof(CMapNode*) * num);
            cmap->capacity = num;
            cmap->size = 0;
            cmap->loadfactor = DEFAULT_LOADFACTOR;
            cmap->threshold = cmap->capacity * cmap->loadfactor;
            return cmap;
        } else {
            free(cmap);
        }
    }
    return NULL;
}

CMap* create_default_map() {
    return create_map(DEFAULT_CAPATICY);
}

void map_put(CMap *cmap, char *key, void *value) {
    int i  = index_for(key, cmap->capacity);
    CMapNode *node = cmap->buckets[i];
    /* 检测是否已经存在了 */
    while (node != NULL) {
        if (strcmp(node->key, key) == 0) {
            /* 已经找到 */
            node->value = value;
            return;
        }
        node = node->next;
    }

    put_entry(cmap, i, key, value);
}

void* map_get(CMap *cmap, char *key) {
    int i = index_for(key, cmap->capacity);
    CMapNode *node = cmap->buckets[i];
    while (node != NULL) {
        if (strcmp(node->key, key) == 0) {
            return node->value;
        }
        node = node->next;
    }
    return NULL;
}

void map_remove(CMap *cmap, char *key) {
    int i = index_for(key, cmap->capacity);
    CMapNode *node = cmap->buckets[i];
    CMapNode *pre_node = NULL;
    while (node != NULL) {
        if (strcmp(node->key, key) == 0) {
            if (pre_node == NULL) {
                cmap->buckets[i] = node->next;
            } else {
                pre_node->next = node->next;
            }
            /* 释放内存 */
            if (node->key != NULL) {
                free(node->key);
            }
            free(node);
            cmap->size--;
            return;
        }
        node = node->next;
        pre_node = node;
    }
}

int map_size(CMap *cmap) {
    return cmap->size;
}

int map_contain(CMap *cmap, char *key) {
    if (cmap == NULL || key == NULL) {
        return 0;
    } 

    return contain_key(cmap, key);
}

void destroy_map(CMap *cmap) {
    if (cmap != NULL) {
        for (int i = 0; i < cmap->capacity; i++) {
            CMapNode *node = cmap->buckets[i];
            while (node != NULL) {
                CMapNode *next = node->next;
                if (node->key != NULL) {
                    free(node->key);
                }
                free(node);
                node = next;
            }
        }
        free(cmap->buckets);
        free(cmap);
    }
}

static void put_entry(CMap *cmap, int i, char *key, void *value) {
    if (cmap->size >= cmap->threshold) {
        resize(cmap, cmap->capacity * 2);
        i = index_for(key, cmap->capacity);
    } 
   
    add_entry(cmap, i, key, value);
}

static void add_entry(CMap *cmap, int i, char *key, void *value) {
    CMapNode *new_node = (CMapNode*)malloc(sizeof(CMapNode));
    char *new_key = NULL;
    if (key != NULL) {
        new_key = (char*)malloc(sizeof(char) * (strlen(key) + 1));
        strcpy(new_key, key);
    }
    new_node->key = new_key;
    new_node->value = value;
    new_node->next = cmap->buckets[i];
    cmap->buckets[i] = new_node;

    cmap->size++;
}

static void resize(CMap *cmap, int new_capacity) {
    CMapNode **new_buckets = (CMapNode**)malloc(sizeof(CMapNode*) * new_capacity);     
    if (new_buckets != NULL) {
        memset(new_buckets, 0, sizeof(CMapNode*) * new_capacity);
        for (int i = 0; i < cmap->capacity; i++) {
            if (cmap->buckets[i] != NULL) {
                /* 表明有数据 */
                CMapNode *node = cmap->buckets[i];
                while (node != NULL) {
                    CMapNode *next = node->next;
                    int newi = index_for(node->key, new_capacity);
                    node->next = new_buckets[newi];
                    new_buckets[newi] = node;
                    node = next;
                }
            }
        }
        CMapNode **old_buckets = cmap->buckets;
        cmap->buckets = new_buckets;
        cmap->capacity = new_capacity;
        cmap->threshold = new_capacity * cmap->loadfactor;

        /* 释放旧资源 */
        free(old_buckets);
    }
}

static long hash(char *key) {
    int len = strlen(key); 
     
    long h = 0;
    for (int i = 0; i < len; i++) {
        h =  h * 31 + (unsigned char)key[i];
    }

    return h;
}

static int index_for(char *key, int len) {
    return key == NULL ? 0 : hash(key) & (len - 1); // len max be pow of 2
}

static int contain_key(CMap *cmap, char *key) {
    int i = index_for(key, cmap->capacity);
    CMapNode *node = cmap->buckets[i];
    while (node != NULL) {
        if (strcmp(node->key, key) == 0) {
            return 1;
        }
        node = node->next;
    }
    return 0;
}
