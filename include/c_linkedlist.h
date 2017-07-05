#ifndef C_LINKEDLIST_H_
#define C_LINKEDLIST_H_

typedef struct LinkedNode {
    void *value;
    struct LinkedNode *pre;
    struct LinkedNode *next;
} LinkedNode;

/**
 * LinkedList双链表实现
 * 简单支持queue和stack操作
 */
typedef struct LinkedList {
    int size;
    LinkedNode *root;
    LinkedNode *end;
} LinkedList;

/* 创建默认linkedlist */
LinkedList* create_default_linkedlist();

/* 添加value到开头 */
void linkedlist_add_first(LinkedList *linkedlist, void *value);

/* 获取开头值 */
void* linkedlist_first(LinkedList *linkedlist);

/* 获取开头值并删除 */
void* linkedlist_remove_first(LinkedList *linkedlist);

/* 添加value到尾部 */
void linkedlist_add_last(LinkedList *linkedlist, void *value);

/* 获取尾部值 */
void* linkedlist_last(LinkedList *linkedlist);

/* 获取尾部值并删除 */
void* linkedlist_remove_last(LinkedList *linkedlist);

/* 获取linkedlist size */
int linkedlist_size(LinkedList *linkedlist);

/* 销毁linkedlist */
void destroy_linkedlist(LinkedList *linkedlist);

#endif
