#ifndef C_LINKEDLIST_H_
#define C_LINKEDLIST_H_

typedef struct CLinkedNode {
    void *value;
    struct CLinkedNode *pre;
    struct CLinkedNode *next;
} CLinkedNode;

/**
 * CLinkedList双链表实现
 * 简单支持queue和stack操作
 */
typedef struct CLinkedList {
    int size;
    CLinkedNode *root;
    CLinkedNode *end;
} CLinkedList;

/* 创建默认linkedlist */
CLinkedList* create_default_linkedlist();

/* 添加value到开头 */
void linkedlist_add_first(CLinkedList *linkedlist, void *value);

/* 获取开头值 */
void* linkedlist_first(CLinkedList *linkedlist);

/* 获取开头值并删除 */
void* linkedlist_remove_first(CLinkedList *linkedlist);

/* 添加value到尾部 */
void linkedlist_add_last(CLinkedList *linkedlist, void *value);

/* 获取尾部值 */
void* linkedlist_last(CLinkedList *linkedlist);

/* 获取尾部值并删除 */
void* linkedlist_remove_last(CLinkedList *linkedlist);

/* 获取linkedlist size */
int linkedlist_size(CLinkedList *linkedlist);

/* 销毁linkedlist */
void destroy_linkedlist(CLinkedList *linkedlist);

#endif
