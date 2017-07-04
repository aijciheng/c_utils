#ifndef C_MAP_H_
#define C_MAP_H_

typedef struct CMapNode {
    char *key;
    void *value;
    struct CMapNode *next;
} CMapNode;

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
} CMap;

/* 初始化map */
CMap* create_default_map();

/* 初始化map, capaticy=num */
CMap* create_map(int num);

/** 存放数据 key:value
 *   key: \0结尾
 */
void map_put(CMap *cmap, char *key, void *value);

/* 获取value数据 */
void* map_get(CMap *cmap, char *key);

/* 删除key数据 */
void map_remove(CMap *cmap, char *key);

/* 获取当前map已经使用的大小 */
int map_size(CMap *cmap);

/* 是否包含key值 1:包含 0:不包含 */
int map_contain(CMap *cmap, char *key);

void destroy_map(CMap *cmap);
#endif
