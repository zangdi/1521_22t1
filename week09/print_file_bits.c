#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void process_file(char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror(filename);
        exit(1);
    }

    int32_t num;
    while (fscanf("%d", &num)) {
        num = num & 0xFF;
        if (num & (1 << 7)) {
            num = num | 0xFFFFFF00;
        }

        printf("%d\n", num);
    }

    fclose(file);
}


int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <filenames>\n", argv[0]);
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        process_file(argv[i]);
    }

    return 0;
}
