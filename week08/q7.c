#include <stdio.h>

#define MAX_LINE_LENGTH 1000

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file>\n", argv[0]);
        return 1;
    }

    char line[MAX_LINE_LENGTH] = {0};
    fgets(line, MAX_LINE_LENGTH, stdin);

    FILE *file = fopen(argv[1], "w");
    if (file == NULL) {
        perror(argv[1]);
        return 1;
    }

    fputs(line, file);
    fclose(file);

    return 0;
}
