#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>


int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <filenames>\n", argv[0]);
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        struct stat s;
        if (!stat(argv[i], &s)) {
            perror(argv[i]);
            return 1;
        }

        mode_t file_mode = s.st_mode;
        if (file_mode & S_IWOTH) {
            file_mode = file_mode & (~S_IWOTH);
            // file_mode = file_mode ^ S_IWOTH;

            if (!chmod(argv[i], file_mode)) {
                perror(argv[i]);
                return 1;
            }

            printf("removing public write from %s\n", argv[i]);
        } else {
            printf("%s is not publically writeable\n", argv[i]);
        }
    }

    return 0;
}
