
#ifndef __TODO_H__
#define __TODO_H__

typedef struct {
    uint8_t index;
    char* comment;
    uint8_t priority;
} todo_item;

todo_item* todo_init(char* databaseFile);

int todo_size(todo_item* items);

void todo_add_item(todo_item* items, todo_item* item);

todo_item* todo_create_item(int words, char** line);

#endif
