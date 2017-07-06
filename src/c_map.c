#include "c_map.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEFAULT_CAPACITY 256
#define DEFAULT_LOADFACTOR 0.75

static void put_entry(CMap *cmap, int i, void *key, void *value);
static void add_entry(CMap *cmap, int i, void *key, void *value);
static void resize(CMap *cmap, int new_capacity);
static int index_for(CMapKeyConf *conf, void *key, int len);
static int contain_key(CMap *cmap, void *key);
static int key_equals(CMapKeyConf *conf, void *key1, void *key2, int len);
static size_t key_len(CMap *cmap, void *key);

static CMap* create_map_with_params(int num, size_t key_type_size_t,
                                    long (*hash_code)(void*key),
                                    int (*key_equals)(void *key1, void *key2)) {
    if (num <= 0) {
        num = DEFAULT_CAPACITY;
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
            
            /* create key conf */
            CMapKeyConf *conf = (CMapKeyConf*)malloc(sizeof(CMapKeyConf)); 
            if (conf != NULL) {
                conf->hash_code = hash_code;
                conf->key_equals = key_equals;
                conf->key_type_size_t = key_type_size_t;
            } else {
                destroy_map(cmap);
                return NULL;
            }
            cmap->key_conf = conf;
            return cmap;
        } 
        destroy_map(cmap);
    }
    return NULL;
}

CMap* create_default_map() {
    return create_map_with_params(DEFAULT_CAPACITY, 0, NULL, NULL);
}

CMap* create_map(size_t key_type_size_t) {
    return create_map_with_params(DEFAULT_CAPACITY, key_type_size_t, NULL, NULL);
}

CMap* create_map_with_struct(size_t key_type_size_t,
                             long (*hash_code)(void *key),
                             int (*key_equals)(void *key1, void *key2)) {
    return create_map_with_params(DEFAULT_CAPACITY, key_type_size_t, hash_code, key_equals);
}

void map_put(CMap *cmap, void *key, void *value) {
    int i  = index_for(cmap->key_conf, key, cmap->capacity);
    CMapNode *node = cmap->buckets[i];
    /* 检测是否已经存在了 */
    while (node != NULL) {
        if (key_equals(cmap->key_conf, node->key, key, key_len(cmap, node->key))) {
            /* 已经找到 */
            node->value = value;
            return;
        }
        node = node->next;
    }

    put_entry(cmap, i, key, value);
}

void* map_get(CMap *cmap, void *key) {
    int i = index_for(cmap->key_conf, key, cmap->capacity);
    CMapNode *node = cmap->buckets[i];
    while (node != NULL) {
        if (key_equals(cmap->key_conf, node->key, key, key_len(cmap, node->key))) {
            return node->value;
        }
        node = node->next;
    }
    return NULL;
}

void map_remove(CMap *cmap, void *key) {
    int i = index_for(cmap->key_conf, key, cmap->capacity);
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
        pre_node = node;
        node = node->next;
    }
}

int map_size(CMap *cmap) {
    return cmap->size;
}

int map_contain(CMap *cmap, void *key) {
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
        if (cmap->buckets != NULL) {
            free(cmap->buckets);
        }
        if (cmap->key_conf != NULL) {
            free(cmap->key_conf);
        }
        free(cmap);
    }
}

void map_iterator(CMap *cmap, CMapIterator *iterator) {
    if (cmap == NULL || iterator == NULL) {
        return;
    }
    iterator->index = 0;
    iterator->node = NULL;
    iterator->cmap = cmap;
}

CMapNode *map_next(CMapIterator *iterator) {
    if (iterator == NULL) {
        return NULL;
    }
    if (iterator->cmap == NULL) {
        return NULL;
    }
    for (int i = iterator->index; i < iterator->cmap->capacity; i++) {
        CMapNode *node = iterator->node;
        if (node != NULL && node->next != NULL) {
            iterator->node = node->next;
            return node->next;
        } else {
            while (i < iterator->cmap->capacity && (node = iterator->cmap->buckets[i++]) == NULL);
            iterator->node = node;
            iterator->index = i;
            return node;
        }
    }

    return NULL;
}

void* mapnode_key(CMapNode *node) {
    if (node == NULL) {
        return NULL;
    }

    return node->key;
}

void* mapnode_value(CMapNode *node) {
    if (node == NULL) {
        return NULL;
    }

    return node->value;
}

static void put_entry(CMap *cmap, int i, void *key, void *value) {
    if (cmap->size >= cmap->threshold) {
        resize(cmap, cmap->capacity * 2);
        i = index_for(cmap->key_conf, key, cmap->capacity);
    } 
   
    add_entry(cmap, i, key, value);
}

static void add_entry(CMap *cmap, int i, void *key, void *value) {
    CMapNode *new_node = (CMapNode*)malloc(sizeof(CMapNode));
    char *new_key = NULL;
    if (key != NULL) {
        size_t new_key_size_t = sizeof(char) * key_len(cmap, key);
        new_key = (char*)malloc(new_key_size_t);
        memcpy(new_key, key, new_key_size_t);
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
                    int newi = index_for(cmap->key_conf, node->key, new_capacity);
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

static size_t key_len(CMap *cmap, void *key) {
    if (cmap->key_conf == NULL || cmap->key_conf->key_type_size_t <= 0) {
        /* 默认为char* */
        return strlen(key) + 1;
    }

    /* 其他类型:int, struct eg. */
    return cmap->key_conf->key_type_size_t;
}

/* 1:相同,0不相同 */
static int key_equals(CMapKeyConf *conf, void *key1, void *key2, int len) {
    if (key1 == NULL && key2 == NULL) {
        return 1;
    }
    if (key1 == NULL || key2 == NULL) {
        return 0;
    }

    if (conf != NULL && conf->key_equals != NULL) {
        return conf->key_equals(key1, key2);
    }

    for (int i = 0; i < len; i++) {
        if (((unsigned char*)key1)[i] != ((unsigned char*)key2)[i]) {
            return 0;
        }
    }
    return 1;
}

static long hash(void *key, size_t key_len) {
    long h = 0;
    for (int i = 0; i < key_len; i++) {
        h =  h * 31 + ((unsigned char*)key)[i];
    }

    return h;
}

static int index_for(CMapKeyConf *conf, void *key, int len) {
    long h = 0;
    if (conf != NULL && conf->hash_code != NULL) {
        /* struct */
        h = conf->hash_code(key);
    } else if (conf != NULL && conf->key_type_size_t > 0) {
        /* basic type */
        h = hash(key, conf->key_type_size_t);
    } else {
        /* char* */
        h = hash(key, strlen((char*)key));
    }
    return key == NULL ? 0 : h & (len - 1); // len max be pow of 2
}

static int contain_key(CMap *cmap, void *key) {
    int i = index_for(cmap->key_conf, key, cmap->capacity);
    CMapNode *node = cmap->buckets[i];
    while (node != NULL) {
        if (key_equals(cmap->key_conf, node->key, key, key_len(cmap, key))) {
            return 1;
        }
        node = node->next;
    }
    return 0;
}
