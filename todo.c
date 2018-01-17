#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include <ctype.h>

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
        todo_items[index].index = index + 1;
        char* comment = malloc(sizeof(buf));
        comment = strncpy(comment, buf+4, sizeof(buf));
        todo_items[index].comment = comment;

        char* pri = malloc(4 * sizeof(buf[0]));
        pri = strncpy(pri, buf+1, 1);
        todo_items[index].priority = atoi(pri);
        index += 1;
    }

    if (feof(mainFile)) {
        // printf("Finished!\n");
    }

    fclose(mainFile);

    if (argc == 2 && strncmp(argv[1], "-l", 2) == 0) {
        // Print items
        for (int i = 0; i < index; i++) {
            printf("%d. [%d]: %s",
                    todo_items[i].index, 
                    todo_items[i].priority, 
                    todo_items[i].comment);
        }
    } else if (argc >= 2) {
        // Append todo to files + array
        int start = 0;
        char line[255]; // TODO: Do something better than 255
        int priority = 0;
        if (isdigit(argv[1][0])) {
            priority = atoi(argv[1]);
            argv++;
            argc--;
        }

        sprintf(&line[start], "[%d] ", priority); 
        start += 4;
        // TODO: Make this support double-digit priorities
        // TODO: Only shift argv if there was a priority specified
        for (int i = 1; i < argc; i++) {
            int len = strlen(argv[i]);
            sprintf(&line[start], "%s%s", argv[i], " ");
            start += len + 1;
        }
        printf("Line: %s\n", line);
        // printf("Size: %d\n", argc);

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
