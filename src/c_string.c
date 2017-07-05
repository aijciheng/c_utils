#include "c_string.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

static char* create_word(char *line, int start_offset, int end_offset);

CList* string_split(char *line, char *split) {
    if (line == NULL || split == NULL) {
        return NULL;
    }

    CList *list = create_default_list();
    int len = strlen(line);
    int split_len = strlen(split);
    int i = 0, pre = 0;
    for (; i < len; i++) {
        if (line[i] == split[0] && (len - i) >= split_len) {
            int j = i + 1;
            int flag = 1;
            for (int index = 1; index < split_len; index++, j++) {
                if (line[j] != split[index]) {
                    flag = 0;
                    break;
                }
            }
            if (flag) {
                /* 找到匹配的 */
                char *new_word= create_word(line, pre, i);
                list_add(list, new_word);
                i = pre = j; 
            }
        }
    }

    if (pre < len) {
        char *new_word= create_word(line, pre, len);
        list_add(list, new_word);
    }
    
    return list;
}

void free_string_split(CList *list) {
    if (list == NULL) {
        return;
    }

    for (int i = 0; i < list_size(list); i++) {
        char *word = (char*)list_get(list, i);
        free(word);
    }
    destroy_list(list);
}

char* string_tolower(char *line) {
    if (line == NULL) {
        return NULL;
    }

    int len = strlen(line);
    for (int i = 0; i < len; i++) {
        if (line[i] >= 0 && line[i] < 128) {
            line[i] = tolower(line[i]);
        }
    }
    return line;
}

static char* create_word(char *line, int start_offset, int end_offset) {
        char *new_word = (char*)malloc(sizeof(char) * (end_offset - start_offset + 1));
        strncpy(new_word, line + start_offset, sizeof(char) * (end_offset - start_offset)); 
        new_word[end_offset - start_offset] = '\0';
        return new_word; 
}
