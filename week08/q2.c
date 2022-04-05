#include <stdio.h>
#include <string.h>

/*
    dcc -o file q2.c

    ./file a b c d e

    argv = [file, a, b, c, d, e, NULL]

*/

#define MAX_LINE_LENGTH 1000

void search_in_file(FILE *file, char *filename, char *search_string) {
    char s[MAX_LINE_LENGTH] = {0};
    int lineno = 0;
    while (fgets(s, MAX_LINE_LENGTH, file) != NULL) {
        if (strstr(s, search_string)) {
            printf("%s %d: %s", filename, lineno, s);
        }

        lineno++;
    }
}


int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <search string> <optionally: files to search through>\n", argv[0]);
        return 1;
    } else if (argc == 2) {
        search_in_file(stdin, "stdin", argv[1]);
    } else {
        for (int i = 2; i < argc; i++) {
            FILE *file = fopen(argv[i], "r");
            if (file == NULL) {
                perror(argv[i]);
                return 1;
            }

            search_in_file(file, argv[i], argv[1]);
            fclose(file);
        }
    }

    return 0;
}
