#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include <ctype.h>

#include "todo.h"

int main(int argc, char** argv) {

    todo_item* todo_items = todo_init("data.db");

    if (argc == 2 && strncmp(argv[1], "-l", 2) == 0) {
        int count = todo_size(todo_items);
        for (int i = 0; i < count; i++) {
            printf("%d. [%d]: %s",
                    todo_items[i].index, 
                    todo_items[i].priority, 
                    todo_items[i].comment);
        }
    } else if (argc >= 2) {
        todo_item* new_item = todo_create_item(argc, argv);

        printf("P: %d, I: %d, C: %s\n", new_item->priority, new_item->index, new_item->comment);
        todo_add_item(todo_items, new_item);

    } else {
        // Catch all
        printf("In else...\n");
    }

    return 0;
}
