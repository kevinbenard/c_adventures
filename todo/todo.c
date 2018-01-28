#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "todo.h"

#define COMMENT_SIZE 127
#define TODO_POOL_SIZE 10

// Load data into structures
todo_item todo_items[TODO_POOL_SIZE];
int todo_count = 0;

todo_item* todo_init(char* databaseFile) {
    FILE* mainFile = fopen(databaseFile, "r+");
    if (!mainFile) {
        mainFile = fopen(databaseFile, "w");
    }

    char buf[COMMENT_SIZE];
    // TODO: Replace with fread()
    while(fgets(buf, sizeof(buf), mainFile) != NULL) {
        todo_items[todo_count].index = todo_count + 1;
        char* comment = malloc(sizeof(buf));
        comment = strncpy(comment, buf+4, sizeof(buf));
        todo_items[todo_count].comment = comment;

        char* pri = malloc(4 * sizeof(buf[0]));
        pri = strncpy(pri, buf+1, 1);
        todo_items[todo_count].priority = atoi(pri);
        todo_count += 1;
    }

    fclose(mainFile);

    return todo_items;
}

int todo_size(todo_item* items) {
    (void) items;
    return todo_count;
}

void todo_add_item(todo_item* items, todo_item* item) {
    items[todo_count] = *item;
    todo_count += 1;

    FILE* mainFile = fopen("data.db", "a+");
    if (!mainFile) {
        printf("Error opening data.db file!\n");
    }

    fprintf(mainFile, "[%d] %s\n", item->priority, item->comment);

    fclose(mainFile);
}

todo_item* todo_create_item(int words, char** line) {
    // Append todo to files + array
    int start = 0;
    char* line_buffer = malloc(255);
    int priority = 0;
    if (isdigit(line[1][0])) {
        priority = atoi(line[0]);
        line++;
        words--;
    }

    // TODO: Make this support double-digit priorities
    for (int i = 1; i < words; i++) {
        int len = strlen(line[i]);
        sprintf(&line_buffer[start], "%s%s", line[i], " ");
        start += len + 1;
    }

    todo_item* new_item = malloc(sizeof(todo_item));
    new_item->index = todo_size(todo_items) + 1; 
    new_item->priority = priority;
    new_item->comment = line_buffer;

    return new_item;
}
