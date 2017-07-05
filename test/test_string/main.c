#include "c_utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

int main(int argc, char **argv) {
    // create content
    const char* value = "测试2343;242;水电费wWWWWEWFFWJ";
    char content[100];
    strcpy(content, value);
    printf("%s\n", content);

    // string split
    CList *list = string_split(content, "3;");
    
    // print info
    for (int i = 0; i < list_size(list); i++) {
        char *word = (char*)list_get(list, i);
        printf("%s\n", word);
    }

    // free string split
    free_string_split(list);

    // tolower
    string_tolower(content);
    printf("%s\n", content);
    return 0;
}
