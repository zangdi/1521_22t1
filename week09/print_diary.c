#include <stdio.h>
#include <stdlib.h>

#define PATH_LEN 256

int main(void) {
    char *home = getenv("HOME");
    char path[PATH_LEN];
    snprintf(path, PATH_LEN, "%s/.diary", home);

    FILE *file = fopen(path, "r");
    if (file == NULL) {
        perror(path);
        return 1;
    }

    int byte;
    while ((byte = fgetc(file)) != EOF) {
        putchar(byte);
    }

    fclose(file);
    return 0;
}
