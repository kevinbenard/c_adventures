#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>

#define COMMENT_SIZE 127

typedef struct {
    uint8_t index;
    char* comment;
    uint8_t priority;
} todo_item;

int main(int argc, char** argv) {

    FILE* mainFile = fopen("data.db", "r+");
    if (!mainFile) {
        mainFile = fopen("data.db", "w");
    }

    // Load data into structures
    todo_item todo_items[10];
    char buf[COMMENT_SIZE];
    uint8_t index = 0;
    // TODO: Replace with fread()
    while(fgets(buf, sizeof(buf), mainFile) != NULL) {
        todo_items[index].index = index;
        char* comment = malloc(sizeof(buf));
        comment = strncpy(comment, buf, sizeof(buf));

        todo_items[index].comment = comment;
        todo_items[index].priority = 0;
        index += 1;
    }

    if (feof(mainFile)) {
        printf("Finished!\n");
    }

    fclose(mainFile);

    if (argc == 2 && strncmp(argv[1], "-l", 2) == 0) {
        // Print items
        for (int i = 0; i < index; i++) {
            printf("%d. [%d]: %s\n", i, todo_items[i].priority, todo_items[i].comment);
        }
    } else if (argc >= 2) {
        // Append todo to files + array
        int start = 0;
        char line[255]; // TODO: Do something better than 255
        for (int i = 1; i < argc; i++) {
            int len = strlen(argv[i]);
            sprintf(&line[start], "%s%s", argv[i], " ");
            start += len + 1;
        }
        printf("Line: %s\n", line);
        printf("Size: %d\n", argc);

        mainFile = fopen("data.db", "a+");
        if (!mainFile) {
            printf("Error opening data.db file!\n");
            return 1;
        }

        fprintf(mainFile, "%s\n", line);

        fclose(mainFile);

    } else {
        // Catch all
        printf("In else...\n");
    }

    return 0;
}
