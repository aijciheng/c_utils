#ifndef C_SET_H_
#define C_SET_H_

#include "c_map.h"

typedef CMapNode CSetNode;
typedef CMapIterator CSetIterator;

/**
 * c set简单实现-map实现
 * 仅支持字符串
 */
typedef struct CSet {
    CMap *cmap;
} CSet;

/* 创建默认set */
CSet* create_default_set();

/* 添加值 */
void set_add(CSet *cset, char *value);

/* set个数 */
int set_size(CSet *cset);

/* set是否包含 1:包含 0:不包含 */
int set_contain(CSet *cset, char *value);

/* set迭代器 */
void set_iterator(CSet *cset, CSetIterator *iterator);

/* 获取下一个数据 */
CSetNode* set_next(CSetIterator *iterator);

/* 获取value */
char* setnode_value(CSetNode *node);

/* 销毁set */
void destroy_set(CSet *cset);

#define set_foreach(set, set_it, value) \
    set_iterator(set, &set_it); \
    for(CSetNode *node = set_next(&set_it); \
        node != NULL && (value = setnode_value(node)); \
        node = set_next(&set_it))
#endif
