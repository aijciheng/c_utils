#ifndef C_STRING_H_
#define C_STRING_H_

#include "c_utils.h"

/* 按照split字符串来切割line */
CList* string_split(char *line, char *split);

/* 释放string split的资源 */
void free_string_split(CList *list);

/* 转换为小写字符串 */
char* string_tolower(char *line);

#endif
