#ifndef C_SET_H_
#define C_SET_H_

#include "c_map.h"

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

/* 销毁set */
void destroy_set(CSet *cset);

#endif
