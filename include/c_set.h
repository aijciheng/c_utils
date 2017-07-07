#ifndef C_SET_H_
#define C_SET_H_

#include "c_map.h"

typedef CMapNode CSetNode;

/**
 * c set简单实现-依赖CMap实现
 */
typedef struct CSet {
    CMap *cmap;
} CSet;

/** 创建默认set
 *  value->char*
 */
CSet* create_default_set();

/**
 * 仅当value为除char*和struct类型之外的基本数据类型使用
 * 如:char,short,int,long,float等
 * value_type_size_t:基本数据类型的size_t,如int,则sizeof(int)
 */
CSet* create_set(size_t value_type_size_t);

/**
 * 当value为struct类型则应该使用该函数创建set
 * 理论上，该函数适用于所有类型的value,如数组指针
 * value_type_size_t:value类型的size_t
 * 如:
 * struct Value{int a;short b;};
 * sizeof(Value)
 * hash_code:函数,将value值转换为long值
 * 如:
 * long hash_code(void *value) {
 *  Value *v = (Value*)value;
 *  return (v->a << 32) | v->b;
 * }
 * value_equals:函数,判断两个value值是否相等,1:表示相等,0:表示不相等
 * 如:
 * int value_equals(void *value1, void *value2) {
 *  Value *v1 = (Value*)value1;
 *  Value *v2 = (Value*)value2;
 *  return v1->a == v2->a && v1->b == v2->b;
 * }
 */
CSet* create_set_with_struct(size_t value_type_size_t,
                             long (*hash_code)(void *value),
                             int (*value_equals)(void *value1, void *value2));

/* 添加值 */
void set_add(CSet *cset, void *value);

/* set个数 */
int set_size(CSet *cset);

/* set是否包含 1:包含 0:不包含 */
int set_contain(CSet *cset, void *value);

/* set迭代器 */
CIterator* set_iterator(CSet *cset);

/* 通过迭代器当前状态获取value */
void* set_iterator_value(CIterator *iterator);

/* 获取value */
void* setnode_value(CSetNode *node);

/* 销毁set */
void destroy_set(CSet *cset);

#define set_foreach(set, value) \
    for(Auto_CIterator it = set_iterator(set); \
        iterator_next(it) != NULL && (value = set_iterator_value(it));)

#endif
