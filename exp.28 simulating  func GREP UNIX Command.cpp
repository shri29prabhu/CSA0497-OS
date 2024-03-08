#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LINE_LENGTH 1024
void grepFile(const char *filename, const char *pattern) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    char line[MAX_LINE_LENGTH];
    int line_number = 0;
    printf("Lines matching '%s' in file '%s':\n", pattern, filename);
    while (fgets(line, sizeof(line), file) != NULL) {
        line_number++;
        if (strstr(line, pattern) != NULL) {
            printf("%d: %s", line_number, line);
        }
    }
    fclose(file);
}
int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <filename> <pattern>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    char *filename = argv[1];
    char *pattern = argv[2];
    grepFile(filename, pattern);
    return 0;
}

