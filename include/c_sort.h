#ifndef C_SORT_H_
#define C_SORT_H_

/** 选择排序 升序
 *  compare:比较函数,1:大于,0:等于,-1:小于
 *  values区值范围[start, end)
 */
void select_sort(int (*compare)(void *value1, void *value2),
                 void **values, int start, int end);

/** 快排 升序
 *  compare:比较函数,1:大于,0:等于,-1:小于
 *  values区值范围[start, end)
 */
void quick_sort(int (*compare)(void *value1, void *value2), 
                void **values, int start, int end);

#endif
